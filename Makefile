TARGET=example1
KDIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

CC = gcc

obj-m := example1.o

default:
	make -C $(KDIR) M=$(PWD)  modules

clean:
	rm -rf *.o *.ko modules.* .*.ko.cmd .*.mod.o.cmd .*.o.cmd *.mod.c
