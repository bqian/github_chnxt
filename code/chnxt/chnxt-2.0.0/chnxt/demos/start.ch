/* File name: start.ch
 *
 * Move the NXT all joints by 360 degrees.*/

#include <nxt.h>

ChNXT nxt;

/* Connect to the paired NXT */
nxt.connect();

/* Set the robot to "home" position,
 * where all joint angles are 0 degrees.*/
nxt.moveToZero();

/* Rotate joint 2 and 3 by 360 degrees */
nxt.move(360, 360, 360);
