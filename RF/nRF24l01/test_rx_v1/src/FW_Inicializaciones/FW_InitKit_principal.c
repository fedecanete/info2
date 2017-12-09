/*
 * KitInic.c
 */

#include "Aplicacion.h"

void InicSysTick(void);
extern void Inicializar_Expansion3(void);
void InicializarKit(void);
extern void Inicializar_SSP1 (void);

//-----------------------------------------------------------------------------
// Configuración del SysTick para 10ms
//-----------------------------------------------------------------------------
void InicSysTick(void) { //si divido x 4, interrumpe cada 2,5ms
	STRELOAD = (STCALIB / 4) - 1;   //N=1 para 10ms
	STCURR = 0;

	ENABLE = 1;
	TICKINT = 1;
	CLKSOURCE = 1;
	return;
}

//-----------------------------------------------------------------------------
// Inicialización general del Kit de acuerdo al uso que se le dará.
//-----------------------------------------------------------------------------
void InicializarKit(void) {
	InicPLL();
	Inicializar_Teclado();				// Inicializa las teclas d ela placa base
	Inicializar_Relay();
	Inicializar_RGB();
	Inicializar_LEDs();
	Inicializar_Buzzer();

// ESCRIBIR CODIGO DE OTRAS INICIALIZACIONES A PARTIR DE AQUI   <<<-----------------------
	InicSysTick();
	Inicializar_Expansion3();
	InitLCD();
	Inicializar_SSP1();
	nRF_TxRx_Init (RECEIVER, 0, 1, 5,1);

}

