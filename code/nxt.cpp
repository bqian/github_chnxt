/*****************************************************************
 * nxt.cpp
 * Functions for NXT control.
 * By Binsen Qian
 *
 * Modified from ch_nxt.c
 * By Joshua Galbraith and Harry H. Cheng
 *
 * This is the source code for the CH Lego mindstorms NXT Control
 * package. Function prototypes are located in the file nxt.h.
 ****************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "nxt.h"
#include "nxt_internal.h"

#ifndef _WIN32
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
#include <signal.h>
#else
#include <windows.h>
#include <shlobj.h>
#endif

#ifdef _CH_
#include <stdarg.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

//#define MAX_PATH 512

#if 0
int bt_connect(SOCKET *sock, SOCKADDR_BTH *sa, char btAddress[18], int channel)
{
    int saLen = sizeof(*sa);
    int status = -1;
    int tries = 0;

    /*
    // convert bth address to machine readable
    sa->addressFamily = AF_BTH;
    if (SOCKET_ERROR == WSAStringToAddress((LPWSTR)btAddress,
            AF_BTH, NULL, (LPSOCKADDR) sa, &saLen)) {
        printf("error\n");
       // ExitProcess(2);
	return -3;
    }
//    strToba(btAddress, (bdaddr_t*)&sa->btAddr);
    sa->port = channel; // default port

    // connect
    printf("Connecting...");
    while (status < 0) {
        status = connect(*sock,
                (LPSOCKADDR) sa, (DWORD) saLen);
//        status = connect(*sock,
 //               (const struct sockaddr *) sa, sizeof(*sa));
        if (tries++ > 3) {
            // return -1 if fail to connect
            printf("fail to connect.\n");
            return -1;
        }
    }
    printf("connected.\n");
    // return 0 if connected
    */
    return 0;
} // bt_connect()
#endif

int NXT_init(br_comms_t* comms)
{
    int i;
#ifndef __MACH__
    memset(&comms->addr, 0, sizeof(sockaddr_t));
#endif
    comms->connected = 0;
#ifdef _WIN32
    WSADATA wsd;
    if(WSAStartup (MAKEWORD(2,2), &wsd) != 0) {
        printf("WSAStartup failed with error %d\n", WSAGetLastError());
    }
#endif
    /*
       for(i = 0; i < 4; i++) {
       comms->jointSpeeds[i] = DEF_MOTOR_SPEED;
       comms->recordingInProgress[i] = 0;
//Set the default maximum speed to something reasonable
comms->maxSpeed[i] = DEF_MOTOR_MAXSPEED;
}
THREAD_CREATE(&comms->thread, nullThread, NULL);
comms->commsLock = (MUTEX_T*)malloc(sizeof(MUTEX_T));
MUTEX_INIT(comms->commsLock);
comms->motionInProgress = 0;
MUTEX_NEW(comms->recvBuf_lock);
MUTEX_INIT(comms->recvBuf_lock);
COND_NEW(comms->recvBuf_cond);
COND_INIT(comms->recvBuf_cond);
comms->recvBuf_ready = 0;
MUTEX_NEW(comms->commsBusy_lock);
MUTEX_INIT(comms->commsBusy_lock);
COND_NEW(comms->commsBusy_cond);
COND_INIT(comms->commsBusy_cond);
comms->commsBusy = 0;
MUTEX_NEW(comms->callback_lock);
MUTEX_INIT(comms->callback_lock);
comms->callbackEnabled = 0;
*/
return 0;
}

const char* NXT_getConfigFilePath(void)
{
    static char path[512];
    /* Find the configuration file path */
#ifdef _WIN32
    /* Find the user's local appdata directory */
    if(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path) != S_OK) 
    {
        /* Could not get the user's app data directory */
    } else {
        //MessageBox((LPCTSTR)path, (LPCTSTR)"Test");
        //fprintf(fp, "%s", path); 
    }
    strcat(path, "\\nxt.config");
#else
    /* Try to open the barobo configuration file. */
#define MAX_PATH 512
    strcpy(path, getenv("HOME"));
    strcat(path, "/.nxt.config");
#endif
    return path;
}

int NXT_connectWithAddress(br_comms_t* comms, const char* address, int channel)
{
    int err = -1;
#ifndef __MACH__
    int status;
    int flags;
    char buf[256];
#ifndef _WIN32
    comms->socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
#else
    comms->socket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
#endif

#ifdef _WIN32
    if(comms->socket == INVALID_SOCKET) {
        err = WSAGetLastError();
        printf("Could not bind to socket. Error %d\n", err);
        if(err == 10047) {
            fprintf(stderr, "A bluetooth device could not be found on this computer. You may need to attach\nan external Bluetooth dongle to continue.\n");
            return -5;
        } else {
            return -1;
        }
    }
#endif

    // set the connection parameters (who to connect to)
#ifndef _WIN32
    comms->addr.rc_family = AF_BLUETOOTH;
    comms->addr.rc_channel = (uint8_t) channel;
    strToba( address, &comms->addr.rc_bdaddr );
#else
    comms->addr.addressFamily = AF_BTH;
    strToba( address, (bdaddr_t*)&comms->addr.btAddr);
    comms->addr.port = channel;
#endif

    // connect to server
    status = -1;
    int tries = 0;
    while(status < 0) {
        if(tries > 2) {
            break;
        }
        status = connect(comms->socket, (const struct sockaddr *)&comms->addr, sizeof(comms->addr));
        if(status == 0) {
            comms->connected = 1;
        } 
        tries++;
    }
    if(status < 0) {
#ifndef _WIN32
        perror("Error connecting.");
#else
        LPVOID lpMsgBuf;
        FormatMessage( 
                FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                FORMAT_MESSAGE_FROM_SYSTEM | 
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &lpMsgBuf,
                0,
                NULL 
                );
        // Process any inserts in lpMsgBuf.
        // ...
        // Display the string.
        //MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
        fprintf(stderr, "Error Connecting: %s", lpMsgBuf);
        int wsaerror = WSAGetLastError();
        if(wsaerror == 10048) {
            fprintf(stderr, "Make sure there are no other programs currently connected to the Mobot.\n");
        } else if (wsaerror == 10047 || wsaerror == 10050) {
            fprintf(stderr, "A bluetooth device could not be found on this computer. You may need to attach\nan external Bluetooth dongle to continue.\n");
            err = -5;
        }
        // Free the buffer.
        LocalFree( lpMsgBuf );
#endif
        return err;
    }
    /* Make the socket non-blocking */
    //flags = fcntl(comms->socket, F_GETFL, 0);
    //fcntl(comms->socket, F_SETFL, flags | O_NONBLOCK);
    /* Wait for the MoBot to get ready */
    //sleep(1);
    //  status = finishConnect(comms);
    return status;
#else
    fprintf(stderr, "ERROR: connectWithAddress() is currently unavailable on the Mac platform.\n");
    return -1;
#endif
}

void baSwap(bdaddr_t *dst, const bdaddr_t *src)
{
    register unsigned char *d = (unsigned char *) dst;
    register const unsigned char *s = (const unsigned char *) src;
    register int i;

    for (i = 0; i < 6; i++)
        d[i] = s[5-i];
}

int strToba(const char *str, bdaddr_t *ba)
{
    UINT8 b[6];
    const char *ptr = str;
    int i;

    for (i = 0; i < 6; i++) {
        b[i] = (UINT8) strtol(ptr, NULL, 16);
        if (i != 5 && !(ptr = strchr(ptr, ':')))
            ptr = ":00:00:00:00:00";
        ptr++;
    }

    baSwap(ba, (bdaddr_t *) b);

    return 0;
}

int SendToNXT(br_comms_t* comms, const char str[], int datasize)
{
    int err = 0;
    if(comms->connected == 1) {
#ifdef _WIN32
        err = send(comms->socket, (const char*)str, datasize, 0);
#else
        err = write(comms->socket, str, datasize);
#endif
    } else if (comms->connected == 2) {
#ifdef _WIN32
        DWORD bytes;
        if(!WriteFile(comms->hSerial, str, datasize, &bytes, NULL)) {
            err = -1;
        }
#else
        err = -1;
#endif
    } else {
        err = -1;
    }
    if(err < 0) {
        return err;
    } else {
        return 0;
    }
}


ChNXT::ChNXT() {
    NXT_init(&_comms);
    int i;
	/*
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int saLen = sizeof(sa);

    connected = 0; // 0 if not connected
    for(i = 0; i < 3; i++){
	runDirection[i] = 1;
	iRunState[i] = 0;
    }
    // initialize windows socket
    if (WSAStartup(wVersionRequested, &wsaData) != NO_ERROR) {
        fprintf(stderr, "Error initializaing window sockets!\n");
        ExitProcess(2);
    }
    // get windows socket
    sock = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (sock == INVALID_SOCKET) {
        error = WSAGetLastError();
        printf("could not bind to socket. Error: %d\n", error);
        ExitProcess(2);
    } */
    // initialize default speeds
    for(i = 0; i<3; i++){
	jointSpeedRatio[i] = 0.25;
        jointSpeed[i] = jointSpeedRatio[i]*100;
    }
} // ChNXT::ChNXT()

ChNXT::~ChNXT() {
    // if the user foget to disconnect
    if (connected == 1)
        disconnect();
} // ChNXT::~ChNXT()

int ChNXT::connect(void) 
{
    /* Function Name: ChNXT::connect()
     * This function is going to connect with NXT
     * and it will get the bluetooth address from
     * the configuration file somewhere.
     *
     * Created by Binsen Qian */
    char path[MAX_PATH];
    FILE *stream;
#ifdef _WIN32
    // int saLen = sizeof(sa);

    // connect only if not connected
    //if (connected == 0) {
    /* get configuration file path in Windows */
    if(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path) != S_OK) 
    {
        //Could not get the user's app data directory
    } else {
        //MessageBox((LPCTSTR)path, (LPCTSTR)"Test");
        //fprintf(fp, "%s", path); 
    }
    /* cat the configuration file at the end of the path */
    strcat(path, "\\nxt.config");
    /* This part is to display the path on the screen
    printf("%s\n", path);
    Sleep(2000);*/
    /* Modified by Binsen Qian, old version of getting path
       if ((stream = fopen(path, "r")) == NULL) 
       {
        printf("Cannot open configuration file.\n");
       }*/
    // open the configuration file to get bth address
    stream = fopen(path, "r");
    if(stream == NULL) {
        /* The file doesn't exist. Gotta make the file */
        fprintf(stderr, 
                "ERROR: Your Ch NXT configuration file does not exist.\n"
                "Please create one by opening the NXT remote control, clicking on\n"
                "the 'Robot' menu entry, and selecting 'Configure Robot Bluetooth'.\n");
        return -1;
    }
    /*
       fgets(btAddress, 18, stream);
       */
    if(fgets(btAddress, 18, stream) == NULL) {
        return -4;
    }
    fclose(stream);
#else
    /* Mach or Linux */
#endif

    /* after getting the Bluetooth Address, try to connect to the NXT */
    // if (bt_connect(&sock, &sa, btAddress, 1) == 0) {
    if (NXT_connectWithAddress(&_comms, btAddress, 1) == 0) {
        connected = 1;
        return 0;
    } else {
        // return 1 if fail to connect
        return 1;
    }
    //}
} // ChNXT::connect()

int ChNXT::connectWithAddress(char usr_address[18], int channel) {
    // connect only if not connected
    if (connected == 0) {
        // copy bth address from user's input
        strcpy(btAddress, usr_address);
//        if (bt_connect(&sock, &sa, btAddress, channel) == 0) 
        if(NXT_connectWithAddress(&_comms, btAddress, 1) == 0){
            connected = 1;
            return 0;
        } else {
            // return 1 if fail to connected
            return 1;
        }
    }
    return 0;
} // ChNXT::connectWithAddress()

int ChNXT::disconnect(void) {
    int i;
    // stop motors
    stopAllJoints();
    // stop sensors
    for (i = 0; i < 4; i++)
        setSensor((nxtSensorId_t)i, 
                NXT_SENSORTYPE_NOSENSOR, NXT_SENSORMODE_RAWMODE);
    connected = 0;
    return closesocket(_comms.socket);
} // ChNXT::disconnect()

/* functions for nxt motors */
int ChNXT::setJointSpeed(nxtJointId_t joint, int speed){
    if(speed < 0 || speed >100){
        printf("Invalid speed.\n");
        return -1;
    }
    jointSpeed[joint] = speed;
    return 0;
} // ChNXT::setJointSpeed()

int ChNXT::setJointSpeeds(int speed1, int speed2, int speed3){
    setJointSpeed(NXT_JOINT1, speed1);
    setJointSpeed(NXT_JOINT2, speed2);
    setJointSpeed(NXT_JOINT3, speed3);
    return 0;
} // ChNXT::setJointSpeeds()

int ChNXT::setJointSpeedRatio(nxtJointId_t id, double ratio){
    if(ratio < 0 || ratio >1)
    {
//        printf("Invalid speed ratio.\n");
        return -1;
    }

    jointSpeedRatio[id] = ratio;
    jointSpeed[id] = jointSpeedRatio[id] * 100;

    return 0;
} // ChNXT::setJointSpeedRatio()

int ChNXT::setJointSpeedRatios(double ratio1, double ratio2,
        double ratio3){
    setJointSpeedRatio(NXT_JOINT1, ratio1);
    setJointSpeedRatio(NXT_JOINT2, ratio2);
    setJointSpeedRatio(NXT_JOINT3, ratio3);
    return 0;
} // ChNXT::setJointSpeedRatios()

int ChNXT::setJointRelativeZero(nxtJointId_t id){
    /**********************************************
    Resets the motor tachometer counters to zero on
    all the of the motors connected to the NXT.
    Returns 1 if sucessfull, 0 if fail
    ***********************************************/
    int i, rec;
    sendMsg[0] = 0x04;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x80;
    sendMsg[3] = 0x0A;
    sendMsg[4] = (unsigned char) id;
    sendMsg[5] = TRUE; // 1: relative; 0: absolute
    rec = sendMessage(6);
    
    Sleep(60);
    if (!rec) {
        printf("Fail to reset joint%d.\n", id+1);
        return 0;
    }
    return 1;
} // ChNXT::setJointRelativeZero()

int ChNXT::setJointZero(nxtJointId_t id){
    /**********************************************
    Resets the motor tachometer counters to zero on
    all the of the motors connected to the NXT.
    Returns 1 if sucessfull, 0 if fail
    ***********************************************/
    int i, rec;
    sendMsg[0] = 0x04;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x80;
    sendMsg[3] = 0x0A;
    sendMsg[4] = (unsigned char) id;
    sendMsg[5] = 0; // 1: relative; 0: absolute
    rec = sendMessage(6);
    
    Sleep(60);
    if (!rec) {
        printf("Fail to reset joint%d.\n", id+1);
        return 0;
    }
    return 1;
} // ChNXT::setJointZero()

int ChNXT::setJointRelativeZeros(void){
    setJointRelativeZero(NXT_JOINT1);
    setJointRelativeZero(NXT_JOINT2);
    setJointRelativeZero(NXT_JOINT3);
    return 0;
} // ChNXT::setJointRelativeZeros()

int ChNXT::setJointZeros(void){
    setJointZero(NXT_JOINT1);
    setJointZero(NXT_JOINT2);
    setJointZero(NXT_JOINT3);
    return 0;
} // ChNXT::setJointZeros()

int ChNXT::resetToZeros(void){
    setJointZero(NXT_JOINT1);
    setJointZero(NXT_JOINT2);
    setJointZero(NXT_JOINT3);
    return 0;
} // ChNXT::resetToZeros()

int ChNXT::moveJointContinuousNB(nxtJointId_t    id, 
                                 nxtJointState_t dir){
    /* set initial motor output */
    unsigned char mode = 0x01 | 0x04;
    unsigned char runstate = 0x00;
    unsigned char regulationmode = 0x00;
    int res;
    if(dir > 0){
	    runDirection[id] = 1;
    }else if(dir < 0){
	    runDirection[id] = -1;
    }else{
	    printf("Invalid direction.\n");
    }
    mode = 0x01 | 0x02 | 0x04;
    regulationmode = REM_MOTOR_SPEED;
    runstate = RS_RUNNING;
    //13 bytes follow (0x0c)
    sendMsg[0] = 0x0C;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x80;	//no response please
    sendMsg[3] = 0x04;	//SETOUTPUTSTATE
    sendMsg[4] = (unsigned char)id; //port number 0, 1, 2
    sendMsg[5] = (unsigned char) runDirection[id]*jointSpeed[id];
    sendMsg[6] = mode;
    sendMsg[7] = regulationmode;
    sendMsg[8] = 0x00;		//turnratio;
    sendMsg[9] = runstate;
    sendMsg[10] = 0;
    sendMsg[11] = 0;
    sendMsg[12] = 0;
    sendMsg[13] = 0;
    res = sendMessage(14);
//    res = SendToNXT(&_comms, sendMsg, 14);
    if (res == 0)
        return 1; //make sure response lenght is not zero
    return 0;
} // ChNXT::moveJointContinuousNB()

int ChNXT::moveJointNB(nxtJointId_t id, double angle) {
    /******************************************
    sets the motor output for NXT
    returns 1 if sucessfull, 0 if fail
    port: (motor connection to NXT)
        port_A..........0
        port_B..........1
        port_C..........2
    speed: (value between -100 and 100)
        -100 is fullspeed Counter Clockwise
         100 is full speed Clockwise
           0 is no speed
    degrees:
        number of degrees that motor will turn
        from current position.
    ******************************************/
#if 0
    double currentPosition;
    double targetPosition;
    double currentSpeedRatio;
    double offset = 1.0;
    int count = 0;
	
    getJointSpeedRatio(id, currentSpeedRatio);
    getJointAngle(id, currentPosition);
    targetPosition = currentPosition + angle;

    do{
        /* if current angle is really near to the target, slow down the speed */
        if(abs(currentPosition - targetPosition) < 10.0){
            setJointSpeedRatio(id, 0.01);
        } else if (abs(currentPosition - targetPosition) < 20.0){
            setJointSpeedRatio(id, currentSpeedRatio*0.1);
        }

        /* if current angle is grater than target, move backward,
         * if current angle is less than target, move forward,
         * else stop the motor */
        if(currentPosition > targetPosition + offset){
            moveJointContinuousNB(id, NXT_BACKWARD);
        }else if(currentPosition < targetPosition - offset){
            moveJointContinuousNB(id, NXT_FORWARD);
        }else{
            stopOneJoint(id);
            count++;
        }

        /* get current posstion for comparasion */
        getJointAngle(id, currentPosition);
        Sleep(100);
    } while((currentPosition > targetPosition + offset) 
            || (currentPosition < targetPosition - offset)
            || (count < 5));
    /* to stop joint */
    stopOneJoint(id);
    /* set the joint speed back to origin speed ratio */
    setJointSpeedRatio(id, currentSpeedRatio);
#endif
//#if 0
    int res, i;
    int degrees;
    unsigned char runMode = RM_MOTORON | RM_BRAKE | RM_REGULATED;
    unsigned char regulationMode = REM_MOTOR_SPEED;
    unsigned char runState = RS_RUNNING;
    if(angle < 0){
        angle = -angle;
        runDirection[id] = -1;
    } else {
        runDirection[id] = 1;
    }
//    angle -= angle*0.14;
    degrees = (int)angle;
    /*
    //set initial motor output
    int addDeg[4];
    int moveTo[4] = {0, 0, 0, 0};
    int degreeTemp;
    //printf("%d\n", moveTo[0]);
    addDeg[3] = (int)(degrees / (256 * 256 * 256));
    degreeTemp = degrees % (256 * 256 * 256);
    addDeg[2] = (int)(degreeTemp / (256 * 256));
    degreeTemp = degreeTemp % (256 * 256);
    addDeg[1] = (int)(degreeTemp / (256));
    degreeTemp = degreeTemp % (256);
    addDeg[0] = (int)(degreeTemp);

    for (i = 0; i < 3; i++)
        moveTo[i] = addDeg[i];
    */
    sendMsg[0] = 0x0c;  //12 bytes follow (0x0c)
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x80;	//no response please
    sendMsg[3] = 0x04;	//SETOUTPUTSTATE
    sendMsg[4] = (unsigned char)id; //port number 0..2
    sendMsg[5] = (unsigned char)runDirection[id] * jointSpeed[id];
//    sendMsg[6] = 0x01 | 0x20 | 0x04; //mode
    sendMsg[6] = runMode; //mode
    sendMsg[7] = regulationMode;
    sendMsg[8] = 100;		//turnratio
    sendMsg[9] = runState;		//runstate
    //unsigned long tacholimit
    sendMsg[10] = (unsigned int)degrees;
    sendMsg[11] = (unsigned int)degrees >> 8;
    sendMsg[12] = (unsigned int)degrees >> 16;
    sendMsg[13] = (unsigned int)degrees >> 24;
    /*
    sendMsg[10] = (unsigned char)moveTo[0];
    sendMsg[11] = (unsigned char)moveTo[1];
    sendMsg[12] = (unsigned char)moveTo[2];
    sendMsg[13] = (unsigned char)moveTo[3];
    */
    sendMsg[14] = 0x00;
    res = sendMessage(14);
    if (res == 0)
        return 0; //make sure response lenght is not zero
    return 1;
//#endif
	return 0;
}// ChNXT::moveJointNB()

int ChNXT::moveJoint(nxtJointId_t id, double angle){
    moveJointNB(id, angle);

    return moveJointWait(id);
} // ChNXT::moveJoint()

int ChNXT::moveJointToNB(nxtJointId_t id, double angle){
    int degrees;
    double currentPosition;
    double targetPosition = angle;
    double currentSpeedRatio;
    double speed;
    int count = 0;
    double offset = 1.0;
#if 0
    getJointSpeedRatio(id, currentSpeedRatio);
    do{
        getJointAngle(id, currentPosition);
        if(abs(currentPosition - targetPosition) < 10.0){
            setJointSpeedRatio(id, 0.01);
        } else if (abs(currentPosition - targetPosition) < 20.0){
            setJointSpeedRatio(id, currentSpeedRatio*0.1);
        } else if (abs(currentPosition - targetPosition) < 40.0){
            setJointSpeedRatio(id, currentSpeedRatio*0.2);
        } else if (abs(currentPosition - targetPosition) < 80.0){
            setJointSpeedRatio(id, currentSpeedRatio*0.3);
        } 
        /*
           else {
           setJointSpeedRatio(id, currentSpeedRatio);
           }
        */
        if(currentPosition > targetPosition + offset){
            moveJointContinuousNB(id, NXT_BACKWARD);
        }else if(currentPosition < targetPosition - offset){
            moveJointContinuousNB(id, NXT_FORWARD);
        }else {
            count++;
            stopOneJoint(id);
            //            setJointSpeedRatio(id, 0);
        }

        getJointAngle(id, currentPosition);
    } while(((currentPosition > targetPosition + offset) 
		|| (currentPosition < targetPosition - offset)) 
		|| count < 5);

    stopOneJoint(id);
	setJointSpeedRatio(id, currentSpeedRatio);
#endif
    
    getOutputState(id);
    if(iRotationCount[id] > (int)angle){
        degrees = -(iRotationCount[id] - (int)angle);
        moveJointNB(id, degrees);
    }else if(iRotationCount[id] < angle){
	degrees = angle - iRotationCount[id];
        moveJointNB(id, (double)degrees);
    }else{
	degrees = 0;
    }

    return 0;
} // ChNXT::moveJointToNB()

int ChNXT::moveJointTo(nxtJointId_t id, double angle){
    moveJointToNB(id, angle);

    return moveJointWait(id);
} //ChNXT::moveJointTo()

int ChNXT::moveContinuousNB(nxtJointState_t dir1,
	nxtJointState_t dir2, nxtJointState_t dir3){
    moveJointContinuousNB(NXT_JOINT1, dir1);
    moveJointContinuousNB(NXT_JOINT2, dir2);
    moveJointContinuousNB(NXT_JOINT3, dir3);
    return 0;
} // ChNXT::moveContinuousNB()

int ChNXT::moveContinuousTime(nxtJointState_t dir1,
	nxtJointState_t dir2, nxtJointState_t dir3, double seconds){
    moveJointContinuousNB(NXT_JOINT1, dir1);
    moveJointContinuousNB(NXT_JOINT2, dir2);
    moveJointContinuousNB(NXT_JOINT3, dir3);
    Sleep(seconds * 1000);
    stopAllJoints();
    return 0;
} // ChNXT::moveContinuousTime()

int ChNXT::moveTo(double angle1, double angle2, double angle3){
    moveJointToNB(NXT_JOINT1, angle1);
    moveJointToNB(NXT_JOINT2, angle2);
    moveJointToNB(NXT_JOINT3, angle3);

    return moveWait();
} // ChNXT::moveTo();

int ChNXT::move(double angle1, double angle2, double angle3){
    moveJointNB(NXT_JOINT1, angle1);
    moveJointNB(NXT_JOINT2, angle2);
    moveJointNB(NXT_JOINT3, angle3);

    return moveWait();
} // ChNXT::move();

int ChNXT::moveNB(double angle1, double angle2, double angle3){
    moveJointNB(NXT_JOINT1, angle1);
    moveJointNB(NXT_JOINT2, angle2);
    moveJointNB(NXT_JOINT3, angle3);

    return 0;
} // ChNXT::moveNB();

int ChNXT::moveToNB(double angle1, double angle2, double angle3){
    moveJointToNB(NXT_JOINT1, angle1);
    moveJointToNB(NXT_JOINT2, angle2);
    moveJointToNB(NXT_JOINT3, angle3);

    return 0;
} // ChNXT::moveToNB();

int ChNXT::moveToZero(void){
    moveToNB(0, 0, 0);
    return moveWait();
} //ChNXT::moveToZero()
 
int ChNXT::moveToZeroNB(void){
    moveToNB(0, 0, 0);
    return 0;
} //ChNXT::moveToZeroNB()

int ChNXT::stopOneJoint(nxtJointId_t id){
//    unsigned char mode = 0x01 | 0x02 | 0x04;
    unsigned char mode = RM_MOTORON | RM_BRAKE | RM_REGULATED;
//    unsigned char regulationmode = 0x01;
	unsigned char regulationmode = REM_MOTOR_SPEED;
    unsigned char turnratio = 0;
//    unsigned char runstate = 0x20;
//    unsigned char runstate = RS_IDLE;
    unsigned char runstate = RS_RUNNING;
    unsigned int tacholimit = 0;
    int res;
    //13 bytes follow (0x0c)
    sendMsg[0] = 0x0C;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x80;	//no response please
    sendMsg[3] = 0x04;	//SETOUTPUTSTATE
    sendMsg[4] = (unsigned char)id; //port number 0, 1, 2
    sendMsg[5] = 0x00;
    sendMsg[6] = mode;
    sendMsg[7] = regulationmode;
    sendMsg[8] = 0x00;		//turnratio;
    sendMsg[9] = runstate;
    sendMsg[10] = 0;
    sendMsg[11] = 0;
    sendMsg[12] = 0;
    sendMsg[13] = 0;
    res = sendMessage(14);
    if (res == 0)
        return 1; //make sure response lenght is not zero
    return 0;
} //ChNXT::stopOneJoint()

int ChNXT::stopTwoJoints(nxtJointId_t id1, nxtJointId_t id2){
    stopOneJoint(id1);
    stopOneJoint(id2);
    return 0;
} // ChNXT::stopTwoJoints()

int ChNXT::stopAllJoints(void){
    stopOneJoint(NXT_JOINT1);
    stopOneJoint(NXT_JOINT2);
    stopOneJoint(NXT_JOINT3);
    return 0;
} // ChNXT::stopAllJoints()

int ChNXT::getJointAngle(nxtJointId_t id, double &angle){
//int ChNXT::getJointAngle(nxtJointId_t id, int &angle){
    getOutputState(id);
//    angle = (double)iRotationCount[id];
    angle = iRotationCount[id];
    return 0;
} // ChNXT::getJointAngle()

int ChNXT::getJointSpeedRatio(nxtJointId_t id, double &ratio){
    ratio = jointSpeedRatio[id];
    return 0;
} // ChNXT::getJointSpeedRatio()

int ChNXT::getJointSpeedRatios(double &ratio1, double &ratio2,
        double &ratio3){
    ratio1 = jointSpeedRatio[1];
    ratio2 = jointSpeedRatio[2];
    ratio3 = jointSpeedRatio[3];
    return 0;
} // ChNXT::getJointSpeedRatios()

int ChNXT::getJointState(nxtJointId_t id, int &status){
    isJointMoving(id);
    if(iRunState == 0)
        status = 0;
    else
        status = 1;
    return 0;
} // ChNXT::getJointState()
/*
double ChNXT::getJointPosition(nxtJointId_t id){
    getTacho(id);
    return motorPosCum[id];
} //ChNXT::getJointPosition()
*/

int ChNXT::isConnected(void){
    return connected;
} //ChNXT::isConnected()

int ChNXT::isJointMoving(nxtJointId_t id){
    getOutputState(id);
    Sleep(100);
    return iRunState[id];
} //ChNXT::isJointMoving()

int ChNXT::isMoving(){
    int i;
    for(i = 0; i<3; i++){
        isJointMoving((nxtJointId_t)i);
        if(iRunState[i] == 1)
            return 1;
    }
    return 0;
} //ChNXT::isMoving()

int ChNXT::moveJointWait(nxtJointId_t id){
    while(isJointMoving(id) != 0){
        Sleep(200);
    }
    return 0;
} // ChNXT::moveJointWait()

int ChNXT::moveWait(){
    int i;
    for(i = 0; i<3; i++){
	if(moveJointWait((nxtJointId_t)i))
	    return -1;
    }
    return 0;
} // ChNXT::moveWait()

int ChNXT::setSensor(nxtSensorId_t id, 
        nxtSensorType_t type, nxtSensorMode_t mode) {
    if (id > 3) {
        printf("Invalid port number: %d\n", id);
        return 1; //only ports 0..3
    }
    sensorOn[id] = 1; // 1 means sensor on
    sensorType[id] = type;
    sensorMode[id] = mode;
    if (!updateInputTypeMode(id))
        return 1;
    if (!initInput(id))
        return 1;
    return 0;
} // ChNXT::setSensor()

int ChNXT::getSensor(nxtSensorId_t id, int &value) {
    if (id > 3) {
        printf("Invalid port number: %d\n", id);
        return 1; //only ports 0..3
    }
    value = pollInput(id);
    /*
    if ( value < 0){
        value = 0;
        return 1;
    } else {
        return 0;
    }
    */
    return 0;
} // ChNXT::getSensor()

int ChNXT::printMess(){
    int j;
    printf("\n last sent:\nlength: %d", sendMsg[0]);
    for(j=1;j<(int)(sendMsg[0])+2;j++) 
        printf(" %x", sendMsg[j]);
    printf("\n");
    printf("\n last received:\nlength: %d", recvMsg[0]);
    for(j=1;j<(int)(recvMsg[0])+2;j++) 
        printf(" %x", recvMsg[j]);
    printf("\n");
    return(1);
}// ChNXT::printMess

int ChNXT::playTone(int freq, int duration){
    sendMsg[0] =0x04;
    sendMsg[1] =0x00;
    sendMsg[2] =0x80;
    sendMsg[3] =0x03;
    sendMsg[4] =freq;
    sendMsg[5] =duration;
    return sendMessage(6);
} //ChNXT::playTone()
/*
int ChNXT::getTacho(int port){
	int res;
	double new_pos;
	double old_pos;
	double change=0.0;
	unsigned int max = 4294967295;	
	sendMsg[0] =0x03;
	sendMsg[1] =0x00;
	sendMsg[2] =0x00;
	sendMsg[3] =0x06;
	sendMsg[4] =port;
	res= sendMessage(5);
	if (res==0)
		return 0;
	
	Sleep(20);
	res = recvMessage(25+2);
	if ((res==0) ||(recvMsg[2]!=0x02)||(recvMsg[3] != 0x06))
		return 0;
	
	new_pos = ((int) recvMsg[15])+((int)recvMsg[16])*256+((int)recvMsg[17])*256*265+((int)recvMsg[18])*256*256*256;
	old_pos = motorPosRaw[port];
	
	//if new<old && big jump
	if ((new_pos<old_pos) && ((old_pos-new_pos)>4000000000)){
		change= max-old_pos+new_pos;
	}
	//else if position<old
	else if (new_pos<old_pos){
		change=-1*(old_pos-new_pos);
	}
	//else if new>old && big jump
	else if ((new_pos>old_pos) && ((new_pos-old_pos)>4000000000)){
		change=-1*(old_pos+max-new_pos);
	}
	//else if new>old
	else if (new_pos>old_pos){
		change= new_pos-old_pos;
	}

	motorPosCum[port]= motorPosCum[port] + change;
	motorPosRaw[port]= new_pos;

	return 1;
} // ChNXT::getTacho()
*/
int ChNXT::vehicleRollForwardNB(double angle){
    if(angle < 0)
        angle = -angle;
    moveJointNB(NXT_JOINT2, angle);
    moveJointNB(NXT_JOINT3, angle);
    return 0;
} // ChNXT::vehicleRollForwardNB()

int ChNXT::vehicleRollForward(double angle){
    if(angle < 0)
        angle = -angle;
    moveJointNB(NXT_JOINT2, angle);
    moveJointNB(NXT_JOINT3, angle);
    return vehicleMotionWait();
} // ChNXT::vehicleRollForward()

int ChNXT::vehicleRollBackwardNB(double angle){
    if(angle < 0)
        angle = -angle;
    moveJointNB(NXT_JOINT2, -angle);
    moveJointNB(NXT_JOINT3, -angle);
    return 0;
} // ChNXT::vehicleRollBackwardNB()

int ChNXT::vehicleRollBackward(double angle){
    if(angle < 0)
        angle = -angle;
    moveJointNB(NXT_JOINT2, -angle);
    moveJointNB(NXT_JOINT3, -angle);
    return vehicleMotionWait();
} // ChNXT::vehicleRollBackward()

int ChNXT::vehicleRotateLeftNB(double angle){
    if(angle < 0)
        angle = -angle;
    moveJointNB(NXT_JOINT2, angle);
    moveJointNB(NXT_JOINT3, -angle);
    return 0;
} // ChNXT::vehicleRotateLeftNB()

int ChNXT::vehicleRotateLeft(double angle){
    if(angle < 0)
        angle = -angle;
    moveJointNB(NXT_JOINT2, angle);
    moveJointNB(NXT_JOINT3, -angle);
    return vehicleMotionWait();
} // ChNXT::vehicleRotateLeft()

int ChNXT::vehicleRotateRightNB(double angle){
    if(angle < 0){
        angle = -angle;
    }

    moveJointNB(NXT_JOINT2, -angle);
    moveJointNB(NXT_JOINT3, angle);
    return 0;
}

int ChNXT::vehicleRotateRight(double angle)
{
    /* check if the input angle is negative */
    if(angle < 0){
        angle = -angle;
    }

    moveJointNB(NXT_JOINT2, -angle);
    moveJointNB(NXT_JOINT3, angle);

    return vehicleMotionWait();
}

int ChNXT::vehicleMotionWait(void){
    moveJointWait(NXT_JOINT2);
    moveJointWait(NXT_JOINT3);
    return 0;
}

int ChNXT::humanoidWalkForward(double angle)
{
    /* Function Name: ChNXT::humanoidWalkForward()
     *
     * Description: This function is to move the NXT 
     * forward block as the humanoid configuration. */

    /* to make sure angle is positive */
    angle = angle>0?angle:-angle;

    moveNB(angle, angle, angle);

    return humanoidMotionWait();
} 

int ChNXT::humanoidWalkBackward(double angle)
{
    /* Function Name: ChNXT::humanoidWalkBackward()
     *
     * Description: This function is to move the NXT 
     * backward block as the humanoid configuration. */

    /* to make sure angle is positive */
    angle = angle>0?angle:-angle;

    moveNB(-angle, -angle, -angle);

    return humanoidMotionWait();
}

int ChNXT::humanoidWalkForwardNB(double angle)
{
    /* Function Name: ChNXT::humanoidWalkForward()
     *
     * Description: This function is to move the NXT 
     * forward non-block as the humanoid configuration. */

    /* to make sure angle is positive */
    angle = angle>0?angle:-angle;

    moveNB(angle, angle, angle);

    return 0;
}

int ChNXT::humanoidWalkBackwardNB(double angle)
{
    /* Function Name: ChNXT::humanoidWalkBackwardNB()
     *
     * Description: This function is to move the NXT 
     * backward non-block as the humanoid configuration. */

    /* to make sure angle is positive */
    angle = angle>0?angle:-angle;

    moveNB(-angle, -angle, -angle);

    return 0;
}

int ChNXT::humanoidMotionWait(void)
{
    /* Function Name: humanoidMotionWait()
     * 
     * Description: This function is to wait the NXT
     * until it stops moving */

    moveJointWait(NXT_JOINT1);
    moveJointWait(NXT_JOINT2);
    moveJointWait(NXT_JOINT3);

    return 0;
}

int ChNXT::motionMoveForward(void){
    moveJointContinuousNB(NXT_JOINT2, NXT_FORWARD);
    moveJointContinuousNB(NXT_JOINT3, NXT_FORWARD);
    return 0;
} // ChNXT::motionMoveForward()

int ChNXT::motionMoveBackward(void){
    moveJointContinuousNB(NXT_JOINT2, NXT_BACKWARD);
    moveJointContinuousNB(NXT_JOINT3, NXT_BACKWARD);
    return 0;
} // ChNXT::motionMoveBackward()

int ChNXT::motionRotateLeft(void){
    moveJointContinuousNB(NXT_JOINT2, NXT_FORWARD);
    moveJointContinuousNB(NXT_JOINT3, NXT_BACKWARD);
    return 0;
} // ChNXT::motionRotateLeft()

int ChNXT::motionRotateRight(void){
    moveJointContinuousNB(NXT_JOINT2, NXT_BACKWARD);
    moveJointContinuousNB(NXT_JOINT3, NXT_FORWARD);
    return 0;
} // ChNXT::motionRotateRight()

int ChNXT::motionTurnLeft(void){
    jointSpeed[NXT_JOINT3] = 0.7*jointSpeed[NXT_JOINT2];
    moveJointContinuousNB(NXT_JOINT2, NXT_FORWARD);
    moveJointContinuousNB(NXT_JOINT3, NXT_FORWARD);
    return 0;
} // ChNXT::motionTurnLeft()

int ChNXT::motionTurnRight(void){
    jointSpeed[NXT_JOINT2] = 0.7*jointSpeed[NXT_JOINT3];
    moveJointContinuousNB(NXT_JOINT2, NXT_FORWARD);
    moveJointContinuousNB(NXT_JOINT3, NXT_FORWARD);
    return 0;
} // ChNXT::motionTurnRight()

int ChNXT::stopMotion(void){
    stopOneJoint(NXT_JOINT2);
    stopOneJoint(NXT_JOINT3);
    return 0;
} // ChNXT::motionTurnRight()

/* internal functions */
int ChNXT::sendMessage(int length) {
    error = send(_comms.socket, (const char*) sendMsg, length, 0);
    if (error == 0){
        printf("failure sending!\n");
        return 0;
    }
    return 1;
} // ChNXT::sendMessage()

int ChNXT::recvMessage(int length) {
    error = recv(_comms.socket, (char *)recvMsg, length, 0);
    if (error == 0) {
        printf("connection broken or no more charactors\n");
    }
    return error;
} // ChNXT::recvMessage()
/*
int ChNXT::setOutputState(nxtJointId_t id, unsigned char mode,
        unsigned char regulationMode, char turnRatio,
        unsigned char runState, unsigned int tachoLimit, int reply){
    int res, i;
    int addDeg[4];
    int moveTo[4] = {0, 0, 0, 0};
    int degreeTemp;
    tachoLimit = tachoLimit - 2;
    //printf("%d\n", moveTo[0]);
    addDeg[3] = (int)(tachoLimit / (256 * 256 * 256));
    degreeTemp = tachoLimit % (256 * 256 * 256);
    addDeg[2] = (int)(degreeTemp / (256 * 256));
    degreeTemp = degreeTemp % (256 * 256);
    addDeg[1] = (int)(degreeTemp / (256));
    degreeTemp = degreeTemp % (256);
    addDeg[0] = (int)(degreeTemp);

    for (i = 0; i < 3; i++)
        moveTo[i] = addDeg[i];

    sendMsg[0] = 0x0C;//13 bytes follow without first two tyes
    sendMsg[1] = 0x00;
    if(reply){
        sendMsg[2] = 0x00;
    }else{
        sendMsg[2] = 0x80;  //no response required
    }
    sendMsg[3] = 0x04;	    //SETOUTPUTSTATE
    sendMsg[4] = id;        //port number 0, 1, 2
    sendMsg[5] = runDirection[id] * jointSpeed[id];
    sendMsg[6] = mode;
    sendMsg[7] = regulationMode;
    sendMsg[8] = turnRatio; //turnratio
    sendMsg[9] = runState;
    //unsigned long tacholimit: 0: run forever
    sendMsg[10] = (unsigned char)moveTo[0];
    sendMsg[11] = (unsigned char)moveTo[1];
    sendMsg[12] = (unsigned char)moveTo[2];
    sendMsg[13] = (unsigned char)moveTo[3];
    sendMsg[14] = 0;
    res = sendMessage(15);

    if (res == 0)
        return 1;   //make sure response lenght is not zero
    return 0;
} // ChNXT::setOutputState()
*/
int ChNXT::getOutputState(nxtJointId_t id){
    int res;
    sendMsg[0] =0x03;
    sendMsg[1] =0x00;
    sendMsg[2] =0x00;
    sendMsg[3] =0x06;
    sendMsg[4] = (unsigned char) id;
    res= sendMessage(5);
    if (res==0)
	return 0;

    Sleep(20);
    res = recvMessage(27);
    if ((res==0) ||(recvMsg[2]!=0x02)||(recvMsg[3] != 0x06))
	return 0;
    
    iRunState[id] = recvMsg[10];
    iTachoLimit[id] = (0xFF & recvMsg[11]) | ((0xFF & recvMsg[12]) << 8)| ((0xFF & recvMsg[13]) << 16)| ((0xFF & recvMsg[14]) << 24);
    iTachoCount[id] = (0xFF & recvMsg[15]) | ((0xFF & recvMsg[16]) << 8)| ((0xFF & recvMsg[17]) << 16)| ((0xFF & recvMsg[18]) << 24);
    iBlockCount[id] = (0xFF & recvMsg[19]) | ((0xFF & recvMsg[20]) << 8)| ((0xFF & recvMsg[21]) << 16)| ((0xFF & recvMsg[22]) << 24);
    iRotationCount[id] = (0xFF & recvMsg[23]) | ((0xFF & recvMsg[24]) << 8)| ((0xFF & recvMsg[25]) << 16)| ((0xFF & recvMsg[26]) << 24);
    return 0;
} // ChNXT::getOutputState()

int ChNXT::pollInput(nxtSensorId_t id) {
    /****************************************************
     * returns 0 if communication failed and 1 if success
     * (NXT_error might still be set even then)
     * communication with NXT needs to be successfully
     * initiated BEFORE calling this routine!
     ***************************************************/
    int res;
    //special care for the ultrasound sensor
    if (i_sensorType[id] == 0x0B) {
        //if (nxt_usr->NXT_sensorvalraw[id]==0)
        return getUltrasonic(id);
        //else NXT_getultrasonicvaluefast(id);
    } else {
        sendMsg[0] = 3; //three bytes follow
        sendMsg[1] = 0;
        sendMsg[2] = 0x00; //request response
        sendMsg[3] = 0x07; //GETINPUTVALUES
        sendMsg[4] = id; //from port 0 (1 on the brick)
        if (!sendMessage(5)) {
            error = -1; //communication error
            return 0;
        }
        Sleep(60); //wait 60ms for response
        res = recvMessage(16 + 2);
        if ((res == 18) && (recvMsg[2] == 0x02) && (recvMsg[3] == 0x07)) {   //correct return message received
            if (recvMsg[4] != 0) {
                /* error */
                error = recvMsg[4];
            } else { 
                /* no error */
                if (recvMsg[5] == id) { //correct input
                    /* read current sensor type back */
                    i_sensorType[id] = recvMsg[8];
                    /* read current sensor mode back */
                    i_sensorMode[id] = recvMsg[9];
                    if (recvMsg[6] == 1) { //new data is valid
                        sensorValRaw[id] = (int)recvMsg[10] + ((int)recvMsg[11] << 8);
//                        raw_AD_value=((0xff & answer[10]) | (answer[11] << 8));
                        sensorValNorm[id] = (int)recvMsg[12] + ((int)recvMsg[13] << 8);
//                        sensorValScaled[id] = (int)((short)((int)recvMsg[12] || ((int)recvMsg[13] << 8)));
                        sensorValScaled[id] = ((0xff & recvMsg[14]) | (recvMsg[15] << 8));
                        sensorValCalib[id] = (int)((short)((int)recvMsg[14] || ((int)recvMsg[15] << 8)));
                    }
                }
            }
        } else {
            return 0;
        }
        if((i_sensorType[id] == NXT_SENSORTYPE_SOUND_DB)
        || (i_sensorType[id] == NXT_SENSORTYPE_SOUND_DBA)
        || (i_sensorType[id] == NXT_SENSORTYPE_LIGHT_ACTIVE)
		|| (i_sensorType[id] == NXT_SENSORTYPE_LIGHT_INACTIVE)
		|| (i_sensorType[id] == NXT_SENSORTYPE_TOUCH))
		{
            return sensorValScaled[id];
        } else {
            return sensorValRaw[id];
        }
    }
//    return 1;
} // ChNXT::pollInput()

int ChNXT::updateInputTypeMode(nxtSensorId_t id) {
    /*************************************************
     * sets current sensor type and sensor mode
     * of specified input to specified values use
     * NXT_pollinput to read these values back, to
     * see if the NXT accepted them returns 0 if
     * failed and 1 if success. Communication with
     * NXT needs to be successfully initiated BEFORE
     * calling this routine!
     *************************************************/
    int ret;

    //was ultrasonic, de-init
    if (i_sensorType[id] == 0x0B) {
        ret = stopUltrasonic(id);
        if (ret == 0)
            return 0; //return if de-init failed
    }
    // set sensor type and mode
    if (sensorType[id] == 0x0B) {
        // set ultrasonic
        ret = setUltrasonic(id);
    } else { // set other sensors
        sendMsg[0] = 0x05; //five bytes follow
        sendMsg[1] = 0x00;
        sendMsg[2] = 0x80; //no response
        sendMsg[3] = 0x05;
        sendMsg[4] = id;
        sendMsg[5] = sensorType[id];
        sendMsg[6] = sensorMode[id];
        ret = sendMessage(7);
    }
    i_sensorType[id] = sensorType[id];
    i_sensorMode[id] = sensorMode[id];
    return ret;
} // ChNXT::updateInputTypeMode()

int ChNXT::initInput(nxtSensorId_t id) {
    /**********************************************
     * returns 0 if communication failed and
     * returns 1 if success (NXT_error might
     * still be set even then). Communication
     * with NXT needs to be successfully initiated
     * BEFORE calling this routine!
     **********************************************/
    int res;
    sendMsg[0] = 3;      //three bytes follow
    sendMsg[1] = 0;
    sendMsg[2] = 0x00;    //request response
    sendMsg[3] = 0x07;    //GETINPUTVALUES
    sendMsg[4] = id; //from port passed in through id
    if (!sendMessage(5)) {
        error = -1; //communication error
        return 0;
    }
    Sleep(60); //wait 60ms for response
    res = recvMessage(16 + 2);
    if ((res == 18) && (recvMsg[2] == 0x02) && (recvMsg[3] == 0x07)) {
        //correct return message received
        if (recvMsg[4] != 0) { //error
            error = recvMsg[4];
        } else { //received 'no error'
            if (recvMsg[5] == id) { //correct input
                sensorType[id] = recvMsg[8];
                //read current sensor type back
                i_sensorType[id] = recvMsg[8];
                sensorMode[id] = recvMsg[9];
                //read current sensor mode back
                i_sensorMode[id] = recvMsg[9];
                if (recvMsg[6] == 1) { //new data is valid
                    sensorValRaw[id] = (int)recvMsg[10] + ((int)recvMsg[11] << 8);
                    sensorValNorm[id] = (int)recvMsg[12] + ((int)recvMsg[13] << 8);
                    sensorValScaled[id] = (int)((short)((int)recvMsg[12] || ((int)recvMsg[13] << 8)));
                    sensorValCalib[id] = (int)((short)((int)recvMsg[14] || ((int)recvMsg[15] << 8)));
                }
            }
        }
    } else {
        return 0;
    }
    return 1;
} // ChNXT::initInput()

int ChNXT::setUltrasonic(nxtSensorId_t id) {
    /*************************************
     * special initialization routine for
     * the ultrasonic sensor
     *************************************/
    int res;

    //set sensor to "digital" mode
    sendMsg[0] = 0x05; //five bytes follow
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; // response requested
    sendMsg[3] = 0x05; //setinputmode
    sendMsg[4] = id;
    sendMsg[5] = 0x0b; //lowspeed_9v type
    sendMsg[6] = 0x00; //rawmode mode
    res = sendMessage(7);
    if (res == 0)
        return 0;
    Sleep(60);

    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0))
        return 0;
    Sleep(20); //Sleep(50);

    //configure sensor: 00 02 41 02 via lswrite
    sendMsg[0] = 0x08;
    //message length without first two bytes
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; //0x80; //no response please
    sendMsg[3] = 0x0F; //LS Write
    sendMsg[4] = id; //port number 0..3
    sendMsg[5] = 0x03; //Tx Data length
    sendMsg[6] = 0x00; //Rx Data length (no reply expected)
    //Data: "set sensor to send sonar pings continuously"
    sendMsg[7] = 0x02; // sonar address
    sendMsg[8] = 0x41;
    sendMsg[9] = 0x02;

    res = sendMessage(10);
    if (res == 0)
        return 0;
    //Sleep(50);
    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0))
        return 0;
    return 1;
} // ChNXT::setUltrasonic()

int ChNXT::stopUltrasonic(nxtSensorId_t id) {
    /*******************************************************
     * stops and de-initializes the ultrasonic sensor
     * at the given input returns 0 if failed, 1 if success
     *******************************************************/
    int res;
    sendMsg[0] = 0x08; //message length without first two bytes
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; //0x80; //no response please
    sendMsg[3] = 0x0F; //LS Write
    sendMsg[4] = id; //port number 0..3
    sendMsg[5] = 0x03; //Tx Data length
    sendMsg[6] = 0x00; //Rx Data length (no reply expected)
    sendMsg[7] = 0x02; //Data: "set sensor to off"
    sendMsg[8] = 0x41;
    sendMsg[9] = 0x00;
    res = sendMessage(10);
    if (res == 0)
        return 0;
    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0))
        return 0;
    return 1;
} //ChNXT::stopUltrasonic()

int ChNXT::getUltrasonic(nxtSensorId_t id) {
    /********************************************
     * attempts to read an ultrasonic
     * measurement value from an ultrasonic
     * sensor returns 0 if failed, 1 if success
     ********************************************/
    int res;
//    int i;
    //NXT_sensorvalraw[id]=-10;
    //check for pending reply bytes in the NXT buffers:
    //send 'read bytes', retrieve garbage reply bytes.
    //LSRead out all remaining data
    sendMsg[0] = 0x03; //message length without first two bytes
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; //response please
    sendMsg[3] = 0x10; //LSRead
    sendMsg[4] = id; //port number 0..3
    res = sendMessage(5);
    if (res == 0) {
        sensorValRaw[id] = -2;
        return(0);
    }
    Sleep(60);
    res = recvMessage(20 + 2);
    if ((res != 22) || (recvMsg[4] != 0)) {
        sensorValRaw[id] = -3;
        return(0);
    }
    Sleep(60);

    //send 0x01 0x02 0x42, to retrieve 0x01 bytes
    //from read a continuous measurement distance (0x42)
    //from address 0x02
    sendMsg[0] = 0x07; //message length without first two bytes
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; //0x80; //no response please (to LS write)
    sendMsg[3] = 0x0F; //LSWrite
    sendMsg[4] = id; //port number 0..3
    sendMsg[5] = 0x02; //Tx Data length (two bytes sent - 02 42)
    sendMsg[6] = 0x01; //Rx Data length (1 byte reply expected)
    sendMsg[7] = 0x02; //address for "read sonar"
    sendMsg[8] = 0x42; //read distance
    res = sendMessage(9);
    if (res == 0) {
        sensorValRaw[id] = -4;
        return 0;
    }

    Sleep(60);

    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0)) {
        sensorValRaw[id] = -5;
        return 0;
    }

    Sleep(50);

    //check status of I2C message channel until idle,
    //timeout or error
    //LSGetStatus: 0x00 0x0E port;
    //return: 0x02 0x0E statusbyte nrofbytesready
    //statusbyte: 0 success, else error
    sendMsg[0] = 0x03; //message length without first two bytes
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; //response please
    sendMsg[3] = 0x0E; //LSGetStatus
    sendMsg[4] = id; //port number 0..3
    res = sendMessage(5);

    if (res == 0) {
        sensorValRaw[id] = -6;
        return 0;
    }

    Sleep(50);

    //if 'idle', send "read 1 I2C reply byte" and read response
    res = recvMessage(4 + 2);
    if (res != 6) {
        sensorValRaw[id] = -7;
        return 0;
    }

    if ((recvMsg[4] == 0) && (recvMsg[5] > 0)) {
        //status OK and bytes available for reading?
        //message length without first two bytes
        sendMsg[0] = 0x03;
        sendMsg[1] = 0x00;
        sendMsg[2] = 0x00; //response please
        sendMsg[3] = 0x10; //LSRead
        sendMsg[4] = id; //port number 0..3
        res = sendMessage(5);

        Sleep(50);

        res = recvMessage(20 + 2);
        sensorValRaw[id] = recvMsg[6];
        if( sensorValRaw[id] < 0 ){
            sensorValRaw[id] = 80;
        }
        return sensorValRaw[id];
    }
    sensorValRaw[id] = -8;
    return 0;
} // ChNXT::getUltrasonic()

int ChNXT::test(void) {
//    int i;
//    int res;
    /*
    getOutputState(NXT_JOINT2);
    printf("isMoving = %d\n", iRunState[NXT_JOINT2]);
    printf("tacholimit = %d\n", iTachoLimit[NXT_JOINT2]);
    printf("tachocount = %d\n", iTachoCount[NXT_JOINT2]);
    printf("blockcount = %d\n", iBlockCount[NXT_JOINT2]);
    printf("rotationcount = %d\n", iRotationCount[NXT_JOINT2]);
    */
    double currentPosition;
    double targetPosition = 360.0;
    double offset = 1.0;
    getJointAngle(NXT_JOINT1, currentPosition);
    do{
        if(abs(currentPosition - targetPosition) < 30){
            setJointSpeedRatio(NXT_JOINT1, 0.01);
        }

        if(currentPosition > targetPosition + offset){
            moveJointContinuousNB(NXT_JOINT1, NXT_BACKWARD);
        }else if(currentPosition < targetPosition - offset){
            moveJointContinuousNB(NXT_JOINT1, NXT_FORWARD);
        }

        getJointAngle(NXT_JOINT1, currentPosition);
    } while((currentPosition > targetPosition + offset) || (currentPosition < targetPosition - offset));
    stopOneJoint(NXT_JOINT1);
    getJointAngle(NXT_JOINT1, currentPosition);
    printf("target angle = %lf, current angle = %lf\n",
            targetPosition, currentPosition);
//    setOutputState(NXT_JOINT3, MOTORON | BRAKE | REGULATED, 0x01, 0x00, 0x20, 720, 0);
    return 0;
} // ChNXT::test()
