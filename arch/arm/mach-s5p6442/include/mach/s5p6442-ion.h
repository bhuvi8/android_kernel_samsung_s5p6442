/* linux/arch/arm/mach-s5p6442/include/mach/s5p6442-ion.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __MACH_S5P6442_ION_H_

struct platform_device;

#ifdef CONFIG_S5P6442_SETUP_ION
extern struct platform_device s5p6442_device_ion;
void s5p6442_ion_set_platdata(void);
#else
static inline void s5p6442_ion_set_platdata(void)
{
}
#endif

#endif /* __MACH_S5P6442_ION_H_ */
