#include "Aplicacion.h"

extern volatile int DemoraLCD;
extern volatile uint16_t segundos;
extern volatile int aux;
extern uint8_t f_refresh_LCD;

extern volatile uint8_t full_word;
extern volatile uint8_t led_blink;

static volatile int  aux_enviadas=0; //Contador de letras enviadas

void SysTick_Handler(void) {

	static volatile uint8_t decimas  = DECIMAS;

// Aquí escribo todo aquello que deseo que ocurra cada 2,5ms.

	BarridoDisplay();
	Dato_LCD();
	if ( Demora_LCD )
		Demora_LCD--;


	decimas-- ;
 	if( !decimas )	//pasaron 100ms
	{
		decimas = DECIMAS ;

		// Aquí escribo todo aquello que deseo que ocurra cada 100ms.
		if (GetPIN(LEDXpresso,1))SetPIN(LEDXpresso,0);
		else SetPIN (LEDXpresso,1);

		if (led_blink){

			GetPIN(RGBG,1)? SetPIN (RGBG,0): SetPIN (RGBG,1);

		}

		 AnalizarTimer();
		//Cuento segundos
		aux++;
		if (aux==10){
			segundos++;
			aux=0;
		}

	}

}


