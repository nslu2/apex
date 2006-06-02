/* debug_ll.h
     $Id$

   with modifications by David Anders
   06 Nov 2005


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

   This header is for debug only.  As such, it conflicts with the
   normal serial includes.  Thus these macros are protected from being
   included when the uart macros have previously been included.

   Do not include this header in source files.  Use

      #include <debug_ll.h>

   which will get the global header that has additional macros.

*/

#if !defined (__DEBUG_LL_H__)
#    define   __DEBUG_LL_H__

/* ----- Includes */

#include <config.h>
#include <asm/reg.h>

#if !defined (UART_BASE)

#define S3C2410_UART_BASE		0x50000000
#define S3C2410_UART0_BASE		(S3C2410_UART_BASE + 0x00 )
#define UART_BASE			__REG(S3C2410_UART0_BASE + 0x00)
#define UART0_CTRL_UFCON		__REG(S3C2410_UART0_BASE + 0x08)
#define UART0_CTRL_UMCON		__REG(S3C2410_UART0_BASE + 0x0C)
#define UART0_CTRL_ULCON		__REG(S3C2410_UART0_BASE + 0x00)
#define UART0_CTRL_UCON			__REG(S3C2410_UART0_BASE + 0x04)
#define UART0_CTRL_UBRDIV		__REG(S3C2410_UART0_BASE + 0x28)
#define UART0_CTRL_OUTRSTAT		__REG(S3C2410_UART0_BASE + 0x10)
#define UART0_CTRL_UTXHL		__REG(S3C2410_UART0_BASE + 0x20)

#define UTRSTAT_TX_EMPTY	(1 << 2)
#define UTRSTAT_RX_READY	(1 << 0)

#endif

#define PUTC(c)		({ while ( (UART0_CTRL_OUTRSTAT & UTRSTAT_TX_EMPTY)\
			    == UART0_CTRL_OUTRSTAT) ; \
			    UART0_CTRL_UTXHL = c; })


#endif				/* __DEBUG_LL_H__ */
