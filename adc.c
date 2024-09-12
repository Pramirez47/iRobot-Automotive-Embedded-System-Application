/*
 * adc.c
 *
 *  Created on: Oct 18, 2023
 *      Author: pram1347
 */
//#include <inc/tm4c123gh6pm.h>

#include "adc.h"

void adc_init(void){
    //adc0 ss 1
   SYSCTL_RCGCGPIO_R |= 0x02;
   SYSCTL_RCGCADC_R |= 0x01;
   GPIO_PORTB_AFSEL_R |= 0x10;
   GPIO_PORTB_DEN_R &= 0xEF;
   GPIO_PORTB_DIR_R &= 0xEF;
   GPIO_PORTB_AMSEL_R |= 0x10;
   GPIO_PORTB_ADCCTL_R = 0x00;
   ADC0_CC_R &= 0xFFFFFFF0;
   ADC0_ACTSS_R |= 0x02;
   ADC0_EMUX_R &= 0xFF0F;
   ADC0_SSMUX1_R |= 0xAAAA;
   ADC0_SSCTL1_R = 0x0002;
   ADC0_SAC_R |= 0x4;
}

int adc_read(void){
    int readvalue = 0;
    ADC0_PSSI_R |= 0x2;
    if (ADC0_RIS_R | 0x2){
        readvalue = ADC0_SSFIFO1_R;
        return readvalue;
    }
}






