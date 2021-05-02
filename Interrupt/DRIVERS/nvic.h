#ifndef NVIC_H
#define NVIC_H
#include "types.h"
#include "registers.h"

#define _Pos_Assignment_IP(irq)         (((uint32_t)irq)>>2UL)
#define _Bit_Shift(irq)                 (((uint32_t)irq & 0x03UL)*8UL)      

/*Establece la prioridad que tendrá la interrupción.*/
void nvic_SetPriority( IRQ_types irq, uint32_t priority );

/*regresa el valor que tiene la prioridad.*/
uint32_t nvic_GetPriority( IRQ_types irq );

/*habilita la interrupción deseada, esto quiere decir que una interrupción podrá ser activada por una señal*/
void nvic_EnableIrq( IRQ_types irq );

/*deshabilita la interrupción deseada */
void nvic_DisableIrq( IRQ_types irq );

/*Regresa la interrupción que esta activa (esto no implica que el procesador la este atendiendo aun)*/
uint32_t nvic_GetPendingIrq( IRQ_types irq );

/*activa la interrupción para que el procesador la atienda.*/
void nvic_SetPendingIrq( IRQ_types irq );

/*Indica al procesador que ya no debe atender la interrupción*/
void nvic_ClearPendingIrq( IRQ_types irq );

#endif