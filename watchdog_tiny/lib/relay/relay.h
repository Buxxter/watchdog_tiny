/*
 * relay.h
 *
 * Created: 02.04.2017 19:02:20
 *  Author: My
 */ 


#ifndef RELAY_H_
#define RELAY_H_

#include "../../includes.h"
#include "../hardware.h"

#define RELAY_CYCLE_MS 1000

void relay_init(void);
void relay_on(void);
void relay_off(void);
void relay_blink(void);
void relay_start_watch(void);
void relay_set_timeout(uint16_t new_val);

#endif /* RELAY_H_ */