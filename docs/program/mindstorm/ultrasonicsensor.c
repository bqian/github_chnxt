/************************************************************
ultrasonicsensor.c
Vehicle moving forward controlled by ultra sonic sensor demo
By Wai Hong Tsang

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the NXT Mindstorm to use
the ultra sonic sensor.
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
    status = nxt_setsensor(PORT_4, ULTRASONIC, RAWMODE);
    if (status == 0){
        return(0);
    }
    
    //Define the variables
    int  speed = 25;	//the speed of the motors. (default to 25)
    
    //Commands:
    while(1){
        //Get ultrasonic sensor data
        nxt_getsensor(PORT_4);
        //If obstacle is really close
        if (nxtr.NXT_sensorvalraw[PORT_4] < 20){
            speed = 25;
            //Move backward
            nxt_motor(PORT_B, -speed, RUN_IDLE);
            nxt_motor(PORT_C, -speed, RUN_IDLE);
            sleep(3);
            //Quit the while loop
            break;
        }
        //Else if the obstacle is close
        else if(nxtr.NXT_sensorvalraw[PORT_4] < 60){
            speed = 25;
        }
        //Else if the obstacle is not close
        else if(nxtr.NXT_sensorvalraw[PORT_4] < 100){
            speed = 50;
        }
        //Else if there is no obstacle in sight
        else if(nxtr.NXT_sensorvalraw[PORT_4] < 200){
            speed = 75;
        }
        //Sensor value larger than 200
        else{
            speed = 75;
        }
        //Move forward (constantly)
        nxt_motor(PORT_B, speed, RUN_IDLE);
        nxt_motor(PORT_C, speed, RUN_IDLE);
    }

    //Stop the motors
    nxt_motor(PORT_B, 0, OFF_IDLE);
    nxt_motor(PORT_C, 0, OFF_IDLE);
    
    //Disconnect NXT
    nxt_disconnect();
    return 0;
}
