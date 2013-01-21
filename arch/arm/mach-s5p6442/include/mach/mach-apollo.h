/*
 *  arch/arm/mach-s5p6442/include/mach/mach-apollo.h
 *
 *  Author:		Samsung Electronics
 *  Created:	19, Nov, 2009
 *  Copyright:	Samsung Electronics Co.Ltd.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#ifndef MACH_APOLLO_EMUL_H

#define MACH_APOLLO_EMUL_H

#define CONFIG_RESERVED_MEM_CMM_JPEG_MFC_POST_CAMERA

/*
 * GPIO Configuration
 */

#include <mach/gpio.h>
#include <mach/memory.h>

#define GPIO_LEVEL_LOW      		0
#define GPIO_LEVEL_HIGH     		1
#define GPIO_LEVEL_NONE				2

#define GPIO_DRV_SR_1X				0
#define GPIO_DRV_SR_2X				1
#define GPIO_DRV_SR_3X				2
#define GPIO_DRV_SR_4X				3

/* GPA0 */
#define GPIO_BT_UART_RXD			S5P6442_GPA0(0)
#define GPIO_BT_UART_RXD_STATE		2

#define GPIO_BT_UART_TXD			S5P6442_GPA0(1)
#define GPIO_BT_UART_TXD_STATE		2

#define GPIO_BT_UART_CTS			S5P6442_GPA0(2)
#define GPIO_BT_UART_CTS_STATE		2

#define GPIO_BT_UART_RTS			S5P6442_GPA0(3)
#define GPIO_BT_UART_RTS_STATE		2

#define GPIO_AP_COM_RXD				S5P6442_GPA0(4)			// FLM_SEL H: AP_FLM_RXD, FLM_SEL L: AP_RXD
#define GPIO_AP_COM_RXD_STATE		2

#define GPIO_AP_COM_TXD				S5P6442_GPA0(5)			// FLM_SEL H: AP_FLM_TXD, FLM_SEL L: AP_TXD
#define GPIO_AP_COM_TXD_STATE		2

/* GPA1 */
#define GPIO_AP_FLM_RXD_2_8V		S5P6442_GPA1(0)
#define GPIO_AP_FLM_RXD_2_8V_STATE	2

#define GPIO_AP_FLM_TXD_2_8V		S5P6442_GPA1(1)	
#define GPIO_AP_FLM_TXD_2_8V_STATE	2

/* GPC0 */
#define GPIO_CODEC_I2S_CLK			S5P6442_GPC0(0)
#define GPIO_CODEC_I2S_CLK_STATE	2

#define GPIO_CODEC_I2S_WS			S5P6442_GPC0(2)
#define GPIO_CODEC_I2S_WS_STATE		2

#define GPIO_CODEC_I2S_DI			S5P6442_GPC0(3)
#define GPIO_CODEC_I2S_DI_STATE		2

#define GPIO_CODEC_I2S_DO			S5P6442_GPC0(4)
#define GPIO_CODEC_I2S_DO_STATE		2

/* GPD0 */
#define GPIO_VIBTONE_PWM			S5P6442_GPD0(0)
#define GPIO_VIBTONE_PWM_STATE		2

/* GPD1 */
#define GPIO_CAM_SDA_2_8V			S5P6442_GPD1(0)
#define GPIO_CAM_SDA_2_8V_STATE		2

#define GPIO_CAM_SCL_2_8V			S5P6442_GPD1(1)
#define GPIO_CAM_SCL_2_8V_STATE		2

#define GPIO_AP_SDA_2_8V		S5P6442_GPD1(2)
#define GPIO_AP_SDA_2_8V_STATE	2

#define GPIO_AP_SCL_2_8V		S5P6442_GPD1(3)
#define GPIO_AP_SCL_2_8V_STATE	2

#define GPIO_TSP_SDA_2_8V			S5P6442_GPD1(4)
#define GPIO_TSP_SDA_2_8V_STATE		1 //2

#define GPIO_TSP_SCL_2_8V			S5P6442_GPD1(5)
#define GPIO_TSP_SCL_2_8V_STATE		1 //2

/* GPE0 */
#define GPIO_CAM_PCLK				S5P6442_GPE0(0)
#define GPIO_CAM_PCLK_STATE			2

#define GPIO_CAM_VSYNC				S5P6442_GPE0(1)
#define GPIO_CAM_VSYNC_STATE		2

#define GPIO_CAM_HSYNC				S5P6442_GPE0(2)
#define GPIO_CAM_HSYNC_STATE		2

#define GPIO_CAM_D_0				S5P6442_GPE0(3)
#define GPIO_CAM_D_0_STATE			2

#define GPIO_CAM_D_1				S5P6442_GPE0(4)
#define GPIO_CAM_D_1_STATE			2

#define GPIO_CAM_D_2				S5P6442_GPE0(5)
#define GPIO_CAM_D_2_STATE			2

#define GPIO_CAM_D_3				S5P6442_GPE0(6)
#define GPIO_CAM_D_3_STATE			2

#define GPIO_CAM_D_4				S5P6442_GPE0(7)
#define GPIO_CAM_D_4_STATE			2

/* GPE1 */
#define GPIO_CAM_D_5				S5P6442_GPE1(0)
#define GPIO_CAM_D_5_STATE			2

#define GPIO_CAM_D_6				S5P6442_GPE1(1)
#define GPIO_CAM_D_6_STATE			2

#define GPIO_CAM_D_7				S5P6442_GPE1(2)
#define GPIO_CAM_D_7_STATE			2

#define GPIO_CAM_MCLK				S5P6442_GPE1(3)
#define GPIO_CAM_MCLK_STATE			2

#define GPIO_TOUCH_RST				S5P6442_GPE1(4)			// H: Nothing,	L: Reset
#define GPIO_TOUCH_RST_STATE		1

/* GPF0 */
#define GPIO_LCD_HSYNC				S5P6442_GPF0(0)
#define GPIO_LCD_HSYNC_STATE		2

#define GPIO_LCD_VSYNC				S5P6442_GPF0(1)
#define GPIO_LCD_VSYNC_STATE		2

#define GPIO_LCD_VDEN				S5P6442_GPF0(2)			// H: Enable,	L: Disable
#define GPIO_LCD_VDEN_STATE			2

#define GPIO_LCD_MCLK				S5P6442_GPF0(3)
#define GPIO_LCD_MCLK_STATE			2

#define GPIO_LCD_D_0				S5P6442_GPF0(4)
#define GPIO_LCD_D_0_STATE			2

#define GPIO_LCD_D_1				S5P6442_GPF0(5)
#define GPIO_LCD_D_1_STATE			2

#define GPIO_LCD_D_2				S5P6442_GPF0(6)
#define GPIO_LCD_D_2_STATE			2

#define GPIO_LCD_D_3				S5P6442_GPF0(7)
#define GPIO_LCD_D_3_STATE			2

/* GPF1 */
#define GPIO_LCD_D_4				S5P6442_GPF1(0)
#define GPIO_LCD_D_4_STATE			2

#define GPIO_LCD_D_5				S5P6442_GPF1(1)
#define GPIO_LCD_D_5_STATE			2

#define GPIO_LCD_D_6				S5P6442_GPF1(2)
#define GPIO_LCD_D_6_STATE			2

#define GPIO_LCD_D_7				S5P6442_GPF1(3)
#define GPIO_LCD_D_7_STATE			2

#define GPIO_LCD_D_8				S5P6442_GPF1(4)
#define GPIO_LCD_D_8_STATE			2

#define GPIO_LCD_D_9				S5P6442_GPF1(5)
#define GPIO_LCD_D_9_STATE			2

#define GPIO_LCD_D_10				S5P6442_GPF1(6)
#define GPIO_LCD_D_10_STATE			2

#define GPIO_LCD_D_11				S5P6442_GPF1(7)
#define GPIO_LCD_D_11_STATE			2

/* GPF2 */
#define GPIO_LCD_D_12				S5P6442_GPF2(0)
#define GPIO_LCD_D_12_STATE			2

#define GPIO_LCD_D_13				S5P6442_GPF2(1)
#define GPIO_LCD_D_13_STATE			2

#define GPIO_LCD_D_14				S5P6442_GPF2(2)
#define GPIO_LCD_D_14_STATE			2

#define GPIO_LCD_D_15				S5P6442_GPF2(3)
#define GPIO_LCD_D_15_STATE			2

#define GPIO_LCD_D_16				S5P6442_GPF2(4)
#define GPIO_LCD_D_16_STATE			2

#define GPIO_LCD_D_17				S5P6442_GPF2(5)
#define GPIO_LCD_D_17_STATE			2

#define GPIO_LCD_D_18				S5P6442_GPF2(6)
#define GPIO_LCD_D_18_STATE			2

#define GPIO_LCD_D_19				S5P6442_GPF2(7)
#define GPIO_LCD_D_19_STATE			2

/* GPF3 */
#define GPIO_LCD_D_20				S5P6442_GPF3(0)
#define GPIO_LCD_D_20_STATE			2

#define GPIO_LCD_D_21				S5P6442_GPF3(1)
#define GPIO_LCD_D_21_STATE			2

#define GPIO_LCD_D_22				S5P6442_GPF3(2)
#define GPIO_LCD_D_22_STATE			2

#define GPIO_LCD_D_23				S5P6442_GPF3(3)
#define GPIO_LCD_D_23_STATE			2

/*GPG0 */   //SD 1
#define GPIO_CAM_EN					S5P6442_GPG0(0)
#define GPIO_CAM_EN_STATE			1

#define GPIO_TOUCH_INT				S5P6442_GPG0(2)
#define GPIO_TOUCH_INT_STATE		0xF

#define GPIO_CAM_3M_nSTBY			S5P6442_GPG0(3)		
#define GPIO_CAM_3M_nSTBY_STATE		1

#define GPIO_UART_SEL				S5P6442_GPG0(5)
#define GPIO_UART_SEL_STATE			1
/* GPG1 */ //SD 2
#define GPIO_WLAN_SDIO_CLK			S5P6442_GPG1(0)
#define GPIO_WLAN_SDIO_CLK_STATE	2

#define GPIO_WLAN_SDIO_CMD			S5P6442_GPG1(1)
#define GPIO_WLAN_SDIO_CMD_STATE	2

#define GPIO_WLAN_nRST				S5P6442_GPG1(2)			// H: ON,		L: OFF
#define GPIO_WLAN_nRST_STATE		1			

#define GPIO_WLAN_SDIO_D_0			S5P6442_GPG1(3)
#define GPIO_WLAN_SDIO_D_0_STATE	2

#define GPIO_WLAN_SDIO_D_1			S5P6442_GPG1(4)
#define GPIO_WLAN_SDIO_D_1_STATE	2

#define GPIO_WLAN_SDIO_D_2			S5P6442_GPG1(5)
#define GPIO_WLAN_SDIO_D_2_STATE	2

#define GPIO_WLAN_SDIO_D_3			S5P6442_GPG1(6)
#define GPIO_WLAN_SDIO_D_3_STATE	2

/* GPG2 */ //SD 3
#define GPIO_T_FLASH_CLK			S5P6442_GPG2(0)
#define GPIO_T_FLASH_CLK_STATE		2

#define GPIO_T_FLASH_CMD			S5P6442_GPG2(1)
#define GPIO_T_FLASH_CMD_STATE		2

#define GPIO_T_FLASH_D_0			S5P6442_GPG2(3)	
#define GPIO_T_FLASH_D_0_STATE		2

#define GPIO_T_FLASH_D_1			S5P6442_GPG2(4)	
#define GPIO_T_FLASH_D_1_STATE		2

#define GPIO_T_FLASH_D_2			S5P6442_GPG2(5)	
#define GPIO_T_FLASH_D_2_STATE		2

#define GPIO_T_FLASH_D_3			S5P6442_GPG2(6)	
#define GPIO_T_FLASH_D_3_STATE		2

/* GPH0 */
#define GPIO_AP_PS_HOLD				S5P6442_GPH0(0)			// H: Hold,	L: Release
#define GPIO_AP_PS_HOLD_STATE		3			

#define GPIO_ACC_INT				S5P6442_GPH0(1)			// H: Nothing,	L: Power KEY Detect
#define GPIO_ACC_INT_STATE			0XF

#define GPIO_BUCK_1_EN_A			S5P6442_GPH0(2)			// H: Active,	L: Not Active
#define GPIO_BUCK_1_EN_A_STATE		1

#define GPIO_BUCK_1_EN_B			S5P6442_GPH0(3)			// used for check Phone reset
#define GPIO_BUCK_1_EN_B_STATE		1

#define GPIO_BUCK_2_EN				S5P6442_GPH0(4)			// used for check Phone reset
#define GPIO_BUCK_2_EN_STATE		1

#define GPIO_FLM_SEL				S5P6442_GPH0(5)			// H: Nothing,	L: Interrupt
#define GPIO_FLM_SEL_STATE			1

#define GPIO_EARJACK_DET			S5P6442_GPH0(6)			// H: Nothing,	L: Detect
#define GPIO_EARJACK_DET_STATE		0XF

#define GPIO_AP_PMIC_IRQ			S5P6442_GPH0(7)			// H: Nothing,	L: Interrupt
#define GPIO_AP_PMIC_IRQ_STATE		0XF

/* GPH1 */
#define GPIO_SIM_nDETECT				S5P6442_GPH1(0)	
#define GPIO_SIM_nDETECT_STATE	0xF

#define GPIO_PDA_ACTIVE				S5P6442_GPH1(2)
#define GPIO_PDA_ACTIVE_STATE		0

#define GPIO_nINT_ONEDRAM_AP		S5P6442_GPH1(3)			// H: Enable,	L: Disable
#define GPIO_nINT_ONEDRAM_AP_STATE	0

#define GPIO_RESET_REQ_N			S5P6442_GPH1(4)			// H: Nothing,	L: Reset
#define GPIO_RESET_REQ_N_STATE		1

#define GPIO_CODEC_LDO_EN			S5P6442_GPH1(5)			// H: Active,	L: StandBy
#define GPIO_CODEC_LDO_EN_STATE	 	1	

#define GPIO_PHONE_ACTIVE			S5P6442_GPH1(7)			// H: FLM I/F,	L: USIM I/F
#define GPIO_PHONE_ACTIVE_STATE		1

/* GPH2 */
#define GPIO_T_FLASH_DETECT			S5P6442_GPH2(0)			// H: Detect	,	L: Nothing
#define GPIO_T_FLASH_DETECT_STATE	0XF

#define GPIO_MSENSE_IRQ				S5P6442_GPH2(1)
#define GPIO_MSENSE_IRQ_STATE		0XF

#define GPIO_EAR_SEND_END			S5P6442_GPH2(2)
#define GPIO_EAR_SEND_END_STATE		0XF

#define GPIO_WLAN_HOST_WAKE			S5P6442_GPH2(4)		// H: WakeUp		L: Nothing	
#define GPIO_WLAN_HOST_WAKE_STATE	0XF

#define GPIO_BT_HOST_WAKE			S5P6442_GPH2(5)		// H: Nothing,	L: Interrupt
#define GPIO_BT_HOST_WAKE_STATE		0XF

#define GPIO_nPOWER				 	S5P6442_GPH2(6)		// H: Nothing,	L: Interrupt
#define GPIO_nPOWER_STATE			0XF

#define GPIO_JACK_nINT				S5P6442_GPH2(7)		// H: Nothing,	L: Interrupt
#define GPIO_JACK_nINT_STATE		0XF

/* GPH3 */
#define GPIO_KEY_ROW0				S5P6442_GPH3(0)
#define GPIO_KEY_ROW0_STATE			3

#define GPIO_KEY_ROW1				S5P6442_GPH3(1)
#define GPIO_KEY_ROW1_STATE			3

#define GPIO_KEY_ROW2				S5P6442_GPH3(2)
#define GPIO_KEY_ROW2_STATE			3

#define GPIO_KEY_ROW3				S5P6442_GPH3(3)
#define GPIO_KEY_ROW3_STATE			3

#define S5P6442_GPH3CON			(S5P6442_GPH3_BASE + 0x00)
#define S5P6442_GPH3DAT			(S5P6442_GPH3_BASE + 0x04)
#define S5P6442_GPH3PUD			(S5P6442_GPH3_BASE + 0x08)
#define S5P6442_GPH3DRV			(S5P6442_GPH3_BASE + 0x0c)

#define S5P6442_GPH3_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5P6442_GPH3_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5P6442_GPH3_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5P6442_GPH3_0_KP_ROW_0		(0x3 << 0)
#define S5P6442_GPH3_0_EXT_INT3_0	(0xf << 0)

#define S5P6442_GPH3_1_KP_ROW_1		(0x3 << 4)
#define S5P6442_GPH3_1_EXT_INT3_1	(0xf << 4)

#define S5P6442_GPH3_2_KP_ROW_2		(0x3 << 8)
#define S5P6442_GPH3_2_EXT_INT3_2	(0xf << 8)

#define S5P6442_GPH3_3_KP_ROW_3		(0x3 << 12)
#define S5P6442_GPH3_3_EXT_INT3_3	(0xf << 12)

#define S5P6442_GPH3_4_KP_ROW_4		(0x3 << 16)
#define S5P6442_GPH3_4_EXT_INT3_4	(0xf << 16)

#define S5P6442_GPH3_5_KP_ROW_5		(0x3 << 20)
#define S5P6442_GPH3_5_EXT_INT3_5	(0xf << 20)

#define S5P6442_GPH3_6_KP_ROW_6		(0x3 << 24)
#define S5P6442_GPH3_6_EXT_INT3_6	(0xf << 24)

#define S5P6442_GPH3_7_KP_ROW_7		(0x3 << 28)
#define S5P6442_GPH3_7_EXT_INT3_7	(0xf << 28)



/* GPJ0 */  
#define GPIO_KEY_COL0				S5P6442_GPJ0(0)
#define GPIO_KEY_COL0_STATE			1

#define GPIO_KEY_COL1				S5P6442_GPJ0(1)
#define GPIO_KEY_COL1_STATE			1

#define GPIO_KEY_COL2				S5P6442_GPJ0(2)
#define GPIO_KEY_COL2_STATE			1

#define GPIO_KEY_COL3				S5P6442_GPJ0(3)
#define GPIO_KEY_COL3_STATE			1

#define GPIO_FM_SCL_2_8V			S5P6442_GPJ0(4)
#define GPIO_FM_SCL_2_8V_STATE			2

#define GPIO_FM_SDA_2_8V			S5P6442_GPJ0(5)
#define GPIO_FM_SDA_2_8V__STATE			2


/* GPJ1 */  
#define GPIO_PHONE_ON				S5P6442_GPJ1(0)	
#define GPIO_PHONE_ON_STATE			1

#define GPIO_HAPTIC_EN				S5P6442_GPJ1(1)	
#define GPIO_HAPTIC_EN_STATE		1

#define GPIO_MLCD_ON				S5P6442_GPJ1(3)	
#define GPIO_MLCD_ON_STATE			1

#define GPIO_CAM_3M_nRST			S5P6442_GPJ1(5)	
#define GPIO_CAM_3M_nRST_STATE		1

/* GPJ2 */  // DPRAM Data
#define GPIO_CP_RST					S5P6442_GPJ2(0)	
#define GPIO_CP_RST_STATE			1

#define GPIO_CODEX_XTAL_EN			S5P6442_GPJ2(1) 	
#define GPIO_CODEX_XTAL_EN_STATE	1

#define GPIO_MICBIAS2_EN			S5P6442_GPJ2(2)
#define GPIO_MICBIAS2_EN_STATE		1

#define GPIO_TA_CURRENT_SEL_AP			S5P6442_GPJ2(3)	
#define GPIO_TA_CURRENT_SEL_AP_STATE	1

#define GPIO_FM_INT					S5P6442_GPJ2(4)	
#define GPIO_FM_INT_STATE			0xF

#define GPIO_FM_BUS_nRST			S5P6442_GPJ2(5)	
#define GPIO_FM_BUS_nRST_STATE		1

#define GPIO_BT_WAKE				S5P6442_GPJ2(6)	
#define GPIO_BT_WAKE_STATE			1

#define GPIO_WLAN_WAKE				S5P6442_GPJ2(7)	
#define GPIO_WLAN_WAKE_STATE		1

/* GPJ3 */  // DPRAM Data
#define GPIO_WLAN_BT_EN				S5P6442_GPJ3(0)	
#define GPIO_WLAN_BT_EN_STATE		1

#define GPIO_MIC_SEL				S5P6442_GPJ3(1)	
#define GPIO_MIC_SEL_STATE		1

#define GPIO_EAR_SEL				S5P6442_GPJ3(2)	
#define GPIO_EAR_SEL_STATE		1

#define GPIO_BOOT_MODE				S5P6442_GPJ3(3)	
#define GPIO_BOOT_MODE_STATE		0

#define GPIO_PS_OUT				S5P6442_GPJ3(4)	
#define GPIO_PS_OUT_STATE			0xF

#define GPIO_PS_EN				S5P6442_GPJ3(5)	
#define GPIO_PS_EN_STATE			1

#define GPIO_SENSOR_SDA				S5P6442_GPJ3(5)
#define GPIO_SENSOR_SDA_STATE			2

#define GPIO_SENSOR_SCL				S5P6442_GPJ3(6)
#define GPIO_SENSOR_SCL_STATE			2

#define GPIO_BT_nRST				S5P6442_GPJ3(7)
#define GPIO_BT_nRST_STATE			1

/* GPJ4 */ //DPRAM IF
#define GPIO_AP_PMIC_SDA			S5P6442_GPJ4(0)
#define GPIO_AP_PMIC_SDA_STATE		1

#define GPIO_AP_PMIC_SCL			S5P6442_GPJ4(3)
#define GPIO_AP_PMIC_SCL_STATE		1

#define GPIO_MSENSE_nRST			S5P6442_GPJ4(4)			// H: Active,	L: StandBy
#define GPIO_MSENSE_nRST_STATE		1

/* MP01 */
#define GPIO_DISPLAY_CS				S5P6442_MP01(1)
#define GPIO_DISPLAY_CS_STATE		1

#define GPIO_AP_NANDCS				S5P6442_MP01(2)
#define GPIO_AP_NANDCS_STATE		4

/* MP04 */	
#define GPIO_DISPLAY_CLK			S5P6442_MP04(1)
#define GPIO_DISPLAY_CLK_STATE		1

#define GPIO_DISPLAY_SI				S5P6442_MP04(3)
#define GPIO_DISPLAY_SI_STATE		1

#define GPIO_LCD_ID					S5P6442_MP04(4)
#define GPIO_LCD_ID_STATE			0

#define GPIO_HW_REV_MODE0			S5P6442_MP04(7)
#define GPIO_HW_REV_MODE0_STATE		0

/* MP05 */	
#define GPIO_HW_REV_MODE1			S5P6442_MP05(0)	// H: Codec,		L: CP
#define GPIO_HW_REV_MODE1_STATE		0

#define GPIO_HW_REV_MODE2			S5P6442_MP05(1)
#define GPIO_HW_REV_MODE2_STATE		0

#define GPIO_AP_SCL					S5P6442_MP05(2)
#define GPIO_AP_SCL_STATE			1

#define GPIO_AP_SDA					S5P6442_MP05(3)
#define GPIO_AP_SDA_STATE			1

#define GPIO_MLCD_RST				S5P6442_MP05(5)
#define GPIO_MLCD_RST_STATE			1

#if 0
#define GPIO_ROW(x) S5P6442_GPH3(x)
#define GPIO_COL(x) S5P6442_GPH2(x)
#else
#define GPIO_ROW(x) S5P6442_GPH3(x)
#define GPIO_COL(x) S5P6442_GPJ0(x)
#endif

/* temp defines to prevent build errors  */
#define GPIO_NAND_CLK				0
#define GPIO_NAND_CLK_STATE			1

#define GPIO_NAND_CMD				0
#define GPIO_NAND_CMD_STATE			1

#define GPIO_NAND_D_0				0
#define GPIO_NAND_D_0_STATE			1

#define GPIO_NAND_D_1				0
#define GPIO_NAND_D_1_STATE			1

#define GPIO_NAND_D_2				0
#define GPIO_NAND_D_2_STATE			1

#define GPIO_NAND_D_3				0
#define GPIO_NAND_D_3_STATE			1

#define GPIO_USB_SEL30				S5P6442_GPJ1(2)	
#define GPIO_USB_SEL30_STATE		1

#define GPIO_ADC_EN					0	
#define GPIO_ADC_EN_STATE			1

#define GPIO_EAR_ADC_SEL1			0
#define GPIO_EAR_ADC_SEL1_STATE		1

#define GPIO_EAR_ADC_SEL2			0
#define GPIO_EAR_ADC_SEL2_STATE		1

#define GPIO_MICBIAS_EN				0
#define GPIO_MICBIAS_EN_STATE		1

//#define GPIO_USB_SEL				S5P6442_MP04(0)
#define GPIO_USB_SEL				0
#define GPIO_USB_SEL_STATE			1

#endif	/* MACH_APOLLO_EMUL_H */

