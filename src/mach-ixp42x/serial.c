/* serial.c
     $Id$

   written by Marc Singer
   14 Jan 2005

   Copyright (C) 2005 Marc Singer

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

   Serial driver for the ixp42x UARTs.  These appear to be variants of
   the pl010 PrimeCell.

*/

#include <config.h>
#include <driver.h>
#include <service.h>

#if defined (CONFIG_MACH_IXP42X)
# include "ixp42x.h"
#endif

#define UART_DR		__REG(UART_PHYS + 0x00)
#define UART_DLL	__REG(UART_PHYS + 0x00)
#define UART_DLH	__REG(UART_PHYS + 0x04)
#define UART_IER	__REG(UART_PHYS + 0x04)	/* Interrupt enable */
#define UART_FCR	__REG(UART_PHYS + 0x08)	/* FIFO control */
#define UART_LCR	__REG(UART_PHYS + 0x0c)	/* Line control */
#define UART_LSR	__REG(UART_PHYS + 0x14)	/* Line status */
#define UART_ISR	__REG(UART_PHYS + 0X20)	/* Interrupt status */

#define UART_IER_UUE	(1<<6)

#define UART_LCR_DLAB	(1<<7)
#define UART_LCR_WLS_8	(0x3<<0)
#define UART_LCR_STB_1	(0<<2)

#define UART_FCR_RESETTF (1<<2)
#define UART_FCR_RESETRF (1<<1)
#define UART_FCR_TRFIFOE (1<<0)

#define UART_LSR_TEMT	 (1<<6)
#define UART_LSR_TDRQ	 (1<<5)
#define UART_LSR_FE	 (1<<3)
#define UART_LSR_PE	 (1<<2)
#define UART_LSR_OE	 (1<<1)
#define UART_LSR_DR	 (1<<0)

extern struct driver_d* console_driver;

static struct driver_d ixp42x_serial_driver;

void ixp42x_serial_init (void)
{
  u32 baudrate = 115200;
  u32 divisor_l = 0;
  u32 divisor_h = 0;

  switch (baudrate) {
  case 115200: 
    divisor_l = 8; break;

  default:
    return;
  }

  UART_LCR  = UART_LCR_WLS_8 | UART_LCR_STB_1 | UART_LCR_DLAB;
  UART_DLL  = divisor_l;
  UART_DLH  = divisor_h;
  UART_LCR  = UART_LCR_WLS_8 | UART_LCR_STB_1;

  UART_IER  = UART_IER_UUE;	/* Enable UART, mask all interrupts */
				/* Clear interrupts? */

  if (console_driver == 0)
    console_driver = &ixp42x_serial_driver;

//  console_driver->write (0, "Console initialized\r\n", 21);
}

ssize_t ixp42x_serial_poll (struct descriptor_d* d, size_t cb)
{
  return cb ? ((UART_LSR & UART_LSR_DR) ? 0 : 1) : 0;
}

ssize_t ixp42x_serial_read (struct descriptor_d* d, void* pv, size_t cb)
{
  ssize_t cRead = 0;
  unsigned char* pb;
  for (pb = (unsigned char*) pv; cb--; ++pb) {
    u32 v;

    while ((UART_LSR & UART_LSR_DR) == 0)
      ;				/* block until character is available */

    v = UART_DR;
    if (UART_LSR & (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE))
      return -1;		/* -ESERIAL */
    *pb = v;
    ++cRead;
  }

  return cRead;
}

ssize_t ixp42x_serial_write (struct descriptor_d* d, 
			      const void* pv, size_t cb)
{
  ssize_t cWrote = 0;
  const unsigned char* pb = pv;
  for (pb = (unsigned char*) pv; cb--; ++pb) {

    while (!(UART_LSR & UART_LSR_TDRQ))
      ;

    UART_DR = *pb;

    ++cWrote;
  }
  return cWrote;
}

static __driver_0 struct driver_d ixp42x_serial_driver = {
  .name = "serial-ixp42x",
  .description = "ixp42x serial driver",
  .flags = DRIVER_SERIAL | DRIVER_CONSOLE,
  .read = ixp42x_serial_read,
  .write = ixp42x_serial_write,
  .poll = ixp42x_serial_poll,
};

static __service_3 struct service_d ixp42x_serial_service = {
  .init = ixp42x_serial_init,
};
