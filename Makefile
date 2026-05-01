CC = riscv64-unknown-elf-gcc
LD = riscv64-unknown-elf-ld
OBJCOPY = riscv64-unknown-elf-objcopy

CFLAGS = -ffreestanding -nostdlib -fno-stack-protector -mcmodel=medany -march=rv64g -mno-relax -O0 

OBJS = entry.o main.o uart.o kalloc.o vm.o start.o kernelvec.o time_interupt.o trap.o proc.o swtch.o spinlock.o

all: kernel.elf

kernel.elf: $(OBJS)
		$(LD) -T linker.ld $(OBJS) -o kernel.elf

entry.o: entry.S
		$(CC) $(CFLAGS) -c entry.S -o entry.o

main.o: main.c
		$(CC) $(CFLAGS) -c main.c -o main.o

uart.o: uart.c
		$(CC) $(CFLAGS) -c uart.c -o uart.o

kalloc.o: kalloc.c
		$(CC) $(CFLAGS) -c kalloc.c -o kalloc.o

vm.o: vm.c
		$(CC) $(CFLAGS) -c vm.c -o vm.o

start.o: start.c
		$(CC) $(CFLAGS) -c start.c -o start.o

kernelvec.o: kernelvec.S
		$(CC) $(CFLAGS) -c kernelvec.S -o kernelvec.o

time_interupt.o: time_interupt.c
		$(CC) $(CFLAGS) -c time_interupt.c -o time_interupt.o

trap.o: trap.c
		$(CC) $(CFLAGS) -c trap.c -o trap.o

proc.o: proc.c
		$(CC) $(CFLAGS) -c proc.c -o proc.o

swtch.o: swtch.S
		$(CC) $(CFLAGS) -c swtch.S -o swtch.o 

spinlock.o:
		$(CC) $(CFLAGS) -c spinlock.c -o spinlock.o

clean:
		rm -f *.o kernel.elf

qemu: kernel.elf
		qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf -nographic 

