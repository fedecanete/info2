/*
 * FW_InicTeclado5x1.c
 *
 *  Created on: 17 de oct. de 2017
 *      Author: Lucas
 */

#include "Aplicacion.h"

void Inicializar_Teclado( void )
{
	SetPINSEL ( KEY0 , PINSEL_GPIO);
	SetPINSEL ( KEY1 , PINSEL_GPIO);
	SetPINSEL ( KEY2 , PINSEL_GPIO);
	SetPINSEL ( KEY3_RC , PINSEL_GPIO);
	SetPINSEL ( KEY4_RC , PINSEL_GPIO);

	SetDIR ( KEY0 , ENTRADA);
	SetDIR ( KEY1 , ENTRADA);
	SetDIR ( KEY2 , ENTRADA);
	SetDIR ( KEY3_RC , ENTRADA);
	SetDIR ( KEY4_RC , ENTRADA);

	SetPINMODE ( KEY0 , PINMODE_PULLUP);
	SetPINMODE ( KEY1 , PINMODE_PULLUP);
	SetPINMODE ( KEY2 , PINMODE_PULLUP);
}
