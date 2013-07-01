/* File name: blockNonblock.ch
   To illustrate the block and non-block functions */

#include <nxt.h>

ChNXT nxt;

/* Connect to the NXT */
nxt.connect();

/* Non-blocking Function */
nxt.moveMotorNB(NXT_MOTORA, 360);
printf("This message will be printed on \
        the screen when motor1 is moving.\n");
nxt.moveWait();

/* Blocking Function */
nxt.moveMotor(NXT_MOTORA, 360);
printf("This message will be printed on \
        the screen after motor1 stopped moving.\n");
