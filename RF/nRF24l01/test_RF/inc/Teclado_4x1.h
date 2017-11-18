/*
 * Teclado_4x1.h
 *
 *  Created on: 30/09/2013
 *      Author: marcelo
 */

#ifndef TECLADO_4X1_H_
#define TECLADO_4X1_H_

	#include "Aplicacion.h"

	#define		SW1			1
	#define		SW2			2
	#define		SW3			3
	#define		SW4			4
	#define		SW5			5
	#define		SW6			6
	#define		SW7			7
	#define		SW8			8

	#define     SW1_OFF     GetPIN(COL0,ACTIVO_BAJO)
	#define     SW2_OFF     GetPIN(COL0,ACTIVO_BAJO)
	#define     SW3_OFF     GetPIN(COL0,ACTIVO_BAJO)
	#define     SW4_OFF     GetPIN(COL0,ACTIVO_BAJO)
	#define     SW5_OFF     GetPIN(COL1,ACTIVO_BAJO)
	#define     SW6_OFF     GetPIN(COL1,ACTIVO_BAJO)
    #define     SW7_OFF     GetPIN(COL1,ACTIVO_BAJO)
    #define     SW8_OFF     GetPIN(COL1,ACTIVO_BAJO)

	#define 	CANT_REBOTES	10 //valor empírico
	#define		REPOSO			0
	#define		DETECCION		1
	#define		CHEQUEO			2
	#define		EMERGENCIA		CHEQUEO
	#define		NO_KEY			(uint8_t) 0xFF

	/** -------------------------------------------------------------------------------------
	 * Prototipos
	 */
	void DriverTeclado(void);
	void TecladoSW (uint8_t);
	uint8_t TecladoHW (void);


#endif /* TECLADO_4X1_H_ */
