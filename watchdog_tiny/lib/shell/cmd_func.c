#include "cmd_func.h"

/*Code module from AVR command shell project.
See appropriate header file for detais.*/

//Command line functions and their data
#define new_line (usart_pgm_send_string(pgm_newline))

const uint8_t help_text[] PROGMEM = {
"help - display this help;\r\n\
wd [rst|set <seconds>];\r\n\
restart;\r\n\
"
};

const uint8_t wd_help[] PROGMEM = {
"wd [rst|set <sec>]\r\n\
\trst\t - reset wd timer\r\n\
\tset <sec>\t - (0 - turn off timer)\r\n\
"
};

void print_help(uint8_t* p_arg[],uint8_t num_args)
{	
	usart_pgm_send_string(help_text);
}


const uint8_t msg_err_unknown[] PROGMEM = {"Err: unknown params\r\n"};
const uint8_t msg_set[] PROGMEM = {"set"};
const uint8_t msg_rst[] PROGMEM = {"rst"};

volatile uint8_t ledtype;

#ifndef _LOCAL_FUNCTIONS

// Headers

// Implementations

#endif

void print_wd_help(void)
{
	usart_pgm_send_string(wd_help);
	usart_send_string("Cur:");
	usart_send_string(str_uint16_to_str(main_watchdog_timeout_s));
	new_line;
}

void print_unknown(char *msg)
{
	usart_pgm_send_string(msg_err_unknown);
	usart_send_string(msg);
	new_line;
}

void wd(uint8_t * p_arg[], uint8_t num_args)
{
	if (1 == num_args) {
		if (str_equal_pgm(p_arg[0], msg_rst))
		{
			relay_start_watch();
		} else if (str_equal_pgm(p_arg[0], msg_set))
		{
			print_wd_help();
		} else {
			//print_unknown((char*)p_arg[0]);
			usart_pgm_send_string(msg_err_unknown);
			//usart_send_string((char*)p_arg[0]);
			//new_line;
		}
	} else if ((2 == num_args) && (str_equal_pgm(p_arg[0], msg_set)))
	{
		if (!str_is_number(p_arg[1]) || (str_len(p_arg[1]) > 5))
		{
			print_unknown((char*)p_arg[1]);
			return;
		}
		relay_set_timeout(str_to_uint16(p_arg[1]));		
	} else
	{
		print_unknown((char*)p_arg[1]);
		print_wd_help();
	}
}


void restart(uint8_t * p_arg[], uint8_t num_args)
{
	wdt_enable(WDTO_15MS);
	while(1);
}


//Function table

void (*sys_func[]) (uint8_t* p_arg[],uint8_t num_args) = {

    print_help,
	wd,
	restart

};

//Command line alias table

const uint8_t funcname1[] PROGMEM = {"help"};
const uint8_t funcname2[] PROGMEM = {"wd"};
const uint8_t funcname3[] PROGMEM = {"restart"};


const uint8_t * const sys_func_names[] PROGMEM = {

    funcname1,
	funcname2,
	funcname3
};
