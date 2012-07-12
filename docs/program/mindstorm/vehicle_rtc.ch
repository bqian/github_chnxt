/************************************************************
vehicle_rtc.ch
Vehicle Robot Real Time Control Demo
By Joshua Galbraith and Harry H. Cheng
Modified by Binsen Qian

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the machine robot model,
As well as demonstrate how to get and use sensor data.
*************************************************************/
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <nxt.h>

ChNXT nxt;
int speed = 25,	//speed of the motors. (default to 25)
    quit = 0,	//used by quit case to exit the loop
    status1,	//used to check for errors
    status2;	//used to check for errors
char key = 'x',	//stores the input from the user
     movemode = 'x';//stores the last movement command

/* Connect to NXT */
printf("Initializing vehicle and assuming control...");
if (!nxt.connect()) {
    printf("\nPress any key to exit.\n");
    while (!_kbhit()); //wait for keypress
    exit(0);
}

/* GUI display */
printf("Vehicle Direction:  Other Commands:");
printf("\n    [w]               [x] Stop Motors");
printf("\n [q] ^ [e]            [r] Exit Program");
printf("\n    \\|/               [1] Set Speed to 25");
printf("\n[a]<-|->[d]           [2] Set Speed to 50");
printf("\n     v                [3] Set Speed to 75");
printf("\n    [s]               [4] Set Speed to 100\n");
printf("Please Enter command:");

/* Control loop. Interprets user command and does action*/
while (quit != 1 ) {
    key = _getch();
    switch (key) {
        case 'w': //up
            nxt.setJointSpeeds(0, speed, speed);
            nxt.moveJointContinuousNB(ROBOT_JOINT2, 1);
            nxt.moveJointContinuousNB(ROBOT_JOINT3, 1);
            movemode = 'w';
            break;
        case 's': //down
            nxt.setJointSpeeds(0, speed, speed);
            nxt.moveJointContinuousNB(ROBOT_JOINT2, -1);
            nxt.moveJointContinuousNB(ROBOT_JOINT3, -1);
            movemode = 's';
            break;
        case 'd': //right
            nxt.setJointSpeeds(0, speed, speed);
            nxt.moveJointContinuousNB(ROBOT_JOINT2, -1);
            nxt.moveJointContinuousNB(ROBOT_JOINT3, 1);
            movemode = 'd';
            break;
        case 'a': //left
            nxt.setJointSpeeds(0, speed, speed);
            nxt.moveJointContinuousNB(ROBOT_JOINT2, 1);
            nxt.moveJointContinuousNB(ROBOT_JOINT3, -1);
            movemode = 'a';
            break;
        case 'q': //forward-left
            nxt.setJointSpeeds(0, speed, 0.7*speed);
            nxt.moveJointContinuousNB(ROBOT_JOINT2, 1);
            nxt.moveJointContinuousNB(ROBOT_JOINT3, 1);
            movemode = 'q';
            break;
        case 'e': //forward-right
            nxt.setJointSpeeds(0, 0.7*speed, speed);
            nxt.moveJointContinuousNB(ROBOT_JOINT2, 1);
            nxt.moveJointContinuousNB(ROBOT_JOINT3, 1);
            movemode = 'e';
            break;
        case 'x': //stop
            nxt.stopJoint(ROBOT_JOINT2);
            nxt.stopJoint(ROBOT_JOINT3);
            movemode = 'x';
            break;
        case 'r': //quit
            printf("\nExiting program.\n");
            quit = 1;
            break;
        case '1': //speed 25
            speed = 25;
            ungetch(movemode);
            break;
        case '2': //speed 50
            speed = 50;
            ungetch(movemode);
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
printf("Press any key to exit.\n");
while (!_kbhit()); //wait for key press
exit 0;
