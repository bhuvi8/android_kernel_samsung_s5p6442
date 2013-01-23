/*
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 *
 * S5P6442 camera interface GPIO configuration.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <plat/camport.h>

int s5p6442_fimc_setup_gpio(void)
{
	u32 gpio8, gpio5;
	int ret;

	gpio8 = S5P6442_GPE0(0);
	gpio5 = S5P6442_GPE1(0);

	ret = s3c_gpio_cfgall_range(gpio8, 8, S3C_GPIO_SFN(2),
				    S3C_GPIO_PULL_UP);
	if (ret)
		return ret;

	return s3c_gpio_cfgall_range(gpio5, 5, S3C_GPIO_SFN(2),
				     S3C_GPIO_PULL_UP);
}
