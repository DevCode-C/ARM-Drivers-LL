CC = arm-none-eabi-gcc
TARGET = UART_Driver
INCLUDE = -I DRIVERS
VPATH = DRIVERS
OBJS_F =  ObjetsFiles

CFLAGS =-g3 -c -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -std=gnu11 -Wall  $(INCLUDE) -O0 -o
LDFLAGS =-g3 -mcpu=cortex-m0 -mthumb -mfloat-abi=soft --specs=rdimon.specs -T Linker/stm32f0_ls.ld -Wl,-Map=$(TARGET).map -o
OBJS = stm32_startup.o main.o  gpio.o nvic.o exti.o uart.o
#######################################################################################################################
#Semi Hosting
#######################################################################################################################
all: $(TARGET)
#######################################################################################################################
$(TARGET): $(OBJS_F)/$(TARGET).elf
	arm-none-eabi-objdump -S $< > $(OBJS_F)/$(TARGET).lst
	arm-none-eabi-size --format=berkeley $<

$(OBJS_F)/$(TARGET).elf: $(addprefix $(OBJS_F)/,$(OBJS)) 
	$(CC) $(LDFLAGS) $@ $^

$(OBJS_F)/%.o: %.c
	@mkdir -p $(OBJS_F)
	$(CC) $(CFLAGS) $@ $^
#######################################################################################################################
#######################################################################################################################
.PHONY : clean
clean : 
#	@rm -rf $(OBJS_F)/*.o $(OBJS_F)/*.elf $(OBJS_F)/*.lst *.map 
	@rm -rf $(OBJS_F) *.map 
load:
	@openocd -f board/st_nucleo_f0.cfg

debug:
	@arm-none-eabi-gdb $(OBJS_F)/$(TARGET).elf