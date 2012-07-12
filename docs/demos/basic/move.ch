/* File name: move.ch
 * illustrate the full series of moving function */

#include <nxt.h>
ChNXT nxt;

/* Connect to the NXT */
nxt.connect();

/* Set speed ratios */
nxt.setJointSpeedRatios(0.5, 0.5, 0.5);

/* move joint to zero position */
nxt.moveToZero();

/* move a joint by user specified angle */
nxt.moveJoint(NXT_JOINT1, 360);

/* move a joint to absolute angle */
nxt.moveJointTo(NXT_JOINT1, 360);

/* move all joints by specified angles */
nxt.move(180, 360, 360);

/* move all joints to absolute angles */
nxt.moveTo(360, 360, 360);

/* disconnect from NXT */
nxt.disconnect();
