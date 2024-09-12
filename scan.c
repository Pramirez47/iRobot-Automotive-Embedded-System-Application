#include "scan.h"
void scanObjects(oi_t *sensor, objectsFound *totalObjects, int dis[], int ang[], int pingD[]){
    int q;
        //assign all objects to null
        for (q = 0; q < 5; q++){
            totalObjects[q].object_num = NULL;
            totalObjects[q].angle_detected = NULL;
            totalObjects[q].object_distance = NULL;
            totalObjects[q].radial_width = NULL;
        }
        int j;
        for (j = 0; j < 90; j++){
            dis[j] = NULL;
            ang[j] = NULL;
            pingD[j] = NULL;
        }
        int objectLoc = 0;
        int indexCurrent = 0;
        int num = 0; // Distance
        double IRRaw = 0;
        //delay cybot while resetting
        servo_move(0);
         timer_waitMillis(2000);
        //scan all distances and store in array
        int degrees = 0;
        for (degrees = 0; degrees <= 180; degrees += 2)
        {
            //start scanning
            servo_move(degrees);
            //grab current distance
            num = ping_getDistance();
            //grab IR
            IRRaw = adc_read();
            int distanceValue = 148914 * pow(IRRaw, -1.214);
              dis[indexCurrent] = distanceValue;
              pingD[indexCurrent] = num;
              ang[indexCurrent] = degrees;
            indexCurrent++;
            //print current angle and current distance
            char data[] = "";
            sprintf(data, "%d\t\t\t%d\t\t\t%d\n \r", degrees, num, distanceValue);
            int j = 0;
            for (j = 0; j < strlen(data); j++)
            {
                uart_sendChar(data[j]);
            }
        }
         int m = 0;
         int objectIn = 0; //0:false, 1:true
        //go through distance array
        for(m = 1; m < 90; m++){
            objectIn = 0;
            int threshold;
            //object is found then add it to array of objectsFound, the distance is IR being tracked
            if (dis[m] <= 40){
                //index of next loop
                int g;
                //keeps track of how many times you move in array
                int tracker = 0;
                for (g = m + 1; g < 90; g++){
                    //keep track of the index where you first stopped at to know the threshold
                    //ping 36-40
                    if (dis[m] <= 40 && dis[m] > 35){
                        threshold = 20;
                    }
                    //ping 30-35
                    else if (dis[m] >= 30 && dis[m] <= 35){
                        threshold = 14;
                    }
                    //ping 10-29
                    else if (dis[m] < 30 && dis[m] >= 10){
                        threshold = 9;
                    }
                    //ping less than 10
                    else if(dis[m] < 10){
                        threshold = 4;
                    }
                    //scan the difference of current value and next value
                    int difference = abs(dis[m] - dis[g]);
                    //if values are similar then start tracking width AND THEN create object, this allows outliers to not be created as objects
                    if (difference <= threshold){
                        //create object if it has not been created already and dont overfill objects array, if objectLoc is 3 then still create object
                        if (objectIn == 0 && objectLoc < 4){
                            //increase num of objects when a object is found and remember angle
                            totalObjects[objectLoc].object_num = objectLoc + 1;
                            totalObjects[objectLoc].angle_detected = ang[m];
                            //determines if object is created
                            objectIn = 1;
                        }
                        //update width
                        totalObjects[objectLoc].radial_width += 2;
                        //tracker only updates if object has been created so if no object is created then it will be zero
                        tracker++;
                    }
                    //exit once values are not similar and move to next value in distance array
                    else{
                        break;
                    }
                }
                //end of loop for tracking, update m to pick up where new object might be IF it has been created
                m = m + tracker;
                //dont overfill objects array
                if (objectLoc <= 4 && objectIn == 1){
                    totalObjects[objectLoc].object_distance = pingD[(totalObjects[objectLoc].angle_detected / 2)  + (totalObjects[objectLoc].radial_width / 2)];
                    if (objectLoc < 4){
                        objectLoc++;
                    }
                }
            }
        }

            char header2[] =
                    "-----------------------------------------------------------\n\r";
            uart_sendStr(header2);

        //print objectLoc
            char data3[] = "";
            sprintf(data3,"Objects:%d\n \r", objectLoc);
            uart_sendStr(data3);

        int p;
        for (p = 0; p < objectLoc; p++) //Index
                    {
                    char data2[50] = "";

                     sprintf(data2, "OBJ: %d\t\t\t ANG: %d\t\t\t DIS: %d\t\t\t\t WID: %d\n\r",totalObjects[p].object_num, totalObjects[p].angle_detected, totalObjects[p].object_distance, totalObjects[p].radial_width); // String
                     uart_sendStr(data2);
                     }
}
