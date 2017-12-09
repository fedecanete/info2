/*
 * FW_Init_nRF.c
 *
 *  Created on: 14 de nov. de 2017
 *      Author: fedec
 */
#include "Aplicacion.h"
void Init_nRF(void)
{
	//!<Los únicos pines que se inicializan son CSN y CE

	//Pin CE (Conectado al SDA1 - P0.0)
	SetPINSEL (pin_CE,PINSEL_GPIO);
	SetDIR (pin_CE,SALIDA);
	SetPIN (pin_CE, 0);
	//Pin CSN (Conectado al SCL1 - P0.1)
	SetPINSEL (pin_CSN,PINSEL_GPIO);
	SetDIR (pin_CSN,SALIDA);
	SetPIN (pin_CSN, 1);

}
