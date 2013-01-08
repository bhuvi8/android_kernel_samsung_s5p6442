/* linux/arch/arm/mach-s5p6442/mach-apollo.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Maintainers: Mark Kennard	<komcomputers@gmail.com>
 *		Miki Dahab	<codermoikop@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/i2c.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/onenand.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/bml.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/hardware/vic.h>

#include <mach/map.h>
#include <mach/regs-clock.h>

#include <plat/regs-serial.h>
#include <plat/s5p6442.h>
#include <plat/devs.h>
#include <plat/gpio-cfg.h>
#include <plat/cpu.h>
#include <plat/iic.h>
#include <plat/s5p-time.h>
#include <plat/sdhci.h>
#include <plat/onenand-core.h>

#include <media/s5p_fimc.h>

/* Following are default values for UCON, ULCON and UFCON UART registers */
#define apollo_UCON_DEFAULT	(S3C2410_UCON_TXILEVEL |	\
				 S3C2410_UCON_RXILEVEL |	\
				 S3C2410_UCON_TXIRQMODE |	\
				 S3C2410_UCON_RXIRQMODE |	\
				 S3C2410_UCON_RXFIFO_TOI |	\
				 S3C2443_UCON_RXERR_IRQEN)

#define apollo_ULCON_DEFAULT	S3C2410_LCON_CS8

#define apollo_UFCON_DEFAULT	(S3C2410_UFCON_FIFOMODE |	\
				 S5PV210_UFCON_TXTRIG4 |	\
				 S5PV210_UFCON_RXTRIG4)

static struct s3c2410_uartcfg apollo_uartcfgs[] __initdata = {
	[0] = {
		.hwport		= 0,
		.flags		= 0,
		.ucon		= apollo_UCON_DEFAULT,
		.ulcon		= apollo_ULCON_DEFAULT,
		.ufcon		= apollo_UFCON_DEFAULT,
	},
	[1] = {
		.hwport		= 1,
		.flags		= 0,
		.ucon		= apollo_UCON_DEFAULT,
		.ulcon		= apollo_ULCON_DEFAULT,
		.ufcon		= apollo_UFCON_DEFAULT,
	},
	[2] = {
		.hwport		= 2,
		.flags		= 0,
		.ucon		= apollo_UCON_DEFAULT,
		.ulcon		= apollo_ULCON_DEFAULT,
		.ufcon		= apollo_UFCON_DEFAULT,
	},
};

static struct mtd_partition apollo_onenand_partitions[] = {
	{
		.name		= "kernel",
		.offset		= (40 * SZ_256K),
		.size		= (30 * SZ_256K),
	},
	{
		.name		= "system",
		.offset		= MTDPART_OFS_APPEND,
		.size		= (CONFIG_APOLLO_MTD_SYSTEM_SZ * SZ_256K),
	},
	{
		.name		= "data",
		.offset		= MTDPART_OFS_APPEND,
		.size		= (CONFIG_APOLLO_MTD_DATA_SZ * SZ_256K),
	},
	{
		.name		= "cache",
		.offset		= MTDPART_OFS_APPEND,
		.size		= (CONFIG_APOLLO_MTD_CACHE_SZ * SZ_256K),
	},
};

static struct s3c_sdhci_platdata apollo_hsmmc0_pdata __initdata = {
	.cd_type		= S3C_SDHCI_CD_INTERNAL,
	.clk_type		= S3C_SDHCI_CLK_DIV_INTERNAL,
	.max_width		= 8,
};

static struct s3c_sdhci_platdata apollo_hsmmc1_pdata __initdata = {
	.cd_type		= S3C_SDHCI_CD_INTERNAL,
	.clk_type		= S3C_SDHCI_CLK_DIV_INTERNAL,
	.max_width		= 8,
};

static struct onenand_platform_data apollo_onenand_pdata = {
	.parts			= apollo_onenand_partitions,
	.nr_parts		= ARRAY_SIZE(apollo_onenand_partitions),
};

static struct platform_device apollo_onenand_device = {
	.name			= "mtd-onenand",
	.id			= -1,
	.dev			= {
				.platform_data = &apollo_onenand_pdata,
	},
};

static struct bml_partition apollo_bml_partitions[] = {
	{
		.name		= "kernel",
		.offset		= (40 * SZ_256K),
	}
};

static struct bml_platform_data apollo_bml_pdata = {
	.parts			= apollo_bml_partitions,
	.nr_parts		= ARRAY_SIZE(apollo_bml_partitions),
};

static struct platform_device apollo_bml_device = {
	.name			= "mtd-bml",
	.id			= -1,
	.dev			= {
				.platform_data = &apollo_bml_pdata,
	},
};

static struct platform_device *apollo_devices[] __initdata = {
	&s3c_device_i2c0,
	&samsung_asoc_dma,
	&s5p6442_device_iis0,
	&s3c_device_wdt,
	&s3c_device_rtc,

	&s3c_device_hsmmc0,
	&s3c_device_hsmmc1,		// SDIO for WLAN

	&s5p_device_fimc0,
	&s5p_device_fimc1,
	&s5p_device_fimc2,
	&s5p_device_jpeg,
	&s3c_device_fb,

	&s5p_device_onenand,
	&apollo_onenand_device,
	&apollo_bml_device,
};

static struct i2c_board_info apollo_i2c_devs0[] __initdata = {
	{ I2C_BOARD_INFO("wm8994", 0x1b), },
};

static void __init apollo_map_io(void)
{
	s5p_init_io(NULL, 0, S5P_VA_CHIPID);
	s3c24xx_init_clocks(12000000);
	s3c24xx_init_uarts(apollo_uartcfgs, ARRAY_SIZE(apollo_uartcfgs));
	s5p_set_timer_source(S5P_PWM3, S5P_PWM4);
}

static void __init apollo_machine_init(void)
{
	s3c_i2c0_set_platdata(NULL);
	i2c_register_board_info(0, apollo_i2c_devs0,
			ARRAY_SIZE(apollo_i2c_devs0));
	s3c_set_platdata(&apollo_onenand_pdata, sizeof(apollo_onenand_pdata),
			&s5p_device_onenand);
	platform_add_devices(apollo_devices, ARRAY_SIZE(apollo_devices));

	s3c_sdhci0_set_platdata(&apollo_hsmmc0_pdata);
	s3c_sdhci1_set_platdata(&apollo_hsmmc1_pdata);
}

static void __init apollo_fixup(struct tag *tags, char **cmdline,
	struct meminfo *mi)
{
	mi->nr_banks = 2;
	mi->bank[0].start = PHYS_OFFSET;
	mi->bank[0].size = PHYS_SIZE_DDR;

	mi->bank[1].start = PHYS_OFFSET_ONEDRAM;
	mi->bank[1].size = PHYS_SIZE_ONEDRAM;
}

MACHINE_START(APOLLO, "APOLLO")
	.atag_offset	= 0x100,

	.fixup		= apollo_fixup,

	.init_irq	= s5p6442_init_irq,
	.handle_irq	= vic_handle_irq,
	.map_io		= apollo_map_io,
	.init_machine	= apollo_machine_init,
	.timer		= &s5p_timer,
MACHINE_END

