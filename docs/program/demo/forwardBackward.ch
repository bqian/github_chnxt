/************************************************************
forwardBackward.ch
Created by Michael Schirle
Modified by Binsen Qian

The purpose of this program is to introduce how to get the
nxt_robot to reverse direction.
*************************************************************/
#include <conio.h>
#include <nxt.h>
#include <unistd.h>

ChNXT nxt;
double speedRatio = 0.25;

/* Connect to NXT */
if (nxt.connect() == -1) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(0);
}

/* set speed via pass the speed ratio*/
nxt.setJointSpeedRatios(0, speedRatio, speedRaio);

/* Move the Robot Forward */
nxt.vehicleRollForward(360);

/* Move the Robot Backwards */
nxt.vehicleRollBackward(360);

/* Disconnect NXT */
nxt.disconnect();
