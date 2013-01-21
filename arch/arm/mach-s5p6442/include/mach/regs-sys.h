/* arch/arm/mach-s5p6442/include/mach/regs-sys.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5PV210 - System registers definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#define S5P6442_USB_PHY_CON	(S3C_VA_SYS + 0xE80C)
#define S5P6442_USB_PHY0_EN	(1 << 0)
#define S5P6442_USB_PHY1_EN	(1 << 1)

#define S3C64XX_OTHERS		(S3C_VA_SYS + 0x900)
#define S3C64XX_OTHERS_USBMASK	(1 << 16)

