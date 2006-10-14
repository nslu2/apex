/* drv-nand.c

   written by Marc Singer
   4 Nov 2004

   Copyright (C) 2004 Marc Singer

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA.

   -----------
   DESCRIPTION
   -----------

   NAND flash driver.

   Unlike the NOR driver, this one hasn't received the same attention
   for reducing code size.  It is probably amenable to the same
   optimizations.  However, since it already much smaller than the NOR
   driver, there isn't the same incentive to optimize.

   Status
   ------

   (1<<0) Program/erase error
   (1<<6) Ready
   (1<<7) !R/O

*/

#include <config.h>
#include <apex.h>
#include <driver.h>
#include <service.h>
#include <linux/string.h>
#include <spinner.h>

#include "mach/drv-nand.h"

#define Reset		(0xff)
#define ReadID		(0x90)
#define Status		(0x70)
#define Read1		(0x00)	/* Start address in first 256 bytes of page */
#define Read2		(0x01)	/* Start address in second 256 bytes of page */
#define Read3		(0x50)	/* Start address in last 16 bytes, (ECC?) */
#define Erase		(0x60)
#define EraseConfirm	(0xd0)
#define AutoProgram	(0x10)
#define SerialInput	(0x80)

#define Fail		(1<<0)
#define Ready		(1<<6)
#define Writable	(1<<7)

struct nand_chip {
  unsigned char device;
  unsigned long total_size;
  int erase_size;
  //  int address_size;	/* *** FIXME: Better than Boot code */
};

const static struct nand_chip chips[] = {
  { 0x75, 32*1024*1024, 16*1024 },
};

const static struct nand_chip* chip;

static void wait_on_busy (void)
{
  /* *** FIXME: need to time-out and detect absence of the device */
  while (NAND_ISBUSY)
    ;
}


/* nand_init

   probes the NAND flash device.

   Note that the status check redundantly sends the Status command
   when we are not using the CONFIG_NAND_LPD mode.  It's left in for
   now.

*/

static void nand_init (void)
{
  unsigned char manufacturer;
  unsigned char device;

  SMC_BCR6 = 0xffef;

  NAND_CS_ENABLE;

  NAND_CLE = Reset;
  wait_on_busy ();

  NAND_CLE = Status;
  wait_on_busy ();
  if ((NAND_DATA & Ready) == 0)
    goto exit;

  NAND_CLE = ReadID;
  NAND_ALE = 0;

  manufacturer = NAND_DATA;
  device       = NAND_DATA;

  for (chip = &chips[0];
       chip < chips + sizeof(chips)/sizeof (struct nand_chip);
       ++chip)
    if (chip->device == device)
      break;
  if (chip >= chips + sizeof(chips)/sizeof (chips[0]))
      chip = NULL;

#if defined (TALK)
  printf ("NAND flash ");

  if (chip)
    printf (" %ldMiB total, %dKiB erase\n",
	    chip->total_size/(1024*1024), chip->erase_size/1024);
  else
    printf (" unknown 0x%x/0x%x\n", manufacturer, device);
#endif

 exit:
  NAND_CS_DISABLE;
}

static int nand_open (struct descriptor_d* d)
{
  if (!chip)
    return -1;

  /* Perform bounds check */

  return 0;
}

static ssize_t nand_read (struct descriptor_d* d, void* pv, size_t cb)
{
  ssize_t cbRead = 0;

  if (!chip)
    return cbRead;

  NAND_CS_ENABLE;

  if (d->index + cb > d->length)
    cb = d->length - d->index;

  while (cb) {
    unsigned long page  = (d->start + d->index)/512;
    int index = (d->start + d->index)%512;
    int available = 512 - index;

    if (available > cb)
      available = cb;

    d->index += available;
    cb -= available;
    cbRead += available;

    NAND_CLE = Reset;
    wait_on_busy ();
    NAND_CLE = (index < 256) ? Read1 : Read2;
    NAND_ALE = (index & 0xff);
    NAND_ALE = ( page        & 0xff);
    NAND_ALE = ((page >>  8) & 0xff);
    wait_on_busy ();
    //#if !defined (CONFIG_NAND_LPD)
		/* Switch back to read mode */
    NAND_CLE = (index < 256) ? Read1 : Read2;
    //#endif
    while (available--)		/* May optimize with assembler...later */
      *((char*) pv++) = NAND_DATA;
  }

  NAND_CS_DISABLE;

  return cbRead;
}

static ssize_t nand_write (struct descriptor_d* d, const void* pv, size_t cb)
{
  int cbWrote = 0;

  if (!chip)
    return cbWrote;

  NAND_CS_ENABLE;

  if (d->index + cb > d->length)
    cb = d->length - d->index;

  SPINNER_STEP;

  while (cb) {
    unsigned long page  = (d->start + d->index)/512;
    unsigned long index = (d->start + d->index)%512;
    int available = 512 - index;
    int tail;

    if (available > cb)
      available = cb;
    tail = 528 - index - available;

    NAND_CLE = SerialInput;
    NAND_ALE = 0;	/* Always start at page beginning */
    NAND_ALE = ( page        & 0xff);
    NAND_ALE = ((page >>  8) & 0xff);

    while (index--)	   /* Skip to the portion we want to change */
      NAND_DATA = 0xff;

    d->index += available;
    cb -= available;
    cbWrote += available;

    while (available--)
      NAND_DATA = *((char*) pv++);

    while (tail--)	   /* Fill to end of block */
      NAND_DATA = 0xff;

    NAND_CLE = AutoProgram;

    wait_on_busy ();

    SPINNER_STEP;

    NAND_CLE = Status;
    if (NAND_DATA & Fail) {
      printf ("Write failed at page %ld\n", page);
      goto exit;
    }
  }

 exit:
  NAND_CS_DISABLE;

  return cbWrote;
}

static void nand_erase (struct descriptor_d* d, size_t cb)
{
  if (!chip)
    return;

  NAND_CS_ENABLE;

  if (d->index + cb > d->length)
    cb = d->length - d->index;

  SPINNER_STEP;

  do {
    unsigned long page = (d->start + d->index)/512;
    unsigned long available
      = chip->erase_size - ((d->start + d->index) & (chip->erase_size - 1));

    NAND_CLE = Erase;
    NAND_ALE = ( page & 0xff);
    NAND_ALE = ((page >> 8) & 0xff);
    NAND_CLE = EraseConfirm;

    wait_on_busy ();

    SPINNER_STEP;

    NAND_CLE = Status;
    if (NAND_DATA & Fail) {
      printf ("Erase failed at page %ld\n", page);
      goto exit;
    }

    if (available < cb) {
      cb -= available;
      d->index += available;
    }
    else {
      cb = 0;
      d->index = d->length;
    }
  } while (cb > 0);

 exit:
  NAND_CS_DISABLE;
}

#if !defined (CONFIG_SMALL)

static void nand_report (void)
{
  unsigned char status;

#if defined (USE_DETECT_ENDIAN_MISMATCH)
  if (endian_error) {
    printf ("  nor:    *** Endian Mismatch ***\n");
    return;
  }
#endif

  if (!chip)
    return;

  NAND_CLE = Status;
  status = NAND_DATA;

  printf ("  nand:   %ldMiB total, %dKiB erase %s%s%s\n",
	  chip->total_size/(1024*1024), chip->erase_size/1024,
	  (status & Fail) ? " FAIL" : "",
	  (status & Ready) ? " RDY" : "",
	  (status & Writable) ? " R/W" : " R/O"
	  );
}

#endif

static __driver_3 struct driver_d nand_driver = {
  .name = "nand",
  .description = "NAND flash driver",
  .flags = DRIVER_WRITEPROGRESS(6),
  .open = nand_open,
  .close = close_helper,
  .read = nand_read,
  .write = nand_write,
  .erase = nand_erase,
  .seek = seek_helper,
};

static __service_6 struct service_d nand_service = {
  .init = nand_init,
#if !defined (CONFIG_SMALL)
  .report = nand_report,
#endif
};