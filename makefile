CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld 
BIN = arm-none-eabi-objcopy
ST = st-flash
CFLAGS = -mthumb -mcpu=cortex-m3

all: app.bin

crt.o: crt.s
	$(AS) -o crt.o crt.s
main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c
app.elf: linker.ld crt.o main.o
	$(LD) -T linker.ld -o app.elf crt.o main.o
app.bin: app.elf
	$(BIN) -O binary app.elf app.bin 
clean:
	rm -f *.o *.elf *.bin
flash: app.bin
	$(ST) write app.bin 0x08000000
erase:
	$(ST) erase 

