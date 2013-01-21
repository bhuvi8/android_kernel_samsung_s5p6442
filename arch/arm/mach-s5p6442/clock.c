/* linux/arch/arm/mach-s5p6442/clock.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5P6442 - Clock support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/io.h>

#include <mach/map.h>

#include <plat/cpu-freq.h>
#include <mach/regs-clock.h>
#include <plat/clock.h>
#include <plat/cpu.h>
#include <plat/pll.h>
#include <plat/s5p-clock.h>
#include <plat/clock-clksrc.h>
#include <plat/s5p6442.h>

#define GET_DIV(clk, field) ((((clk) & field##_MASK) >> field##_SHIFT) + 1)

static struct clksrc_clk clk_mout_apll = {
	.clk	= {
		.name		= "mout_apll",
		.id		= -1,
	},
	.sources	= &clk_src_apll,
	.reg_src	= { .reg = S5P_CLK_SRC0, .shift = 0, .size = 1 },
};

static struct clksrc_clk clk_mout_mpll = {
	.clk = {
		.name		= "mout_mpll",
		.id		= -1,
	},
	.sources	= &clk_src_mpll,
	.reg_src	= { .reg = S5P_CLK_SRC0, .shift = 4, .size = 1 },
};

static struct clksrc_clk clk_mout_epll = {
	.clk	= {
		.name		= "mout_epll",
		.id		= -1,
	},
	.sources	= &clk_src_epll,
	.reg_src	= { .reg = S5P_CLK_SRC0, .shift = 8, .size = 1 },
};

/* Possible clock sources for ARM Mux */
static struct clk *clk_src_arm_list[] = {
	[1] = &clk_mout_apll.clk,
	[2] = &clk_mout_mpll.clk,
};

static struct clksrc_sources clk_src_arm = {
	.sources	= clk_src_arm_list,
	.nr_sources	= ARRAY_SIZE(clk_src_arm_list),
};

static struct clksrc_clk clk_mout_arm = {
	.clk	= {
		.name		= "mout_arm",
		.id		= -1,
	},
	.sources	= &clk_src_arm,
	.reg_src	= { .reg = S5P_CLK_MUX_STAT0, .shift = 16, .size = 3 },
};

static struct clk clk_dout_a2m = {
	.name		= "dout_a2m",
	.id		= -1,
	.parent		= &clk_mout_apll.clk,
};

/* Possible clock sources for D0 Mux */
static struct clk *clk_src_d0_list[] = {
	[1] = &clk_mout_mpll.clk,
	[2] = &clk_dout_a2m,
};

static struct clksrc_sources clk_src_d0 = {
	.sources	= clk_src_d0_list,
	.nr_sources	= ARRAY_SIZE(clk_src_d0_list),
};

static struct clksrc_clk clk_mout_d0 = {
	.clk = {
		.name		= "mout_d0",
		.id		= -1,
	},
	.sources	= &clk_src_d0,
	.reg_src	= { .reg = S5P_CLK_MUX_STAT0, .shift = 20, .size = 3 },
};

static struct clk clk_dout_apll = {
	.name		= "dout_apll",
	.id		= -1,
	.parent		= &clk_mout_arm.clk,
};

/* Possible clock sources for D0SYNC Mux */
static struct clk *clk_src_d0sync_list[] = {
	[1] = &clk_mout_d0.clk,
	[2] = &clk_dout_apll,
};

static struct clksrc_sources clk_src_d0sync = {
	.sources	= clk_src_d0sync_list,
	.nr_sources	= ARRAY_SIZE(clk_src_d0sync_list),
};

static struct clksrc_clk clk_mout_d0sync = {
	.clk	= {
		.name		= "mout_d0sync",
		.id		= -1,
	},
	.sources	= &clk_src_d0sync,
	.reg_src	= { .reg = S5P_CLK_MUX_STAT1, .shift = 28, .size = 3 },
};

/* Possible clock sources for D1 Mux */
static struct clk *clk_src_d1_list[] = {
	[1] = &clk_mout_mpll.clk,
	[2] = &clk_dout_a2m,
};

static struct clksrc_sources clk_src_d1 = {
	.sources	= clk_src_d1_list,
	.nr_sources	= ARRAY_SIZE(clk_src_d1_list),
};

static struct clksrc_clk clk_mout_d1 = {
	.clk	= {
		.name		= "mout_d1",
		.id		= -1,
	},
	.sources	= &clk_src_d1,
	.reg_src	= { .reg = S5P_CLK_MUX_STAT0, .shift = 24, .size = 3 },
};

/* Possible clock sources for D1SYNC Mux */
static struct clk *clk_src_d1sync_list[] = {
	[1] = &clk_mout_d1.clk,
	[2] = &clk_dout_apll,
};

static struct clksrc_sources clk_src_d1sync = {
	.sources	= clk_src_d1sync_list,
	.nr_sources	= ARRAY_SIZE(clk_src_d1sync_list),
};

static struct clksrc_clk clk_mout_d1sync = {
	.clk	= {
		.name		= "mout_d1sync",
		.id		= -1,
	},
	.sources	= &clk_src_d1sync,
	.reg_src	= { .reg = S5P_CLK_MUX_STAT1, .shift = 24, .size = 3 },
};

static struct clk clk_hclkd0 = {
	.name		= "hclkd0",
	.id		= -1,
	.parent		= &clk_mout_d0sync.clk,
};

static struct clk clk_hclkd1 = {
	.name		= "hclkd1",
	.id		= -1,
	.parent		= &clk_mout_d1sync.clk,
};

static struct clk clk_pclkd0 = {
	.name		= "pclkd0",
	.id		= -1,
	.parent		= &clk_hclkd0,
};

static struct clk clk_pclkd1 = {
	.name		= "pclkd1",
	.id		= -1,
	.parent		= &clk_hclkd1,
};

int s5p6442_clk_ip0_ctrl(struct clk *clk, int enable)
{
	return s5p_gatectrl(S5P_CLKGATE_IP0, clk, enable);
}

int s5p6442_clk_ip1_ctrl(struct clk *clk, int enable)
{
	return s5p_gatectrl(S5P_CLKGATE_IP1, clk, enable);
}

int s5p6442_clk_ip2_ctrl(struct clk *clk, int enable)
{
	return s5p_gatectrl(S5P_CLKGATE_IP2, clk, enable);
}

int s5p6442_clk_ip3_ctrl(struct clk *clk, int enable)
{
	return s5p_gatectrl(S5P_CLKGATE_IP3, clk, enable);
}

int s5p6442_clk_mask0_ctrl(struct clk *clk, int enable)
{
	return s5p_gatectrl(S5P_CLK_SRC_MASK0, clk, enable);
}

int s5p6442_clk_mask1_ctrl(struct clk *clk, int enable)
{
	return s5p_gatectrl(S5P_CLK_SRC_MASK1, clk, enable);
}

static struct clksrc_clk clksrcs[] = {
	{
		.clk	= {
			.name		= "dout_a2m",
			.id		= -1,
			.parent		= &clk_mout_apll.clk,
		},
		.sources = &clk_src_apll,
		.reg_src = { .reg = S5P_CLK_SRC0, .shift = 0, .size = 1 },
		.reg_div = { .reg = S5P_CLK_DIV0, .shift = 4, .size = 3 },
	}, {
		.clk	= {
			.name		= "dout_apll",
			.id		= -1,
			.parent		= &clk_mout_arm.clk,
		},
		.sources = &clk_src_arm,
		.reg_src = { .reg = S5P_CLK_MUX_STAT0, .shift = 16, .size = 3 },
		.reg_div = { .reg = S5P_CLK_DIV0, .shift = 0, .size = 3 },
	}, {
		.clk	= {
			.name		= "hclkd1",
			.id		= -1,
			.parent		= &clk_mout_d1sync.clk,
		},
		.sources = &clk_src_d1sync,
		.reg_src = { .reg = S5P_CLK_MUX_STAT1, .shift = 24, .size = 3 },
		.reg_div = { .reg = S5P_CLK_DIV0, .shift = 24, .size = 4 },
	}, {
		.clk	= {
			.name		= "hclkd0",
			.id		= -1,
			.parent		= &clk_mout_d0sync.clk,
		},
		.sources = &clk_src_d0sync,
		.reg_src = { .reg = S5P_CLK_MUX_STAT1, .shift = 28, .size = 3 },
		.reg_div = { .reg = S5P_CLK_DIV0, .shift = 16, .size = 4 },
	}, {
		.clk	= {
			.name		= "pclkd0",
			.id		= -1,
			.parent		= &clk_hclkd0,
		},
		.sources = &clk_src_d0sync,
		.reg_src = { .reg = S5P_CLK_MUX_STAT1, .shift = 28, .size = 3 },
		.reg_div = { .reg = S5P_CLK_DIV0, .shift = 20, .size = 3 },
	}, {
		.clk	= {
			.name		= "pclkd1",
			.id		= -1,
			.parent		= &clk_hclkd1,
		},
		.sources = &clk_src_d1sync,
		.reg_src = { .reg = S5P_CLK_MUX_STAT1, .shift = 24, .size = 3 },
		.reg_div = { .reg = S5P_CLK_DIV0, .shift = 28, .size = 3 },
	}
};

static struct clk clk_hsmmc0 = {
	.name		= "hsmmc",
	.devname	= "s3c-sdhci.0",
	.parent		= &clk_mout_d1.clk,
	.enable		= s5p6442_clk_ip2_ctrl,
	.ctrlbit	= (1<<16),
};

static struct clk clk_hsmmc1 = {
	.name		= "hsmmc",
	.devname	= "s3c-sdhci.1",
	.parent		= &clk_mout_d1.clk,
	.enable		= s5p6442_clk_ip2_ctrl,
	.ctrlbit	= (1<<17),
};

static struct clk clk_hsmmc2 = {
	.name		= "hsmmc",
	.devname	= "s3c-sdhci.2",
	.parent		= &clk_mout_d1.clk,
	.enable		= s5p6442_clk_ip2_ctrl,
	.ctrlbit	= (1<<18),
};

static struct clk *clkset_group2_list[] = {
	[6] = &clk_mout_mpll.clk,
	[7] = &clk_mout_epll.clk,
};

static struct clksrc_sources clkset_group2 = {
	.sources	= clkset_group2_list,
	.nr_sources	= ARRAY_SIZE(clkset_group2_list),
};

static struct clksrc_clk clk_sclk_mmc0 = {
	.clk		= {
		.name		= "sclk_mmc",
		.devname	= "s3c-sdhci.0",
		.enable		= s5p6442_clk_mask0_ctrl,
		.ctrlbit	= (1 << 8),
	},
	.sources = &clkset_group2,
	.reg_src = { .reg = S5P_CLK_SRC4, .shift = 0, .size = 4 },
	.reg_div = { .reg = S5P_CLK_DIV4, .shift = 0, .size = 4 },
};

static struct clksrc_clk clk_sclk_mmc1 = {
	.clk		= {
		.name		= "sclk_mmc",
		.devname	= "s3c-sdhci.1",
		.enable		= s5p6442_clk_mask0_ctrl,
		.ctrlbit	= (1 << 9),
	},
	.sources = &clkset_group2,
	.reg_src = { .reg = S5P_CLK_SRC4, .shift = 4, .size = 4 },
	.reg_div = { .reg = S5P_CLK_DIV4, .shift = 4, .size = 4 },
};

static struct clksrc_clk clk_sclk_mmc2 = {
	.clk		= {
		.name		= "sclk_mmc",
		.devname	= "s3c-sdhci.2",
		.enable		= s5p6442_clk_mask0_ctrl,
		.ctrlbit	= (1 << 10),
	},
	.sources = &clkset_group2,
	.reg_src = { .reg = S5P_CLK_SRC4, .shift = 8, .size = 4 },
	.reg_div = { .reg = S5P_CLK_DIV4, .shift = 8, .size = 4 },
};

/* Clock initialisation code */
static struct clksrc_clk *init_parents[] = {
	&clk_mout_apll,
	&clk_mout_mpll,
	&clk_mout_epll,
	&clk_mout_arm,
	&clk_mout_d0,
	&clk_mout_d0sync,
	&clk_mout_d1,
	&clk_mout_d1sync,
	&clk_sclk_mmc0,
};

void __init_or_cpufreq s5p6442_setup_clocks(void)
{
	struct clk *pclkd0_clk;
	struct clk *pclkd1_clk;

	unsigned long xtal;
	unsigned long arm;
	unsigned long hclkd0 = 0;
	unsigned long hclkd1 = 0;
	unsigned long pclkd0 = 0;
	unsigned long pclkd1 = 0;

	unsigned long apll;
	unsigned long mpll;
	unsigned long epll;
	unsigned int ptr;

	u32 clkdiv0;

	printk(KERN_DEBUG "%s: registering clocks\n", __func__);

	xtal = clk_get_rate(&clk_xtal);

	printk(KERN_DEBUG "%s: xtal is %ld\n", __func__, xtal);

	apll = s5p_get_pll45xx(xtal, __raw_readl(S5P_APLL_CON), pll_4502);
	mpll = s5p_get_pll45xx(xtal, __raw_readl(S5P_MPLL_CON), pll_4502);
	epll = s5p_get_pll45xx(xtal, __raw_readl(S5P_EPLL_CON), __raw_readl(S5P_EPLL_CON_K));

	clkdiv0 = __raw_readl(S5P_CLK_DIV0);
	printk(KERN_INFO "%s: clkdiv0 = %08x\n", __func__, clkdiv0);

	printk(KERN_INFO "S5P6442: PLL settings, A=%ld, M=%ld, E=%ld\n",
			apll, mpll, epll);

	clk_fout_apll.rate = apll;
	clk_fout_mpll.rate = mpll;
	clk_fout_epll.rate = epll;

	for (ptr = 0; ptr < ARRAY_SIZE(init_parents); ptr++)
		s3c_set_clksrc(init_parents[ptr], true);

	for (ptr = 0; ptr < ARRAY_SIZE(clksrcs); ptr++)
		s3c_set_clksrc(&clksrcs[ptr], true);

	arm = clk_get_rate(&clk_dout_apll);
	hclkd0 = clk_get_rate(&clk_hclkd0);
	hclkd1 = clk_get_rate(&clk_hclkd1);

	pclkd0_clk = clk_get(NULL, "pclkd0");
	BUG_ON(IS_ERR(pclkd0_clk));

	//pclkd0 = clk_get_rate(pclkd0_clk); <- why does this code give me 166MHz but the code below gives me the correct 83MHz?
	pclkd0 = hclkd0 / GET_DIV(clkdiv0, S5P_CLKDIV0_P0CLK);
	clk_put(pclkd0_clk);

	pclkd1_clk = clk_get(NULL, "pclkd1");
	BUG_ON(IS_ERR(pclkd1_clk));

	//pclkd1 = clk_get_rate(pclkd1_clk);
	pclkd1 = hclkd1 / GET_DIV(clkdiv0, S5P_CLKDIV0_P1CLK);
	clk_put(pclkd1_clk);

	printk(KERN_INFO "S5P6442: HCLKD0=%ld, HCLKD1=%ld, PCLKD0=%ld, PCLKD1=%ld\n",
			hclkd0, hclkd1, pclkd0, pclkd1);

	/* For backward compatibility */
	clk_f.rate = arm;
	clk_h.rate = hclkd1;
	clk_p.rate = pclkd1;

	clk_pclkd0.rate = pclkd0;
	clk_pclkd1.rate = pclkd1;
}

static struct clk init_clocks_off[] = {
	{
		.name		= "pdma",
		.id		= -1,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip0_ctrl,
		.ctrlbit	= (1 << 3),
	},{
		.name		= "mfc",
		.devname	= "s5p-mfc",
		.id		= -1,
		.parent		= &clk_hclkd1,
		.enable		= s5p6442_clk_ip0_ctrl,
		.ctrlbit	= (1 << 16),
	},
};

static struct clk init_clocks[] = {
	{
		.name           = "jpeg",
		.id             = -1,
		.parent         = &clk_hclkd0,
		.enable         = s5p6442_clk_ip0_ctrl,
		.ctrlbit        = (1 << 28),
	}, {
		.name           = "lcd",
		.id             = -1,
		.parent         = &clk_hclkd1,
		.enable         = s5p6442_clk_ip1_ctrl,
		.ctrlbit        = (1 << 0),
	}, {
		.name		= "rtc",
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 15),
	}, {
		.name		= "systimer",
		.id		= -1,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 16),
	}, {
		.name		= "uart",
		.id		= 0,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 17),
	}, {
		.name		= "uart",
		.id		= 1,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 18),
	}, {
		.name		= "uart",
		.id		= 2,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 19),
	}, {
		.name		= "i2c",
		.id		= 0,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 7),
	}, {
		.name		= "i2c",
		.id		= 1,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 5),
	}, {
		.name		= "i2c",
		.id		= 2,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 4),
	}, {
		.name		= "keypad",
		.id		= -1,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 21),
	}, {
		.name		= "watchdog",
		.id		= -1,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 22),
	}, {
		.name		= "timers",
		.id		= -1,
		.parent		= &clk_pclkd1,
		.enable		= s5p6442_clk_ip3_ctrl,
		.ctrlbit	= (1 << 23),
	},

};

static struct clk *clks[] __initdata = {
	&clk_ext,
	&clk_epll,
	&clk_mout_apll.clk,
	&clk_mout_mpll.clk,
	&clk_mout_epll.clk,
	&clk_mout_d0.clk,
	&clk_mout_d0sync.clk,
	&clk_mout_d1.clk,
	&clk_mout_d1sync.clk,
	&clk_hclkd0,
	&clk_pclkd0,
	&clk_hclkd1,
	&clk_pclkd1,
};

static struct clksrc_clk *clksrc_cdev[] = {
	&clk_sclk_mmc0,
	&clk_sclk_mmc1,
	&clk_sclk_mmc2,
};

static struct clk *clk_cdev[] = {
	&clk_hsmmc0,
	&clk_hsmmc1,
	&clk_hsmmc2,
};

static struct clk_lookup s5p6442_clk_lookup[] = {
	CLKDEV_INIT("s3c-sdhci.0", "mmc_busclk.0", &clk_hsmmc0),
	CLKDEV_INIT("s3c-sdhci.1", "mmc_busclk.0", &clk_hsmmc1),
	CLKDEV_INIT("s3c-sdhci.2", "mmc_busclk.0", &clk_hsmmc2),
	CLKDEV_INIT("s3c-sdhci.0", "mmc_busclk.2", &clk_sclk_mmc0.clk),
	CLKDEV_INIT("s3c-sdhci.1", "mmc_busclk.2", &clk_sclk_mmc1.clk),
	CLKDEV_INIT("s3c-sdhci.2", "mmc_busclk.2", &clk_sclk_mmc2.clk),
};

void __init s5p6442_register_clocks(void)
{
	int ptr;

	s3c24xx_register_clocks(clks, ARRAY_SIZE(clks));

	s3c_register_clksrc(clksrcs, ARRAY_SIZE(clksrcs));
	s3c_register_clocks(init_clocks, ARRAY_SIZE(init_clocks));

	s3c_register_clocks(init_clocks_off, ARRAY_SIZE(init_clocks_off));
	s3c_disable_clocks(init_clocks_off, ARRAY_SIZE(init_clocks_off));
	clkdev_add_table(s5p6442_clk_lookup, ARRAY_SIZE(s5p6442_clk_lookup));

	s3c24xx_register_clocks(clk_cdev, ARRAY_SIZE(clk_cdev));
	for (ptr = 0; ptr < ARRAY_SIZE(clk_cdev); ptr++)
		s3c_disable_clocks(clk_cdev[ptr], 1);

	for (ptr = 0; ptr < ARRAY_SIZE(clksrc_cdev); ptr++)
		s3c_register_clksrc(clksrc_cdev[ptr], 1);

	s3c_pwmclk_init();
}
