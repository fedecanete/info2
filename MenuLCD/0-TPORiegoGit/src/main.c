/*
===============================================================================
 Name        : 0-TPORiego.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "Aplicacion.h"

volatile uint8_t msgDisplay[DIGITOS];			//!< Buffer del display
volatile uint8_t buffKey;						//!< Buffer del teclado
volatile uint16_t DemoraLCD;					//!< Demora LCD por Systick
volatile uint8_t Temperatura=24;				//!< Temperatura del ambiente en ºC
volatile uint8_t Humedad_T=80;					//!< Humedad de la tierra (%)
volatile uint8_t Humedad_A=53;					//!< Humedad del ambiente (%)
volatile uint8_t flag_RiegoAut;					//!< Flag de interrupción por alarma (RTC)
volatile uint8_t flag_IntMinutos;				//!< Flag de interrupción por incrementos del contador minutos (RTC)

int main(void) {


	InicializarKit ();

    while(1) {
    	Menu_LCD (Teclado());
    	Displays7seg(Humedad_T, DSP_HUMEDAD);
    	Displays7seg(Temperatura, DSP_TEMPERATURA);
    }

    return 0 ;
}



