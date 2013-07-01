/************************************************************
  touchsensor.ch
  
  The purpose of this demo is to demonstrate the CH Mindstorms
  Control Package's ability to control the NXT Mindstorm to use
  the touch sensor.
*************************************************************/
#include <conio.h>
#include <nxt.h>
#include <unistd.h>

ChNXT nxt;
int status;
int touchValue;

/* Connect to NXT */
if (nxt.connect() == 1) {
    exit(0);
}

/* Set sensor types */
status = nxt.setSensor(NXT_SENSORPORT1, NXT_SENSORTYPE_TOUCH, NXT_SENSORMODE_BOOLEANMODE);
if (status == 0) {
    exit(0);
}

/* set motor speed ratios */
nxt.setMotorSpeedRatios(0, 0.25, 0.25);

/* Move Robot Forward */
nxt.moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
nxt.moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);

/* Commands: */
while (1) {
    /* Get touch sensor data */
    touchValue = nxt.getSensor(NXT_SENSORPORT1);
    /* If touch sensor is triggered */
    if (touchValue == 1) {
        /* Move backward */
        nxt.moveMotorContinuousNB(ROBOT_MOTORB, NXT_BACKWARD);
        nxt.moveMotorContinuousNB(ROBOT_MOTORC, NXT_BACKWARD);
        sleep(5);
        /* quit the while loop */
        break;
    }
}

/* Stop the motors */
nxt.stopTwoMotors(ROBOT_MOTORB, ROBOT_MOTORC);
