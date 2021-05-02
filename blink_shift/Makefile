CC = arm-none-eabi-gcc
CFLAGS =-g3 -c -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 -o
LDFLAGS =-g3 -mcpu=cortex-m0 -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32f0_ls.ld -Wl,-Map=final.map -o
OBJS = main.o stm32_startup.o gpio.o syscalls.o
################################################
#Semi Hosting
LDFLAGS_SH =-g3 -mcpu=cortex-m0 -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32f0_ls.ld -Wl,-Map=final.map -o
OBJS_SH = main.o stm32_startup.o gpio.o 
################################################
all: $(OBJS) final.elf
semi:  $(OBJS_SH) final_sh.elf
################################################m
%.o: %.c
	$(CC) $(CFLAGS) $@ $^

final.elf: $(OBJS) 
	$(CC) $(LDFLAGS) $@ $^

final_sh.elf: $(OBJS_SH) 
	$(CC) $(LDFLAGS_SH) $@ $^
###################################################################
###################################################################
.PHONY : clean
clean : 
	@rm -rf *.o *.elf *.map

load:
	@openocd -f board/st_nucleo_f0.cfg

debug:
	@arm-none-eabi-gdb final_sh.elf