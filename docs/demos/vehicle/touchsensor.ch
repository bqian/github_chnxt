/* File name: touchsensor.ch
 *
 * Demonstrate the CH Mindstorms Control Package's ability 
 * to control the NXT Mindstorm to use the touch sensor. */

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

/* set motor speed ratios */
nxt.setMotorSpeedRatios(0, 0.25, 0.25);

/* Move Robot Forward */
nxt.moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
nxt.moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);

/* Commands: */
while (1) {
    /* Get touch sensor data */
    nxt.getSensor(NXT_SENSORPORT1, touchValue);
    /* If touch sensor is triggered */
    if (touchValue == 1) {
        /* Move backward */
        nxt.moveMotorContinuousNB(NXT_MOTORB, NXT_BACKWARD);
        nxt.moveMotorContinuousNB(NXT_MOTORC, NXT_BACKWARD);
        delay(2);
        /* quit the while loop */
        break;
    }
}

/* Stop the motors */
nxt.stopTwoMotors(NXT_MOTORB, NXT_MOTORC);
