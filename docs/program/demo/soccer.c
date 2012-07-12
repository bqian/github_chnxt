/************************************************************
soccer.c
Vehicle moving forward demo
By Wai Hong Tsang

The purpose of this demo is to demonstrate the CH Mindstorms
Control Package's ability to control the NXT Mindstorm to
play soccer.
*************************************************************/
#include <windows.h>
#include <conio.h>
#include <ch_nxt.h>

int main(){
    struct nxt_remote nxtr;
        
    //Connect to NXT
    if (!nxt_connect(&nxtr)){
        return(0);
    }
    
    //Define the variables
    int  speed = 25;	//the speed of the motors. (default to 25)
    char key = 'x';     // 'x' = stop
    char movemode = 'x';// save last move setting
    int quit = 0;       // not equal to 1
    int count = 0;
    //Greaphical User Interface
    printf("Vehicle Direction:  Other Commands:");
    printf("\n    [w]             [x] Stop Motors");
    printf("\n [q] ^ [e]          [p] Exit Program");
    printf("\n    \\|/             [1] Set Speed to 25");
    printf("\n[a]<-|->[d]         [2] Set Speed +10");
    printf("\n     v              [3] Set Speed -10");
    printf("\n    [s]             [t] Shovel forward");
    printf("\n                    [y] Shovel backward");
    printf("\n                    [u] Shovel engage\n");
    //Commands:
    while (quit !=1){
        key = _getch();
        switch(key){
            case 'w': //forward
                nxt_motor(PORT_B, speed, RUN_IDLE);
                nxt_motor(PORT_C, speed, RUN_IDLE);
                movemode = 'w';
                break;
            case 's': //backward
                nxt_motor(PORT_B, -speed, RUN_IDLE);
                nxt_motor(PORT_C, -speed, RUN_IDLE);
                movemode = 's';
                break;
            case 'q': //left forward
                nxt_motor(PORT_B, speed, RUN_IDLE);
                nxt_motor(PORT_C, 0.5*speed, RUN_IDLE);
                movemode = 'q';
                break;
            case 'e':
                nxt_motor(PORT_B, 0.5*speed, RUN_IDLE);
                nxt_motor(PORT_C, speed, RUN_IDLE);
                movemode = 'q';
                break;
            case '1': //speed = 10
                speed = 25;
                ungetch(movemode);
                break;
            case '2': //speed = 10
                speed += 10;
                ungetch(movemode);
                break;
            case '3': //speed = 10
                speed -= 10;
                ungetch(movemode);
                break;
            case 'p': //quit
                printf("program is terminated\n");
                quit = 1;
                break;
            case 'x': //stop all motors
                nxt_motor(PORT_A, 0, OFF_IDLE);
                nxt_motor(PORT_B, 0, OFF_IDLE);
                nxt_motor(PORT_C, 0, OFF_IDLE);
                movemode = 'x';
                break;
            case 't': // move shovel
                nxt_motor(PORT_A, 100, RUN_IDLE);
                Sleep(150);
                nxt_motor(PORT_A, 0, OFF_IDLE);
                ungetch(movemode);
                break;
            case 'y': // reverse shovel
                nxt_motor(PORT_A, -100, RUN_IDLE);
                Sleep(150);
                nxt_motor(PORT_A, 0, OFF_IDLE);
                ungetch(movemode);
                break;
            case 'u': // engage shovel
                nxt_motor(PORT_A, 100, RUN_IDLE);
                Sleep(300);
                nxt_motor(PORT_A, 0, OFF_IDLE);
                Sleep(50);
                nxt_motor(PORT_A, -100, RUN_IDLE);
                Sleep(250);
                nxt_motor(PORT_A, 0, OFF_IDLE);
                ungetch(movemode);
                break;
            case 'a': // turn 90 left
                nxt_motor(PORT_B, 50, RUN_IDLE);
                nxt_motor(PORT_C, -50, RUN_IDLE);
                Sleep(200);
                ungetch(movemode);
                break;
            case 'd': // turn 90 right
                nxt_motor(PORT_B, -50, RUN_IDLE);
                nxt_motor(PORT_C, 50, RUN_IDLE);
                Sleep(200);
                ungetch(movemode);
                break;                  
        }
    }
    
    //Stop the motors
    nxt_motor(PORT_A, 0, OFF_IDLE);
    nxt_motor(PORT_B, 0, OFF_IDLE);
    nxt_motor(PORT_C, 0, OFF_IDLE);
    
    //Disconnect NXT
    nxt_disconnect();
    return 0;
}
