// main.c
// @file    practica1_equipo3.c
// @brief   Application entry point.
//  Created on: 30 sep 2022
// author: EQUIPO_3 Armando Cabrales & Laura Reyes

#include "display.h"
#include "config.h"
#include "gpio.h"
#include "fsl_gpio.h"
#include "pit.h"
#include "clock.h"
#include "nvic.h"
#include "display.h"
#include "state_machine.h"
#include "callback_manager.h"
#include "alarm.h"
#include "dac.h"
#include "watchdog.h"

int main(void) {
	GPIO_init();
	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_8);

	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_2);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ,PRIORITY_7);
	// pit1 activates when the alarm sounds
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ,PRIORITY_9);
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ,PRIORITY_2);

	NVIC_global_enable_interrupts;

	PIT_start();
	DAC_init();
	setup_watchdog();

	GPIO_callback_init(GPIO_B, change_time);
	GPIO_callback_init(GPIO_C, callback_time_stopwatch);
	PIT_callback_init(kPIT_Chnl_0, callback_add_msec);
	PIT_callback_init(kPIT_Chnl_1, alarm_sound);

	while(1) {
		if (get_reset_count() == 0){
			state_machine();
			// if stop is pressed
            if(!(GPIO_PinRead(SW2_GPIO, SW2_PIN))){
            	// pit stops adding msec
            	NVIC_set_basepri_threshold(PRIORITY_6);
            }
		}
		else{
			GPIO_PortClear(GREEN_LED_GPIO, GREEN_LED_MASK);
			display_show_error();
		}
    }
    return 0 ;
}
