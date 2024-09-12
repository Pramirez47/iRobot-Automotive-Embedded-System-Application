//#include "cyBot_Scan.h"
#include "lcd.h"
#include "Timer.h"
#include "movement.h"
#include "open_interface.h"
#include "scan.h"
#include "uart.h"
#include "music.h"


/**
 * main.c
 */


int main(void){


     //Initialization and create variables
    timer_init();

    ping_init();
    lcd_init();
    //print on
//    lcd_printf("working");
    adc_init();
    servo_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
//    oi_free(sensor_data);
    uart_init();
    //create an array of objects
    objectsFound totalObjects[5];
//    dataArrays dataObjects;
    int dis[90];
    int ang[90];
    int pingD[90];
    char data4[] = "";
//    char data5[] = "";
    char data6[] = "";
    char data8[] = "";
//    char data9[] = "";
//    char lastMoves [5];
    /*
     * a: forward
     * b: right
     * c: down
     * d: left
     * e: clockwise turn
     * f: counter-clockwise turn
     *
     */
//    int counterMoves = 0;
//    int movesLoc = 0;
    int currentAngle = 0;
    while (1){
                sprintf(data6,"--------------------------------------- \n \r");
                uart_sendStr(data6);
        //print direction
        if (currentAngle == 0 || currentAngle == 360 || currentAngle == -360){
            sprintf(data8,"Compass: North \n \r");
            uart_sendStr(data8);
        }
        else if (currentAngle == -90 || currentAngle == 270){
            sprintf(data8,"Compass: East \n \r");
            uart_sendStr(data8);
        }
        else if (currentAngle == 180 || currentAngle == -180){
            sprintf(data8,"Compass: South \n \r");
            uart_sendStr(data8);
        }
        else if (currentAngle == 90 || currentAngle == -270){
            sprintf(data8,"Compass: West \n \r");
            uart_sendStr(data8);
        }
        else if (currentAngle == 45 || currentAngle == -315){
            sprintf(data8,"Compass: North-West \n \r");
            uart_sendStr(data8);
        }
        else if (currentAngle == 315 || currentAngle == -45){
            sprintf(data8,"Compass: North-East \n \r");
            uart_sendStr(data8);
        }
        else if (currentAngle == 135 || currentAngle == -225){
            sprintf(data8,"Compass: South-West \n \r");
            uart_sendStr(data8);
        }
        else if (currentAngle == -135 || currentAngle == 225){
            sprintf(data8,"Compass: South-East \n \r");
            uart_sendStr(data8);
        }
//        //print previous moves
//        sprintf(data9,"Last Known Moves:  \n \r");
//        uart_sendStr(data9);
//        int u;
//        for (u = 0; u <= counterMoves; u++){
//            char data7[] = "";
//            if (lastMoves[u] == 'a'){
//                sprintf(data7,"Forward \n \r");
//                uart_sendStr(data7);
//            }
//            else if (lastMoves[u] == 'b'){
//                sprintf(data7,"Right \n \r");
//                uart_sendStr(data7);
//            }
//            else if (lastMoves[u] == 'c'){
//                sprintf(data7,"Down \n \r");
//                uart_sendStr(data7);
//            }
//            else if (lastMoves[u] == 'd'){
//                sprintf(data7,"Left \n \r");
//                uart_sendStr(data7);
//            }
//            else if (lastMoves[u] == 'e'){
//                sprintf(data7,"clockwise \n \r");
//                uart_sendStr(data7);
//            }
//            else if (lastMoves[u] == 'f'){
//                sprintf(data7,"counter-clockwise \n \r");
//                uart_sendStr(data7);
//            }
//        }



        lcd_printf("in loop");
        //pause code to wait for character
        char grabByte = uart_receive();
        //scan
        if (grabByte == 'm' )
        {
//            sprintf(data5,"Scanning... \n \r");
//            uart_sendStr(data5);
            scanObjects(sensor_data, totalObjects, dis,ang, pingD);
        }
        //move foward
        else if (grabByte == 'w')
        {
            move_forward(sensor_data, 150,200,data4);
//            lastMoves[counterMoves] = 'a';
//            counterMoves++;
        }
        //play music
        else if (grabByte == 'q')
        {
//            load_songs();
//            oi_play_song(IMERPIAL_MARCH);
        }
        //move right
        else if (grabByte == 'd')
        {
            currentAngle = currentAngle - 90;
            turn_Rumba(sensor_data,-90);
            move_forward(sensor_data, 150,200,data4);
//            lastMoves[counterMoves] = 'b';
//            counterMoves++;
        }
        //move down
        else if (grabByte == 'x')
        {
            move_backward(sensor_data, -150);
//            lastMoves[counterMoves] = 'c';
//            counterMoves++;
        }
        else if (grabByte == 's')
        {
            currentAngle = currentAngle + 180;
            turn_Rumba(sensor_data,180);
            move_forward(sensor_data, 150,200,data4);
//            lastMoves[counterMoves] = 'c';
//            counterMoves++;
        }
        //move left
        else if (grabByte == 'a')
        {
            currentAngle = currentAngle + 90;
            turn_Rumba(sensor_data,90);
            move_forward(sensor_data, 150,200,data4);
//            lastMoves[counterMoves] = 'd';
//            counterMoves++;
        }
        //turn clockwise 45 degrees
        else if (grabByte == 'c')
        {
            currentAngle = currentAngle - 45;
            turn_Rumba(sensor_data,-43);
//            lastMoves[counterMoves] = 'e';
//            counterMoves++;
        }
        //turn counter-clockwise 45 degrees
//        else if (grabByte == 'z')
//        {
//            currentAngle = currentAngle + 45;
//            turn_Rumba(sensor_data,43);
////            lastMoves[counterMoves] = 'f';
////            counterMoves++;
//        }
        //exit loop and free oi
        else if (grabByte == 'e')
        {
            break;
        }
        /////////////////////////////////////////////////////////////////////////////////
        //reset current angle
        if (currentAngle >= 360 || currentAngle <= -360){
            currentAngle = 0;
        }
//       //keep counter move array size at 5 if maxed
//        if (counterMoves > 4){
//            counterMoves = 4;
//        }

    }
    oi_free(sensor_data);
    return 0;
}
