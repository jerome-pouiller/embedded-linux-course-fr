
obj-m += concurence-user.o
# EXTRA_CFLAGS = -I/lib/modules/$(shell uname -r)/build/include/xenomai
KDIR ?= /lib/modules/$(shell uname -r)/build

default: concurence-user modules
# default: rtc modules

concurence-user: CFLAGS = $(shell xeno-config --skin native --cflags)
concurence-user: LDFLAGS = $(shell xeno-config --skin native --ldflags)

modules:
	$(MAKE) -C $(KDIR) SUBDIRS=$(shell pwd) modules

clean:
	rm *.ko *.o *.mod.c

