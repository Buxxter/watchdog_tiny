#include "uart_text_io.h"
#include <util/atomic.h>
#include <avr/io.h>


void usart_init(void)
{
	#include <util/setbaud.h>
	
	/* Set baud rate */
	UBRRH = (unsigned char)(USART_BAUDRATE>>8);
	UBRRL = (unsigned char)(USART_BAUDRATE);
	UCSRA = (1<<U2X);
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<USBS)|(3<<UCSZ0);
	
}


unsigned char usart_rx_interrupt (void) // USART_RX_vect
{
	unsigned char rx_byte = UDR;
	#if defined(_USART_FIFO_ENABLED)	
		usart_send_char(rx_byte);
		if (rx_byte == CHR_BS)
		{
			FIFO_REMOVE_LAST(Rx_buffer);
		} else {
			FIFO_PUT(Rx_buffer, rx_byte);
		}
	#endif // _USART_FIFO_ENABLED
	return rx_byte;
}

void usart_tx_interrupt(void) // USART_UDRE_vect
{
	#if defined(_USART_FIFO_ENABLED)
	if (FIFO_IS_EMPTY(Tx_buffer))
	{
		UCSRB &= ~(1<<UDRIE);
	} else {
		UDR = FIFO_GET(Tx_buffer);
	}
	#endif
}

void usart_check_tx_buffer(void)
{
	#if defined(_USART_FIFO_ENABLED)
		if (!FIFO_IS_EMPTY(Tx_buffer))
		{
			UCSRB |= (1<<UDRIE);
		}
	#endif		
}

void usart_send_string(char *outtxt)
{
	uint8_t i=0;
	while (outtxt[i] != 0)
	{
		usart_send_char(outtxt[i]);
		i++;
	}
	usart_check_tx_buffer();
}

void usart_send_char(char ch)
{
	#if defined(_USART_FIFO_ENABLED)
		if (FIFO_IS_FULL(Tx_buffer))
		{
			return;
		}
		FIFO_PUT(Tx_buffer, ch);
		UCSRB |= (1<<UDRIE);
	#else
		usart_send_char_hard(ch);
	#endif
}

void usart_send_char_hard(char ch)
{
	// Wait for empty transmit buffer
	while ( !( UCSRA & (1<<UDRE)) );
	// Put data into buffer, sends the data
	UDR = ch;
}

void usart_pgm_send_string(const uint8_t* pgm_msg)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		uint16_t	i=0;
		uint8_t	ch;
		do
		{
			ch=pgm_read_byte(&(pgm_msg[i]));
			i++;

			if (ch)
			{
				usart_send_char(ch);
			}
		} while (ch!=0);
	}
}