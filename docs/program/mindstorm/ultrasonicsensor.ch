/************************************************************
ultrasonicsensor.ch
Vehicle moving forward controlled by ultra sonic sensor demo
By Wai Hong Tsang

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the NXT Mindstorm to use
the ultra sonic sensor.
*************************************************************/
#include <conio.h>
#include <nxt.h>
#include <unistd.h>

ChNXT nxt;
int status;
int ultraValue;
double speedRatio;

/* Connect to NXT */
if (nxt.connect() == -1) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(0);
}

/* Set sensor types */
status = nxt.setSensor(SENSOR_PORT4, SENSOR_TYPE_ULTRASONIC, SENSOR_MODE_RAWMODE);
if (status == 0) {
    exit(0);
}

/* Commands: */
while (1) {
    /* get ultrasonic sensor data */
    ultraValue = nxt.getSensor(SENSOR_PORT4);
    /* If obstacle is really close */
    if (ultraValue < 20) {
        speedRatio = .25;
        /* Move backward */
        nxt.moveJointContinuousNB(ROBOT_JOINT2, -1);
        nxt.moveJointContinuousNB(ROBOT_JOINT3, -1);
        sleep(3);
        /* Quit the while loop */
        break;
    }/* Else if the obstacle is close */
    else if (ultraValue < 60) {
        speedRatio = .25;
    }/* Else if the obstacle is not close */
    else if (ultraValue < 100) {
        speedRatio = .50;
    }/* Else if there is no obstacle in sight */
    else if (ultraValue < 200) {
        speedRatio = .75;
    } /* Sensor value larger than 200 */
    else {
        speedRatio = .75;
    }
    /* Move forward (constantly)*/
    nxt.setJointSpeedRatios(0, speedRatio, speedRatio);
    nxt.moveJointContinuousNB(ROBOT_JOINT2, 1);
    nxt.moveJointContinuousNB(ROBOT_JOINT3, 1);
}

/* Stop the motors*/
nxt.stopTwoJoints(ROBOT_JOINT2);

/*Disconnect NXT*/
nxt.disconnect();
