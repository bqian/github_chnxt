/************************************************************
forward.c
Vehicle moving forward demo
By Wai Hong Tsang

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the NXT Mindstorm to move
forward a few seconds and then stop.
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
    
    //Define the variables
    int  speed = 25;	//the speed of the motors. (default to 25)
    
    //Commands:
    //Move forward
    nxt_motor(PORT_B, speed, RUN_IDLE);
    nxt_motor(PORT_C, speed, RUN_IDLE);
    //Pause program for a while
    sleep(5);
    
    //Stop the motors
    nxt_motor(PORT_B, 0, OFF_IDLE);
    nxt_motor(PORT_C, 0, OFF_IDLE);
    
    //Disconnect NXT
    nxt_disconnect();
    return 0;
}
