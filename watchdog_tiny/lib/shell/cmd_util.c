#include "cmd_util.h"
#include "../macros.h"
#include <stdbool.h>

/*Code module from AVR command shell project.
See appropriate header file for detais.*/

uint8_t is_regular_char(char x)
{
    if (((x>='A') && (x<='Z')) || ((x>='a') && (x<='z')) || ((x>='0') && (x<='9')) || x == '|' || x == '&')
        return 1;
    else
        return 0;
}

uint8_t is_digit(char x)
{
    if ((x>='0') && (x<='9'))
        return 1;
    else
        return 0;
}

uint8_t str_len(uint8_t* str)
{
    uint8_t l=0;

    while (str[l]!=0)
        l++;

    return l;
}

uint8_t str_len_pgm(uint8_t const * pgm_str)
{
    uint8_t l=0;

    while (pgm_read_byte(&(pgm_str[l]))!=0)
        l++;

    return l;
}

uint8_t str_equal_pgm(uint8_t* str, uint8_t const *pgm_str)
{
    uint8_t i,l;

    l=str_len(str);

    if (l!=str_len_pgm(pgm_str))
        return 0;

    for (i=0; i<l; i++)
    {
        if (str[i]!=pgm_read_byte(&(pgm_str[i])))
            return 0;
    }

    return 1;
}

uint16_t str_to_uint16(uint8_t *s_num)
{
    uint8_t i=0,dgt_len=0;
    uint16_t r_val=0,mult=1;

    while (is_digit(s_num[dgt_len]))
        dgt_len++;

    for (i=dgt_len; i>0; i--)
    {
        r_val+=(s_num[i-1]-'0')*mult;
        mult*=10;
    }

    return r_val;
}

uint8_t str_to_uint8(uint8_t *s_num)
{
	uint8_t i=0,dgt_len=0;
	uint8_t r_val=0,mult=1;

	while (is_digit(s_num[dgt_len]))
	dgt_len++;

	for (i=dgt_len; i>0; i--)
	{
		r_val += (s_num[i-1]-'0') * mult;
		mult *= 10;
	}

	return r_val;
}

bool str_is_number(uint8_t *str)
{
	uint8_t i = 0;
	while (str[i] != '\0')
	{
		if (!(is_digit(str[i++])))
		{
			return false;
		}
	}
	
	return true;	
}


uint16_t str_to_b_uint16(uint8_t *str)
{
	uint16_t result = 0;
	if (16 == str_len(str))
	{
		for (uint8_t i = 0; i < 16; i++)
		{
			if (str[i] == '1')
			{
				sbit(result, i);
			}
		}
	}
	return result;
}

char* str_uint16_to_str(uint16_t num)
{
	uint8_t i;
	
	uint8_t len;
	if (num < 10000)
	{
		if (num < 1000)
		{
			if (num < 100)
			{
				if (num < 10)
				{
					len = 1;
				} else
				{
					len = 2;
				}
			} else
			{
				len = 3;
			}
		} else
		{
			len = 4;
		}
	} else
	{
		len = 5;
	}
	
	char str[len];
	str[len] = '\0';
	for(i=(len-1); i>=0; i--){
		str[i] = '0' + num % 10;
		num /= 10;
	}
	return str;
}