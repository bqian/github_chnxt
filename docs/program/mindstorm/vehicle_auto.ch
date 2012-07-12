/************************************************************
vehicle_auto.ch
Vehicle Robot Autonomous Exploration Example
By Joshua Galbraith and Harry H. Cheng
Modified by Binsen Qian

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the machine robot model
autonomously, as well as demonstrate how use sensor data from
the NXT to controle it's actions.
*************************************************************/
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <nxt.h>

ChNXT nxt;
int speedRatio = .25,	 //speed ratio of the motors. (default to .25)
int status1 = 2, //used to check for errors
int status2 = 2; //used to check for errors
int touchValue, ultraValue; //used to store sensor data
char key = 'x',  //stoes user input
     movemode = 'x';	//stores last movement command
/* Connect to NXT */
printf("Initializing vehicle and assuming control...");
if (nxt.connect() == -1){
    printf("\nPress any key to exit.\n");
    while (!_kbhit()); //wait for keypress
    return(0);
}

/* Set sensor types */
status1 = nxt.setSensor(SENSOR_PORT1, SENSOR_TYPE_TOUCH, SENSOR_MODE_BOOLEANMODE);
status2 = nxt.setSensor(SENSOR_PORT4, SENSOR_TYPE_ULTRASONIC, SENSOR_MODE_RAWMODE);
if ((status1 == 0) || (status2 == 0)){
    printf("\nError initializing sensors.\nPress any key to exit.\n");
    while (!_kbhit()); //wait for keypress
    return(0);
}

/* set speed ratios */
nxt.setSpeedRatios(0, speedRatio, speedRatio);

while (1) {
    /* check user input 'q' to quit */
    if (kbhit()){
        if (getch() == 'q'){
            printf("\nExiting.");
            break;
        }
    }

    /* get touch sensor. If pressed reverse and turn left */
    touchValue = nxt.getSensor(PORT_1);
    if (touchValue < 500){
        nxt.moveJoint(ROBOT_JOINT2, -720);
        nxt.moveJoint(ROBOT_JOINT3, -720);
        pause(1);
        nxt.moveJoint(ROBOT_JOINT2, -720);
        nxt.moveJoint(ROBOT_JOINT3, 720);
    }

    /* get distance from UltraSonic sensor,
       set speed according to distance. Turn left if really close.
       */
    ultraValue = nxt.getSensor(PORT_4);
    if (ultraValue < 10){
        nxt.moveJoint(ROBOT_JOINT2, -720);
        nxt.moveJoint(ROBOT_JOINT3, -720);
        pause(1);
        nxt.moveJoint(ROBOT_JOINT2, 720);
        nxt.moveJoint(ROBOT_JOINT3, -720);
        speedRatio = 0;
        pause(.75);
    } else if (ultraValue < 30)
        speedRatio = .25;
    else if (ultraValue < 50)
        speedRatio = .50;
    else if (ultraValue< 100)
        speedRatio = .75;
    else if (ultraValue< 200)
        speedRatio = 1;
    else
        speedRatio = .75;

    /* Turn motors on (drive forward) */
    nxt.setJointSpeeds(0, speedRatio, speedRatio);
    nxt.moveJointContinuousNB(ROBOT_JOINT2, ROBOT_FORWARD);
    nxt.moveJointContinuousNB(ROBOT_JOINT3, ROBOT_FORWARD);
}
/* stop interfacing. This also stops the motors. */
nxt.disconnect();   
printf("\nPress any key to exit.\n");
while (!_kbhit()); //wait for keypress
