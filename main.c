#include "s3c44b0x.h"
#include "s3cev40.h"
#include "common_types.h"
#include "at24c04.h"


extern void DelayMs(int ms_time);
extern void sys_init();
extern void iic_init();
extern void D8Led_symbol(int value);
extern void at24c04_bytewrite( uint16 addr, uint8 data );
extern void at24c04_byteread( uint16 addr, uint8 *data );

int val;

void Main( void )
{
    uint8 buffer[AT24C04_DEPTH];
    uint16 i;
    
    sys_init();

    iic_init();
    D8Led_symbol(8);//8

    //Inicializamos la EEPROM
    for( i=0; i<AT24C04_DEPTH; i++ ){
      val = (uint8)i%16;
      at24c04_bytewrite( i, val );
    }

    /*for( i=0; i<AT24C04_DEPTH; i++ ){
      golden_at24c04_byteread( i, &buffer[i] );
    }*/

    DelayMs(100);

    for( i=0; i<AT24C04_DEPTH; i++ ){
      at24c04_byteread( i, &buffer[i] );
      val = buffer[i] & 0xF;
      D8Led_symbol(val);
      DelayMs(100);
    }

    while( 1 );
}
