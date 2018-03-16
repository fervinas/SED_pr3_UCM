#ifndef __SYSTEM_H__
#define __SYSTEM_H__


/* Modos de operación */
#define USRMODE (0x10)
#define FIQMODE (0x11)
#define IRQMODE (0x12)
#define SVCMODE (0x13)
#define ABTMODE (0x17)
#define UNDMODE (0x1b)
#define SYSMODE (0x1f)

#define IRQ_NESTING_ENABLE                        \
    asm volatile ( "mrs   lr, spsr" );            \
	asm volatile ( "stmfd sp!, {lr}" );           \
	asm volatile ( "msr   cpsr_c, #0b00011111" ); \
	asm volatile ( "stmfd sp!, {lr}" );

#define IRQ_NESTING_DISABLE                       \
    asm volatile ( "ldmfd sp!, {lr}" );           \
	asm volatile ( "msr   cpsr_c, #0b10010010" ); \
	asm volatile ( "ldmfd sp!, {lr}" );           \
	asm volatile ( "msr   spsr, lr" );

#define GET_SWI_NUMBER( var )                               \
    asm volatile ( "ldr %0, [lr, #-4]" : "=r" (var) : );       \
	asm volatile ( "bic %0, %0, #0xff000000" : "=r" (var) : );
	
#define SWI( var ) asm volatile ( "swi %0" : : "i" (var) );

#define NOP asm( "nop" );

#define INT_DISABLE \
    asm volatile( "mrs   r0, cpsr" : : : "r0" ); \
	asm volatile( "stmfd sp!, {r0}" ); \
	asm volatile( "orr   r0, r0, #0b11000000" ); \
	asm volatile( "msr   cpsr_c, r0" );
	
#define INT_ENABLE \
    asm volatile( "ldmfd sp!, {r0}" : : : "r0" ); \
	asm volatile( "msr   cpsr_c, r0" );

#define TEST_AND_SET( dir, value ) \
    asm volatile( "mov r0, #1" : : : "r0" ); \
    asm volatile( "swp %0, r0, [%1]" : "=r" (value) : "r" (dir) );
    
#define CHANGE_OPMODE( mode )                                 \
	asm volatile ( "mrs r0, cpsr" : : : "r0" );   \
    asm volatile ( "bic r0, r0, #0x1f" );         \
    asm volatile ( "orr r0, r0, %0" : : "i" (mode) ); \
  	asm volatile ( "msr cpsr_c, r0" );    


void sys_init( void );

#endif
