#include "types.h"
#include "registers.h"
#include "rcc.h"
#include "gpio.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);
void mostrarBits(uint16_t valor);
int main(void){
    initialise_monitor_handles();
    GPIO_InitTypeDef GPIOA_Init;
    GPIO_InitTypeDef GPIOB_Init;

    RCC_GPIOx_enable(RCC_GPIOA);
    GPIOA_Init.MODE = GPIO_MODE_OUTPUT;
    GPIOA_Init.PIN = GPIO_PIN_5; 
    gpio_configPort(GPIOA,&GPIOA_Init);

    RCC_GPIOx_enable(RCC_GPIOB);
    GPIOB_Init.PIN = GPIO_PIN_ALL;
    GPIOB_Init.MODE = GPIO_MODE_OUTPUT;
    gpio_configPort(GPIOB,&GPIOB_Init);

    printf("\nDireccion del Registro ODR: %p\n",&GPIOB->ODR);
    _delay(100000);
    while (1){
        gpio_togglePins(GPIOA,GPIO_PIN_5);
        gpio_setPins(GPIOB,GPIO_PIN_0);
        for (uint8_t i = 0; i < 16; i++){
            mostrarBits((uint16_t)GPIOB->ODR);
            LEFT_SHIFT(GPIOB->ODR,1);
            _delay(100000);
        }
        printf("\n");
    }   
}
void mostrarBits(uint16_t valor){
    volatile uint16_t temp ;
    volatile uint16_t shift1 = 1<<15 ;
    temp = valor;
    printf("\nValor asignado al registro ODR en HEX: %x\t\t Valor asignado al registro ODR en BIN: ",valor);
    for (uint8_t i = 0; i < 16; i++){
        putchar(temp & shift1 ? '1':'0');
        temp <<= 1;
    }
    
}