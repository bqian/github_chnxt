/*File name: vehicle_rtc.ch
  Vehicle Robot Real Time Control Demo
  By Joshua Galbraith and Harry H. Cheng
  Modified by Binsen Qian

  The purpose of this demo is to demonstrate the CH Mindstorms
  Control Package's ability to control the machine robot model,
  As well as demonstrate how to get and use sensor data. */
#include <conio.h>
#include <stdio.h>
#include <nxt.h>

ChNXT nxt;
double speedRatio = 0.25;	//speedRatio of the motors. (default to 25)
int quit = 0,	//used by quit case to exit the loop
    status1,	//used to check for errors
    status2;	//used to check for errors
char key = 'x',	//stores the input from the user
     movemode = 'x';//stores the last movement command

/* Connect to NXT */
printf("Initializing vehicle and assuming control...");
if (nxt.connect()) {
    printf("\nPress any key to exit.\n");
    while (!_kbhit()); //wait for keypress
    exit(0);
}

/* GUI display */
printf("Vehicle Direction:  Other Commands:");
printf("\n    [w]               [x] Stop Motors");
printf("\n [q] ^ [e]            [r] Exit Program");
printf("\n    \\|/               [1] Set SpeedRatio to 0.25");
printf("\n[a]<-|->[d]           [2] Set SpeedRatio to 0.50");
printf("\n     v                [3] Set SpeedRatio to 0.75");
printf("\n    [s]               [4] Set SpeedRatio to 1\n");
printf("Please Enter command:");

/* Control loop. Interprets user command and does action*/
while (quit != 1 ) {
    key = _getch();
    if(key == 'w'){//up
        nxt.setJointSpeedRatios(0, speedRatio, speedRatio);
        nxt.moveJointContinuousNB(NXT_JOINTB, NXT_FORWARD);
        nxt.moveJointContinuousNB(NXT_JOINTC, NXT_FORWARD);
        movemode = 'w';
    }else if(key == 's'){//down
        nxt.setJointSpeedRatios(0, speedRatio, speedRatio);
        nxt.moveJointContinuousNB(NXT_JOINTB, NXT_BACKWARD);
        nxt.moveJointContinuousNB(NXT_JOINTC, NXT_BACKWARD);
        movemode = 's';
    }else if(key == 'd'){//right
        nxt.setJointSpeedRatios(0, speedRatio, speedRatio);
        nxt.moveJointContinuousNB(NXT_JOINTB, NXT_BACKWARD);
        nxt.moveJointContinuousNB(NXT_JOINTC, NXT_FORWARD);
        movemode = 'd';
    }else if(key == 'a'){//left
        nxt.setJointSpeedRatios(0, speedRatio, speedRatio);
        nxt.moveJointContinuousNB(NXT_JOINTB, NXT_FORWARD);
        nxt.moveJointContinuousNB(NXT_JOINTC, NXT_BACKWARD);
        movemode = 'a';
    }else if(key == 'q'){//forward-left
        nxt.setJointSpeedRatios(0, speedRatio, 0.7*speedRatio);
        nxt.moveJointContinuousNB(NXT_JOINTB, NXT_FORWARD);
        nxt.moveJointContinuousNB(NXT_JOINTC, NXT_FORWARD);
        movemode = 'q';
    }else if(key == 'e'){//forward-right
        nxt.setJointSpeedRatios(0, 0.7*speedRatio, speedRatio);
        nxt.moveJointContinuousNB(NXT_JOINTB, NXT_FORWARD);
        nxt.moveJointContinuousNB(NXT_JOINTC, NXT_FORWARD);
        movemode = 'e';
    }else if(key == 'x'){//stop
        nxt.stopOneJoint(NXT_JOINTB);
        nxt.stopOneJoint(NXT_JOINTC);
        movemode = 'x';
    }else if(key == 'r'){//quit
        printf("\nExiting program.\n");
        quit = 1;
    }else if(key == '1'){//speedRatio 0.25
        speedRatio = 0.25;
        ungetch(movemode);
    }else if(key == '2'){//speedRatio 0.50
        speedRatio = 0.50;
        ungetch(movemode);
    }else if(key == '3'){//speedRatio 0.75
        speedRatio = 0.75;
        ungetch(movemode);
    }else if(key == '4'){//speedRatio 1
        speedRatio = 1;
        ungetch(movemode);
    }else{
        printf("\nInvalid Input!\n");
    }
}

/* disconnect from NXT */
nxt.disconnect(); 
