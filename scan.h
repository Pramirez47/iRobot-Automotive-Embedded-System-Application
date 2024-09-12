#include "open_interface.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Timer.h"
#include "servoP1.h"
#include "part3ping.h"
#include "uart.h"
#include "adc.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
typedef struct
{
    int object_num;
    int angle_detected;
    int radial_width;
    int object_distance;
    int ping_distance;
} objectsFound;
void scanObjects(oi_t *sensor, objectsFound *totalObjects, int dis[], int ang[], int pingD[]);
