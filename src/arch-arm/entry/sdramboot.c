/* sdramboot.c
     $Id$

   written by Marc Singer
   30 Sep 2005

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

   This is code to support a message telling the user that SDRAM has
   not been initialized.

*/

#include <config.h>
#include <apex.h>
#include <service.h>
#include <attributes.h>
#include <sdramboot.h>

int __xbss(init) fSDRAMBoot;

void sdramboot_report (void)
{
  if (fSDRAMBoot)
    printf ("          *** No SDRAM init when APEX executed from SDRAM.\n");
}

static __service_0 struct service_d sdramboot_service = {
  .report = sdramboot_report,
};