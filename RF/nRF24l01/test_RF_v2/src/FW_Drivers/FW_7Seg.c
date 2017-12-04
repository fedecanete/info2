/**
 \file KitInfo2FW_7Seg.c
 \brief Drivers del display de 7 segmentos
 \details Expansion 2
 \author Ing. Marcelo Trujillo
 \date 2012.04.25
 */

#include "KitInfo2_BaseBoard.h"
#include "FW_GPIO.h"
#include "FW_Display_Exp3.h"

extern volatile uint8_t msgDisplay[];		//!< Buffer de display
void BarridoDisplay(void);
/**
 \fn void BarridoDisplay( void )
 \brief Barrido del display de 7 segmentos
 \param void
 \return void
 */

void BarridoDisplay(void)
{
	static uint8_t i = 0;

	SetPIN(BCD_A, (msgDisplay[i] & 	  (uint8_t) 0x01) );
	SetPIN(BCD_B, (msgDisplay[i]>>1 & (uint8_t) 0x01));
	SetPIN(BCD_C, (msgDisplay[i]>>2 & (uint8_t) 0x01));
	SetPIN(BCD_D, (msgDisplay[i]>>3 & (uint8_t) 0x01));

	if(!i) { //reseteo al comienzo de cada ciclo
		SetPIN (BCD_RST, ON);
		SetPIN (BCD_RST, OFF);
	}
	else {	//produzco el desplazamiento de dígito con un clock
		SetPIN (BCD_CLOCK, ON);
		SetPIN (BCD_CLOCK, OFF);
	}
	i++;
	i%= DIGITOS;
}
