/* sdram.h

   written by Marc Singer
   20 Feb 2007

   Copyright (C) 2007 Marc Singer

   -----------
   DESCRIPTION
   -----------

*/

#if !defined (__SDRAM_H__)
#    define   __SDRAM_H__

/* ----- Includes */

/* ----- Types */

/* ----- Globals */

/* ----- Prototypes */

#if CONFIG_SDRAM_BANK_LENGTH == (32*1024*1024)
# if defined CONFIG_SDRAM_BANK1
#  define SDR_CONFIG_CHIPS	SDR_CONFIG_4x8Mx16
# else
#  define SDR_CONFIG_CHIPS	SDR_CONFIG_2x8Mx16
# endif
#endif

#if CONFIG_SDRAM_BANK_LENGTH == (64*1024*1024)
# if defined CONFIG_SDRAM_BANK1
#  define SDR_CONFIG_CHIPS	SDR_CONFIG_4x16Mx16
# else
#  define SDR_CONFIG_CHIPS	SDR_CONFIG_2x16Mx16
# endif
#endif

#if CONFIG_SDRAM_BANK_LENGTH == (128*1024*1024)
# if defined CONFIG_SDRAM_BANK1
#  define SDR_CONFIG_CHIPS	SDR_CONFIG_4x32Mx16
# else
#  define SDR_CONFIG_CHIPS	SDR_CONFIG_2x32Mx16
# endif
#endif


/* *** FIXME: sdram config constants should go here.  The Integrated
   Circuit Solution Inc IC42S16800 DRAM can do CAS2.  Later. */



#endif  /* __SDRAM_H__ */