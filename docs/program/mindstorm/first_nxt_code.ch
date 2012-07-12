/************************************************************
first_nxt_code.c
By Michael Schirle

The purpose of this demo is to introduce the CH Mindstorms
Control Package syntax to new users by moving the robot
forward.
*************************************************************/
#include <conio.h>
#include <ch_nxt.h>
#include <unistd.h>

//Define speed variable, can be set [-100 to 100]
int speed = 25;	//the speed of the motors.

//Connect to NXT
struct nxt_remote nxtr;
if (!nxt_connect(&nxtr)) {
    exit(0);
}

//Turn the motors on
nxt_forward(speed);

//Add time delay before next command
sleep(5);

//Turn the motors off
nxt_stop();

//Disconnect NXT
nxt_disconnect();
