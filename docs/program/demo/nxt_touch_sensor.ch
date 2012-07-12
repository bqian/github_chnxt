#include <windows.h>
#include <conio.h>
#include <ch_nxt.h>
#include <unistd.h>

//Define the variables
int  speed = 25;	//the speed of the motors. (default to 25)
int data1;

//Connect to NXT
struct nxt_remote nxtr;
if (!nxt_connect(&nxtr)) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(0);
}

//connect to sensor
int status1;
status1 = nxt_setsensor(PORT_1, TOUCH, BOOLEANMODE);
if ( status1 == 0 ) {
    exit(0);
}

//Commands:
//stop motor
nxt_motor(PORT_B, 0, OFF_IDLE);
nxt_motor(PORT_C, 0, OFF_IDLE);
while (1) {
    nxt_getsensor(PORT_1);
    data1 = nxtr.NXT_sensorvalraw[PORT_1];
    if (data1 < 500) {
        nxt_motor(PORT_B, speed, RUN_IDLE);
        nxt_motor(PORT_C, speed, RUN_IDLE);
        Sleep(1000);
        break;
    }
}

//Stop the motors
nxt_motor(PORT_B, 0, OFF_IDLE);
nxt_motor(PORT_C, 0, OFF_IDLE);

//Disconnect NXT
nxt_disconnect();
