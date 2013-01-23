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
obj-$(CONFIG_CPU_S5P6442)	+= cpu-s5p.o
# TODO: obj-$(CONFIG_PM)		+= pm.o

# machine support

obj-$(CONFIG_MACH_SMDK6442)	+= mach-smdk6442.o
obj-$(CONFIG_MACH_APOLLO)	+= mach-apollo.o

# device support
obj-y					+= dev-audio.o setup-i2c0.o
obj-$(CONFIG_S5P6442_SETUP_FB_24BPP)	+= setup-fb-24bpp.o
obj-$(CONFIG_S5P6442_SETUP_FIMC)	+= setup-fimc.o
obj-$(CONFIG_S5P6442_SETUP_I2C1)	+= setup-i2c1.o
obj-$(CONFIG_S5P6442_SETUP_I2C2)	+= setup-i2c2.o
obj-$(CONFIG_S5P6442_SETUP_KEYPAD)	+= setup-keypad.o
# TODO: obj-$(CONFIG_S5P6442_SETUP_SDHCI_GPIO)	+= setup-sdhci-gpio.o
obj-$(CONFIG_S5P6442_SETUP_SPI)		+= dev-spi.o setup-spi.o
obj-$(CONFIG_S5P6442_SETUP_USB_PHY)	+= setup-usb-phy.o
