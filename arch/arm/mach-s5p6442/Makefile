# arch/arm/mach-s5p6442/Makefile
#
# Copyright (c) 2010 Samsung Electronics Co., Ltd.
# 		http://www.samsung.com/
#
# Licensed under GPLv2

obj-y				:=
obj-m				:=
obj-n				:=
obj-				:=

# Core support for S5P6442 system

obj-$(CONFIG_CPU_S5P6442)	+= cpu.o init.o clock.o dma.o
obj-$(CONFIG_CPU_S5P6442)	+= setup-keypad.o setup-i2c0.o setup-i2c1.o setup-i2c2.o cpu-s5p.o setup-fb-24bpp.o

# machine support

obj-$(CONFIG_MACH_SMDK6442)	+= mach-smdk6442.o
obj-$(CONFIG_MACH_APOLLO)	+= mach-apollo.o

# device support
obj-y				+= dev-audio.o
obj-$(CONFIG_S3C64XX_DEV_SPI)	+= dev-spi.o
