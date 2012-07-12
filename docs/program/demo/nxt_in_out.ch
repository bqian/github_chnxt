/************************************************************
nxt_in_out.ch
By Michael Schirle

The purpose of this program is to introduce how to incorportate
input and output functions into NXT programs.
*************************************************************/
#include <windows.h>
#include <conio.h>
#include <ch_nxt.h>

//Initialize Speed Variable
int speed;

//Connect to NXT
struct nxt_remote nxtr;

//Connect to NXT
if (!nxt_connect(&nxtr)) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(0);
}

//Prompt user for speed value
printf("Hello, I am the nxt robot!\n");
printf("Please enter a speed [1 - 100] for the robot\n");

//Read user speed value
scanf("%d", &speed);

//Tell user it will be moving forward
printf("I will now move forward\n");

//Move the Robot Forward
nxt_forward(speed);
sleep(5);

//Tell user it has arrived
printf("I have arrived at the destination!\n");

//Stop the robot in place
nxt_stop();
sleep(1);

//Tell user the next action
printf("I am now moving in reverse!\n");

//Move the Robot Backwards
nxt_backward(speed);
sleep(5);

//Tell user that the program is complete
printf("I am done!\n");

//Turn the motors off
nxt_stop();

//Disconnect NXT
nxt_disconnect();
