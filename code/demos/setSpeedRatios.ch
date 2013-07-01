/* File name: setSpeedRatios.ch
 * set speed ratios for motors of NXT. */

#include <nxt.h>
ChNXT nxt;

/* Connect to the paired NXT */
nxt.connect();

/* set speed ratios */
nxt.setMotorSpeedRatios(0, 0.4, 0.4);
nxt.setMotorSpeedRatio(NXT_MOTORA, 0.5);

/* make NXT motors move */
nxt.move(360, 360, 360);
