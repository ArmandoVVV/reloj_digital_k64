/*
 * clock.h
 * brief:
 * 		This source file is an abstraction of a clock, it has its own values
 *		this clock has a maximum range of 23:59:59, after this value it resets to
 *		00:00:00
 *		The clock uses the display to show its values.
 *		It has a total_value variable to compare with alarm.
 *
 *  Created on: Sep 29, 2022
 *      Author: armando
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "stdint.h"

#define SEC_TEN_MAX_VALUE 5
#define SEC_UNIT_MAX_VALUE 9
#define MIN_UNIT_MAX_VALUE 9
#define MIN_TEN_MAX_VALUE 5
#define HOUR_TEN_MAX_VALUE 2
#define HOUR_UNIT_MAX_VALUE 9
#define HOUR_UNIT_RESET_VALUE 3

void add_one_sec(uint32_t pit1);
void show_clock(void);

void hour_plus_one(void);
void min_plus_one(void);

// getters
uint8_t get_hour_ten_value(void);
uint8_t get_hour_unit_value(void);
uint8_t get_min_ten_value(void);
uint8_t get_min_unit_value(void);
uint8_t get_sec_ten_value(void);
uint8_t get_sec_unit_value(void);
uint16_t get_clock_total_value(void);

// setters
void set_hour_ten_value(uint8_t new_value);
void set_hour_unit_value(uint8_t new_value);
void set_min_ten_value(uint8_t new_value);
void set_min_unit_value(uint8_t new_value);
void set_sec_ten_value(uint8_t new_value);
void set_sec_unit_value(uint8_t new_value);
void set_clock_total_value(void);

void reset_clock(void);

#endif /* CLOCK_H_ */
