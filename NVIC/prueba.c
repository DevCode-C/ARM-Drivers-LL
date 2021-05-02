#include <stdio.h>
#include <stdlib.h>
#include "registers.h"
typedef unsigned long uint32_t;
typedef enum{
    GPIO_MODE_INPUT  =  ((uint32_t)0x0),
    GPIO_MODE_OUTPUT =  ((uint32_t)0x1),
    GPIO_MODE_ALT    =  ((uint32_t)0x2),
    GPIO_MODE_ANALOG =  ((uint32_t)0x3)
}enumeracion;

// typedef struct Registers{
//     volatile uint32_t ISER;
//              uint32_t Reserved0[31];
//     volatile uint32_t ICER;
//              uint32_t Reserved1[31];
//     volatile uint32_t ISPR;
//              uint32_t Reserved2[31];
//     volatile uint32_t ICPR;
//              uint32_t Reserved3[95];
//     volatile uint32_t IPR[8];
// }NVIC_Typedef;

#define PPS         ((uint32_t)0xE000E000U)
#define NVIC_BASE   (PPS + 0x100UL)
#define NVIC_Type   ((NVIC_Typedef *) NVIC_BASE)
#define _Pos_Assignment(irq)        (((uint32_t)irq)>>2UL)
#define _Bit_Shift(irq)             (((uint32_t)irq & 0x03UL)*8UL)
void nvic_EnableIrq( IRQ_types irq );
void mostrarBits(uint16_t valor);
int main (void){
    NVIC_Typedef estructura;






    printf("NVIC->ISER:     %p\n",&NVIC_Type->ISER);
    printf("NVIC->ICER:     %p\n",&NVIC_Type->ICER);
    printf("NVIC->ISPR:     %p\n",&NVIC_Type->ISPR);
    printf("NVIC->ICPR:     %p\n",&NVIC_Type->ICPR);
    printf("NVIC->IPR[0] :  %p\n",&NVIC_Type->IPR);
    printf("NVIC->IPR[7] :  %p\n",&NVIC_Type->IPR[7]);

    printf("Posicion: %ld\n",_Pos_Assignment(0));
    printf("_Bit_Shift: %ld\n",_Bit_Shift(0));

    uint32_t prioridad=3;
    prioridad = (prioridad << ((6)&0xFFUL)) << _Bit_Shift(0);
    printf("Priotidad: %lX\n",prioridad);



    return 0;
}
// void nvic_EnableIrq( IRQ_types irq ){
//     uint32_t prueba = ((uint32_t)(1<<irq));
//     mostrarBits((uint16_t)prueba);
// }
// void mostrarBits(uint16_t valor){
//     volatile uint16_t temp ;
//     volatile uint16_t shift1 = 1<<15 ;
//     temp = valor;
//     printf("\nValor asignado al registro ODR en HEX: %x\t\t Valor asignado al registro ODR en BIN: ",valor);
//     for (uint8_t i = 0; i < 16; i++){
//         putchar(temp & shift1 ? '1':'0');
//         temp <<= 1;
//     }
    
// }
