/**
 	\file KitInfo2.h
 	\brief Configuracion de Infotronic
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/

#ifndef DISPLAY_H_
#define DISPLAY_H_

	#include "Aplicacion.h"

	/** -----------------------------------------------------------------------
	 *PLACA EXPANSION 2
	 */
	#define		digito0			EXPANSION0	//PORT2,7	//!< Display 7 Segmentos
	#define		digito1			EXPANSION1	//PORT1,29
	#define		digito2			EXPANSION2	//PORT4,28
	#define		digito3			EXPANSION3	//PORT1,23
	#define		digito4			EXPANSION4	//PORT1,20
	#define		digito5			EXPANSION5	//PORT0,19

	#define		segmento_a		EXPANSION6	//PORT3,26
	#define		segmento_b		EXPANSION15	//PORT1,18
	#define		segmento_c		EXPANSION14	//PORT1,21
	#define		segmento_d		EXPANSION13	//PORT1,24
	#define		segmento_e		EXPANSION12	//PORT1,27
	#define		segmento_f		EXPANSION11	//PORT3,25
	#define		segmento_g		EXPANSION10	//PORT0,20
	#define		segmento_dp		EXPANSION9	//PORT1,19

	#define		DIGITO_0			0			//!< Numero de Digito
	#define		DIGITO_1			1
	#define		DIGITO_2			2
	#define		DIGITO_3			3
	#define		DIGITO_4			4
	#define		DIGITO_5			5

	#define		DIGITOS				6

	#define		DSP_HUMEDAD			0			//!< Display indicador de humedad
	#define		DSP_TEMPERATURA		1			//!< Display indicador de temperatura

	#define		DIG_HACHE			0x76		//!< Digito Hache en 7seg
	#define		DIG_GRADOS			0x63		//!< Digito Grados en 7seg


	/** ----------------------------------------------------------------------
	 * Prototipos
	 */
		void BarridoDisplay( void );
		void Displays7seg (uint8_t , uint8_t );


#endif
