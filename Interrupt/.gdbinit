target remote localhost:3333
monitor arm semihosting enable
load
monitor reset halt 
break main
b main.c:26
b main.c:37
c
print /a GPIOC_Init.PIN
print /a GPIOC_Init.MODE
print /a GPIOC_Init.PULL

print /a GPIOA->MODER
print /a GPIOC->MODER
print /t GPIOC->MODER