#include "Aplicacion.h"

void Inic_PinesLCD(void)
{
	SetPINSEL(LCD_RS,PINSEL_GPIO);
	SetDIR(LCD_RS,SALIDA);
	SetMODE_OD(LCD_RS, OPEN_DRAIN);
	SetPIN(LCD_RS,OFF);

	SetPINSEL(LCD_E,PINSEL_GPIO);
	SetDIR(LCD_E,SALIDA);
	SetMODE_OD(LCD_E,OPEN_DRAIN);
	SetPIN(LCD_E,OFF);

	SetPINSEL(LCD_D4,PINSEL_GPIO);
	SetDIR(LCD_D4,SALIDA);
	SetMODE_OD(LCD_D4,OPEN_DRAIN);
	SetPIN(LCD_D4,OFF);

	SetPINSEL(LCD_D5,PINSEL_GPIO);
	SetDIR(LCD_D5,SALIDA);
	SetMODE_OD(LCD_D5,OPEN_DRAIN);
	SetPIN(LCD_D5,OFF);

	SetPINSEL(LCD_D6,PINSEL_GPIO);
	SetDIR(LCD_D6,SALIDA);
	SetMODE_OD(LCD_D6,OPEN_DRAIN);
	SetPIN(LCD_D6,OFF);

	SetPINSEL(LCD_D7,PINSEL_GPIO);
	SetDIR(LCD_D7,SALIDA);
	SetMODE_OD(LCD_D7,OPEN_DRAIN);
	SetPIN(LCD_D7,OFF);
}

void Inic_LCD (void)
{
	Inic_PinesLCD();		// Configura pines de interfaz con LCD
	LCDDelay(100);			// 400 Demora inicial para dejar que todo se estabilice

	LCDDelay(10); 			// 25ms
	WComando4(0x30);

	LCDDelay(3);			// 7,5ms
	WComando4(0x30);

	LCDDelay(2);			// 5ms
	WComando4(0x30);

	// A partir de aca se puede chequear BF
	LCDDelay(2);			// 5ms
	WComando4(0x20);		// 4 bits

	LCDDelay(2);			// 5ms
	WComando4(0x20);		// 4 bits

	LCDDelay(2);			// 5ms
	WComando4(0x80);		// Clear del LCD

	LCDDelay(2);			// 5ms
	WComando4(0x00);		// Display y cursos off

	LCDDelay(2);			// 5ms
	WComando4(0xC0);		// Display de dos lineas caractetes de 5x11

	LCDDelay(2);			// 5ms
	WComando8(LCD_CLEAR);	// Limpia LCd y va a Home

	WComando8(BLINK_ON);
	LCD_Menu ();
}
