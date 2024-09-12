/*
 * part3ping.h
 *
 */

#ifndef PART3PING_H_
#define PART3PING_H_
#ifndef PING_H_
#define PING_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

/**
 * Initialize ping sensor. Uses PB3 and Timer 3B
 */
void ping_init (void);

/**
 * @brief Trigger the ping sensor
 */
void ping_trigger (void);

/**
 * @brief Timer3B ping ISR
 */
void TIMER3B_Handler(void);

/**
 * @brief Calculate the distance in cm
 *
 * @return Distance in cm
 */
float ping_getDistance (void);

long getPulseLength(void);

int getOverflow(void);

#endif /* PING_H_ */


#endif /* PART3PING_H_ */
