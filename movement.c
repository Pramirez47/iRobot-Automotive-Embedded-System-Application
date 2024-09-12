#include "movement.h"

void move_forward(oi_t *sensor, int centimeters, int speed, char data[]){
//    char data4[] = "";
    double sum = 0;
       while (sum < centimeters) {
           oi_setWheels(speed,speed);
           oi_update(sensor);
               //bump sensors
               if(sensor->bumpLeft){
                   sprintf(data,"Bump Left \n \r");
                   uart_sendStr(data);
                   move_backward(sensor, -150);
                   oi_update(sensor);
                   break;

               }
               else if (sensor->bumpRight){
                   sprintf(data,"Bump Right \n \r");
                   uart_sendStr(data);
                   move_backward(sensor, -150);
                   oi_update(sensor);
                   break;
               }
               //hole detection
               else if (sensor->cliffFrontLeft){
                   sprintf(data,"Hole Front Left \n \r");
                   uart_sendStr(data);
                   oi_setWheels(0,0);          //stop
                   move_backward(sensor, -150);   //back away from cliff/boundary
                   oi_update(sensor);
                   break;
               }
               else if (sensor->cliffLeft){
                   sprintf(data,"Hole Left \n \r");
                   uart_sendStr(data);
                   oi_setWheels(0,0);          //stop
                   move_backward(sensor, -150);   //back away from cliff/boundary
                   oi_update(sensor);
                   break;
               }
               else if (sensor->cliffFrontRight){
                   sprintf(data,"Hole Front Right \n \r");
                   uart_sendStr(data);
                   oi_setWheels(0,0);          //stop
                   move_backward(sensor, -150);   //back away from cliff/boundary
                   oi_update(sensor);
                   break;
               }
               else if (sensor->cliffRight){
                   sprintf(data,"Hole Right \n \r");
                   uart_sendStr(data);
                   oi_setWheels(0,0);          //stop
                   move_backward(sensor, -150);   //back away from cliff/boundary
                   oi_update(sensor);
                   break;
               }
//               //test field boundary detection
               else if (sensor->cliffFrontLeftSignal >= 2600){
                   sprintf(data,"Border Front Left \n \r");
                   uart_sendStr(data);
                   oi_setWheels(0,0);          //stop
                   move_backward(sensor, -100);   //back away from cliff/boundary
                   oi_update(sensor);
                   break;
               }
               else if (sensor->cliffLeftSignal >= 2600 ){
                   sprintf(data,"Border Left \n \r");
                   uart_sendStr(data);
                   oi_setWheels(0,0);          //stop
                   move_backward(sensor, -100);   //back away from cliff/boundary
                   oi_update(sensor);
                   break;
               }
               else if (sensor->cliffFrontRightSignal >= 2600 ){
                   sprintf(data,"Border Front Right \n \r");
                   uart_sendStr(data);
                   oi_setWheels(0,0);          //stop
                   move_backward(sensor, -100);   //back away from cliff/boundary
                   oi_update(sensor);
                   break;
               }
               else if (sensor->cliffRightSignal >= 2600){
                   sprintf(data,"Border Right \n \r");
                   uart_sendStr(data);
                   oi_setWheels(0,0);          //stop
                   move_backward(sensor, -100);   //back away from cliff/boundary
                   oi_update(sensor);
                   break;
               }

           //increment sum to keep cybot moving
           sum += sensor->distance;

       }
       oi_setWheels(0,0); //stop
}
void turn_Rumba(oi_t *sensor,int degrees){

        double sum = 0;
        if(degrees > 0){
            //counter-clockwise
                oi_setWheels(100,-100);
//                while (sum < (degrees - 2)) { //while sum is < than requested degree amount
                  while (sum < (degrees)) {
//                     oi_update(sensor); //request sensor data from struct
                     sum += sensor->angle; // sum = angle in oi struct
                     oi_update(sensor);
                 }
        }
        else if (degrees < 0){
            //clockwise
            oi_setWheels(-100,100); //rotates  clockwise}
//            while (sum > (degrees + 2)) { //while sum is < than requested degree amount
                while (sum > (degrees)) {
//                 oi_update(sensor); //request sensor data from struct
                 sum += sensor->angle; // sum = angle in oi struct
                 oi_update(sensor);
             }
        }
         oi_setWheels(0,0); //stop
}
void move_backward(oi_t *sensor, int centimeters){


       double sum = 0;
       oi_setWheels(-100,-100); //moveforward full speed
       while (sum > centimeters) {
           oi_update(sensor);
           sum += sensor->distance;
       }
       oi_setWheels(0,0); //stop
}




