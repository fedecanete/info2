#include "Aplicacion.h"

extern volatile uint16_t DemoraLCD;

void SysTick_Handler ( void );

void SysTick_Handler(void)
{
	BarridoDisplay();
	DriverTeclado();
	if (DemoraLCD) DemoraLCD--;
}
