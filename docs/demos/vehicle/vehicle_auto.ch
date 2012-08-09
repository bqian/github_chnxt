/* File name: vehicle_auto.ch
 *
 * Demonstrate the CH Mindstorms Control Package's ability 
 * to control the machine robot model autonomously, as well 
 * as demonstrate how use sensor data from the NXT to controle it's actions. */

#include <conio.h>
#include <stdio.h>
#include <nxt.h>

ChNXT nxt;
double speedRatio = 0.25;       //speed ratio of the motors. (default to .25)
int status1 = 2;                //used to check for errors
int status2 = 2;                //used to check for errors
int touchValue, ultraValue;     //used to store sensor data
char key = 'x',                 //stoes user input
     movemode = 'x';	        //stores last movement command
     
/* Connect to NXT */
printf("Initializing vehicle and assuming control...");
if (nxt.connect()){
    printf("\nPress any key to exit.\n");
    while (!_kbhit());          //wait for keypress
    exit(-1);
}

/* Set sensor types */
status1 = nxt.setSensor(NXT_SENSORPORT1, 
        NXT_SENSORTYPE_TOUCH, NXT_SENSORMODE_BOOLEANMODE);
status2 = nxt.setSensor(NXT_SENSORPORT4, 
        NXT_SENSORTYPE_ULTRASONIC, NXT_SENSORMODE_RAWMODE);
if ((status1) || (status2)){
    printf("\nError initializing sensors.\nPress any key to exit.\n");
    while (!_kbhit());          //wait for keypress
    exit(-1);
}

while (1) {
    /* check user input 'q' to quit */
    if (kbhit()){
        if (getch() == 'q'){
            printf("\nExiting.");
            break;
        }
    }

    /* get touch sensor. If pressed reverse and turn left */
    nxt.getSensor(NXT_SENSORPORT1, touchValue);
    if (touchValue == 1){
        nxt.moveJoint(NXT_JOINT2, 720);
        nxt.moveJoint(NXT_JOINT3, 720);
        delay(1);
        nxt.moveJoint(NXT_JOINT2, -720);
        nxt.moveJoint(NXT_JOINT3, 720);
    }

    /* get distance from UltraSonic sensor,
       set speed according to distance. Turn left if really close.*/
    nxt.getSensor(NXT_SENSORPORT4, ultraValue);
    if (ultraValue < 10){
        nxt.moveJoint(NXT_JOINT2, -720);
        nxt.moveJoint(NXT_JOINT3, -720);
        delay(1);
        nxt.moveJoint(NXT_JOINT2, 720);
        nxt.moveJoint(NXT_JOINT3, -720);
        delay(0.75);
    } else if (ultraValue < 20){
        speedRatio = 0.25;
    }else if (ultraValue < 40){
        speedRatio = 0.50;
    }else if (ultraValue< 80){
        speedRatio = 0.75;
    }else{
        speedRatio = 1;
    }

    /* Turn motors on (drive forward) */
    nxt.setJointSpeedRatios(0, speedRatio, speedRatio);
    nxt.moveJointContinuousNB(NXT_JOINT2, NXT_FORWARD);
    nxt.moveJointContinuousNB(NXT_JOINT3, NXT_FORWARD);
}
