/*
 * system.c

 *
 *  Created on: 14/03/2014
 *      Author: Alberto
 */

#include "s3c44b0x.h"
#include "s3cev40.h"
#include "common_types.h"
#include "system.h"

static uint32 clk_normal = CLKIN;  // Frecuencia en modo normal (Hz)
static uint32 clk_slow = CLKIN;	   // Frecuencia en modo slow (Hz)
uint32 mclk = CLKIN;			   // Frecuencia actual del reloj (Hz)

void DelayMs(int ms_time)
{
	int i;

	for( i = 0 ; i < 1000*ms_time ; i++ )
		;
}

void sys_init( void )
{
	WTCON  = 0;				// deshabilita el watchdog
	INTMSK = ~0;			// enmascara todas las interrupciones

	// Configuracion del gestor de reloj
	LOCKTIME   = 0xfff;		// estabilización del PLL = 512 us
	PLLCON     = 0x38021;	// MCLK = 64MHz
	clk_normal = 64000000;
	CLKSLOW    = 0x8;		// MCLK_SLOW = 500 KHz
	clk_slow   = 500000;
	CLKCON     = (1<<10) | (1<<7); 	// modo NORMAL y todos los controladores desactivados menos el BDMA y GPIO (para poder acceder a todos lo perifericos y a los puertos)
	mclk       = clk_normal;

	// Configuracion del arbitro de bus
	SBUSCON = 0x8000001b;	// prioridad fija por defecto LCD > ZDMA > BDMA > IRQ

	// Configuracion de cache
	SYSCFG = 0;				// deshabilitada

	// Configuacion del controlador de interrupciones
	I_PMST = 0x1f1b;		// prioridades fijas por defecto
	I_PSLV = 0x1b1b1b1b;
	INTMOD = 0;				// todas las interrupciones en modo IRQ
	EXTINTPND = ~0;			// borra las interrupciones externas pendientes por linea EINT7..4
    I_ISPC = ~0;			// borra todas las interrupciones pendientes
	INTCON = 1;				// IRQ vectorizadas, linea IRQ activada, linea FIQ desactivada

	// Configuracion de puertos
	port_init();
}


inline void port_init( void )
{

	PDATA = ~0;
	PCONA = (0x7f<<1);		// PA[7:1] = ADDR[22:16], resto = out

	PDATB = ~0;
	PCONB = (1<<8) | (1<<6) | (0xf);	// PA[8] = nGCS3, PA[6] = nGCS1, PA[3:0] = (nSRAS, nSCAS, SCLK, SCKE), resto = out

	PDATC = ~0;
	PCONC = 0x55555555;		// PC[x] = out
	PUPC  = ~0;		 		// Pull-up disable

	PDATD = ~0;
	PCOND = 0x5555;			// PD[x] = out
	PUPD  = ~0;				// Pull-up disable

	PDATE = ~0;
	PCONE = 0x15555; 		// PE[x] = out
	PUPE  = ~0;		 		// Pull-up disable

	PDATF = ~0;
	PCONF = 0x002555; 		// PF[8] = in, PF[7] = in, resto = out
	PUPF  = ~0;			 	// Pull-up disable

	PDATG = ~0;
	PCONG = 0x5555;			// PG[x] = out
	PUPG  = ~0;		 		// Pull-up disable

	SPUCR = 0x7;			// DATA[15:0] Pull-up disable

	EXTINT = 0x22222222;	// Falling edge triggered
}


