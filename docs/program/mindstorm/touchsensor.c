/************************************************************
touchsensor.c
Vehicle moving forward demo
By Wai Hong Tsang

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the NXT Mindstorm to use
the touch sensor.
*************************************************************/
#include <conio.h>
#include <ch_nxt.h>
#include <unistd.h>

int main(){
    struct nxt_remote nxtr;
    
    //Connect to NXT
    if (!nxt_connect(&nxtr)){
        return(0);
    }
    
    //Set sensor types
    int status;
    status = nxt_setsensor(PORT_1, TOUCH, BOOLEANMODE);
    if (status == 0){
        return(0);
    }
    
    //Define the variables
    int  speed = 25;	//the speed of the motors. (default to 25)
    
    //Move Robot Forward
    nxt_motor(PORT_B, speed, RUN_IDLE);
    nxt_motor(PORT_C, speed, RUN_IDLE);
    
    //Commands:
    while(1){
        //Get touch sensor data
        nxt_getsensor(PORT_1);
        //If touch sensor is triggered
        if (nxtr.NXT_sensorvalraw[PORT_1] < 500){
            //Move backward
            nxt_motor(PORT_B, -speed, RUN_IDLE);
            nxt_motor(PORT_C, -speed, RUN_IDLE);
            sleep(5);
            //Quit the while loop
            break;
        }
    }

    //Stop the motors
    nxt_motor(PORT_B, 0, OFF_IDLE);
    nxt_motor(PORT_C, 0, OFF_IDLE);
    
    //Disconnect NXT
    nxt_disconnect();
    return 0;
}
