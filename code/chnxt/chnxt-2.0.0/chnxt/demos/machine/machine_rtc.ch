/* File name: machine_rtc.ch

   The purpose of this demo is to demonstrate the CH Mindstorms
   Control Package's ability to control the machine robot model,
   As well as demonstrate how to set up and get sensor data. */
#include <conio.h>
#include <stdio.h>
#include <nxt.h>         //this is the control package.

ChNXT nxt;
double speedRatio = 1;        //used to control the motor speedRatio.
int angle = 0;          //stores the angle input from the user.
int quit = 0;           //used to break out of the control loop
int status = 0;
int touchValue, lightValue;
double gearratio = (8.0 / 56) * (1.0 / 24);//gear ratio on the arm
char dir = 0;       //stores "direction to move" input from user.
char color[5];
char temp[20];
char *temp_loc;
printf("gear ratio: %f", gearratio);

/* call nxt_connect function and check for success */
printf("\nInitializing arm and assuming control...");
status = nxt.connect();
if (status) {
    while (!_kbhit());  //wait for key press
    nxt.disconnect();   //stop interfacing. This also stops the motors.
    exit(0);
}//if (status ==0)

/* Initialize sensor and check for success*/
status = nxt.setSensor(NXT_SENSORPORT1, 
        NXT_SENSORTYPE_TOUCH, NXT_SENSORMODE_BOOLEANMODE);
if (status) {
    printf("\nSensor Setup failed. Exiting program.");
    while (!_kbhit());  //wait for key press
    nxt.disconnect();   //stop interfacing. This also stops the motors.
    exit(0);
}//if (status ==0)

status = nxt.setSensor(NXT_SENSORPORT3, 
        NXT_SENSORTYPE_LIGHT_ACTIVE, NXT_SENSORMODE_RAWMODE);
if (status) {
    printf("\nSensor Setup failed. Exiting program.");
    while (!_kbhit());  //wait for key press
    nxt.disconnect();   //stop interfacing. This also stops the motors.
    exit(0);
}//if (status ==0)

/*This is the user input loop, that gets the user input and
sends the commands to the NXT accordingly.
w,s move arm up and down
a,d move arm left and right
q,e open and close the claw
x stops the motor
r quits the program
f sets the speedRatio (default to 100)    */

printf("\nArm Direction:     Claw Control:\n");
printf("    [w]             [q] Claw Open\n");
printf("     ^              [e] Claw Close\n");
printf("[a]<-|->[d]        Other Commands:\n");
printf("     v              [x] Stop Motors\n");
printf("    [s]             [r] Exit Program\n");
printf("                    [f] Set Speed\n");
printf("Please Enter Command and Angle or Speed:\n");
printf("[Command]   [Argument]\n");

while (quit != 1)
{
    printf("\nEnter command: ");
    dir = getche();
    if ((dir == 'w') || (dir == 'a') || (dir == 's') ||
            (dir == 'd')) {
        printf("  Enter angle: ");
        scanf("%d", &angle);
    }
    if(dir == 'f'){
        printf("   Enter speed ratio:");
        scanf("%lf", &speedRatio);
    }

    if(dir == 'a'){ //Arm rotate left.
        nxt.moveJoint(NXT_JOINT3, (angle / gearratio));
    }else if(dir == 'd'){ //Arm rotate right.
        nxt.moveJoint(NXT_JOINT3, (int)(-angle / gearratio));
    }else if(dir == 'w'){
        nxt.moveJoint(NXT_JOINT2, (int)(angle / gearratio));
    }else if(dir == 's'){//lowdder arm down
        nxt.moveJoint(NXT_JOINT2, (int)(-angle / gearratio));
    }else if(dir == 'q'){//claw open
        nxt.moveJointContinuousNB(NXT_JOINT1, NXT_BACKWARD);
        delay(1);
        nxt.stopOneJoint(NXT_JOINT1);
    }else if(dir == 'e'){//claw close
        nxt.moveJointContinuousNB(NXT_JOINT1, NXT_FORWARD);
        delay(1);
        nxt.stopOneJoint(NXT_JOINT1);
    }else if(dir == 'x'){//stop
        nxt.stopAllJoints();
    }else if(dir == 'r'){//quit
        printf("\nQuit.");
            quit = 1;
    }else if(dir == 'f'){
        nxt.setJointSpeeds(speedRatio, speedRatio, speedRatio);
        printf("\nSpeed ratio set to %d.", speedRatio);
    }else
        printf("\n");

    delay(0.2);
    nxt.getSensor(NXT_SENSORPORT1, touchValue);
    if (touchValue < 0) {
        printf("    The Ball was grabbed ");
        nxt.getSensor(NXT_SENSORPORT3, lightValue);
        if (lightValue < 500) {
            printf("and the color is red\n");
        }else {
            printf("and the color is blue\n");
        }
    }
}
