 /**
 * Oscilador.h
 *
 *  Created on: 17/04/2012 -   Author: Mica y Chor
 */

#ifndef OSCILADOR_H_
#define OSCILADOR_H_


	//Prototipos de función:
	void InicPLL ( void );

	//Valores para configuracion del PLL:
	#define CLOCK_SETUP_Value 		1
	#define SCS_Value				0x00000020
	#define CLKSRCSEL_Value         0x00000001
	#define PLL0_SETUP_Value        1
	#define PLL0CFG_Value           0x00050063
	#define PLL1_SETUP_Value        1
	#define PLL1CFG_Value           0x00000023
	#define CCLKCFG_Value           0x00000003
	#define USBCLKCFG_Value         0x00000000
	#define PCLKSEL0_Value          0x00000000
	#define PCLKSEL1_Value          0x00000000
	#define PCONP_Value             0x042887DE
	#define CLKOUTCFG_Value         0x00000000
	#define FLASHCFG_Value			0x00004000

#endif /* OSCILADOR_H_ */
