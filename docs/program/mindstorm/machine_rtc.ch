/************************************************************
machine_rtc.ch
Machine Robot Real Time Control Demo
By Joshua Galbraith
Modified by Binsen Qian

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the machine robot model,
As well as demonstrate how to set up and get sensor data.
*************************************************************/
#include <conio.h>
#include <stdio.h>
#include <nxt.h>         //this is the control package.

ChNXT nxt;
int speedRatio = 100;        //used to control the motor speedRatio.
int angle = 0;          //stores the angle input from the user.
int quit = 0;           //used to break out of the control loop
int result = 0;
int status1, status2;
double gearratio = (8.0 / 56) * (1.0 / 24); //gear ratio on the arm
char dir = 0;           //stores "direction to move" input from user.
char color[5];
char temp[20];
char *temp_loc;
printf("gear ratio: %f", gearratio);

/* call nxt_connect function and check for success */
printf("\nInitializing arm and assuming control...");
result = nxt.connect();
if (result == 0) {
    while (!_kbhit());  //wait for key press
    nxt.disconnect();   //stop interfacing. This also stops the motors.
    exit(0);
}//if (result ==0)


/* Initialize sensor and check for success*/
result = nxt.setSensor(SENSOR_PORT1, SENSOR_TYPE_TOUCH, SENSOR_MODE_BOOLEANMODE);
if (result == 0) {
    printf("\nSensor Setup failed. Exiting program.");
    while (!_kbhit());  //wait for key press
    nxt.disconnect();   //stop interfacing. This also stops the motors.
    exit(0);
}//if (result ==0)

result = nxt.setSensor(SENSOR_PORT3, SENSOR_TYPE_LIGHT_ACTIVE, SENSOR_MODE_RAWMODE);
if (result == 0) {
    printf("\nSensor Setup failed. Exiting program.");
    while (!_kbhit());  //wait for key press
    nxt.disconnect();   //stop interfacing. This also stops the motors.
    exit(0);
}//if (result ==0)

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
            (dir == 'd') || (dir == 'f')) {
        printf("  Enter angle or Speed: ");
        scanf("%d", &angle);
    }
    //	scanf("%c %d",&dir, &angle);
    nxt.setJointSpeeds(speedRatio, speedRatio, speedRatio);
    switch (dir) {
        case 'a': //Arm rotate left.
            nxt.moveJoint(ROBOT_JOINT3, (int)(angle / gearratio));
            break;
        case 'd': //Arm rotate right.
            nxt.moveJoint(ROBOT_JOINT3, (int)(-angle / gearratio));
            break;
        case 'w': //Raise arm up.
            nxt.moveJoint(ROBOT_JOINT2, (int)(angle / gearratio));
            break;
        case 's': //lower arm down
            nxt.moveJoint(ROBOT_JOINT2, (int)(-angle / gearratio));
            break;
        case 'q': //claw open
            nxt.moveJointContinuousNB(ROBOT_JOINT1, -1);
            Sleep(1000);
            nxt.stopJoint(ROBOT_JOINT1);
            break;
        case 'e': //claw close
            nxt.moveJointContinuousNB(ROBOT_JOINT1, 1);
            Sleep(1000);
            nxt.stopJoint(ROBOT_JOINT1);
            break;
        case 'x': //stop
            nxt.setZeros();
            nxt.stopJoints();
            break;
        case 'r': //quit
            printf("\nQuit.");
            quit = 1;
            break;
        case 'f': //set speed ratio
            speedRatio = angle;
            printf("\nSpeed ratio set to %d.", speedRatio);
            break;
        default:
            printf("\n");
    }//switch(dir)
    pause(0.2);
    status1 = nxt.getSensor(SENSOR_PORT1);
    if (status1 < 500) {
        printf("    The Ball was grabbed ");
        status2 = nxt.getSensor(SENSOR_PORT3);
        if (status < 500) {
            printf("and the color is red\n");
        }else {
            printf("and the color is blue\n");
        }
    }
}

nxt.disconnect();		//stop interfacing. This also stops the motors.
while (!_kbhit());		//wait for key press
