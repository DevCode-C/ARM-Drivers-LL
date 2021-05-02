#include "types.h"
#include "registers.h"
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"
#include "exti.h"
#include "uart.h"
#include <stdio.h>
extern void initialise_monitor_handles(void);

UART_InitTypeDef USART2_Init;
uint8_t arratRX[] = {"Interrupcion\n"};
int main(void){
    initialise_monitor_handles();
    GPIO_InitTypeDef GPIOA_Init;
    GPIO_InitTypeDef GPIOC_Init;
    

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
        //printf("dentro del while\n");
        gpio_togglePins(GPIOA,GPIO_PIN_5);
        uart_sendBuffer(&USART2_Init,array,sizeof(array));
        uart_receiveBufferInt(&USART2_Init,array,sizeof(array));
        //printf("\n");
        _delay(10000);
    }   
}

void EXTI4_15_Handler(void){
    printf("\ndentro de la interrupcion\n");
    uart_sendBufferInt(&USART2_Init,arratRX,sizeof(arratRX)-1);
    gpio_isrHandler(EXTI_LINE13);
} 
//Funcion de interrupcion para el UART
void USART2_Handler(void){
    uart_isrHandler(&USART2_Init);
}
//Callback del EXTI
void gpio_isrCallback(uint32_t pin){
    
    printf("Adios\n");
}
//Funcion que agrega instrucciones extras en uart_ConfigPort
void uart_mspInit( UART_InitTypeDef *uartH ){
    RCC_USART2_enable();
}


//Funciones que se llaman al terminar de enviar/recibir por uart
void uart_isrTxCallback(UART_InitTypeDef *uartH){
    uartH->uart->CR1 = Reset_Bit(uartH->uart->CR1,5);
    printf("uart_isrTxCallback\n");
}

void uart_isrRxCallback(UART_InitTypeDef *uartH){
    printf("uart_isrRxCallback\n");
    // for (uint8_t i = 0; i < uartH->Rx_Length; i++){
        printf("%c\n",uartH->RxMsg[0]);

    // }
    
}
