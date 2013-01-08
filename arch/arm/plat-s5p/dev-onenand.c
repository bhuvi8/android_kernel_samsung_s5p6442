/* linux/arch/arm/plat-s5p/dev-onenand.c
 *
 * Copyright 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 *  Copyright (c) 2008-2010 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 * S5P series device definition for OneNAND devices
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/platform_device.h>

#include <asm/irq.h>
#include <mach/map.h>

#define SZ_1K                           0x00000400
#define SZ_2K                           0x00000800
#define SZ_4K                           0x00001000
#define SZ_8K                           0x00002000
#define SZ_16K                          0x00004000
#define SZ_32K                          0x00008000
#define SZ_64K                          0x00010000
#define SZ_128K                         0x00020000
#define SZ_256K                         0x00040000
#define SZ_512K                         0x00080000

static struct resource s5p_onenand_resources[] = {
	[0] = {
		.start	= S5P_PA_ONENAND,
		.end	= S5P_PA_ONENAND + SZ_128K - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= S5P_PA_ONENAND_DMA,
		.end	= S5P_PA_ONENAND_DMA + SZ_8K - 1,
		.flags	= IORESOURCE_MEM,
	},
	[2] = {
		.start	= IRQ_ONENAND_AUDI,
		.end	= IRQ_ONENAND_AUDI,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device s5p_device_onenand = {
	.name		= "s5p-onenand",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s5p_onenand_resources),
	.resource	= s5p_onenand_resources,
};
