/************************************************************
first_forward_back.ch
By Michael Schirle

The purpose of this program is to introduce how to get the
nxt_robot to reverse direction.
*************************************************************/
#include <conio.h>
#include <ch_nxt.h>
#include <unistd.h>

//Define Speed Variable
int speed = 25;	//the speed of the motors.

//Connect to NXT
struct nxt_remote nxtr;
if (!nxt_connect(&nxtr)) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(0);
}

//Move the Robot Forward
nxt_forward(speed);
sleep(5);

//Stop the robot in place
nxt_stop();
sleep(1);

//Move the Robot Backwards
nxt_backward(speed);
sleep(5);

//Turn the motors off
nxt_stop();

//Disconnect NXT
nxt_disconnect();
