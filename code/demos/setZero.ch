/* File name: setZero.ch
 * presents how to set zero positions for NXT joints. */

#include <nxt.h>

ChNXT nxt;

/* Connect to the NXT */
nxt.connect();

/* Set new zero positions */
nxt.setJointZero(NXT_JOINTA);

/* Move to zero */
nxt.moveToZero();
