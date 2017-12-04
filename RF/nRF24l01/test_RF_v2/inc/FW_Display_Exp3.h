/*
 * FW_Display_Exp3.h
 *
 *  Created on: 07/09/2013
 *      Author: marcelo
 */

#ifndef FW_DISPLAY_EXP3_H_
#define FW_DISPLAY_EXP3_H_


	#include "Aplicacion.h"

	/** -------------------------------------------------------------------------------------
	 *PLACA EXPANSION 3
	 */
	//!< Display
	#define		BCD_A			EXPANSION0
	#define		BCD_B			EXPANSION1
	#define		BCD_C			EXPANSION2
	#define		BCD_D			EXPANSION3
	#define		EXP3_dp			EXPANSION4


	#define		BCD_RST			EXPANSION6
	#define		BCD_CLOCK		EXPANSION5


	#define		DIGITOS			6

	#define		DSP0			0			//!< Display verde
	#define		DSP1			1

	//!< Teclado
	#define		FILA0			EXPANSION7
	#define		FILA1			EXPANSION8
	#define		FILA2			EXPANSION9
	#define		FILA3			EXPANSION10
	#define		COL0			EXPANSION11
	#define		COL1			EXPANSION12


	/** -------------------------------------------------------------------------------------
	 * Prototipos
	 */
		//#define DOSDISPLAYS
		#ifdef  DOSDISPLAYS
			void Display(uint16_t ,uint8_t );
		#else
			void Display (uint32_t );
		#endif

	void BarridoDisplay(void);

#endif /* FW_DISPLAY_EXP3_H_ */
