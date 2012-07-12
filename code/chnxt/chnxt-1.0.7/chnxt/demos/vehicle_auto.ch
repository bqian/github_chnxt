/************************************************************
vehicle_auto.ch
Vehicle Robot Automatically Run Demo
By Joshua Galbraith and Harry H. Cheng
Modified by Binsen Qian, June 2012

The purpose of this demo is to demonstrate the CH Mindstorms 
Control Package's ability to control the machine robot model,
As well as demonstrate how to get and use sensor data.
*************************************************************/ 
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <nxt.h>

int main() {
    ChNXT nxt;
    int  speed = 25,	//sets the speed for the motors. Default is 25
         status1 = 2,	//used to check for errors
         status2 = 2;	//used to check for errors
    int ultraValue, touchValue;
    char key = 'x',		//stores user input
         movemode = 'x';//stores last movement command

    /* connect with Lego mindstorm */
    nxt.connect();
    
    /* 
     * Set sensor types.
     * Set port 1 as touch sensor.
     * Set port 4 as ultrasonic sensor.
     */
    status1 = nxt.setSensor(PORT_1, TOUCH, BOOLEANMODE);
    status2 = nxt.setSensor(PORT_4, 0x0B, RAWMODE);
    if ((status1 == 0) || (status2 == 0)) {
        printf("\nError initializing sensors.\nPress any key to exit.\n");
        return(0);
    }

    while (1) {
        /* check user input 'q' to quit */
        if (kbhit()) {
            if (getch() == 'q') {
                printf("\nExiting...");
                break;
            }
        }
        /*
         * get touch sensor.
         * If pressed reverse and turn left.
         */
        touchValue = nxt.getSensor(PORT_1);
        if(touchValue < 0){
            nxt.backward(25);
            Sleep(500);
            nxt.stop();
            Sleep(500);
            nxt.rotateLeft(50);
        }
        /* 
         * get distance from UltraSonic sensor,
         * set speed according to distance.
         * Turn right if really close.
         */
        ultraValue = nxt.getSensor(PORT_4);
        if (ultraValue < 25) {
            nxt.backward(25);
            Sleep(500);
            nxt.stop();
            Sleep(500);
            nxt.rotateRight(50);
            speed = 0;
            Sleep(500);
        } else if (ultraValue < 50)
            speed = 25;
        else if (ultraValue < 75)
            speed = 50;
        else if (ultraValue < 100)
            speed = 75;
        else if (ultraValue < 200)
            speed = 100;
        else
            speed = 50;
        /* 
         * Turn motors on (drive forward)
         */
        nxt.forward(speed);
    }
    /*
     * stop interfacing. 
     * Disconnect from Lego Mindstorms.
     * This also stops the motors.
     */
    nxt.disconnect();
    printf("exited.\n");
    return 0;
}
