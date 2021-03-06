/*
 * include/linux/s5p6442_ion.h
 *
 * Copyright (C) 2011 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _LINUX_S5P6442_ION_H
#define _LINUX_S5P6442_ION_H

#include <linux/ion.h>

enum {
	ION_HEAP_TYPE_S5P6442_CONTIG = ION_HEAP_TYPE_CUSTOM + 1,
	ION_HEAP_TYPE_S5P6442,
	ION_HEAP_TYPE_S5P6442_USER,
};

#define ION_HEAP_S5P6442_CONTIG_MASK	(1 << ION_HEAP_TYPE_S5P6442_CONTIG)
#define ION_HEAP_S5P6442_MASK		(1 << ION_HEAP_TYPE_S5P6442)
#define ION_HEAP_S5P6442_USER_MASK	(1 << ION_HEAP_TYPE_S5P6442_USER)
#define ION_S5P6442_WRITE_MASK		(1 << (BITS_PER_LONG - 1))
#define ION_S5P6442_MFC_SH_MASK		(1 << (BITS_PER_LONG - 2))
#define ION_S5P6442_MSGBOX_SH_MASK	(1 << (BITS_PER_LONG - 3))
#define ION_S5P6442_FIMD_VIDEO_MASK	(1 << (BITS_PER_LONG - 4))
#define ION_S5P6442_GSC_MASK		(1 << (BITS_PER_LONG - 5))
#define ION_S5P6442_MFC_OUTPUT_MASK	(1 << (BITS_PER_LONG - 6))
#define ION_S5P6442_MFC_INPUT_MASK	(1 << (BITS_PER_LONG - 7))
#define ION_S5P6442_MFC_FW_MASK		(1 << (BITS_PER_LONG - 8))
#define ION_S5P6442_SECTBL_MASK		(1 << (BITS_PER_LONG - 9))

#define ION_HEAP_S5P6442_MFC_SH_MASK					\
		(ION_HEAP_S5P6442_CONTIG_MASK|ION_S5P6442_MFC_SH_MASK)
#define ION_HEAP_S5P6442_MFC_FW_MASK					\
		(ION_HEAP_S5P6442_CONTIG_MASK|ION_S5P6442_MFC_FW_MASK)
#define ION_HEAP_S5P6442_SECTBL_MASK					\
		(ION_HEAP_S5P6442_CONTIG_MASK|ION_S5P6442_SECTBL_MASK)
#define ION_HEAP_S5P6442_FIMD_VIDEO_MASK					\
		(ION_HEAP_S5P6442_CONTIG_MASK|ION_S5P6442_FIMD_VIDEO_MASK)
#define ION_HEAP_S5P6442_GSC_MASK					\
		(ION_HEAP_S5P6442_CONTIG_MASK|ION_S5P6442_GSC_MASK)
#define ION_HEAP_S5P6442_MFC_OUTPUT_MASK					\
		(ION_HEAP_S5P6442_CONTIG_MASK|ION_S5P6442_MFC_OUTPUT_MASK)
#define ION_HEAP_S5P6442_MFC_INPUT_MASK					\
		(ION_HEAP_S5P6442_CONTIG_MASK|ION_S5P6442_MFC_INPUT_MASK)
#define ION_HEAP_S5P6442_MSGBOX_SH_MASK					\
		(ION_HEAP_S5P6442_CONTIG_MASK|ION_S5P6442_MSGBOX_SH_MASK)

#endif /* _LINUX_ION_H */
