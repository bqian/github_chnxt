/* File name: setZero.ch
 * presents how to set zero positions for NXT motors. */

#include <nxt.h>

ChNXT nxt;

/* Connect to the NXT */
nxt.connect();

/* Set new zero positions */
nxt.setMotorZero(NXT_MOTORA);

/* Move to zero */
nxt.moveToZero();
