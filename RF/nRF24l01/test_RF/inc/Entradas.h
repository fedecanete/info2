/*
 * Entradas.h
 *
 *  Created on: 30/03/2013
 *      Author: Marcelo
 */

#ifndef ENTRADAS_H_
#define ENTRADAS_H_

extern volatile uint8_t BufferEntradas;				//Buffer de Entradas Digitales

	//---Aquí defino nombres de fantasía para identificar a cada uno de los bits de 'BufferEntradas'
	//---que a su vez representan las entradas digitales del HW. Qué bit corresponde a qué entrada queda
	//---definido en la función debounce().
	#define		PUERTA_ABIERTA	( ( BufferEntradas)      & 0x01 )
	#define		PB				( ( BufferEntradas >> 1 ) & 0x01 )
	#define		P1				( ( BufferEntradas >> 2 ) & 0x01 )
	#define		P12				( ( BufferEntradas >> 3 ) & 0x01 )
	#define		P2				( ( BufferEntradas >> 4 ) & 0x01 )

	//--------------------------------------------------------------

	#define		ACEPTAReSTADO	10		//arbitrario
	#define		ENTRADAS		5		// KEY4_RC, KEY3_RC, KEY2, KEY1 y KEY0

	/** -------------------------------------------------------------------------------------
	 * Prototipos
	 */
	void Debounce(void);

#endif /* ENTRADAS_H_ */
