/************************************************************
forward.ch
Created by Michael Schirle
Modified by Binsen Qian

The purpose of this demo is to introduce the CH Mindstorms
Control Package syntax to new users by moving the robot
forward.
*************************************************************/
#include <nxt.h>

ChNXT nxt;

/* Connect to NXT */
if (nxt.connect()) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(-1);
}

/* Set Speed Ratio */
nxt.setJointSpeedRatios(0, 0.25, 0.25);

/* Turn the motors on */
nxt.vehicleRollForward(360);

/* Disconnect NXT */
nxt.disconnect();
