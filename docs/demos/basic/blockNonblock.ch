/* File name: blockNonblock.ch
   To illustrate the block and non-block functions */

#include <nxt.h>

ChNXT nxt;

/* Connect to the NXT */
nxt.connect();

/* Non-blocking Function */
nxt.moveJointNB(NXT_JOINT1, 360);
printf("This message will be printed on \
        the screen when joint1 is moving.\n");
nxt.moveWait();

/* Blocking Function */
nxt.moveJoint(NXT_JOING1, 360);
printf("This message will be printed on \
        the screen after joint1 stopped moving.\n");
