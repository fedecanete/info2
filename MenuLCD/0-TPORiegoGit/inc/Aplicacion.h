/*
 * Aplicacion.h
 *
 *  Created on: 14/06/2013
 *      Author: Marcelo
 */

#ifndef APLICACION_H_
#define APLICACION_H_

#include "RegsLPC1769.h"
#include "GPIO.h"
#include "Oscilador.h"
#include "KitInfo2_BaseBoard.h"
#include "LCD.h"
#include "Teclado_5x1.h"
#include "Display-Expansion2.h"
#include "RTC.h"

<<<<<<< HEAD



uint8_t Teclado (void);
void Menu_LCD (uint8_t, uint8_t, uint8_t, uint8_t
=======
void Menu_LCD (uint8_t);

>>>>>>> 2edd432577076170eb85b31bfef12c9d077279d8
//Defines de  Teclado combinado con LCD
#define 	T_SUMAR			1
#define 	T_RESTAR		2
#define 	T_OK 			3
#define 	T_DESPLAZAR		4
#define 	T_LOBBY			5


#endif /* APLICACION_H_ */
