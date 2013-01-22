/* linux/arch/arm/mach-s5p6442/include/mach/system.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5P6442 - system support header
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_SYSTEM_H
#define __ASM_ARCH_SYSTEM_H __FILE__

static void arch_idle(void)
{
	/* nothing here yet */
}

void s5p6442_restart(char mode, const char *cmd)
{
	__raw_writel(0x1, S5P_SWRESET);
}

#endif /* __ASM_ARCH_SYSTEM_H */
