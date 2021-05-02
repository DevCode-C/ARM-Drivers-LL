#include "types.h"
#include "registers.h"
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"
#include "exti.h"
#include "uart.h"
#include <stdio.h>
extern void initialise_monitor_handles(void);
void mostrarBits(uint16_t valor);
int main(void){
    initialise_monitor_handles();
    GPIO_InitTypeDef GPIOA_Init;
    GPIO_InitTypeDef GPIOC_Init;
    UART_InitTypeDef USART2_Init;

    RCC_GPIOx_enable(RCC_GPIOA);
    GPIOA_Init.MODE = GPIO_MODE_OUTPUT;
    GPIOA_Init.PIN = GPIO_PIN_5; 
    gpio_configPort(GPIOA,&GPIOA_Init);
    
    GPIOA_Init.MODE = GPIO_MODE_ALT;
    GPIOA_Init.PIN = GPIO_PIN_2 | GPIO_PIN_3; 
    GPIOA_Init.PULL = GPIO_NOPULL;
    gpio_configPort(GPIOA,&GPIOA_Init);

    RCC_GPIOx_enable(RCC_GPIOC);
    RCC_SYSCFG();
    GPIOC_Init.PIN = GPIO_PIN_13;
    GPIOC_Init.MODE = GPIO_MODE_IT_RISING;
    GPIOC_Init.PULL = GPIO_PULLUP;
    gpio_configPort(GPIOC,&GPIOC_Init);

    RCC_USART2_enable();
    USART2_Init.uart = USART2;
    USART2_Init.BaudRate = 9600;
    USART2_Init.Parity = UART_PARITY_NONE;
    USART2_Init.StopBits= UART_STOPBITS_1;
    USART2_Init.TxRxMode = UART_MODE_TX_RX;
    USART2_Init.WordLength = UART_WORDLENGTH_9B;
    uart_configPort(&USART2_Init);

    nvic_EnableIrq(EXTI4_15);
    nvic_SetPriority(EXTI4_15,1);

    nvic_EnableIrq(USART2_IRQ);
    nvic_SetPriority(USART2_IRQ,0);
    uint8_t array[] = {"HOLA como estan\n"};
    while (1){
        printf("dentro del while\n");
        uart_sendBuffer(&USART2_Init,array,sizeof(array));
        printf("\n");
        _delay(10000);
    }   
}

void EXTI4_15_Handler(void){
    printf("\ndentro de la interrupcion\n");
    
    gpio_isrHandler(EXTI_LINE13);
} 
//Funcion de interrupcion para el UART
void USART2_Handler(void){
    printf("Hola\n");
    int8_t c;
    if(bitcheck(USART2->ISR,5)){
        c= USART2->RDR;
        printf("Entrada : %c\n",c);
    }
}
//Callback del EXTI
void gpio_isrCallback(uint32_t pin){
    printf("Adios\n");
}




