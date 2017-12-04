/*
 * ssp.h
 *
 *  Created on: 13 de oct. de 2017
 *      Author: fedec
 */

#ifndef SSP_H_
#define SSP_H_

#include "RegsLPC1769.h"

#define PCSSP0	21
#define PCSSP1	10

#define PCLK_SSP0 10
#define PCLK_SSP1 20

//Pines
#define MOSI0 	0,18
#define MISO0	0,17
#define SCK0	0,15
#define SSEL0	0,16

#define MOSI1 	0,9
#define MISO1 	0,8
#define SCK1	0,7
#define SSEL1	0,6



//!< /////////////		SSP		///////////////////////////
//!< Tipo de dato específico para manejar SSP0 y SSP1
typedef struct {
	union {
		__RW uint32_t _SSPxCR0;
		struct {
			__RW uint32_t _DSS :4;
			__RW uint32_t _FRF :2;
			__RW uint32_t _CPOL :1;
			__RW uint32_t _CPHA :1;
			__RW uint32_t _SCR :8;
			__RW uint32_t _RESERVED :16;
		} crbits;
	};

	__RW uint32_t _SSPxCR1;

	union {
			__RW uint32_t _SSPxDR;			//Data Register
			struct {
				__RW uint32_t _SSPxDATA :16;
				__RW uint32_t _RESERVED :16;
			} drbits;
		};

	__R uint32_t _SSPxSR; //Status Register (Read Only)
	__RW uint32_t _SSPxCPSR; //Clock Prescale Register
	__RW uint32_t _SSPxIMSC; //Interrupt Mask Set and Clear Register
	__RW uint32_t _SSPxRIS; //Raw Interrupt Status Register
	__RW uint32_t _SSPxMIS; //Masked Interrupt Status Register
	__RW uint32_t _SSPxICR; //SSPICR Interrupt Clear Register
	__RW uint32_t _SSPxDMACR; //DMA Control Register
} ssp_t;

//////////////        FIN ESTRUCTURA          ////////////////




//!< 0x4008 8000: Comienzo del bloque SSP0

#define 	DIR_SSP0		( (ssp_t *) 0x40088000 )

	#define		SSP0CR0		DIR_SSP0->_SSPxCR0
		#define		SSP0_DSS	DIR_SSP0->crbits._DSS
		#define		SSP0_FRF	DIR_SSP0->crbits._FRF
		#define		SSP0_CPOL	DIR_SSP0->crbits._CPOL
		#define		SSP0_CPHA	DIR_SSP0->crbits._CPHA
		#define		SSP0_SCR	DIR_SSP0->crbits._SCR

	#define		SSP0CR1		DIR_SSP0->_SSPxCR1

	#define		SSP0DR		DIR_SSP0->_SSPxDR
		#define		SSP0DATA	DIR_SSP0->drbits._SSPxDATA

	#define		SSP0SR		DIR_SSP0->_SSPxSR
	#define		SSP0CPSR	DIR_SSP0->_SSPxCPSR
	#define		SSP0IMSC	DIR_SSP0->_SSPxIMSC
	#define		SSP0RIS		DIR_SSP0->_SSPxRIS
	#define		SSP0MIS		DIR_SSP0->_SSPxMIS
	#define		SSP0ICR		DIR_SSP0->_SSPxICR
	#define		SSP0DMACR	DIR_SSP0->_SSPxDMACR


//!< 0x4003 0000: Comienzo del bloque SSP0

#define 	DIR_SSP1		( (ssp_t *) 0x40030000 )

	#define		SSP1CR0		DIR_SSP1->_SSPxCR0
		#define		SSP1_DSS	DIR_SSP1->crbits._DSS
		#define		SSP1_FRF	DIR_SSP1->crbits._FRF
		#define		SSP1_CPOL	DIR_SSP1->crbits._CPOL
		#define		SSP1_CPHA	DIR_SSP1->crbits._CPHA
		#define		SSP1_SCR	DIR_SSP1->crbits._SCR

	#define		SSP1CR1		DIR_SSP1->_SSPxCR1

	#define		SSP1DR		DIR_SSP1->_SSPxDR
		#define		SSP1DATA	DIR_SSP1->drbits._SSPxDATA

	#define		SSP1SR		DIR_SSP1->_SSPxSR
	#define		SSP1CPSR	DIR_SSP1->_SSPxCPSR
	#define		SSP1IMSC	DIR_SSP1->_SSPxIMSC
	#define		SSP1RIS		DIR_SSP1->_SSPxRIS
	#define		SSP1MIS		DIR_SSP1->_SSPxMIS
	#define		SSP1ICR		DIR_SSP1->_SSPxICR
	#define		SSP1DMACR	DIR_SSP1->_SSPxDMACR



//Bits de CR1
#define CR1_LBM 0
#define CR1_SSE	1
#define CR1_MS	2
#define CR1_SOD	3

//Bits de SR
#define TFE 0
#define TNF 1
#define RNE 2
#define RFF 3
#define BSY 4

//Bits de IMSC
#define RORIM 	0
#define RTIM 	1
#define RXIM 	2
#define TXIM 	3

//Bits de RIS

#define RORRIS	0
#define RTRIS	1
#define RXRIS	2
#define TXRIS	3

//Bits de MIS

#define RORMIS	0
#define RTMIS	1
#define RXMIS	2
#define TXMIS	3

//Bits del ICR

#define RORIC	0
#define RTIC	1

//NVIC
#define ISE_SSP0 14
#define ISE_SSP1 15

#define TOPE_SSP1 25


#endif /* SSP_H_ */
