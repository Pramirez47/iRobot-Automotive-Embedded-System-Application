#include "open_interface.h"
//#include "cyBot_Scan.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
#include "uart.h"

void move_forward(oi_t *sensor, int centimeters,int speed, char str[]);
void turn_Rumba(oi_t *sensor,int degrees);
void move_backward(oi_t *sensor, int centimeters);
