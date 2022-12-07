/*
 * state_machine.h
 *brief:
 *		This source file is a button sensitive state machine, it can alternate
 *		between the clock, the alarm and the chronometer
 *  Created on: Oct 1, 2022
 *      Author: armando Cabrales
 */

#include <stdint.h>

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_


typedef enum {
	CLOCK,
	CHRONOMETER,
	ALARM
}State_name_t;

uint8_t get_time_stopwatch(void);
void set_time_stopwatch(uint8_t value);

typedef struct
{
	uint8_t out;
	void(*fptrPort)(void);
	uint8_t next[4];
}State_t;

void state_machine(void);
void check_buttons(void);

#endif /* STATE_MACHINE_H_ */
