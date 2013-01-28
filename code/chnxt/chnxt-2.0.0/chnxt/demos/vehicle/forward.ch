/* File name: forward.ch
 *
 * Introduce the CH Mindstorms control Package syntax 
 * to new users by moving the robot forward. */

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
