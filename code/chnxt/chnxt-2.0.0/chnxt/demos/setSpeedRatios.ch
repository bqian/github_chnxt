/* File name: setSpeedRatios.ch
 * set speed ratios for joints of NXT. */

#include <nxt.h>
ChNXT nxt;

/* Connect to the paired NXT */
nxt.connect();

/* set speed ratios */
nxt.setJointSpeedRatios(0, 0.4, 0.4);
nxt.setJointSpeedRatio(NXT_JOINT1, 0.5);

/* make NXT joints move */
nxt.move(360, 360, 360);
