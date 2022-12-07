/*
 * alarm.h
 * \brief
 *		This source file is an abstraction of an alarm, it has its own values
 *		it can make sound with the DAC and uses the display to show its values.
 *
 *
 *  Created on: 30 sep 2022
 *		Author: Laura García
 */

#ifndef ALARM_H_
#define ALARM_H_

#include <stdint.h>
#include "config.h"

#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

#define MIN_UNIT_MAX_VALUE 9
#define MIN_TEN_MAX_VALUE 5
#define HOUR_TEN_MAX_VALUE 2
#define HOUR_UNIT_MAX_VALUE 9
#define HOUR_UNIT_RESET_VALUE 3

typedef enum {NO_SIGNAL,
			  SINUSOIDAL
}signal_type;

// getters
uint8_t get_hour_ten_value_alm(void);
uint8_t get_hour_unit_value_alm(void);
uint8_t get_min_ten_value_alm(void);
uint8_t get_min_unit_value_alm(void);
uint16_t get_alarm_total_value(void);
device_status_t get_alarm_status(void);

// setters
void set_hour_ten_value_alm(uint8_t new_value);
void set_hour_unit_value_alm(uint8_t new_value);
void set_min_ten_value_alm(uint8_t new_value);
void set_min_unit_value_alm(uint8_t new_value);
void set_alarm_total_value(void);
void set_alarm_status(device_status_t status);

void alarm_sound (uint32_t pit_1);
void show_alarm(void);
void hour_plus_one_alm(void);
void min_plus_one_alm(void);

void alarm_on(void);
void alarm_off(void);

void toggle_alarm_sound(void);


#endif /* ALARM_H_ */
