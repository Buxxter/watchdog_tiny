#include "relay.h"

void _relay_blink_off(void);

const uint16_t wd_timeout_eemem PROGMEM = 600;

void relay_init(void)
{
	main_watchdog_timeout_s = eeprom_read_word(&wd_timeout_eemem);
	sbit(RELAY_DDR, RELAY_PIN);
	relay_off();
}

void relay_on(void)
{
	sbit(RELAY_PORT, RELAY_PIN);
}

void relay_off(void)
{
	cbit(RELAY_PORT, RELAY_PIN);
}

void relay_blink(void)
{
	relay_on();
	AddTimerTask(_relay_blink_off, RELAY_CYCLE_MS, false);
}

void _relay_blink_off(void)
{
	relay_off();
	relay_start_watch();
}

void relay_start_watch(void)
{
	if (main_watchdog_timeout_s != 0)
	{
		AddTimerTask(relay_blink, main_watchdog_timeout_s * 1000, true);
	}
}

void relay_set_timeout(uint16_t new_val)
{
	eeprom_write_word(&wd_timeout_eemem, new_val);
	relay_init();
}