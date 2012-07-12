/************************************************************
humanoid_rtc.ch
Humanoid Robot Real Time Control Demo
By Joshua Galbraith
Modified By Binsen Qian

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the Humanoid Robot Model,
as well as demonstrate how to get sensor data.
*************************************************************/

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <nxt.h>

ChNXT nxt;
int speed = 25,	//speed of the motors. (default to 25)
    quit = 0,	//used by quit case to exit the loop
    status1,	//used to check for errors
    status2,	//used to check for errors
    status3,	//used to check for errors
    status4;	//used to check for errors
char key = 'x',	//stores the input from the user
     movemode = 'x';//stores the last movement command

/* Connect to NXT */
printf("Initializing vehicle and assuming control...");
if (!nxt.connect()) {
    printf("\nPress and key to exit.\n");
    while (!_kbhit()); //wait for keypress
    exit(0);
}


/* Set sensor types */
status1 = nxt.setSensor(PORT_1, TOUCH, BOOLEANMODE);
status2 = nxt.setSensor(PORT_2, SOUND_DB, RAWMODE);
status3 = nxt.setSensor(PORT_4, LIGHT_INACTIVE, RAWMODE);
status4 = nxt.setSensor(PORT_4, ULTRASONIC, RAWMODE);
if ((status1 == 0) || (status2 == 0) || (status3 == 0)
        || (status4 == 0)) {
    printf("\nError initializing sensors.\nPress any key to exit.\n");
    while (!_kbhit()); //wait for key press
    exit(0);
}

/* GUI display */
printf("Vehicle Direction:  Other Commands:");
printf("\n     [w]           [x] Stop all Motors");
printf("\n      ^            [r] Exit Program");
printf("\n      |            [1] Set Speed to 25");
printf("\n     stop          [2] Set Speed to 50");
printf("\n     [s]           [3] Set Speed to 75");
printf("\n[a]<-head->[d]     [q] Get Sensor Data\n");
printf("Please Enter command:");

/* Control loop. Interprets user command and does action*/
while (quit != 1)
{
    nxt.setSpeeds(30, speed, speed);
    key = _getch();
    switch (key) {
        case 'w': //up
            nxt.moveJointContinuousNB(ROBOT_JOINT2, 1);
            nxt.moveJointContinuousNB(ROBOT_JOINT3, 1);
            movemode = 'w';
            break;
        case 's': //down
            nxt.moveJointContinuousNB(ROBOT_JOINT2, -1);
            nxt.moveJointContinuousNB(ROBOT_JOINT3, -1);
            movemode = 's';
            break;
        case 'd': //right
            nxt.moveJointContinuousNB(ROBOT_JOINT1, 1);
            break;
        case 'a': //left
            nxt.moveJointContinuousNB(ROBOT_JOINT1, -1);
            break;
        case 'q': //print sensor
            printSensor(&nxt);
            break;
        case 'x': //stop
            nxt.stopJoint(ROBOT_JOINT2);
            nxt.stopJoint(ROBOT_JOINT3);
            movemode = 'x';
            break;
        case 'r': //quit
            printf("\nExiting program.\nPress any key to exit.");
            quit = 1;
            break;
        case '1': //speed 25
            speed = 25;
            ungetch(movemode);
            break;
        case '2': //speed 50
            speed = 50;
            _ungetch(movemode);
            break;
        case '3': //speed 75
            speed = 75;
            ungetch(movemode);
            break;
        case '4': //speed 100
            speed = 100;
            ungetch(movemode);
            break;
        default:
            printf("\nInvalid Input!\n");
    }//switch(key)

}
nxt.disconnect();   //stop interfacing. This also stops the motors.
while (!_kbhit()); //wait for key press

int printSensor(ChNXT *nxt) {
    int touchValue = 0;
    int ultraValue = 0;
    int soundValue = 0;
    int lightValue = 0;

    touchValue = nxt.getSensor(PORT_1);
    soundValue = nxt.getSensor(PORT_2);
    lightValue = nxt.getSensor(PORT_3);
    ultraValue = nxt.getSensor(PORT_4);

    if (touchValue < 500)
        printf("\n\n\nThe touch sensor has been activated.\n", 
                touchValue);
    else
        printf("\nThe touch sensor has not been activated.\n");
    printf("The distance reported by the ultrasonic sensor is %d.\n", 
            ultraValue);
    /*
    if (light<500)  printf("\nThe touch sensor has been activated\n");
    else    printf("\nThe touch sensor has been activated\n");
    */
    printf("The light level is %d.\n", lightValue);
    printf("The Sound level is %dDb\n\n\n", soundValue);

    /* GUI display */
    printf("Vehicle Direction:  Other Commands:");
    printf("\n     [w]           [x] Stop all Motors");
    printf("\n      ^            [r] Exit Program");
    printf("\n      |            [1] Set Speed to 25");
    printf("\n     stop          [2] Set Speed to 50");
    printf("\n     [s]           [3] Set Speed to 75");
    printf("\n[a]<-head->[d]     [q] Get Sensor Data\n");
    printf("Please Enter command:");
    return(1);
}


