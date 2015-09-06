/*
 * nrf24l01p_Test.c
 *
 * Created: 05.01.2014 15:50:40
 *  Author: cc
 */ 
//m168 10 $(TargetName).hex
//m328p 7 $(TargetName).hex

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

#define PING_Request	1
#define PING_Response	16

int main(void)
{
	volatile union xExtractU32Bytes
	{
		uint32_t u32Value;
		struct u08Help{
			uint8_t u08Byte0;
			uint8_t u08Byte1;
			uint8_t u08Byte2;
			uint8_t u08Byte3;
		}u08Bytes;
	}xExtractU32BytesUnion;
	
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


	u08Toggle=10;

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
			// clear buffer
			for (uint8_t u08Idx=0;u08Idx<mirf_PAYLOAD;u08Idx++)
			{
				au08MirfBuffer[u08Idx] = 0;
			}
	
			//check for new data
// 			mirf_read_register(STATUS,&u08MirfReg,1);
// 			if (u08MirfReg & 0x40)
			if(mirf_data_ready())
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
				
				
				// check if payload contains a ping request
				if (au08MirfBuffer[0] == PING_Request)
				{
					UART_puts("Received Ping request.\r\n");
					//prepare ping response
					au08MirfBuffer[0] = PING_Response;
					// get current timer tick
					xExtractU32BytesUnion.u32Value = BaseTmr_u32GetTimerTicks();
					// fill tx buffer with timer value
					au08MirfBuffer[5] = xExtractU32BytesUnion.u08Bytes.u08Byte0;
					au08MirfBuffer[6] = xExtractU32BytesUnion.u08Bytes.u08Byte1;
					au08MirfBuffer[7] = xExtractU32BytesUnion.u08Bytes.u08Byte2;
					au08MirfBuffer[8] = xExtractU32BytesUnion.u08Bytes.u08Byte3;
					//sending ping response
					mirf_send((uint8_t*)&au08MirfBuffer[0],mirf_PAYLOAD);
					while (PIND & (1<<PIND2))
					{
						// wait for interrupt
					}
					mirf_poll_for_irq();
					UART_puts("Ping response sent with following message\r\n");
					for(uint8_t u08Idx=0;u08Idx<mirf_PAYLOAD;u08Idx++)
					{
						UART_Tx_uint08(au08MirfBuffer[u08Idx]);
						UART_putc(' ');
					}
					UART_puts("\r\n");
					UART_puts("\r\n");
				}
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
				if (u16RxData == '*')
				{
					UART_puts("Sending Ping Request\r\n");
					// get current timer tick
					xExtractU32BytesUnion.u32Value = BaseTmr_u32GetTimerTicks();
					// fill tx buffer with ping request
					au08MirfBuffer[0] = PING_Request;
					// fill tx buffer with timer value
					au08MirfBuffer[1] = xExtractU32BytesUnion.u08Bytes.u08Byte0;
					au08MirfBuffer[2] = xExtractU32BytesUnion.u08Bytes.u08Byte1;
					au08MirfBuffer[3] = xExtractU32BytesUnion.u08Bytes.u08Byte2;
					au08MirfBuffer[4] = xExtractU32BytesUnion.u08Bytes.u08Byte3;
					//clear remaining buffer
					for(uint8_t u08Idx=5;u08Idx<mirf_PAYLOAD;u08Idx++)
					{
						au08MirfBuffer[u08Idx]  = 0;
					}
					//sending ping
					mirf_send((uint8_t*)&au08MirfBuffer[0],mirf_PAYLOAD);
					while (PIND & (1<<PIND2))
					{
						// wait for interrupt
					}
					mirf_poll_for_irq();			
//					UART_puts("\r\n");
				}
				
/*
				UART_puts("Received data on UART: ");
				UART_putc((uint8_t)u16RxData);
				UART_puts("\r\n");
*/
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