/*-------------------------------------------------------------------
**
**  Fichero:
**    at24c04.h  
**
**
**  Propósito:
**    Contiene las definiciones de los prototipos de funciones
**    para la lectura/escritura de la EEPROM serie AT24C04
**
**  Notas de diseño:
**
**-----------------------------------------------------------------*/

#ifndef __AT24C04_H__
#define __AT24C04_H__

#include "common_types.h"

#define AT24C04_ADDRESS (0x28) // la dirección completa del dispositivo (8 bits) es: 0b101000 | PAGE | R/W

#define AT24C04_READ  (1)
#define AT24C04_WRITE (0)

#define AT24C04_WIDTH (8)
#define AT24C04_DEPTH (512)

/*
** Realiza una escritura aleatoria en la dirección indicada
*/
void golden_at24c04_bytewrite( uint16 addr, uint8 data );

/*
** Realiza una lectura aleatoria de la dirección indicada
*/
void golden_at24c04_byteread( uint16 addr, uint8 *data );


#endif

