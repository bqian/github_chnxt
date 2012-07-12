/************************************************************
forward.ch
Created by Michael Schirle
Modified by Binsen Qian

The purpose of this demo is to introduce the CH Mindstorms
Control Package syntax to new users by moving the robot
forward.
*************************************************************/
#include <conio.h>
#include <nxt.h>
#include <unistd.h>

ChNXT nxt;

/* Connect to NXT */
if (nxt.connect() == -1) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(0);
}

/* Set Speed Ratio */
nxt.setSpeedRatios(0, 0.25, 0.25);

/* Turn the motors on */
nxt.vehicleRollForward(360);

/* Disconnect NXT */
nxt.disconnect();
