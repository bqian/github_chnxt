/* File name: humanoid_rtc.ch
   
   The purpose of this demo is to demonstrate the CH Mindstorms
   Control Package's ability to control the Humanoid Robot Model,
   as well as demonstrate how to get sensor data. */
#include <conio.h>
#include <stdio.h>
#include <nxt.h>

ChNXT nxt;
double speedRatio = 0.25;//speedRatio of the motors. (default to 25)
int quit = 0,	//used by quit case to exit the loop
    status1,	//used to check for errors
    status2,	//used to check for errors
    status3,	//used to check for errors
    status4;	//used to check for errors
char key = 'x',	//stores the input from the user
     movemode = 'x';//stores the last movement command

/* Connect to NXT */
printf("Initializing vehicle and assuming control...");
if (nxt.connect()) {
    printf("\nPress and key to exit.\n");
    while (!_kbhit()); //wait for keypress
    exit(0);
}

/* Set sensor types */
status1 = nxt.setSensor(NXT_SENSORPORT1, 
        NXT_SENSORTYPE_TOUCH, NXT_SENSORMODE_BOOLEANMODE);
status2 = nxt.setSensor(NXT_SENSORPORT2, 
        NXT_SENSORTYPE_SOUND_DB, NXT_SENSORMODE_RAWMODE);
status3 = nxt.setSensor(NXT_SENSORPORT3, 
        NXT_SENSORTYPE_LIGHT_INACTIVE, NXT_SENSORMODE_RAWMODE);
status4 = nxt.setSensor(NXT_SENSORPORT4, 
        NXT_SENSORTYPE_ULTRASONIC, NXT_SENSORMODE_RAWMODE);
if ((status1) || (status2) || (status3)
        || (status4)) {
    printf("\nError initializing sensors.\nPress any key to exit.\n");
    while (!_kbhit()); //wait for key press
    exit(0);
}

/* GUI display */
printf("Vehicle Direction:  Other Commands:");
printf("\n     [w]           [x] Stop all Motors");
printf("\n      ^            [r] Exit Program");
printf("\n      |            [1] Set Speed Ratio to 0.25");
printf("\n     stop          [2] Set Speed Ratio to 0.50");
printf("\n     [s]           [3] Set Speed Ratio to 0.75");
printf("\n[a]<-head->[d]     [q] Get Sensor Data\n");
printf("Please Enter command:");

/* Control loop. Interprets user command and does action*/
while (quit != 1){
    nxt.setJointSpeedRatios(0.3, speedRatio, speedRatio);
    key = _getch();
    if(key == 'w'){//up
        nxt.moveJointContinuousNB(NXT_JOINTB, NXT_FORWARD);
        nxt.moveJointContinuousNB(NXT_JOINTC, NXT_FORWARD);
        movemode = 'w';
    }else if(key =='s'){ //down
        nxt.moveJointContinuousNB(NXT_JOINTB, NXT_BACKWARD);
        nxt.moveJointContinuousNB(NXT_JOINTC, NXT_BACKWARD);
        movemode = 's';
    }else if(key == 'd'){//right
        nxt.moveJointContinuousNB(NXT_JOINTA, NXT_FORWARD);
    }else if(key == 'a'){//left
        nxt.moveJointContinuousNB(NXT_JOINTA, NXT_BACKWARD);
    }else if(key == 'q'){//print sensor
        printSensor(&nxt);
    }else if(key == 'x'){//stop
        nxt.stopAllJoints();
        movemode = 'x';
    }else if(key == 'r'){//quit
        printf("\nExiting program.\nPress any key to exit.");
        quit = 1;
    }else if(key == '1'){//speedRatio .25
        speedRatio = 0.25;
        ungetch(movemode);
    }else if(key == '2'){//speedRatio .50
        speedRatio = 0.50;
        ungetch(movemode);
    }else if(key == '3'){//speedRatio .75
        speedRatio = 0.75;
        ungetch(movemode);
    }else if(key == '4'){//speedRatio 1
        speedRatio = 1;
        ungetch(movemode);
    }else{
        printf("\nInvalid Input!\n");
    }
}
nxt.disconnect();  //stop interfacing. This also stops the motors.

int printSensor(ChNXT *nxt) {
    int touchValue = 0;
    int ultraValue = 0;
    int soundValue = 0;
    int lightValue = 0;

    /* get values from NXT */
    nxt->getSensor(NXT_SENSORPORT1, touchValue);
    nxt->getSensor(NXT_SENSORPORT2, soundValue);
    nxt->getSensor(NXT_SENSORPORT3, lightValue);
    nxt->getSensor(NXT_SENSORPORT4, ultraValue);

    /* display the values */
    if (touchValue < 0)
        printf("\n\n\nThe touch sensor has been activated.\n", 
                touchValue);
    else
        printf("\nThe touch sensor has not been activated.\n");

    printf("The distance reported by the ultrasonic sensor is %d.\n", 
			ultraValue);
    /*
    if (light<500)  printf("\nThe touch sensor has been activated\n");
    else    printf("\nThe touch sensor has been activated\n");
    */
    printf("The light level is %d.\n", lightValue);
    printf("The Sound level is %dDb\n\n\n", soundValue);

    /* GUI display */
    printf("Vehicle Direction:  Other Commands:");
    printf("\n     [w]           [x] Stop all Motors");
    printf("\n      ^            [r] Exit Program");
    printf("\n      |            [1] Set Speed to 25");
    printf("\n     stop          [2] Set Speed to 50");
    printf("\n     [s]           [3] Set Speed to 75");
    printf("\n[a]<-head->[d]     [q] Get Sensor Data\n");
    printf("Please Enter command:");
    return 0;
}
