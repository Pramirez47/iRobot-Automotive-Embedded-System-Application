//#include "cyBot_Scan.h"
//#include "lcd.h"
//#include "Timer.h"
//#include "movement.h"
//#include "open_interface.h"
//#include "uart.h"
//#include "servoP1.h"
//#include "part3ping.h"
//#include "adc.h"
//#include "Route.h"
///**
// * main.c
// */
////object definition
//typedef struct
//{
//    int object_num;
//    int angle_detected;
//    int radial_width;
//    int object_distance;
//    int ping_distance;
//} objectsFound;
//
//typedef struct
//{
//    int distance[90];
//    int angles[90];
//    int pingDistance[90];
//} dataArrays;
//
//// x: 437.5
//// y: 250
//// corner 1 = (0,0), Corner 2 = (0,250) Corner 3 = (437.5,0), corner 4 = (437.5,250)
////return best route
//
//
//
// int main(void){
//     uart_init();
//     lcd_init();
//     oi_t *sensor_data = oi_alloc();
//     oi_init(sensor_data);
////     oi_free(sensor_data);
//     lcd_printf("on");
//     while(1){
//         char grabByte = uart_receive();
//         if (grabByte == 'm' || grabByte == 'h'){
//             RouteCalc b = Route(218.75,125,0,0);
//             turn_Rumba(sensor_data,-60.25);
//             move_forward(sensor_data, b.distance,100);
//         }
//     }
//    oi_free(sensor_data);
//    return 0;
//}
