CC = arm-none-eabi-gcc
CC_LOG = arm-none-eabi-objdump
CFLAGS =-c -mcpu=cortex-m0 -mthumb -std=gnu11 -Wall -O0
LDFLAGS = -nostdlib -T stm32f0_ls.ld -Wl,-Map=final.map
LOGS = main_log stm32_startup_log
OBJS = main.o stm32_startup.o gpio.o
################################################
all: $(OBJS) final.elf
log: $(LOGS)
################################################m
main.o:main.c 
	$(CC) $(CFLAGS) -o $@ $^ 

stm32_startup.o:stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^

gpio.o:gpio.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf: $(OBJS)  
	$(CC) $(LDFLAGS) -o $@ $^ 
###################################################################
main_log:main.o
	$(CC_LOG) -h $^ > $@
stm32_startup_log:stm32_startup.o
	$(CC_LOG) -h $^ > $@
stm32f0_ls_log:final.elf
	$(CC_LOG) -h $^ > $@
###################################################################
.PHONY : clean
clean : 
	@rm -rf *.o $(LOGS) *.elf *.map

load:
	openocd -f board/st_nucleo_f0.cfg

gdb:
	arm-none-eabi-gdb