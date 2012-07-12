/************************************************************
vehicle_rtc.ch
Vehicle Robot Real Time Control Demo
By Joshua Galbraith and Harry H. Cheng
Modified by Binsen Qian, June, 2012

The purpose of this demo is to demonstrate the CH Mindstorms 
Control Package's ability to control the machine robot model,
As well as demonstrate how to get and use sensor data.
*************************************************************/ 
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <nxt.h>

int main(){
	ChNXT nxt;
	int  speed=25,	//the speed that the motors will rotate at. (default to 25)
		 quit = 0,	//used by quit case to exit the loop
		 status1,	//used to check for errors
		 status2;	//used to check for errors
	char key='x',	//stores the input from the user
		 movemode='x';//stores the last movement command

    /* connect with Lego mindstorm */
    nxt.connectWithAddress("00:16:53:02:35:b3");

    /* 
     * Set sensor types.
     * Set port 1 as touch sensor.
     * Set port 4 as ultrasonic sensor.
     */
	status1=nxt.setSensor(PORT_1,TOUCH,BOOLEANMODE);
	status2=nxt.setSensor(PORT_4,0x0b,RAWMODE);
	if((status1==0)||(status2==0)){
		printf("\nError initializing sensors.\nPress any key to exit.\n");
		while (!_kbhit()); //wait for key press
		return(0);
	}

	/* Display Graphic User's Interface */
	printf("Vehicle Direction:  Other Commands:");
	printf("\n    [w]               [x] Stop Motors");
	printf("\n [q] ^ [e]            [r] Exit Program");
	printf("\n    \\|/               [1] Set Speed to 25");
	printf("\n[a]<-|->[d]           [2] Set Speed to 50");
	printf("\n     v                [3] Set Speed to 75");
	printf("\n    [s]               [4] Set Speed to 100\n");
	printf("Please Enter command:");
	
	/*
     * Control loop. 
     * Interprets user command and does action.
     */
	while(quit !=1 ) {
		key=_getch();
		switch(key){
			case 'w': //up
				nxt.motor(PORT_B, speed, RUN_IDLE);
				nxt.motor(PORT_C, speed, RUN_IDLE);
				movemode='w';
				break;
			case 's': //down
				nxt.motor(PORT_B, -speed, RUN_IDLE);
				nxt.motor(PORT_C, -speed, RUN_IDLE);
				movemode='s';
				break;
			case 'd': //right
				nxt.motor(PORT_B, -speed, RUN_IDLE);
				nxt.motor(PORT_C, speed, RUN_IDLE);
				movemode='d';
				break;
			case 'a': //left
				nxt.motor(PORT_B, speed, RUN_IDLE);
				nxt.motor(PORT_C, -speed, RUN_IDLE);
				movemode='a';
				break;
			case 'q': //forward-left
				nxt.motor(PORT_B, speed, RUN_IDLE);
				nxt.motor(PORT_C, speed*0.6, RUN_IDLE);
				movemode='q';
				break;
			case 'e': //forward-right
				nxt.motor(PORT_B, speed*0.6, RUN_IDLE);
				nxt.motor(PORT_C, speed, RUN_IDLE);
				movemode='e';
				break;
			case 'x': //stop
				nxt.motor(PORT_B, 0, OFF_IDLE);
				nxt.motor(PORT_C, 0, OFF_IDLE);
				movemode='x';
				break;
			case 'r': //quit
				printf("\nExiting program.\n");
				quit = 1;
				break;
			case '1': //speed 20
				speed = 25;
				ungetch(movemode);
				break;
			case '2': //speed 30
				speed = 50;
				_ungetch(movemode);
				break;
			case '3': //speed 40
				speed = 75;
				ungetch(movemode);
				break;
			case '4': //speed 40
				speed = 100;
				ungetch(movemode);
				break;
			default:
				printf("\nInvalid Input!\n");
		}//switch(key)
	}
    /*
     * stop interfacing. 
     * Disconnect from Lego Mindstorms.
     * This also stops the motors.
     */
	nxt.disconnect();
    printf("Press any key to exit.\n");
    while (!_kbhit()); //wait for key press   
	return 0;
}
