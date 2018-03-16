/*-------------------------------------------------------------------
**
**  Fichero:
**    iic.h  17/5/2013
**
**    (c) J.M. Mendias
**    Programación de Sistemas y Dispositivos
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Contiene las definiciones de los prototipos de funciones
**    para la comunicación por el bus IIC del chip S3C44BOX 
**
**  Notas de diseño:
**
**-----------------------------------------------------------------*/

#ifndef __IIC_H__
#define __IIC_H__

#include "common_types.h"

#define S3C44B0X_SLAVE_ADDRESS (0x08)

#define	RxACK		(1)
#define NO_RxACK	(0)

/*
** Configura el controlador de IIC según los siguientes parámetros 
**   Interrupciones: habilitadas
**   Transmisión/recepción: activada
**   Frecuencia de comunicación: 250 KHz
**   Generación de ACK: automática
**   Dirección como esclavo: 0x08
*/
void iic_init( void );

/*
** Inicia un flujo de transmición en la que el microcontrolador actúa como master:
** 	 Genenera la START condition
**   Envía la dirección del dispositivo esclavo
**   Espera la recepción de ACK 
*/
void iic_putByte_start( uint8 byte );

/*
** Actuando el microcontrolador como master, envía el byte indicado y espera la recepción de ACK
*/
void iic_putByte( uint8 byte );

/*
** Finaliza un flujo de transmisión en la que el microcontrolador actúa como master:
** 	 Envia el byte indicado
**   Espera la recepción de ACK 
**   Genara la STOP condition
*/
void iic_putByte_stop( uint8 byte );

/*
** Inicia un flujo de recepción en la que el microcontrolador actúa como master:
** 	 Genenera la START condition
**   Envía la dirección del dispositivo esclavo
**   Espera la recepción de ACK 
*/
void iic_getByte_start( uint8 byte );

/*
** Actuando el microcontrolador como master, espera la recepción de un byte, genera ACK y lo devuelve
*/
uint8 iic_getByte( void );

/*
** Finaliza un flujo de recepción en la que el microcontrolador actúa como master:
** 	 Espera la recepción de un byte
**   Genera o no ACK 
**   Genera la STOP condition
**   Devuelve el byte recibido
*/
uint8 iic_getByte_stop( int8 ack );

/* 
** Instala, en la tabla de vectores de interrupción, la función isr como RTI de interrupciones por Tx/Rx a traves de IIC
** Desenmascara globalmente las interrupciones y específicamente las interrupciones por Tx/Rx a traves de IIC
** Habilita las interrupciones por Tx/Rx a traves de IIC
*/
void iic_open( void (*isr)(void) );

/* 
** Deshabilita las interrupciones por Tx/Rx a traves de IIC
** Desinstala la RTI por Tx/Rx a traves de IIC
*/
void iic_close( void );

#endif
