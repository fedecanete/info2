/*
 * Aplicacion.h
 *
 *  Created on: 07/09/2013
 *      Author: marcelo
 */

#ifndef APLICACION_H_
#define APLICACION_H_

#include "FW_Display_Exp3.h"
#include "FW_GPIO.h"
#include "FW_SSP.h"
#include "KitInfo2_BaseBoard.h"
#include "Oscilador.h"
#include "RegsLPC1769.h"
#include "Teclado_4x1.h"
#include "Entradas.h"
#include "lcd.h"
#include "Timers.h"
#include "ssp.h"
#include "nRF24l01.h"
#include "FW_nRF.h"
void InicializarKit(void);
uint8_t Teclado( void );
#define REPOSO 0
#define LISTEN 1
#define STATUS 2


#define LED_ROJO_ON 	SetPIN(RGBR,1)
#define LED_ROJO_OFF	SetPIN(RGBR,0)
#define LED_VERDE_OFF	SetPIN(RGBG,0)
#define	LED_AZUL_ON		SetPIN(RGBB,1)
#define LED_AZUL_OFF	SetPIN(RGBB,0)


#endif /* APLICACION_H_ */
