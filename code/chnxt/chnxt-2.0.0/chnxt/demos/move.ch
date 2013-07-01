/* File name: move.ch
 * illustrate the full series of moving function */

#include <nxt.h>
ChNXT nxt;

/* Connect to the NXT */
nxt.connect();

/* Set speed ratios */
nxt.setMotorSpeedRatios(0.5, 0.5, 0.5);

/* move motor to zero position */
nxt.moveToZero();

/* move a motor by user specified angle */
nxt.moveMotor(NXT_MOTORA, 360);

/* move a motor to absolute angle */
nxt.moveMotorTo(NXT_MOTORA, 360);

/* move all motors by specified angles */
nxt.move(180, 360, 360);

/* move all motors to absolute angles */
nxt.moveTo(360, 360, 360);
