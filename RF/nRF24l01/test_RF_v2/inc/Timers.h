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

	// ***********Tiempos Para base de tiempo 2,5mS**********
	#define DECIMAS		40
	#define DELAY_5ms	2
	#define DELAY_10ms	4
	#define DELAY_50ms	20
	#define DELAY_100ms	40

// --- prototipo de funciones
	void TmrStart(uint8_t ,uint8_t);
	void TmrClose(void);
	void TmrStop(uint8_t );
	void AnalizarTimer(void);
	void TmrEvent(void);

#endif
