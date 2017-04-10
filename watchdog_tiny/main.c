#include "includes.h"


void init(void);
void wdt_init(void);
void execute_command(void);


int main(void)
{
	init();
	relay_start_watch();
	sei();

	while (1)
	{
		//wdt_reset();
		TaskManager();
		usart_check_tx_buffer();
	}	
	return 0;
}


void init(void)
{
	//STATUS_DDR |= (1<<STATUS_PIN);
	usart_init();
	rtos_init();	
	//wdt_init();
	relay_init();
}


void wdt_init(void)
{
	wdt_enable(WDTO_2S);
	return;
}


void execute_command(void)
{
	usart_check_tx_buffer();
	unsigned char command[FIFO_SIZE(Rx_buffer) + 1];
	uint8_t index = 0;
	while(!FIFO_IS_EMPTY(Rx_buffer))
	{
		command[index] = FIFO_GET(Rx_buffer);
		if (command[index] != CHR_LF && command[index] != CHR_ENTER)
		{
			index++;
		}
	}
	command[index] = '\0';
	//wdt_reset();
	
	uint8_t result = cmd_exec(command);
	if (result)
	{
		usart_pgm_send_string(pgm_ok);
	} else
	{
		usart_pgm_send_string(pgm_error);
	}
}


ISR(RTOS_ISR)
{
	sei();
	TimerService();
}


ISR(USART_RX_vect)
{
	uint8_t rx_byte = usart_rx_interrupt();
	if (rx_byte == CHR_ENTER)
	{		
		AddTask(execute_command);
	}
}


ISR(USART_UDRE_vect)
{
	usart_tx_interrupt();
}