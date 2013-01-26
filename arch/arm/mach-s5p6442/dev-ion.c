/* linux/arch/arm/mach-s5p6442/dev-ion.c
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/dma-mapping.h>
#include <linux/platform_device.h>
#include <linux/ion.h>
#include <linux/s5p6442_ion.h>
#include <linux/slab.h>
#include <mach/s5p6442-ion.h>

struct platform_device s5p6442_device_ion = {
	.name		= "ion-s5p6442",
	.id		= -1,
};

void __init s5p6442_ion_set_platdata(void)
{
	struct ion_platform_data *pdata;
	pdata = kzalloc(sizeof(struct ion_platform_data)
			+ 5 * sizeof(struct ion_platform_heap), GFP_KERNEL);
	if (pdata) {
		pdata->nr = 4;
		pdata->heaps[0].type = ION_HEAP_TYPE_SYSTEM;
		pdata->heaps[0].name = "ion_noncontig_heap";
		pdata->heaps[0].id = ION_HEAP_TYPE_SYSTEM;
		pdata->heaps[1].type = ION_HEAP_TYPE_SYSTEM_CONTIG;
		pdata->heaps[1].name = "ion_contig_heap";
		pdata->heaps[1].id = ION_HEAP_TYPE_SYSTEM_CONTIG;
		pdata->heaps[2].type = ION_HEAP_TYPE_S5P6442;
		pdata->heaps[2].name = "s5p6442_noncontig_heap";
		pdata->heaps[2].id = ION_HEAP_TYPE_S5P6442;
		pdata->heaps[3].type = ION_HEAP_TYPE_S5P6442_CONTIG;
		pdata->heaps[3].name = "s5p6442_contig_heap";
		pdata->heaps[3].id = ION_HEAP_TYPE_S5P6442_CONTIG;
		s5p6442_device_ion.dev.platform_data = pdata;
	}
}
