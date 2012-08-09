/* File name: setZero.ch
 * presents how to set zero positions for NXT joints. */

#include <nxt.h>

ChNXT nxt;

/* Connect to the NXT */
nxt.connect();

/* Set new zero positions */
nxt.setJointToZero(NXT_JOINT1);

/* Move to zero */
nxt.moveToZero();
