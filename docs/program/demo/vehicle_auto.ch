/************************************************************
vehicle_auto.ch
Vehicle Robot Autonomous Exploration Example
By Joshua Galbraith and Harry H. Cheng

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the machine robot model
autonomously, as well as demonstrate how use sensor data from
the NXT to controle it's actions.
*************************************************************/
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <ch_nxt.h>
#include <unistd.h>

//declare variables
int  speed = 25,	//sets the speed for the motors. Default is 25
     status1 = 2,		//used to check for errors
     status2 = 2;		//used to check for errors
char key = 'x',		//stores user input
     movemode = 'x';	//stores last movement command

//Connect to NXT
struct nxt_remote nxtr;
printf("Initializing vehicle and assuming control...");
if (!nxt_connect(&nxtr)) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    printf("\nPress any key to exit.\n");
    while (!_kbhit()); //wait for keypress
    exit(0);
}

//Set sensor types
status1 = nxt_setsensor(PORT_1, TOUCH, BOOLEANMODE);
status2 = nxt_setsensor(PORT_4, ULTRASONIC, RAWMODE);
if ((status1 == 0) || (status2 == 0)) {
    printf("\nError initializing sensors.\nPress any key to exit.\n");
    while (!_kbhit()); //wait for keypress
    exit(0);
}

while (1) {
    //check user input 'q' to quit
    if (kbhit()) {
        if (getch() == 'q') {
            printf("\nExiting.");
            break;
        }
    }

    //get touch sensor. If pressed reverse and turn left
    nxt_getsensor(PORT_1);
    if (nxtr.NXT_sensorvalraw[PORT_1] < 500) {
        nxt_motor_rotate(PORT_B, -25, 720);
        nxt_motor_rotate(PORT_C, -25, 720);
        Sleep(1000);
        nxt_motor(PORT_B, 0, RUN_BRAKE);
        nxt_motor(PORT_C, 0, RUN_BRAKE);
        Sleep(750);
        nxt_motor_rotate(PORT_C, 50, 720);
    }

    // get distance from UltraSonic sensor,
    // set speed according to distance. Turn left if really close.
    nxt_getsensor(PORT_4);
    if (nxtr.NXT_sensorvalraw[PORT_4] < 10) {
        nxt_motor_rotate(PORT_B, -25, 720);
        nxt_motor_rotate(PORT_C, -25, 720);
        Sleep(1000);
        nxt_motor(PORT_B, 0, RUN_BRAKE);
        nxt_motor(PORT_C, 0, RUN_BRAKE);
        Sleep(750);
        nxt_motor_rotate(PORT_C, 50, 720);
        speed = 0;
        Sleep(750);
    }
    else if (nxtr.NXT_sensorvalraw[PORT_4] < 30)
        speed = 25;
    else if (nxtr.NXT_sensorvalraw[PORT_4] < 50)
        speed = 50;
    else if (nxtr.NXT_sensorvalraw[PORT_4] < 100)
        speed = 75;
    else if (nxtr.NXT_sensorvalraw[PORT_4] < 200)
        speed = 100;
    else
        speed = 75;

    // Turn motors on (drive forward)
    nxt_motor(PORT_B, speed, RUN_BRAKE);
    nxt_motor(PORT_C, speed, RUN_BRAKE);
}
nxt_disconnect();   //stop interfacing. This also stops the motors.
printf("\nPress any key to exit.\n");
while (!_kbhit()); //wait for keypress
