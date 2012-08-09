/*File name: ultrasonicsensor.ch
  
  The purpose of this demo is to demonstrate the CH Mindstorms
  Control Package's ability to control the NXT Mindstorm to use
  the ultra sonic sensor.*/
  
#include <nxt.h>

ChNXT nxt;
int status;
int ultraValue;
double speedRatio;

/* Connect to NXT */
if (nxt.connect()) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(-1);
}

/* Set sensor types */
status = nxt.setSensor(NXT_SENSORPORT4, 
        NXT_SENSORTYPE_ULTRASONIC, NXT_SENSORMODE_RAWMODE);
if (status) {
    exit(-1);
}

/* Commands: */
while (1) {
    /* get ultrasonic sensor data */
    nxt.getSensor(NXT_SENSORPORT4, ultraValue);

    /* If obstacle is really close */
    if (ultraValue < 35) {
        speedRatio = 0.25;
        /* Move backward */
        nxt.moveJointContinuousNB(NXT_JOINT2, NXT_BACKWARD);
        nxt.moveJointContinuousNB(NXT_JOINT3, NXT_BACKWARD);
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
    nxt.moveJointContinuousNB(NXT_JOINT2, NXT_FORWARD);
    nxt.moveJointContinuousNB(NXT_JOINT3, NXT_FORWARD);
}

/* Stop the motors*/
nxt.stopTwoJoints(NXT_JOINT2, NXT_JOINT3);

/*Disconnect NXT*/
nxt.disconnect();
