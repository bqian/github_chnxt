/* File name: touchsensor.ch
   
   The purpose of this demo is to demonstrate the CH Mindstorms
   Control Package's ability to control the NXT Mindstorm to use
   the touch sensor. */

#include <nxt.h>

ChNXT nxt;
int status;
int touchValue;

/* Connect to NXT */
if (nxt.connect()) {
    printf("Fail to connect!\n");
    exit(-1);
}

/* Set sensor types */
status = nxt.setSensor(NXT_SENSORPORT1, 
        NXT_SENSORTYPE_TOUCH, NXT_SENSORMODE_BOOLEANMODE);
if (status) {
    printf("Fail to setup sensors.\n");
    exit(-1);
}

/* set joint speed ratios */
nxt.setJointSpeedRatios(0, 0.25, 0.25);

/* Move Robot Forward */
nxt.moveJointContinuousNB(NXT_JOINT2, NXT_BACKWARD);
nxt.moveJointContinuousNB(NXT_JOINT3, NXT_BACKWARD);

/* Commands: */
while (1) {
    /* Get touch sensor data */
    nxt.getSensor(NXT_SENSORPORT1, touchValue);
    /* If touch sensor is triggered */
    if (touchValue < 0) {
        /* Move backward */
        nxt.moveJointContinuousNB(NXT_JOINT2, NXT_FORWARD);
        nxt.moveJointContinuousNB(NXT_JOINT3, NXT_FORWARD);
        delay(2);
        /* quit the while loop */
        break;
    }
}

/* Stop the motors */
nxt.stopTwoJoints(NXT_JOINT2, NXT_JOINT3);

/* Disconnect NXT */
nxt.disconnect();
