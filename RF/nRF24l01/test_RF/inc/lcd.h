/*
 * lcd.h
 *
 *  Created on: 24/09/2013
 *      Author: gabriel
 *
 * LCD_D4	P0.5
 * LCD_D5	P0.10
 * LCD_D6	P2.4
 * LCD_D7	P2.5
 * LCD_E	P0.4
 * LCD_RST	P2.6
 *
 **/

#ifndef LCD_H_
#define LCD_H_

#include "KitInfo2_BaseBoard.h"


void InitLCD (void);
void ConfigLCD(void);
uint8_t PushLCD (uint8_t dato, uint8_t control);
int PopLCD (void);
void Dato_LCD(void);

extern volatile uint32_t Demora_LCD;


#define		LCD_CONTROL			1
#define		LCD_DATA			0

#define 	RENGLON_1			0
#define 	RENGLON_2			1


#define		LCD_OFF				0x08
#define		LCD_ON				0x0C		// cursor off blink off
#define		LCD_CLEAR			0x01
#define 	CURSOR_ON			0x0E
#define		BLINK_ON			0x0D
#define 	LCD_CURSORON		0x0F
#define 	LCD_CURSOROFF		0x0C
#define 	LCD_CURSORDEC		0x10
#define 	LCD_CURSORINC		0x14
#define 	CURSOR				0x7E
#define		LCD_HOME1			0x80
#define		LCD_HOME2			0xA8

#define		IDLE				0
#define		NIBLE1_CMD			1
#define		NIBLE2_CMD			2
#define		LATCH_CMD			3
#define		NIBLE1_POS			4
#define		NIBLE2_POS			5
#define		LATCH_POS			6
#define		NIBLE1_DATO			7
#define		NIBLE2_DATO			8
#define		LATCH_DATO			9

#define LCDBUFFER_SIZE	160

#define LARGO_RENGLON	16

#define TOPE_BUFFER_LCD 160

void DisplayLCD (char * msg, uint8_t r , uint8_t pos);



#endif /* LCD_H_ */
