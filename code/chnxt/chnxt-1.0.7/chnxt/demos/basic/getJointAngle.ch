/* Filename: getJointAngle.ch
 * Find the current joint angle of a joint */

#include <nxt.h>
ChNXT nxt;

/* Connect to a NXT */
nxt.connect();

/* Get the joint angle of the first joint */
double angle;
nxt.getJointAngle(NXT_JOINT1, angle);

/* Print out the joint angle */
printf("The current joint angle for joint 1 is %lf degrees.\n", angle);

/* Disconnect from NXT */
nxt.disconnect();
