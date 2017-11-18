/*
 * FW_nRF.c
 *
 *  Created on: 18 de nov. de 2017
 *      Author: fedec
 */
#include "Aplicacion.h"

void nRF_Init_as_Tx (void)
{
	//delay100ms // Allow radio to reach power down if shut down

	uint8_t val[5]; //An axuliary array to send data to RWnRF function

	//1. EN_AA - (enable auto-acknowledgments) - Transmitter gets automatic response from receiver when successfull transmission! (lovely function!)
	//Only works if Transmitter has identical RF_Adress on its channel ex: RX_ADDR_P0=TX_ADDR
	val[0]=0;
	val[0]|=(1<<ENAA_P0); //Enable auto ack on data pipe 0 (bit 0 en '1')
	RWnRF (W_REGISTER, EN_AA, val, 1);

	//2. Choose number of enabled data pipes (up to 5)
	val[0]=0;
	val[0]|=(1<<ERX_P0); //Enable data pipe 0
	RWnRF (W_REGISTER, EN_RXADDR, val, 1);

	//3. RF_Address width setup (how many bytes is the receiver address, the more the merrier 1-5)
	val[0]=AW_5BYTES; //0b0000 0011 = 5 bytes RF_Address
	RWnRF (W_REGISTER, SETUP_AW, val, 1);

	//4. RF Channel Setup - Choose frequency: 2,4 - 2,527 GHz  1MHz/step
	val[0]=1; //0b0000 0001 = 2,401GHz (same on Tx and Rx)
	RWnRF (W_REGISTER, RF_CH, val, 1);

	//5. RF Setup - Choose power mode and data speed.
	val[0]=0;
	//Dejamos PLL_LOCK (bit 4)en 0 (default)
	//Data rate
	val[0]|=(1<<RF_DR); //Data rate (bit 3):	'0'= 1Mbps (longer range)
						//						'1'= 2Mbps
	//Power in TX mode
	val[0]|=(3<<1); /*bits (2:1)="00": -18dBm
								"01" : -12dBm
								"10" : -6dBm
								"11" : 0dBm
	*/
	val[0]|=(1<<LNA_HCURR); //Setup LNA gain in default value
	RWnRF (W_REGISTER, RF_SETUP, val, 1);


	//6. Rx RF_Address setup 5 bytes - Set Receiver Address (set RX_ADDR_P0 = TX_ADDR if EN_AA is enabled!)
	uint8_t i;
	for (i=0; i<5;i++)
		val[i]=0x12; //Una dirección arbitraria: 0x1212121212
	RWnRF (W_REGISTER, RX_ADDR_P0, val, 5); //Since we chose pipe 0 on EN_EXADDR we give this address to that channel.
	//Here you can give differents addresses to different channels (if they're enabled in EN_RXADDR) to listen on several different transmitters)

	//7. Tx RF_Address Setup 5 bytes - Set Transmitter address (not used in a receiver but can be set anyway)
	for (i=0; i<5; i++)
		val[i]=0x12; //Same on the Receiver chip and the RX-RF_Address above if EN_AA is enabled!!
	RWnRF (W_REGISTER, TX_ADDR, val, 5);

	//8. Payload Width Setup (How many bytes to send per transmission) - 1 to 32 bytes
	val[0]=5; //Send 5 bytes per package this time (same on receiver and transmitter)
	RWnRF (W_REGISTER, RX_PW_P0, val, 1);

	//9. CONFIG Register Setup - Encender el módulo y decirle si es Transmisor o Receptor
	val[0]=0;
	val[0]|=(1<<MASK_MAX_RT); //(bit 4='1')IRQ interrupt is not triggered if transmission failed
	val[0]|=(1<<EN_CRC);//Enable CRC
	val[0]|=(1<<CRCO); //CRC encoding scheme: 2bytes
	val[0]|=(1<<PWR_UP); //Encender el módulo
	val[0]|=(0<<PRIM_RX); /*bit 0:	'0'=Transmitter
									'1'=Receiver
	*/
	RWnRF (W_REGISTER, CONFIG, val, 1);

	//delay
	//Device needs 1.5ms to reach standby mode (CE=low)
}
