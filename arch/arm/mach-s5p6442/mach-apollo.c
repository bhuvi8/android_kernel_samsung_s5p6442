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

#include <linux/fb.h>
#include <linux/gpio.h>
#include <linux/gpio_keys.h>
#include <linux/i2c.h>
#include <linux/i2c-gpio.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/input/matrix_keypad.h>
#include <linux/kernel.h>
#include <linux/mfd/max8998.h>
#include <linux/serial_core.h>
#include <linux/types.h>

#include <linux/mtd/bml.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/onenand.h>
#include <linux/mtd/partitions.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/hardware/vic.h>

#include <mach/mach-apollo.h>
#include <mach/map.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
#include <mach/system.h>

#include <plat/cpu.h>
#include <plat/devs.h>
#include <plat/fb.h>
#include <plat/gpio-cfg.h>
#include <plat/iic.h>
#include <plat/keypad.h>
#include <plat/mfc.h>
#include <plat/onenand-core.h>
#include <plat/regs-fb-v4.h>
#include <plat/regs-serial.h>
#include <plat/s5p-time.h>
#include <plat/s5p6442.h>
#include <plat/sdhci.h>

#include <media/s5p_fimc.h>

/* Following are default values for UCON, ULCON and UFCON UART registers */
#define APOLLO_UCON_DEFAULT	(S3C2410_UCON_TXILEVEL |	\
				 S3C2410_UCON_RXILEVEL |	\
				 S3C2410_UCON_TXIRQMODE |	\
				 S3C2410_UCON_RXIRQMODE |	\
				 S3C2410_UCON_RXFIFO_TOI |	\
				 S3C2443_UCON_RXERR_IRQEN)

#define APOLLO_ULCON_DEFAULT	S3C2410_LCON_CS8

#define APOLLO_UFCON_DEFAULT	(S3C2410_UFCON_FIFOMODE |	\
				 S5PV210_UFCON_TXTRIG4 |	\
				 S5PV210_UFCON_RXTRIG4)

static struct s3c2410_uartcfg apollo_uartcfgs[] __initdata = {
	[0] = {
		.hwport		= 0,
		.flags		= 0,
		.ucon		= APOLLO_UCON_DEFAULT,
		.ulcon		= APOLLO_ULCON_DEFAULT,
		.ufcon		= APOLLO_UFCON_DEFAULT,
	},
	[1] = {
		.hwport		= 1,
		.flags		= 0,
		.ucon		= APOLLO_UCON_DEFAULT,
		.ulcon		= APOLLO_ULCON_DEFAULT,
		.ufcon		= APOLLO_UFCON_DEFAULT,
	},
	[2] = {
		.hwport		= 2,
		.flags		= 0,
		.ucon		= APOLLO_UCON_DEFAULT,
		.ulcon		= APOLLO_ULCON_DEFAULT,
		.ufcon		= APOLLO_UFCON_DEFAULT,
	},
};

static struct s3c_sdhci_platdata apollo_hsmmc0_pdata __initdata = {
	.cd_type		= S3C_SDHCI_CD_INTERNAL,
	.clk_type		= S3C_SDHCI_CLK_DIV_EXTERNAL,
	.max_width		= 8,
};

static struct s3c_sdhci_platdata apollo_hsmmc1_pdata __initdata = {
	.cd_type		= S3C_SDHCI_CD_INTERNAL,
	.clk_type		= S3C_SDHCI_CLK_DIV_EXTERNAL,
	.max_width		= 8,
};

static struct s3c_sdhci_platdata apollo_hsmmc2_pdata __initdata = {
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_NONE,
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

/* MAX8998 regulators */
#if defined(CONFIG_REGULATOR_MAX8998) || defined(CONFIG_REGULATOR_MAX8998_MODULE)

static struct regulator_consumer_supply apollo_ldo3_consumers[] = {
	REGULATOR_SUPPLY("vusb_a", "s3c-hsotg"),
};

static struct regulator_consumer_supply apollo_ldo5_consumers[] = {
	REGULATOR_SUPPLY("vmmc", "s3c-sdhci.0"),
};

static struct regulator_consumer_supply apollo_ldo8_consumers[] = {
	REGULATOR_SUPPLY("vusb_d", "s3c-hsotg"),
	REGULATOR_SUPPLY("vdd33a_dac", "s5p-sdo"),
};

static struct regulator_consumer_supply apollo_ldo11_consumers[] = {
	REGULATOR_SUPPLY("vddio", "0-0030"), /* "CAM_IO_2.8V" */
};

static struct regulator_consumer_supply apollo_ldo13_consumers[] = {
	REGULATOR_SUPPLY("vdda", "0-0030"), /* "CAM_A_2.8V" */
};

static struct regulator_consumer_supply apollo_ldo14_consumers[] = {
	REGULATOR_SUPPLY("vdd_core", "0-0030"), /* "CAM_CIF_1.8V" */
};

static struct regulator_init_data apollo_ldo2_data = {
	.constraints	= {
		.name		= "VALIVE_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.always_on	= 1,
		.state_mem	= {
			.enabled = 1,
		},
	},
};

static struct regulator_init_data apollo_ldo3_data = {
	.constraints	= {
		.name		= "VUSB+MIPI_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies = ARRAY_SIZE(apollo_ldo3_consumers),
	.consumer_supplies = apollo_ldo3_consumers,
};

static struct regulator_init_data apollo_ldo4_data = {
	.constraints	= {
		.name		= "VDAC_3.3V",
		.min_uV		= 3300000,
		.max_uV		= 3300000,
		.apply_uV	= 1,
	},
};

static struct regulator_init_data apollo_ldo5_data = {
	.constraints	= {
		.name		= "VTF_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies = ARRAY_SIZE(apollo_ldo5_consumers),
	.consumer_supplies = apollo_ldo5_consumers,
};

static struct regulator_init_data apollo_ldo6_data = {
	.constraints	= {
		.name		= "VCC_3.3V",
		.min_uV		= 3300000,
		.max_uV		= 3300000,
		.apply_uV	= 1,
	},
};

static struct regulator_init_data apollo_ldo7_data = {
	.constraints	= {
		.name		= "VLCD_1.8V",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.apply_uV	= 1,
		.always_on	= 1,
	},
};

static struct regulator_init_data apollo_ldo8_data = {
	.constraints	= {
		.name		= "VUSB+VADC_3.3V",
		.min_uV		= 3300000,
		.max_uV		= 3300000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies = ARRAY_SIZE(apollo_ldo8_consumers),
	.consumer_supplies = apollo_ldo8_consumers,
};

static struct regulator_init_data apollo_ldo9_data = {
	.constraints	= {
		.name		= "VCC+VCAM_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
	},
};

static struct regulator_init_data apollo_ldo10_data = {
	.constraints	= {
		.name		= "VPLL_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.boot_on	= 1,
	},
};

static struct regulator_init_data apollo_ldo11_data = {
	.constraints	= {
		.name		= "CAM_IO_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= ARRAY_SIZE(apollo_ldo11_consumers),
	.consumer_supplies	= apollo_ldo11_consumers,
};

static struct regulator_init_data apollo_ldo12_data = {
	.constraints	= {
		.name		= "CAM_ISP_1.2V",
		.min_uV		= 1200000,
		.max_uV		= 1200000,
		.apply_uV	= 1,
	},
};

static struct regulator_init_data apollo_ldo13_data = {
	.constraints	= {
		.name		= "CAM_A_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= ARRAY_SIZE(apollo_ldo13_consumers),
	.consumer_supplies	= apollo_ldo13_consumers,
};

static struct regulator_init_data apollo_ldo14_data = {
	.constraints	= {
		.name		= "CAM_CIF_1.8V",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= ARRAY_SIZE(apollo_ldo14_consumers),
	.consumer_supplies	= apollo_ldo14_consumers,
};

static struct regulator_init_data apollo_ldo15_data = {
	.constraints	= {
		.name		= "CAM_AF_3.3V",
		.min_uV		= 3300000,
		.max_uV		= 3300000,
		.apply_uV	= 1,
	},
};

static struct regulator_init_data apollo_ldo16_data = {
	.constraints	= {
		.name		= "VMIPI_1.8V",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.apply_uV	= 1,
	},
};

static struct regulator_init_data apollo_ldo17_data = {
	.constraints	= {
		.name		= "VCC_3.0V_LCD",
		.min_uV		= 3000000,
		.max_uV		= 3000000,
		.apply_uV	= 1,
		.always_on	= 1,
	},
};

/* BUCK */
static struct regulator_consumer_supply buck1_consumer =
	REGULATOR_SUPPLY("vddarm", NULL);

static struct regulator_consumer_supply buck2_consumer =
	REGULATOR_SUPPLY("vddint", NULL);

static struct regulator_consumer_supply buck3_consumer =
	REGULATOR_SUPPLY("vdet", "s5p-sdo");


static struct regulator_init_data apollo_buck1_data = {
	.constraints	= {
		.name		= "VARM_1.2V",
		.min_uV		= 1200000,
		.max_uV		= 1200000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
				  REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &buck1_consumer,
};

static struct regulator_init_data apollo_buck2_data = {
	.constraints	= {
		.name		= "VINT_1.2V",
		.min_uV		= 1200000,
		.max_uV		= 1200000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
				  REGULATOR_CHANGE_STATUS,
	},
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &buck2_consumer,
};

static struct regulator_init_data apollo_buck3_data = {
	.constraints	= {
		.name		= "VCC_1.8V",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.apply_uV	= 1,
		.state_mem	= {
			.enabled = 1,
		},
	},
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &buck3_consumer,
};

static struct regulator_init_data apollo_buck4_data = {
	.constraints	= {
		.name		= "CAM_CORE_1.2V",
		.min_uV		= 1200000,
		.max_uV		= 1200000,
		.apply_uV	= 1,
		.always_on	= 1,
	},
};

static struct max8998_regulator_data apollo_regulators[] = {
	{ MAX8998_LDO2,  &apollo_ldo2_data },
	{ MAX8998_LDO3,  &apollo_ldo3_data },
	{ MAX8998_LDO4,  &apollo_ldo4_data },
	{ MAX8998_LDO5,  &apollo_ldo5_data },
	{ MAX8998_LDO6,  &apollo_ldo6_data },
	{ MAX8998_LDO7,  &apollo_ldo7_data },
	{ MAX8998_LDO8,  &apollo_ldo8_data },
	{ MAX8998_LDO9,  &apollo_ldo9_data },
	{ MAX8998_LDO10, &apollo_ldo10_data },
	{ MAX8998_LDO11, &apollo_ldo11_data },
	{ MAX8998_LDO12, &apollo_ldo12_data },
	{ MAX8998_LDO13, &apollo_ldo13_data },
	{ MAX8998_LDO14, &apollo_ldo14_data },
	{ MAX8998_LDO15, &apollo_ldo15_data },
	{ MAX8998_LDO16, &apollo_ldo16_data },
	{ MAX8998_LDO17, &apollo_ldo17_data },
	{ MAX8998_BUCK1, &apollo_buck1_data },
	{ MAX8998_BUCK2, &apollo_buck2_data },
	{ MAX8998_BUCK3, &apollo_buck3_data },
	{ MAX8998_BUCK4, &apollo_buck4_data },
};

static struct max8998_platform_data apollo_max8998_pdata = {
	.num_regulators	= ARRAY_SIZE(apollo_regulators),
	.regulators	= apollo_regulators,
	.buck1_set1	= S5P6442_GPH0(2),
	.buck1_set2	= S5P6442_GPH0(3),
	.buck2_set3	= S5P6442_GPH0(4),
	.buck1_voltage1	= 1200000,
	.buck1_voltage2	= 1200000,
	.buck1_voltage3	= 1200000,
	.buck1_voltage4	= 1200000,
	.buck2_voltage1	= 1200000,
	.buck2_voltage2	= 1200000,
};
#endif

static int apollo_hw_rev_pin_value = -1;

static void check_hw_rev_pin(void)
{
	int data;
	apollo_hw_rev_pin_value = 0;

	// set gpio configuration
	s3c_gpio_cfgpin(GPIO_HW_REV_MODE2, GPIO_HW_REV_MODE2_STATE);
	s3c_gpio_cfgpin(GPIO_HW_REV_MODE1, GPIO_HW_REV_MODE1_STATE);
	s3c_gpio_cfgpin(GPIO_HW_REV_MODE0, GPIO_HW_REV_MODE0_STATE);

	data = gpio_get_value(GPIO_HW_REV_MODE2);
	if(data)
		apollo_hw_rev_pin_value |= (0x1<<2);
	data = gpio_get_value(GPIO_HW_REV_MODE1);
	if(data)
		apollo_hw_rev_pin_value |= (0x1<<1);
	data = gpio_get_value(GPIO_HW_REV_MODE0);
	if(data)
		apollo_hw_rev_pin_value |= (0x1<<0);
	
}

int apollo_get_hw_type(void)
{
	int type;

	switch(apollo_hw_rev_pin_value)
		{
		case 2:		// apollo rev0.4 (memory 4-2-1)
		case 6:		// apollo rev0.5
		case 4:		// apollo rev0.6
		case 5:		// apollo rev0.7
		case 7:		// apollo rev0.9b
			type = 0;
			break;
		case 3:		// apollo OPEN rev0.7
		case 1:		// apollo OPEN rev0.9b
		case 0:		// apollo OPEN rev1.0a
			type = 1;
			break;
		default:
			type = 0;
			break;
		}

	return type;
}
EXPORT_SYMBOL(apollo_get_hw_type);

int apollo_get_remapped_hw_rev_pin(void)
{
	int revision;

	switch(apollo_hw_rev_pin_value)
		{
		case 2:		// apollo rev0.4 (memory 4-2-1)
			revision = 2;
			break;
		case 6:		// apollo rev0.5
			revision = 3;
			break;
		case 4:		// apollo rev0.6
			revision = 4;
			break;
		case 5:		// apollo rev0.7
			revision = 5;
			break;
		case 7:		// apollo rev0.9b
			revision = 6;
			break;
		case 3:		// apollo OPEN rev0.7
			revision = 5;
			break;
		case 1:		// apollo OPEN rev0.9b
			revision = 6;
			break;
		case 0:		// apollo OPEN rev1.0a
			revision = 7;
			break;
		default:
			revision = 8;
			break;
		}

	return revision;
}

static struct i2c_board_info apollo_i2c_devs0[] __initdata = {
	{ I2C_BOARD_INFO("wm8994", 0x1b), },
};

static struct i2c_gpio_platform_data apollo_i2c_gpio_pmic_data = {
	.sda_pin	= S5P6442_GPJ4(0),	/* XMSMCSN */
	.scl_pin	= S5P6442_GPJ4(3),	/* XMSMIRQN */
};

static struct platform_device apollo_i2c_gpio_pmic = {
	.name		= "i2c-gpio",
	.id		= 4,
	.dev		= {
		.platform_data	= &apollo_i2c_gpio_pmic_data,
	},
};

static struct i2c_board_info i2c_gpio_pmic_devs[] __initdata = {
#if defined(CONFIG_REGULATOR_MAX8998) || defined(CONFIG_REGULATOR_MAX8998_MODULE)
	{
		/* 0xCC when SRAD = 0 */
		I2C_BOARD_INFO("max8998", 0xCC >> 1),
		.platform_data = &apollo_max8998_pdata,
	},
#endif
};

static void __init apollo_pmic_init(void)
{
	/* AP_PMIC_IRQ: EINT7 */
	s3c_gpio_cfgpin(S5P6442_GPH0(7), S3C_GPIO_SFN(0xf));
	s3c_gpio_setpull(S5P6442_GPH0(7), S3C_GPIO_PULL_UP);

	/* nPower: EINT22 */
	s3c_gpio_cfgpin(S5P6442_GPH2(6), S3C_GPIO_SFN(0xf));
	s3c_gpio_setpull(S5P6442_GPH2(6), S3C_GPIO_PULL_UP);
}


static struct i2c_gpio_platform_data i2c3_platdata = {
        .sda_pin                = GPIO_AP_SDA,
        .scl_pin                = GPIO_AP_SCL,
        .udelay                 = 2,    /* 250KHz */
        .sda_is_open_drain      = 0,
        .scl_is_open_drain      = 0,
        .scl_is_output_only     = 1,
};

static struct platform_device i2c3_gpio = {
        .name                           = "i2c-gpio",
        .id                                     = 3,
        .dev.platform_data      = &i2c3_platdata,
};

static struct i2c_gpio_platform_data i2c7_platdata = {
        .sda_pin                = GPIO_FM_SDA_2_8V,
        .scl_pin                = GPIO_FM_SCL_2_8V,
        .udelay                 = 2,           /*250KHz*/
	.sda_is_open_drain      = 0,
        .scl_is_open_drain      = 0,
        .scl_is_output_only     = 0,
};

static struct platform_device i2c7_gpio = {
        .name                           = "i2c-gpio",
        .id                                     = 7,
        .dev.platform_data      = &i2c7_platdata,
};

static struct i2c_gpio_platform_data i2c8_platdata = {
        .sda_pin                = GPIO_AP_SDA_2_8V,
        .scl_pin                = GPIO_AP_SCL_2_8V,
        .udelay                 = 2,           /*250KHz*/
	.sda_is_open_drain      = 0,
        .scl_is_open_drain      = 0,
        .scl_is_output_only     = 0,
};

static struct platform_device i2c8_gpio = {
        .name                           = "i2c-gpio",
        .id                                     = 8,
        .dev.platform_data      = &i2c8_platdata,
};

static struct i2c_gpio_platform_data i2c9_platdata = {
        .sda_pin                = GPIO_SENSOR_SDA,
        .scl_pin                = GPIO_SENSOR_SCL,
        .udelay                 = 2,           /*250KHz*/
	.sda_is_open_drain      = 0,
        .scl_is_open_drain      = 0,
        .scl_is_output_only     = 0,
};

static struct platform_device i2c9_gpio = {
        .name                	= "i2c-gpio",
        .id                   	= 9,
        .dev.platform_data      = &i2c9_platdata,
};

static void __init apollo_map_io(void)
{
	s5p_init_io(NULL, 0, S5P_VA_CHIPID);
	s3c24xx_init_clocks(12000000);
	s3c24xx_init_uarts(apollo_uartcfgs, ARRAY_SIZE(apollo_uartcfgs));
	s5p_set_timer_source(S5P_PWM3, S5P_PWM4);
}

static uint32_t apollo_keymap[] __initdata = {
	KEY(0, 3, KEY_1), KEY(0, 4, KEY_2), KEY(0, 5, KEY_3),
	KEY(0, 6, KEY_4), KEY(0, 7, KEY_5),
	KEY(1, 3, KEY_A), KEY(1, 4, KEY_B), KEY(1, 5, KEY_C),
	KEY(1, 6, KEY_D), KEY(1, 7, KEY_E)
};

static struct matrix_keymap_data apollo_keymap_data = {
	.keymap			= apollo_keymap,
	.keymap_size		= ARRAY_SIZE(apollo_keymap),
};

static struct samsung_keypad_platdata apollo_keypad_pdata __initdata = {
	.keymap_data		= &apollo_keymap_data,
	.rows			= 4,
	.cols			= 4,
	.no_autorepeat		= 1,
	.wakeup			= 1,
};

static struct gpio_keys_button apollo_gpio_keys_data[] = {
	{
		.gpio			= S5P6442_GPH2(6),
		.code			= KEY_POWER,
		.desc			= "Power",
		.active_low		= 1,
		.debounce_interval	= 5,
		.type			= EV_KEY,
		.wakeup			= 1,
	}, {
		.gpio			= S5P6442_GPH3(0),
		.code			= KEY_HOME,
		.desc			= "Home",
		.active_low		= 1,
		.debounce_interval	= 5,
		.type			= EV_KEY,
		.wakeup			= 1,
	}, {
		.gpio			= S5P6442_GPH3(4),
		.code			= KEY_VOLUMEUP,
		.desc			= "Volume Up",
		.active_low		= 1,
		.debounce_interval	= 5,
		.type			= EV_KEY,
		.wakeup			= 1,
	}, {
		.gpio			= S5P6442_GPH3(5),
		.code			= KEY_VOLUMEDOWN,
		.desc			= "Volume Down",
		.active_low		= 1,
		.debounce_interval	= 5,
		.type			= EV_KEY,
		.wakeup			= 1,
	}, {
		.gpio			= S5P6442_GPH3(6),
		.code			= KEY_BACK,
		.desc			= "Back",
		.active_low		= 1,
		.debounce_interval	= 5,
		.type			= EV_KEY,
		.wakeup			= 1,
	}, {
		.gpio			= S5P6442_GPH3(7),
		.code			= KEY_MENU,
		.desc			= "Menu",
		.active_low		= 1,
		.debounce_interval	= 5,
		.type			= EV_KEY,
		.wakeup			= 1,
	},  
};

static struct gpio_keys_platform_data apollo_gpio_keys_pdata = {
	.buttons		= apollo_gpio_keys_data,
	.nbuttons		= ARRAY_SIZE(apollo_gpio_keys_data),
};

static struct platform_device apollo_gpio_keys = {
	.name			= "gpio-keys",
	.id			= 0,
	.num_resources		= 0,
	.dev			= {
				.platform_data	= &apollo_gpio_keys_pdata,
				}
};

static struct s3c_fb_pd_win apollo_fb_win0 = {
	.win_mode = {
		.left_margin	= 13,
		.right_margin	= 8,
		.upper_margin	= 7,
		.lower_margin	= 5,
		.hsync_len	= 3,
		.vsync_len	= 1,
		.xres		= 240,
		.yres		= 400,
	},
	.max_bpp	= 32,
	.default_bpp	= 24,
};

static struct s3c_fb_platdata apollo_lcd0_pdata __initdata = {
	.win[0]		= &apollo_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
	.setup_gpio	= s5p6442_fb_gpio_setup_24bpp,
};

static struct platform_device *apollo_devices[] __initdata = {
	&s3c_device_i2c0,
	&s3c_device_i2c1,
	&s3c_device_i2c2,
	&i2c3_gpio,
	&apollo_i2c_gpio_pmic,
	&i2c7_gpio,
	&i2c8_gpio,
	&i2c9_gpio,


	&samsung_asoc_dma,
	&s5p6442_device_iis0,
	&s3c_device_wdt,
	&s3c_device_rtc,

	&s3c_device_hsmmc0,
	&s3c_device_hsmmc1,		// SDIO for WLAN
	&s3c_device_hsmmc2,

	&samsung_device_keypad,
	&apollo_gpio_keys,

	&s5p_device_fimc0,
	&s5p_device_fimc1,
	&s5p_device_fimc2,
	&s5p_device_jpeg,
	&s3c_device_fb,
	&s5p_device_mfc,
	&s5p_device_mfc_l,
	&s5p_device_mfc_r,

	&s5p_device_onenand,
	&apollo_bml_device,
};

static void __init apollo_machine_init(void)
{
	check_hw_rev_pin();
	s3c_i2c0_set_platdata(NULL);
	s3c_i2c1_set_platdata(NULL);
	s3c_i2c2_set_platdata(NULL);
	i2c_register_board_info(0, apollo_i2c_devs0,
			ARRAY_SIZE(apollo_i2c_devs0));

	apollo_pmic_init();
	i2c_register_board_info(4, i2c_gpio_pmic_devs,
			ARRAY_SIZE(i2c_gpio_pmic_devs));

	s3c_sdhci0_set_platdata(&apollo_hsmmc0_pdata);
	s3c_sdhci1_set_platdata(&apollo_hsmmc1_pdata);
	s3c_sdhci2_set_platdata(&apollo_hsmmc2_pdata);

	s3c_fb_set_platdata(&apollo_lcd0_pdata);

	samsung_keypad_set_platdata(&apollo_keypad_pdata);

	platform_add_devices(apollo_devices, ARRAY_SIZE(apollo_devices));

	printk("%s : hw_rev_pin=0x%x\n", __func__, apollo_hw_rev_pin_value);
	printk("%s : bootmode=0x%x\n", __func__, gpio_get_value(GPIO_BOOT_MODE));
	printk("%s : lcd_id=%d\n", __func__, gpio_get_value(GPIO_LCD_ID));
	printk("%s : uart_sel=%i\n", __func__, gpio_get_value(GPIO_UART_SEL));

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
	.restart	= s5p6442_restart,
MACHINE_END

