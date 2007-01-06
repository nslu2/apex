/* mx31.h

   written by Marc Singer
   23 Nov 2006

   Copyright (C) 2006 Marc Singer

   -----------
   DESCRIPTION
   -----------

*/

#if !defined (__MX31_H__)
#    define   __MX31_H__

/* ----- Includes */

/* ----- Types */

/* ----- Globals */

/* ----- Prototypes */

#define PHYS_SECUREROM		(0x00000000) /* 16K */
#define PHYS_ROM		(0x00404000) /* 16K */
#define PHYS_RAM		(0x1fffc000) /* 16K */
#define PHYS_L2CC		(0x30000000)
#define PHYS_I2C		(0x43f80000)
#define PHYS_I2C3		(0x43f84000)
#define PHYS_USBOTG		(0x43f88000)
#define PHYS_ATA		(0x43f8c000)
#define PHYS_UART1		(0x43f90000)
#define PHYS_UART2		(0x43f94000)
#define PHYS_I2C2		(0x43f98000)
#define PHYS_1WIRE		(0x43f9c000)
#define PHYS_SSI1		(0x43fa0000)
#define PHYS_CSPI1		(0x43fa4000)
#define PHYS_KPP		(0x43fa8000)
#define PHYS_IOMUXC		(0x43fac000)
#define PHYS_UART4		(0x43fb0000)
#define PHYS_UART5		(0x43fb4000)
#define PHYS_ECT_BUS1		(0x43fb8000)
#define PHYS_ECT_BUS2		(0x43fbc000)
#define PHYS_MMC_SDHC1		(0x50004000)
#define PHYS_MMC_SDHC2		(0x50008000)
#define PHYS_UART3		(0x5000c000)
#define PHYS_CSPI2		(0x50010000)
#define PHYS_SSI2		(0x50014000)
#define PHYS_SIM		(0x50018000)
#define PHYS_IIM		(0x5001c000)
#define PHYS_ATADMA		(0x50020000)
#define PHYS_MSHC1		(0x50024000)
#define PHYS_MSHC2		(0x50028000)
#define PHYS_CCM		(0x53f80000)
#define PHYS_CSPI3		(0x53f84000)
#define PHYS_FIR		(0x53f8c000)
#define PHYS_GPT		(0x53f90000)
#define PHYS_EPIT1		(0x53f94000)
#define PHYS_EPIT2		(0x53f98000)
#define PHYS_GPIO3		(0x53fa4000)
#define PHYS_SCC		(0x53fac000)
#define PHYS_RNGA		(0x53fb0000)
#define PHYS_IPU		(0x53fc0000)
#define PHYS_AUDMUX		(0x53fc4000)
#define PHYS_MPEG		(0x53fc8000)
#define PHYS_GPIO1		(0x53fcc000)
#define PHYS_GPIO2		(0x53fd0000)
#define PHYS_SMDA		(0x53fd4000)
#define PHYS_RTC		(0x53fd8000)
#define PHYS_WDOG		(0x53fdc000)
#define PHYS_PWM		(0x53fe0000)
#define PHYS_RTIC		(0x53fec000)
#define PHYS_ROMPATCH		(0x60000000)
#define PHYS_AVIC		(0x68000000)
#define PHYS_IPU		(0x70000000) /* LCD controller */


#define PHYS_M3IF		(0xb8003000)
#define PHYS_ESDCTL		(0xb8001000)
#define PHYS_PCMCIA		(0xb8004000)
#define PHYS_WEIM		(0xb8002000)
#define PHYS_NANDFC		(0xb8000e00)

#define SDRAM_BANK0_PHYS	(0x80000000)
#define SDRAM_BANK1_PHYS	(0x90000000)

#define WEIM0_PHYS		(0xa0000000)
#define WEIM1_PHYS		(0xa8000000)
#define WEIM2_PHYS		(0xb0000000)
#define WEIM3_PHYS		(0xb2000000)
#define WEIM4_PHYS		(0xb4000000)
#define WEIM5_PHYS		(0xb6000000)

#define NAND_PHYS		(0xb8000000)

#define ESDCTL0			__REG(0xb8001000)
#define ESDCFG0			__REG(0xb8001004)
#define ESDCTL1			__REG(0xb8001008)
#define ESDCFG1			__REG(0xb800100c)
#define ESDMISC			__REG(0xb8001010)
#define ESDCDLY1		__REG(0xb8001020)
#define ESDCDLY2		__REG(0xb8001024)
#define ESDCDLY3		__REG(0xb8001028)
#define ESDCDLY4		__REG(0xb800102c)
#define ESDCDLY5		__REG(0xb8001030)
#define ESDCDLYL		__REG(0xb8001034)


#define NAND_RAM_PAGE0		(0xcc000000)
#define NAND_RAM_PAGE1		(0xb8000200)
#define NAND_RAM_PAGE2		(0xb8000400)
#define NAND_RAM_PAGE3		(0xb8000600)
#define NAND_RAM_SPARE0		(0xb8000800)
#define NAND_RAM_SPARE1		(0xb8000810)
#define NAND_RAM_SPARE2		(0xb8000820)
#define NAND_RAM_SPARE3		(0xb8000830)

#define NFC_BUFFER_SIZE		__REG16(0xb8000e00)
#define NFC_BUFFER_ADDR		__REG16(0xb8000e04)
#define NFC_FLASH_ADDR		__REG16(0xb8000e06)
#define NFC_FLASH_CMD		__REG16(0xb8000e08)
#define NFC_CONFIGURATION	__REG16(0xb8000e0a)
#define NFC_ECC_STATUS		__REG16(0xb8000e0c)
#define NFC_ECC_RESULT_MAIN	__REG16(0xb8000e0e)
#define NFC_ECC_RESULT_SPARE	__REG16(0xb8000e10)
#define NFC_WRITE_PROTECT	__REG16(0xb8000e12)
#define NFC_UNLOCK_START	__REG16(0xb8000e14)
#define NFC_UNLOCK_END		__REG16(0xb8000e16)
#define NFC_WP_STATUS		__REG16(0xb8000e18)
#define NFC_FLASH_CONFIG1	__REG16(0xb8000e1a)
#define NFC_FLASH_CONFIG2	__REG16(0xb8000e1c)

#define CCM_CGR0		__REG(PHYS_CCM + 0x20)
#define CCM_CGR1		__REG(PHYS_CCM + 0x24)
#define CCM_CGR2		__REG(PHYS_CCM + 0x28)

#define CCM_CGR_OFF		(0x00)
#define CCM_CGR_RUN		(0x01)
#define CCM_CGR_RUNWAIT		(0x02)
#define CCM_CGR_ALL		(0x03)
#define CCM_CGR0_GPT_SH		(2*2)
#define CCM_CGR0_EPIT1_SH	(3*2)
#define CCM_CGR0_EPIT2_SH	(4*2)

#define EPT1_CR			__REG(PHYS_EPIT1 + 0x00)
#define EPT1_SR			__REG(PHYS_EPIT1 + 0x04)
#define EPT1_LR			__REG(PHYS_EPIT1 + 0x08)
#define EPT1_CMPR		__REG(PHYS_EPIT1 + 0x0c)
#define EPT1_CNT		__REG(PHYS_EPIT1 + 0x10)

#define EPT2_CR			__REG(PHYS_EPIT2 + 0x00)
#define EPT2_SR			__REG(PHYS_EPIT2 + 0x04)
#define EPT2_LR			__REG(PHYS_EPIT2 + 0x08)
#define EPT2_CMPR		__REG(PHYS_EPIT2 + 0x0c)
#define EPT2_CNT		__REG(PHYS_EPIT2 + 0x10)

#define EPT_CR_EN		(1<<0)
#define EPT_CR_CLKSRC_SH	(24)
#define EPT_CR_CLKSRC_MSK	(0x3<<24)
#define EPT_CR_CLKSRC_32K	(0x3<<24)
#define EPT_CR_CLKSRC_HIGH	(0x2<<24)
#define EPT_CR_FREERUN		(1<<9)
#define EPT_CR_PRESCALE_SH	(4)
#define EPT_CR_PRESCALE_MSK	(0xfff<<4)
#define EPT_IOVW		(1<<17)
#define EPT_RLD			(1<<3)

#define GPT_CR			__REG(PHYS_GPT + 0x00)
#define GPT_PR			__REG(PHYS_GPT + 0x04)
#define GPT_SR			__REG(PHYS_GPT + 0x08)
#define GPT_IR			__REG(PHYS_GPT + 0x0c)
#define GPT_0CR1		__REG(PHYS_GPT + 0x10)
#define GPT_0CR2		__REG(PHYS_GPT + 0x14)
#define GPT_0CR3		__REG(PHYS_GPT + 0x18)
#define GPT_ICR1		__REG(PHYS_GPT + 0x1c)
#define GPT_CNT			__REG(PHYS_GPT + 0x24)

#define GPT_CR_EN		(1<<0)
#define GPT_CR_CLKSRC_SH	(6)
#define GPT_CR_CLKSRC_MSK	(0x7<<6)
#define GPT_CR_CLKSRC_32K	(0x4<<6)
#define GPT_CR_CLKSRC_HIGH	(0x2<<6)
#define GPT_CR_CLKSRC_LOW	(0x1<<6)
#define GPT_CR_FREERUN		(1<<9)

#define GPT_SR_ROV		(1<<5) /* Roll-over */


#endif  /* __MX31_H__ */