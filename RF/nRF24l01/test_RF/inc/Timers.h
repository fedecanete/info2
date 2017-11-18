#ifndef TIMERS_H_
#define TIMERS_H_

	#define			TIMERS			8

	// --- Eventos
	#define			EVENTO0		0	//Evento cada 1 décima de seg
	#define			EVENTO1		1	//Evento cada 1 segundo
	#define			EVENTO2		2	//Evento cada 5 segundos

	// ***********Tiempos Para base de tiempo 100mS**********
	#define			T_500mS		5
	#define			T_1SEG		10
	#define			T_3SEG		30
	#define			T_5SEG		50

	#define DECIMAS		40		//la cuenta es para ticks de2,5ms.

// --- prototipo de funciones
	void TmrStart(uint8_t ,uint8_t);
	void TmrClose(void);
	void TmrStop(uint8_t );
	void AnalizarTimer(void);
	void TmrEvent(void);

#endif
