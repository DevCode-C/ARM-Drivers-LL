#include "types.h"
#include "registers.h"
#include "uart.h"
#include "rcc.h"
#include <stdio.h>

void uart_configPort( UART_InitTypeDef *uartH ){
    uart_mspInit(uartH);
    uartH->uart->CR1 &= ~(1<<0);    //USART enable, Clean bit
    
    uartH->uart->CR1 &= ~(1U<<12);   //Clean register bits, M0 bits 
    uartH->uart->CR1 &= ~(1U<<28);   //Clean register bits,  M0 bit
       
    uartH->uart->CR1 |= uartH->WordLength;  //Set register bits
    
    uartH->uart->CR1 &= ~(1U<<15);   //Clean register bits, OVER8

    uartH->uart->CR2 &= ~(3U<<12);               //Clean register bits, STOP[1:0]
    uartH->uart->CR2 |= (uartH->StopBits<<12);  //Set register bits, STOP[1:0]

    uartH->uart->CR1 &= ~(3U<<9);                   //Parity Control                                                                
    if (uartH->Parity != UART_PARITY_NONE){         //Parity Control                                                    
        uartH->uart->CR1 |= (1U<<10);               //Parity Control    
        uartH->uart->CR1 |= (uartH->Parity<<9);     //Parity Control
    }                                               //Parity Control                
    
    uartH->uart->CR1 &= ~(3<<2);
    uartH->uart->CR1 |= uartH->TxRxMode<<2;
    
    uartH->uart->BRR =(8000000/uartH->BaudRate);    //Set BRR (BAUDIOS)
    
    uartH->uart->CR1 |= (1<<0);
}

void uart_sendBuffer( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len ){
    volatile uint32_t i=0;
    do{
        // if (i == len){
        //    uartH->uart->TDR=0; 
        // }else{
        //     uartH->uart->TDR =ptr[i];
        //     i = i+1;
        //     // printf("Caracter: %d\n",ptr[i-1]);
        //     // printf("Contador: %d\n",i-1);
        // }
        for (i =0; i < len-1; i++){
            uartH->uart->TDR =ptr[i];
            // printf("%ld\n",i);
            _delay(1000);
        }
        //uartH->uart->TDR=0;
        
        uartH->uart->ICR |= 1<<6;
    }while (!bitcheck(uartH->uart->ISR,7));
    
}

void uart_sendBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len ){
        // uartH->uart->CR1 |= 1U<<7;

        // uartH->Tx_Length = len;
        // uartH->TxMsg = ptr;
        // uartH->uart->CR1 &= ~(1U<<7);
        
    
}

void uart_receiveBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len ){
    uartH->uart->CR1 |= 1U<<5;
    if(bitcheck(uartH->uart->ISR,5)){
        char temp = uartH->uart->RDR;
        uartH->uart->RDR = temp;
        printf(" %c",temp);
        while ((bitcheck(uartH->uart->ISR,6)));

    }
}

void uart_isrHandler( UART_InitTypeDef *uartH ){
    uart_isrRxCallback(uartH);
}