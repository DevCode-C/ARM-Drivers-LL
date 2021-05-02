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
    // if(uartH->WordLength == UART_WORDLENGTH_9B){
    //     ptr16Bits = (uint16_t *) &ptr;
    //     ptr8Bits = NULL;
    // }
    // else{
    //     ptr16Bits = NULL;
    //     ptr8Bits = ptr;
    // }
    // while (len > 0){
    //     if(ptr8Bits == NULL){
    //         uartH->uart->TDR = (uint16_t)(*ptr16Bits & 0x01FFU);
    //         ptr16Bits++;
    //     }
    //     else{
    //         uartH->uart->TDR = (uint8_t)(*ptr8Bits & 0xFFU);
    //         ptr8Bits++;
           
    //     }
    //     printf("%ld\n",len);
    //     len--;
    // }
    for (i =0; i < len-1; i++){
        // if(uartH->WordLength == UART_WORDLENGTH_9B){
            //uartH->uart->TDR = (ptr16Bits[i] );
        // }else{
        //     uartH->uart->TDR = (uint8_t)(ptr8Bits[i]);
        // }
        
        uartH->uart->TDR =(uint16_t)(ptr[i] & 0x1FFU);
        // printf("%ld\n",i);
        _delay(1000);
        }
    
}

void uart_sendBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len ){
    if(bitcheck(uartH->uart->CR1,3)){
        uartH->TxMsg = ptr;
        uartH->Tx_Length = len;
        uartH->uart->CR1 = Set_Bit(uartH->uart->CR1,7);
    }
}

void uart_receiveBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len ){
    if(bitcheck(uartH->uart->CR1,2)){
        uartH->Rx_Length = len;
        //uartH->RxMsg = *ptr;
        uartH->uart->CR1 = Set_Bit(uartH->uart->CR1,5);
    }
}

void uart_isrHandler( UART_InitTypeDef *uartH ){
    if(bitcheck(uartH->uart->CR1,7)){
        uartH->uart->TDR = *uartH->TxMsg;
        uartH->TxMsg++;
        uartH->Tx_Length --;
        if (uartH->Tx_Length == 0){
            uartH->uart->CR1 = Reset_Bit(uartH->uart->CR1,7);
            uart_isrTxCallback(uartH);
        }   
    }
    else
    {
        uartH->RxMsg[0] = (uint8_t )uartH->uart->RDR;
        // uartH->RxMsg++;
        // uartH->Rx_Length++;
        if(!bitcheck(uartH->uart->ISR,5)){
            uartH->uart->CR1 = Reset_Bit(uartH->uart->CR1,5);
            uartH->uart->ICR = Set_Bit(uartH->uart->ICR,3); 
            uart_isrRxCallback(uartH);
        }
    }
    
    
}