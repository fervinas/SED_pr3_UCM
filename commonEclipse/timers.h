/*-------------------------------------------------------------------
**
**  Fichero:
**    timers.h  26/4/2013
**
**    (c) J.M. Mendias
**    Programación de Sistemas y Dispositivos
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Contiene las definiciones de los prototipos de las funciones
**    para la generación de retardos y la medida de tiempos
**
**  Notas de diseño:
**
**-----------------------------------------------------------------*/

#ifndef __TIMERS_H__
#define __TIMERS_H__

#include "common_types.h"

/*
** Pone a 0 los registros de configuración
** Pone a 0 todos los búfferes y registros de cuenta y comparación
** Para todos los temporizadores
** Inicializa las variables para retardos software
*/
void timers_init( void );

/*
** Realiza una espera de n milisegundos usando el timer3
*/
void timer3_delay_ms( uint16 n );

/*
** Realiza una espera de n milisegundos sin usar temporizadores
*/
void sw_delay_ms( uint16 n );

/*
** Realiza una espera de n segundos usando el timer3
*/
void timer3_delay_s( uint16 n );

/*
** Realiza una espera de n segundos sin usar temporizadores
*/
void sw_delay_s( uint16 n );

/*
** Arranca el timer3 a una frecuencia de 0,01 MHz 
** Permitirá medir tiempos con una resolución de 0,1 ms (100 us) hasta un máximo de 6.55s
*/
void timer3_start( void );

/*
** Detiene el timer3, devolviendo el número de décimas de milisegundo transcurridas desde que arrancó
** Devuelve 0 si han transcurrido más de 6.55 s
*/
uint16 timer3_stop( void );

/*
** Arranca el timer3 a una frecuencia de 0,01 MHz para que cuente n décimas de milisegundo hasta un máximo de 6.55s
*/
void timer3_start_timeout( uint16 n );

/*
** Indica si el timer3 ha finalizado su cuenta
*/
uint16 timer3_timeout( void );

/* 
** Para cada uno de los timers:
** Instala, en la tabla de vectores de interrupción, la función isr como RTI de interrupciones por fin de timer
** Desenmascara globalmente las interrupciones y específicamente las interrupciones por fin de timer
** Habilita las interrupciones por fin de timer
*/
void timer0_open( void (*isr)(void) );
void timer1_open( void (*isr)(void) );
void timer2_open( void (*isr)(void) );
void timer3_open( void (*isr)(void) );
void timer4_open( void (*isr)(void) );
void timer5_open( void (*isr)(void) );

/* 
** Para cada uno de los timers:
** Deshabilita las interrupciones por fin de timer
** Desinstala la RTI por fin de timer
*/
void timer0_close( void );
void timer1_close( void );
void timer2_close( void );
void timer3_close( void );
void timer4_close( void );
void timer5_close( void );

#endif 
