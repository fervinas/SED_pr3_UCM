/*-------------------------------------------------------------------
**
**  Fichero:
**    common_types.h  2/2/2013
**
**    (c) J.M. Mendias
**    Programación de Sistemas y Dispositivos
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Declaración de tipos comunes
**
**  Notas de diseño:
**    Válidos para la arquitectura ARM7TDMI y el compilador GCC
**
**-----------------------------------------------------------------*/

#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

typedef unsigned char          boolean;    
typedef signed char            int8;    /*                       -128 ... +127                        */
typedef signed short int       int16;   /*                    -32.768 ... +32.767                     */
typedef signed int             int32;   /*             -2.147.483.648 ... +2.147.483.647              */
typedef signed long long int   int64;   /* -9.223.372.036.854.775.808 ... +9.223.372.036.854.775.807  */
typedef unsigned char          uint8;   /*                          0 ... 255                         */
typedef unsigned short int     uint16;  /*                          0 ... 65.535                      */
typedef unsigned int           uint32;  /*                          0 ... 4.294.967.295               */
typedef unsigned long long int uint64;  /*                          0 ... +18.446.744.073.709.551.614 */

#define NULL  ((void *) 0)
#define TRUE  (1)
#define FALSE (0)

#endif 
