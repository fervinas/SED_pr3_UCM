#include "s3c44b0x.h"
#include "s3cev40.h"
#include "iic.h"
#include "44b.h"

extern uint32 mclk;			   // Frecuencia actual del reloj (Hz)

extern void DelayMs(int ms_time);

void iic_init( void )
{
	// Enable IIC & GPIO & BDMA blocks (si no se activa BDMA, el controlador IIC no es accesible)
	rCLKCON = rCLKCON  | (0x1<<13) | (0x1<<10) | (0x<<7);
	//PF[1] = IICSDA; PF[0] = IICSCL;
	rPCONF = rPCONF & 0x3fff0; //Clean first...
	rPCONF = rPCONF | 0xa; //Add new conf...
	// Pull-up enable
	rPUPF = 0xfc; //Bit 0 and bit 1 as 0
    //Configurar la dirección del slave
	rIICADD = S3C44B0X_SLAVE_ADDRESS;
    //Generación ACK habilitada, interrupciones habilitadas
    rIICCON = rIICCON | ((mclk / 4000000 - 1) & 0xf); 	//Valor de preescalado, PREESCALER = mclk/16/250000 -1
    // Activa Tx/Rx
    rIICSTAT = rIICSTAT | (0x1<<4);
}

void iic_putByte_start( uint8 byte )
{
	// Escribe el dato
	rIICDS = byte;
	// Máster Tx, start condition, Tx/Rx habilitada
	rIICSTAT = 0xf0;
	// Comienza la transmisión (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1<<4);
    // Espera la recepción de ACK
	while((rIICSTAT & 0x1) == 1){}
}

void iic_putByte( uint8 byte )
{
    // Escribe el dato
	rIICDS = byte;
	// Comienza la transmisión del dato (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1<<4);
    // Espera la recepción de ACK
	while((rIICSTAT & 0x1) == 1){}
};

void iic_putByte_stop( uint8 byte )
{
    // Escribe el dato
	rIICDS = byte;
	// Comienza la trasmisión del dato (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1<<4);
    // Espera la recepción de ACK  
	while((rIICSTAT & 0x1) == 1){}
    // Máster Tx, stop condition, Tx/Rx habilitada
	rIICSTAT = 0xD0;
    // Comienza la trasmisión de STOP (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1<<4);
    // Espera a que la stop condition tenga efecto (5 ms para la at24c04)
    //TODO
}

void iic_getByte_start( uint8 byte )
{
	// Escribe el dato
	rIICDS = byte;
    // Máster Rx, start condition, Tx/Rx habilitada
	rIICSTAT = 0xB0;
    // Comienza la transmisión (borrando pending bit del IICCON)
	rIICCON = rIICCON & ~(0x1<<4);
    // Espera la rececpión de ACK

}

uint8 iic_getByte( void )
{
    // Reanuda la recepción (borrando pending bit del IICCON)
	// Espera la recepción del dato
    return IICDS;// Lee el dato
}

uint8 iic_getByte_stop( int8 ack )
{
	uint8 byte;

    IICCON = (IICCON & ~(1 << 7)) | (ack << 7); // Habilita/deshabilita la generación de ACK

    // Reanuda la recepción (borrando pending bit del IICCON)
	// Espera la recepción del dato
    byte = IICDS;	// Lee el dato

   	// Máster Rx, stop condition, Tx/Rx habilitada
   	// Comienza la trasmisión de STOP (borrando pending bit del IICCON)
   	// Espera a que la stop condition tenga efecto (5 ms para la at24c04)

	IICCON |= (1<<7); // Habilita la generación de ACK
   	return byte;
}
