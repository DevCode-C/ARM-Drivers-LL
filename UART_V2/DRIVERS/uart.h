#ifndef UART_H
#define UART_H
#include "types.h"
#include "registers.h"
#include "exti.h"
#include "nvic.h"

typedef struct
{
    USART_TypeDef     *uart;            //
    volatile uint32_t BaudRate;         //                
    volatile uint32_t WordLength;  	    //
    volatile uint32_t StopBits;  	    
    volatile uint32_t Parity;
    volatile uint32_t TxRxMode; 

    volatile uint32_t Tx_Length;
    volatile uint8_t *TxMsg;
    volatile uint32_t Rx_Length;
    volatile uint8_t RxMsg[8];
}UART_InitTypeDef;

#define UART_WORDLENGTH_8B      (0x0UL  | ((0<<12) | (0<<28)))
#define UART_WORDLENGTH_9B      (0x0UL  | (1<<12))

#define UART_STOPBITS_0_5       (0x00UL)        	
#define UART_STOPBITS_1         (0x01UL)	
#define UART_STOPBITS_1_5       (0x02UL)
#define UART_STOPBITS_2         (0x03UL)	

#define UART_PARITY_NONE        (0x0UL)
#define UART_PARITY_EVEN        (0x0UL)   	
#define UART_PARITY_ODD         (0x1UL)
           
#define UART_MODE_TX	          (0x1UL)    
#define UART_MODE_RX              (0x2UL)	
#define UART_MODE_TX_RX           (0x3UL)






/*Configura el puerto uart seleccionado con la configuración descrita en la estructura uartH,
 esta tendrá los parámetros para setear la velocidad, bits de parada, paridad, tama;o de palabra y control de flujo
*/
void uart_configPort( UART_InitTypeDef *uartH );

/*Función callback que se manda llamar dentro de la función uart_configPort y que permite agregar código extra a la rutina
 de inicialización (activación de reloj configuración de puertos, etc ...)
*/
void uart_mspInit( UART_InitTypeDef *uartH ) __attribute__((weak));

/*manda la cantidad de caracteres especificados por len y referenciados en ptr a través del uart especificado,
 sin usar interrupciones. La función regresará solo cuando todos los caracteres se hayan mandado.*/
void uart_sendBuffer( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len );

/*manda a través de interrupciones la cantidad de caracteres especificados por len y referenciados en ptr a través del uart especificado. 
La función solo inicia la transferencia, la interrupción se encargará de enviar los caracteres.*/
void uart_sendBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len );

/*recibe mediante interrupciones la cantidad de caracteres especificados por len y referenciados en ptr a través del uart especificado. 
La función solo inicia la transferencia, la interrupción se encargará de recibir los caracteres cuando estos lleguen por el puerto.
*/
void uart_receiveBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len );

/*Procesa (manda o recibe) la información establecida por las funciones*/
void uart_isrHandler( UART_InitTypeDef *uartH );

/*esta función deberá ser escrita por el usuario en la aplicación, es llamada dentro de la función uart_isrHandler solo cuando todos 
los caracteres hayan sido enviados y debe estar declarada como weak dentro del driver uart
*/
void uart_isrTxCallback( UART_InitTypeDef *uartH )  __attribute__((weak));

/*esta función deberá ser escrita por el usuario en la aplicación, es llamada dentro de la función uart_isrHandler solo cuando todos 
los caracteres hayan sido recibidos y debe estar declarada como weak dentro del driver uart
*/
void uart_isrRxCallback( UART_InitTypeDef *uart ) __attribute__((weak));

/*uart_sendBufferInt y  uart_receiveBufferInt ademas de limpiar la(s) bandera(s) de la interrupción que va a atender
 y llamar la función(es) callback(s) en donde el usuario escribirá su aplicación. 
 Esta función solo debe ser llamada dentro de uno de los  vectores de interrupción UART*/

#endif