/**
 \file KitInfo2PR_7Seg.c
 \brief Primitiva de Display de 7 segmentos
 \details Valida para Expansion 2 y Expansion 3
 \author Ing. Marcelo Trujillo
 \date 2012.04.25
 */

#include "FW_Display_Exp3.h"
#include "RegsLPC1769.h"

extern volatile uint8_t msgDisplay[DIGITOS];			//!< Buffer de display
/**
 Tabla de conversion bcd a 7 segmentos
 Codigo bcd		a	b	c	d	e	f	g   dp
 0				1	1	1	1	1	1	0   0
 1				0	1	1	0	0	0	0
 2				1	1	0	1	1	0	1
 3				1	1	1	1	0	0	1
 4				0	1	1	0	0	1	1
 5				1	0	1	1	0	1	1
 6				0	0	1	1	1	1	1
 7				1	1	1	0	0	0	0
 8				1	1	1	1	1	1	1
 9				1	1	1	0	0	1	1
 */
uint8_t Tabla_Digitos_BCD_7seg[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

/**
 \fn  void Display(int Val,char dsp)
 \brief Presentacion de valores en el display de 3 dígitos
 \param [in] val valor a mostrar
 \param [in] dsp seleccion del sector del display
 \return void
 */
//#define DOSDISPLAYS	/*activar para trabajar con 2 displays de 3 dígitos*/
#ifdef  DOSDISPLAYS

void Display(uint16_t Val, uint8_t dsp)
{
	uint8_t i;
	uint8_t auxDisplay[3];
	auxDisplay[0] =auxDisplay[1] =auxDisplay[2]=0;

	//* Convierto a 7 Seg.
	for(i = 0; i<DIGITOS/2; i++ )
	{
		auxDisplay[i] = Tabla_Digitos_BCD_7seg[Val%10];
		Val /= 10;
	}

	switch(dsp)
	{
		case DSP0:
			msgDisplay[ 2 ] = auxDisplay[ 0 ];
			msgDisplay[ 1 ] = auxDisplay[ 1 ];
			msgDisplay[ 0 ] = auxDisplay[ 2 ];
			break;

		case DSP1:
			msgDisplay[ 5 ] = auxDisplay[ 0 ];
			msgDisplay[ 4 ] = auxDisplay[ 1 ];
			msgDisplay[ 3 ] = auxDisplay[ 2 ];
			break;
	}
}

#else
/**
 \fn  void Display(int Val)
 \brief Presentacion de valores en el display de 6 dígitos
 \param [in] val valor a mostrar
 \return void
 */

void Display(uint32_t Val) {
	uint8_t i;
	//	for (i = 0; i < DIGITOS; i++) {
	//		msgDisplay[i] = Tabla_Digitos_BCD_7seg[Val % 10];
	////		msgDisplay[i] = Val % 10;
	//		Val /= 10;
		for (i = DIGITOS-1; i ; i--) {
			msgDisplay[i] = Tabla_Digitos_BCD_7seg[Val % 10];
	//		msgDisplay[i] = Val % 10;
			Val /= 10;
		}
		msgDisplay[0] = Tabla_Digitos_BCD_7seg[Val];
}

#endif
