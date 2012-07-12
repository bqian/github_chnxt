/************************************************************
robot_remotecontrol.ch
Vehicle moving forward demo
By Wai Hong Tsang

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the NXT Mindstorm to move
forward a few seconds and then stop.
*************************************************************/
#include <windows.h>
#include <conio.h>
#include <ch_nxt.h>

struct nxt_remote nxtr;

//Connect to NXT
if (!nxt_connect(&nxtr)) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(0);
}

//Define the variables
int  speed = 25;	//the speed of the motors. (default to 25)
char key = 'x';     // 'x' = stop
char movemode = 'x';// save last move setting
int quit = 0;       // not equal to 1
//Greaphical User Interface
printf("\n");
//Commands:
while (quit != 1) {
    key = _getch();
    switch (key) {
        case 'w': //forward
            nxt_motor(PORT_B, speed, RUN_IDLE);
            nxt_motor(PORT_C, speed, RUN_IDLE);
            movemode = 'w';
            break;
        case 's': //backward
            nxt_motor(PORT_B, -speed, RUN_IDLE);
            nxt_motor(PORT_C, -speed, RUN_IDLE);
            movemode = 's';
            break;
            //360 left
        case 'd': //360 right
            nxt_motor(PORT_B, -speed, RUN_IDLE);
            nxt_motor(PORT_C, speed, RUN_IDLE);
            movemode = 'd';
            break;
        case 'q': //left forward
            nxt_motor(PORT_B, speed, RUN_IDLE);
            nxt_motor(PORT_C, 0.5*speed, RUN_IDLE);
            movemode = 'q';
            break;
            //right forward
        case '1': //speed = 10
            speed = 10;
            ungetch(movemode);
            break;
        case 'r': //quit
            printf("program is terminated\n");
            quit = 1;
            break;
        case 'x': //stop
            nxt_motor(PORT_B, 0, OFF_IDLE);
            nxt_motor(PORT_C, 0, OFF_IDLE);
            movemode = 'x';
            break;
        case 't': // move shovel
            nxt_motor(PORT_A, 10, RUN_IDLE);
            break;
        case 'g': // stop shovel
            nxt_motor(PORT_A, 0, OFF_IDLE);
            break;
    }
}

//Stop the motors
nxt_motor(PORT_A, 0, OFF_IDLE);
nxt_motor(PORT_B, 0, OFF_IDLE);
nxt_motor(PORT_C, 0, OFF_IDLE);

//Disconnect NXT
nxt_disconnect();
