include Kbuild
FLAGS := --warn-undefined-variables --debug -Wall -Werror -lm
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
CC := gcc
RAND := $(shell uuidgen)

default:
	$(MAKE) -C $(KDIR) $(FLAGS) M=$(PWD) LDDINC=$(PWD)/include modules
#	/usr/src/kernels/$(shell uname -r)/scripts/sign-file sha256 buffer.priv buffer_public.der buffer.ko
test:
	$(CC) -o main main.c
clean:
	$(MAKE) -C $(KDIR)  $(FLAGS) M=$(PWD) clean
	rm -rf main
