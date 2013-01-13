/* linux/arch/arm/mach-s5p6442/include/mach/irqs.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5P6442 - IRQ definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_IRQS_H
#define __ASM_ARCH_IRQS_H __FILE__

#include <plat/irqs.h>

#define IRQ_TIMER_BASE	(11)

/* VIC0 */
#define IRQ_EINT0 		S5P_IRQ_VIC0(0)
#define IRQ_EINT1 		S5P_IRQ_VIC0(1)
#define IRQ_EINT2 		S5P_IRQ_VIC0(2)
#define IRQ_EINT3 		S5P_IRQ_VIC0(3)
#define IRQ_EINT4 		S5P_IRQ_VIC0(4)
#define IRQ_EINT5 		S5P_IRQ_VIC0(5)
#define IRQ_EINT6 		S5P_IRQ_VIC0(6)
#define IRQ_EINT7 		S5P_IRQ_VIC0(7)
#define IRQ_EINT8 		S5P_IRQ_VIC0(8)
#define IRQ_EINT9 		S5P_IRQ_VIC0(9)
#define IRQ_EINT10 		S5P_IRQ_VIC0(10)
#define IRQ_EINT11 		S5P_IRQ_VIC0(11)
#define IRQ_EINT12 		S5P_IRQ_VIC0(12)
#define IRQ_EINT13 		S5P_IRQ_VIC0(13)
#define IRQ_EINT14 		S5P_IRQ_VIC0(14)
#define IRQ_EINT15 		S5P_IRQ_VIC0(15)
#define IRQ_EINT16_31 		S5P_IRQ_VIC0(16)
#define IRQ_BATF 		S5P_IRQ_VIC0(17)
#define IRQ_MDMA 		S5P_IRQ_VIC0(18)
#define IRQ_PDMA 		S5P_IRQ_VIC0(19)
#define IRQ_TIMER0_VIC		S5P_IRQ_VIC0(21)
#define IRQ_TIMER1_VIC		S5P_IRQ_VIC0(22)
#define IRQ_TIMER2_VIC		S5P_IRQ_VIC0(23)
#define IRQ_TIMER3_VIC		S5P_IRQ_VIC0(24)
#define IRQ_TIMER4_VIC		S5P_IRQ_VIC0(25)
#define IRQ_SYSTIMER		S5P_IRQ_VIC0(26)
#define IRQ_WDT			S5P_IRQ_VIC0(27)
#define IRQ_RTC_ALARM		S5P_IRQ_VIC0(28)
#define IRQ_RTC_TIC		S5P_IRQ_VIC0(29)
#define IRQ_GPIOINT		S5P_IRQ_VIC0(30)

/* VIC1 */
#define IRQ_PMU			S5P_IRQ_VIC1(0)
#define IRQ_ONENAND 		S5P_IRQ_VIC1(7)
#define IRQ_UART0 		S5P_IRQ_VIC1(10)
#define IRQ_UART1 		S5P_IRQ_VIC1(11)
#define IRQ_UART2 		S5P_IRQ_VIC1(12)
#define IRQ_SPI0 		S5P_IRQ_VIC1(15)
#define IRQ_IIC 		S5P_IRQ_VIC1(19)
#define IRQ_IIC1 		S5P_IRQ_VIC1(20)
#define IRQ_IIC2 		S5P_IRQ_VIC1(21)
#define IRQ_OTG 		S5P_IRQ_VIC1(24)
#define IRQ_MSM 		S5P_IRQ_VIC1(25)
#define IRQ_HSMMC0 		S5P_IRQ_VIC1(26)
#define IRQ_HSMMC1 		S5P_IRQ_VIC1(27)
#define IRQ_HSMMC2 		S5P_IRQ_VIC1(28)
#define IRQ_COMMRX 		S5P_IRQ_VIC1(29)
#define IRQ_COMMTX 		S5P_IRQ_VIC1(30)
#define IRQ_ONENAND_AUDI  IRQ_ONENAND

/* VIC2 */
#define IRQ_LCD0 		S5P_IRQ_VIC2(0)
#define IRQ_LCD1 		S5P_IRQ_VIC2(1)
#define IRQ_LCD2 		S5P_IRQ_VIC2(2)
#define IRQ_LCD3 		S5P_IRQ_VIC2(3)
#define IRQ_ROTATOR 		S5P_IRQ_VIC2(4)
#define IRQ_FIMC0 		S5P_IRQ_VIC2(5)
#define IRQ_FIMC1 		S5P_IRQ_VIC2(6)
#define IRQ_FIMC2 		S5P_IRQ_VIC2(7)
#define IRQ_JPEG 		S5P_IRQ_VIC2(8)
#define IRQ_3D 			S5P_IRQ_VIC2(10)
#define IRQ_Mixer 		S5P_IRQ_VIC2(11)
#define IRQ_MFC 		S5P_IRQ_VIC2(14)
#define IRQ_TVENC 		S5P_IRQ_VIC2(15)
#define IRQ_I2S0 		S5P_IRQ_VIC2(16)
#define IRQ_I2S1 		S5P_IRQ_VIC2(17)
#define IRQ_RP 			S5P_IRQ_VIC2(19)
#define IRQ_PCM0 		S5P_IRQ_VIC2(20)
#define IRQ_PCM1 		S5P_IRQ_VIC2(21)
#define IRQ_ADC 		S5P_IRQ_VIC2(23)
#define IRQ_PENDN 		S5P_IRQ_VIC2(24)
#define IRQ_KEYPAD 		S5P_IRQ_VIC2(25)
#define IRQ_SSS_INT 		S5P_IRQ_VIC2(27)
#define IRQ_SSS_HASH 		S5P_IRQ_VIC2(28)
#define IRQ_VIC_END 		S5P_IRQ_VIC2(31)

#define S5P_IRQ_EINT_BASE	(IRQ_VIC_END + 1)

#define S5P_EINT_BASE1		(S5P_IRQ_VIC0(0))
#define S5P_EINT_BASE2		(S5P_IRQ_EINT_BASE)

/* Compatibility defines */

#define IRQ_LCD_FIFO		IRQ_LCD0
#define IRQ_LCD_VSYNC		IRQ_LCD1
#define IRQ_LCD_SYSTEM		IRQ_LCD2
#define IRQ_TC			IRQ_PENDN

/* Next the external interrupt groups. These are similar to the IRQ_EINT(x)
 * that they are sourced from the GPIO pins but with a different scheme for
 * priority and source indication.
 *
 * The IRQ_EINT(x) can be thought of as 'group 0' of the available GPIO
 * interrupts, but for historical reasons they are kept apart from these
 * next interrupts.
 *
 * Use IRQ_EINT_GROUP(group, offset) to get the number for use in the
 * machine specific support files.
 */

#define IRQ_EINT_GROUP1_NR	(8)   //GPA0
#define IRQ_EINT_GROUP2_NR	(2)   //GPA1
#define IRQ_EINT_GROUP3_NR	(4)   //GPB
#define IRQ_EINT_GROUP4_NR	(5)   //GPC1
#define IRQ_EINT_GROUP5_NR	(2)   //GPD0
#define IRQ_EINT_GROUP6_NR	(6)   //GPD1
#define IRQ_EINT_GROUP7_NR	(8)   //GPE0
#define IRQ_EINT_GROUP8_NR	(5)   //GPE1
#define IRQ_EINT_GROUP9_NR	(8)   //GPF0
#define IRQ_EINT_GROUP10_NR        (8)   //GPF1
#define IRQ_EINT_GROUP11_NR        (8)   //GPF2
#define IRQ_EINT_GROUP12_NR        (6)   //GPF3
#define IRQ_EINT_GROUP13_NR        (7)   //GPG0
#define IRQ_EINT_GROUP14_NR        (7)   //GPG1
#define IRQ_EINT_GROUP15_NR        (7)   //GPG2
#define IRQ_EINT_GROUP16_NR        (8)   //GPJ0
#define IRQ_EINT_GROUP17_NR        (6)   //GPJ1
#define IRQ_EINT_GROUP18_NR        (8)   //GPJ2
#define IRQ_EINT_GROUP19_NR        (8)   //GPJ3
#define IRQ_EINT_GROUP20_NR        (5)   //GPJ4
//#define IRQ_EINT_GROUP21_NR        (5)   //GPJ4


#define IRQ_EINT_GROUP_BASE	S3C_EINT(32)
#define IRQ_EINT_GROUP1_BASE	(IRQ_EINT_GROUP_BASE + 0x00)
#define IRQ_EINT_GROUP2_BASE	(IRQ_EINT_GROUP1_BASE + IRQ_EINT_GROUP1_NR)
#define IRQ_EINT_GROUP3_BASE	(IRQ_EINT_GROUP2_BASE + IRQ_EINT_GROUP2_NR)
#define IRQ_EINT_GROUP4_BASE	(IRQ_EINT_GROUP3_BASE + IRQ_EINT_GROUP3_NR)
#define IRQ_EINT_GROUP5_BASE	(IRQ_EINT_GROUP4_BASE + IRQ_EINT_GROUP4_NR)
#define IRQ_EINT_GROUP6_BASE	(IRQ_EINT_GROUP5_BASE + IRQ_EINT_GROUP5_NR)
#define IRQ_EINT_GROUP7_BASE	(IRQ_EINT_GROUP6_BASE + IRQ_EINT_GROUP6_NR)
#define IRQ_EINT_GROUP8_BASE	(IRQ_EINT_GROUP7_BASE + IRQ_EINT_GROUP7_NR)
#define IRQ_EINT_GROUP9_BASE	(IRQ_EINT_GROUP8_BASE + IRQ_EINT_GROUP8_NR)
#define IRQ_EINT_GROUP10_BASE    (IRQ_EINT_GROUP9_BASE + IRQ_EINT_GROUP9_NR)
#define IRQ_EINT_GROUP11_BASE    (IRQ_EINT_GROUP10_BASE + IRQ_EINT_GROUP10_NR)
#define IRQ_EINT_GROUP12_BASE    (IRQ_EINT_GROUP11_BASE + IRQ_EINT_GROUP11_NR)
#define IRQ_EINT_GROUP13_BASE    (IRQ_EINT_GROUP12_BASE + IRQ_EINT_GROUP12_NR)
#define IRQ_EINT_GROUP14_BASE    (IRQ_EINT_GROUP13_BASE + IRQ_EINT_GROUP13_NR)
#define IRQ_EINT_GROUP15_BASE    (IRQ_EINT_GROUP14_BASE + IRQ_EINT_GROUP14_NR)
#define IRQ_EINT_GROUP16_BASE    (IRQ_EINT_GROUP15_BASE + IRQ_EINT_GROUP15_NR)
#define IRQ_EINT_GROUP17_BASE    (IRQ_EINT_GROUP16_BASE + IRQ_EINT_GROUP16_NR)
#define IRQ_EINT_GROUP18_BASE    (IRQ_EINT_GROUP17_BASE + IRQ_EINT_GROUP17_NR)
#define IRQ_EINT_GROUP19_BASE    (IRQ_EINT_GROUP18_BASE + IRQ_EINT_GROUP18_NR)
#define IRQ_EINT_GROUP20_BASE    (IRQ_EINT_GROUP19_BASE + IRQ_EINT_GROUP19_NR)
//#define IRQ_EINT_GROUP21_BASE    (IRQ_EINT_GROUP20_BASE + IRQ_EINT_GROUP20_NR)

#define IRQ_EINT_GROUP(group, no)	(IRQ_EINT_GROUP##group##_BASE + (no))


/* Set the default NR_IRQS */

#define S5P_GPIOINT_BASE	(IRQ_EINT(31) + 1)
#define S5P_GPIOINT_GROUP_MAXNR	22
#define NR_IRQS 		(IRQ_EINT(31) + 1)

#endif /* __ASM_ARCH_IRQS_H */
