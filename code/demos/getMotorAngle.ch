/* Filename: getMotorAngle.ch
 * Find the current motor angle of a motor */

#include <nxt.h>
ChNXT nxt;

/* Connect to a NXT */
nxt.connect();

/* Get the motor angle of the first motor */
double angle;
nxt.getMotorAngle(NXT_MOTORA, angle);

/* Print out the motor angle */
printf("The current motor angle for motor 1 is %lf degrees.\n", angle);
