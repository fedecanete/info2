#include "Aplicacion.h"

void InicializarKit ( void )
{
	InicPLL();
	InicSysTick();

	Inicializar_Teclado();
	Inicializar_Displays7seg();
	Inic_LCD();

	SetPINSEL (RGBB, PINSEL_GPIO);
	SetPINSEL (RGBG, PINSEL_GPIO);
	SetPINSEL (RGBR, PINSEL_GPIO);
	SetDIR (RGBB, SALIDA);
	SetDIR (RGBG, SALIDA);
	SetDIR (RGBR, SALIDA);
	SetPIN (RGBB, OFF);
	SetPIN (RGBG, OFF);
	SetPIN (RGBR, OFF);
}
