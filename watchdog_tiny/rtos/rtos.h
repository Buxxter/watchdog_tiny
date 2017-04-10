#ifndef RTOS_H_
#define RTOS_H_

#include <stdint.h>
#include <stdbool.h>
#include <util/atomic.h>

#include "../lib/hardware.h"
#include "../lib/macros.h"

#define RTOS_ISR  			TIMER1_COMPA_vect

#define MAX_TASKS_COUNT		5
#define MAX_TIMERS_COUNT	5 // 4 bytes per timer
#define MAX_ARGS_COUNT		1  // uint8_t per arg
//#define _ARGS_SUPPORT		// �� ��������

typedef void (*TPTR)(void);

extern void rtos_init(void);
extern void Idle(void);
extern void rtos_timer_setup (void);

extern void AddTask(TPTR TS);
//extern void AddTimerHardTask(TPTR TS, uint16_t NewTime, bool update_if_exist);
extern void AddTimerTask(TPTR TS, uint16_t NewTime_ms, bool update_if_exist);

extern void TaskManager(void);
extern void TimerService(void);

////RTOS Errors ���� �� ������������.
//#define TaskSetOk			 'A'
//#define TaskQueueOverflow	 'B'
//#define TimerUpdated		 'C'
//#define TimerSetOk		 'D'
//#define TimerOverflow		 'E'





#endif /* RTOS_H_ */