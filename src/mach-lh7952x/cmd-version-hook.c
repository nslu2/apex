/* cmd-version-hook.c
     $Id$

   written by Marc Singer
   15 Jan 2005

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

*/

#include <config.h>
#include <linux/types.h>
#include <apex.h>
#include <command.h>
#include <service.h>
#include "hardware.h"

extern command_func_t hook_cmd_version;

int lh7952x_cmd_version (int argc, const char** argv)
{
  unsigned short v = __REG16 (RCPC_PHYS + RCPC_CHIPID);
  char* sz = NULL;

  switch (v>>4) {
  default   : sz = "lh?"; break;
  case 0x524: sz = "lh79524"; break;
  case 0x525: sz = "lh79525"; break;
  }

  printf ("  CPU  id 0x%x, %s\r\n", v, sz);

#if defined (CONFIG_MACH_LPD79524)
  printf ("  CPLD revision 0x%x\r\n", __REG8 (0x4ca00000));
#endif

  return 0;
}

static void hook_init (void)
{
  hook_cmd_version = lh7952x_cmd_version;
}

static __service_7 struct service_d hook_cmd_version_service = {
  .init = hook_init,
};