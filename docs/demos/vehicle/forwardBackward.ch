/* File name: forwardBackward.ch
 *
 * Introduce how to get the nxt robot 
 * to reverse direction.*/

#include <nxt.h>

ChNXT nxt;
double speedRatio = 0.25;

/* Connect to NXT */
if (nxt.connect() != 0) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(-1);
}

/* set speed via pass the speed ratio*/
nxt.setJointSpeedRatios(0, speedRatio, speedRatio);

/* Move the Robot Forward */
nxt.vehicleRollForward(360);

/* Move the Robot Backwards */
nxt.vehicleRollBackward(360);
