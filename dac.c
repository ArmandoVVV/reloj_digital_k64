/*
 * dac.c
 *
 * 		\brief
 *				This source file helps us to set the DAC values to create
 *				different signals, and start the DAC.
 *  	Created on: Sep 20, 2022
 *		Author: Laura García
 */

#include "MK64F12.h"
#include "DAC.h"
#include "fsl_gpio.h"

void DAC_init(void){
	CLOCK_EnableClock(kCLOCK_Dac0);

    DAC0->C0 = 0xC0;
    DAC0->DAT[0].DATL = 0;
    DAC0->DAT[0].DATH = 0;
}

void DAC_noSignal(void){
	DAC0->DAT[0].DATL = (0) & 0xFF;
	DAC0->DAT[0].DATH = (0 >> 8) & 0x0F;
}

void DAC_sinusoidal (uint16_t sin_value){
	DAC0->DAT[0].DATL = (sin_value) & 0xFF;
	DAC0->DAT[0].DATH = (sin_value >> 8) & 0x0F;
}
