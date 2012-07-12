#include <windows.h>
#include <conio.h>
#include <ch_nxt.h>
#include <unistd.h>

//Define the variables
int  speed = 25;	//the speed of the motors. (default to 25)
int data2;

//Connect to NXT
struct nxt_remote nxtr;
if (!nxt_connect(&nxtr)) {
    printf("Error: Cannot connect to Lego Mindstorm NXT.\n");
    exit(0);
}

//connect to sensor
int status1;
status1 = nxt_setsensor(PORT_4, ULTRASONIC, RAWMODE);
if ( status1 == 0 ) {
    exit(0);
}

//Commands:
//stop motor
nxt_motor(PORT_B, 0, OFF_IDLE);
nxt_motor(PORT_C, 0, OFF_IDLE);

//Commands:
while (1) {
    nxt_getsensor(PORT_4);
    data2 = nxtr.NXT_sensorvalraw[PORT_4];
    if (data2 < 20) {
        speed = 25;
        nxt_motor(PORT_B, -speed, RUN_IDLE);
        nxt_motor(PORT_C, -speed, RUN_IDLE);
        Sleep(1000);
        break;
    }
    else if (data2 < 100) {
        speed = 50;
    }
    else {
        speed = 75;
    }
    nxt_motor(PORT_B, speed, RUN_BRAKE);
    nxt_motor(PORT_C, speed, RUN_BRAKE);
}

//Stop the motors
nxt_motor(PORT_B, 0, OFF_IDLE);
nxt_motor(PORT_C, 0, OFF_IDLE);

//Disconnect NXT
nxt_disconnect();

