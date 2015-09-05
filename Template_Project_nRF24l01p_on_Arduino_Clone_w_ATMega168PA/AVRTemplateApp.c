/*
 * nrf24l01p_Test.c
 *
 * Created: 05.01.2014 15:50:40
 *  Author: cc
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "BaseTmr.h"
#include "Port.h"
#include "Dio_Driver.h"
#include "ADC.h"
#include "UART.h"
#include "nRF24L01.h"
#include "mirf.h"
#include "spi.h"
#include <avr/interrupt.h>

int main(void)
{
	volatile uint8_t u08Toggle;
	volatile uint32_t u32AdcVal;

	uint8_t u08Cnt;
	uint8_t u08MirfReg;
	uint8_t au08MirfBuffer[mirf_PAYLOAD];
	
	Port_init();
	BaseTmr_Init();
	UART_init();
	//ADC_init(ADC_RM_Poll);

	
	// Initialize AVR for use with mirf
	mirf_init();
	// Wait for mirf to come up
	_delay_ms(50);
	// Activate interrupts
	sei();
	// Configure mirf
	mirf_config();
	
	// UART example
	UART_puts("nrf24l01p_Test\r\n");
	
	
	mirf_read_register(CONFIG,&u08MirfReg,1);
	if (u08MirfReg == 75)
	{
		UART_puts("Module correctly configured\r\n");
	}
	else
	{
		UART_puts("Module not correctly configured\r\n");	
	}
	
	//read back rx/tx addresses
	UART_puts("Module Configuration\r\n");

	UART_puts("TX Adress: ");
	mirf_read_register(TX_ADDR,&au08MirfBuffer[0],5);
	for(uint8_t u08Idx=0;u08Idx<5;u08Idx++)
	{
		UART_Tx_uint08(au08MirfBuffer[u08Idx]);
		UART_putc(' ');
	}
	UART_puts("\r\n");

	UART_puts("RX Adress (Pipe 0): ");
	mirf_read_register(RX_ADDR_P0,&au08MirfBuffer[0],5);
	for(uint8_t u08Idx=0;u08Idx<5;u08Idx++)
	{
		UART_Tx_uint08(au08MirfBuffer[u08Idx]);
		UART_putc(' ');
	}
	UART_puts("\r\n");


	UART_puts("RX Adress (Pipe 1): ");
	mirf_read_register(RX_ADDR_P1,&au08MirfBuffer[0],5);
	for(uint8_t u08Idx=0;u08Idx<5;u08Idx++)
	{
		UART_Tx_uint08(au08MirfBuffer[u08Idx]);
		UART_putc(' ');
	}
	UART_puts("\r\n");


	u08Toggle=250;

	while(1)
	{
		BaseTmr_WaitForNextTimeSlot_10ms();
		if (u08Toggle==10)
		{
			u08Toggle=0;
	
	/*
			mirf_read_register(CONFIG,&u08MirfReg,1);
			
			UART_puts("CONFIG REG: ");
			UART_Tx_uint08(u08MirfReg);
			UART_puts("        ");
			
			mirf_read_register(STATUS,&u08MirfReg,1);
			UART_puts("STATUS REG: ");
			UART_Tx_uint08(u08MirfReg);
			UART_puts("\r\n");
			
		*/	
			//check for new data
			mirf_read_register(STATUS,&u08MirfReg,1);
			if (u08MirfReg & 0x40)
			{
				//data available
				mirf_get_data(&au08MirfBuffer[0]);
				UART_puts("Data received:\r\n");
				UART_puts("Raw: ");
				for(uint8_t u08Idx=0;u08Idx<mirf_PAYLOAD;u08Idx++)
				{
					UART_Tx_uint08(au08MirfBuffer[u08Idx]);
					UART_putc(' ');
				}
				UART_puts("\r\n");	
				
				UART_puts("ASCII: ");
				for(uint8_t u08Idx=0;u08Idx<mirf_PAYLOAD;u08Idx++)
				{
					UART_putc(au08MirfBuffer[u08Idx]);
					UART_putc(' ');
				}
				UART_puts("\r\n");
			}

			/*
			mirf_read_register(CD,&u08MirfReg,1);
			UART_puts("RPD REG: ");
			UART_Tx_uint08(u08MirfReg);
			UART_puts("\r\n");			
			*/
			/*
			mirf_read_register(XXX,&u08MirfReg,1);
			UART_puts("XXX REG: ");
			UART_Tx_uint08(u08MirfReg);
			UART_puts("\r\n");
			*/
			
			/* ******************************************************* */
			/* ADC Test */
			/*
			u32AdcVal = (uint32_t)ADC_u16SampleChannel(ADC_IN_1,1000);
			u32AdcVal *= 330;
			u32AdcVal /= 1024;
			UART_puts("Voltage on ADC input 1: ");
			UART_Tx_uint16((uint16_t)u32AdcVal);
			UART_puts("\r\n");
			*/
			
			
			/* ******************************************************* */
			/* UART Rx Test */
			uint16_t u16RxData;
			u16RxData = UART_Rx();
			if (u16RxData != 0xFFFF)
			{
				UART_puts("Received data on UART: ");
				UART_putc((uint8_t)u16RxData);
				UART_puts("\r\n");	
			}
			
		}
		u08Toggle++;
	}


    while(1)
    {
		BaseTmr_WaitForNextTimeSlot_10ms();
		
		// DIO example
		u08Toggle++;
		if(u08Toggle & 0x01)
		{
			Dio_WriteChannel(Dio_Name0,Dio_Low);
		}
		else
		{
			Dio_WriteChannel(Dio_Name0,Dio_High);
		}						
		
		// ADC example
		u32AdcVal = 0;
		for (u08Cnt=0;u08Cnt<16;u08Cnt++)
		{
			u32AdcVal += (uint16_t)ADC_u16SampleChannel(ADC_IN_0,2000);
		}
		
		// send measured value via UART
		UART_Tx_uint32(u32AdcVal);
		UART_puts("\r\n");
		
    }
}