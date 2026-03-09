

# AUTHOR - K MAREMELA
# STUDENT NUMBER - 221030105
# HW4

#KERNEL DIRACTORY
KDIR:=/lib/modules/$(shell uname -r)/build

obj-m:=main.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

install:
	sudo insmod main.ko

uninstall:
	sudo rmmod main || true
	rm -f *.ko

log:
	sudo dmesg | tail -20
