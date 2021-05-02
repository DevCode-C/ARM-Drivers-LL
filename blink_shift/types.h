#ifndef TYPES_H
#define TYPES_H
/*Privates defines*/
#define LEFT_SHIFT(var,bits) (var<<=bits)
#define RIGTH_SHIFT(var,bits) (var>>=bits)

#define Set_Bit(PORT,BIT)       (PORT|  (1<<BIT))
#define Reset_Bit(PORT,BIT)     (PORT& ~(1<<BIT))
#define Toogle_Bit(PORT,BIT)    (PORT ^ (1<<BIT))
#define bitcheck(PORT,BIT)      (PORT & (1<<BIT))


/*----------------*/

/*Private typedef definitions---*/
typedef unsigned long uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
/*------------------------------*/
typedef signed long int32_t;
typedef signed short int16_t;
typedef signed char int8_t;

#define _delay(cuentas)         for(volatile int32_t i= 0; i<cuentas;i ++)

#endif