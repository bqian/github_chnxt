/************************************************************
touchsensor.ch
Vehicle moving forward demo
Created by Wai Hong Tsang
Modified by Binsen Qian

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
status = nxt.setSensor(SENSOR_PORT1, SENSOR_TYPE_TOUCH, SENSOR_MODE_BOOLEANMODE);
if (status == 0) {
    exit(0);
}

/* set joint speed ratios */
nxt.setJointSpeedRatios(0, 0.25, 0.25);

/* Move Robot Forward */
nxt.moveJointContinuousNB(ROBOT_JOINT2, 1);
nxt.moveJointContinuousNB(ROBOT_JOINT3, 1);

/* Commands: */
while (1) {
    /* Get touch sensor data */
    touchValue = nxt.getSensor(SENSOR_PORT1);
    /* If touch sensor is triggered */
    if (touchValue < 500) {
        /* Move backward */
        nxt.moveJointContinuousNB(ROBOT_JOINT2, -1);
        nxt.moveJointContinuousNB(ROBOT_JOINT3, -1);
        sleep(5);
        /* quit the while loop */
        break;
    }
}

/* Stop the motors */
nxt.stopTwoJoints(ROBOT_JOINT2, ROBOT_JOINT3);

/* Disconnect NXT */
nxt.disconnect();
