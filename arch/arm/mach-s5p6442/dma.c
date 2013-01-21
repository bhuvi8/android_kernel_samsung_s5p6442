/*
 * Copyright (C) 2010 Samsung Electronics Co. Ltd.
 *	Jaswinder Singh <jassi.brar@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/platform_device.h>
#include <linux/dma-mapping.h>

#include <plat/devs.h>
#include <plat/irqs.h>

#include <mach/map.h>
#include <mach/irqs.h>
#include <mach/dma.h>

//#include <plat/s3c-pl330-pdata.h>
#include <linux/amba/pl330.h>

static u64 dma_dmamask = DMA_BIT_MASK(32);

static struct resource s5p6442_pdma_resource[] = {
	[0] = {
		.start  = S5P6442_PA_PDMA,
		.end    = S5P6442_PA_PDMA + SZ_4K,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_PDMA0,
		.end	= IRQ_PDMA0,
		.flags	= IORESOURCE_IRQ,
	},
};

static u8 s5p6442_pdma_peri[] = {
	DMACH_UART0_RX,
	DMACH_UART0_TX,
	DMACH_UART1_RX,
	DMACH_UART1_TX,
	DMACH_UART2_RX,
	DMACH_UART2_TX,
	DMACH_UART3_RX,
	DMACH_UART3_TX,
	DMACH_MAX,
	DMACH_MAX,
	DMACH_PCM0_TX,
	DMACH_PCM0_RX,
	DMACH_I2S0_TX,
	DMACH_I2S0_RX,
	DMACH_SPI0_TX,
	DMACH_SPI0_RX,
	DMACH_MAX,
	DMACH_MAX,
	DMACH_MAX,
	DMACH_MAX,
	DMACH_SPI1_TX,
	DMACH_SPI1_RX,
};

static struct dma_pl330_platdata s5p6442_pdma_pdata = {
	.nr_valid_peri = ARRAY_SIZE(s5p6442_pdma_peri),
	.peri_id = s5p6442_pdma_peri,
};

static struct platform_device s5p6442_device_pdma = {
	.name		= "s3c-pl330",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s5p6442_pdma_resource),
	.resource	= s5p6442_pdma_resource,
	.dev		= {
		.dma_mask = &dma_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platform_data = &s5p6442_pdma_pdata,
	},
};

static struct platform_device *s5p6442_dmacs[] __initdata = {
	&s5p6442_device_pdma,
};

static int __init s5p6442_dma_init(void)
{
	platform_add_devices(s5p6442_dmacs, ARRAY_SIZE(s5p6442_dmacs));

	return 0;
}
arch_initcall(s5p6442_dma_init);
