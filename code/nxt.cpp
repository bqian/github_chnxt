/*****************************************************************
 * nxt.cpp
 * Functions for NXT control.
 * By Binsen Qian and Michael Schirle
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

int NXT_init(br_comms_t* comms)
{
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

    return 0;
}

const char* NXT_getConfigFilePath(void) {
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
    /* Try to open the nxt configuration file. */
#define MAX_PATH 512
    strcpy(path, getenv("HOME"));
    strcat(path, "/.nxt.config");
#endif
    return path;
}

int NXT_connectWithAddress(
        br_comms_t* comms, 
        const char* address, 
        int channel
        ){
    int err = -1;
    int flags;

    NXT_buildSocket(comms);
#ifdef _WIN32
    if(comms->socket == INVALID_SOCKET) {
        return PrintSocketBuildError();
    }
#endif

    NXT_setConnectionParameters(comms, address, channel);
    int connectionStatus = NXT_connectToServer(comms);
    if(connectionStatus < 0) {
        return PrintConnectionError();
    }

    return connectionStatus;
}

int NXT_buildSocket(br_comms_t *comms){
#ifndef _WIN32
    comms->socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
#else
    comms->socket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
#endif
    return 0;
}

int PrintSocketBuildError(void){
    int err = WSAGetLastError();
    if(err == 10047) {
        fprintf(stderr, "A bluetooth device could not be found on this computer.\n"
                "You may need to attach an external Bluetooth dongle to continue.\n");
        return -5;
    } else {
        return -1;
    }
}

int NXT_setConnectionParameters(
        br_comms_t *comms,
        const char *address,
        int channel
        ){
#ifndef _WIN32
    comms->addr.rc_family = AF_BLUETOOTH;
    comms->addr.rc_channel = (uint8_t) channel;
    strToba( address, &comms->addr.rc_bdaddr );
#else
    comms->addr.addressFamily = AF_BTH;
    strToba( address, (bdaddr_t*)&comms->addr.btAddr);
    comms->addr.port = channel;
#endif
    return 0;
}

int NXT_connectToServer(br_comms_t *comms){
    int status = -1;
    int tries = 0;
    while(status < 0) {
        if(tries > 2) {
            break;
        }
        status = connect(
                comms->socket, 
                (const struct sockaddr *)&comms->addr, 
                sizeof(comms->addr)
                );
        if(status == 0) {
            comms->connected = 1;
        } 
        tries++;
    }
    return status;
}

int PrintConnectionError(void){
    int err = -1;
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
    fprintf(stderr, "Error Connecting: %s", lpMsgBuf);
    int wsaerror = WSAGetLastError();
    if(wsaerror == 10048) {
        fprintf(stderr, "Make sure there are no other programs currently"
                "connected to the Mobot.\n");
    } else if (wsaerror == 10047 || wsaerror == 10050) {
        fprintf(stderr, "A bluetooth device could not be found on this computer.\n"
                "You may need to attach an external Bluetooth dongle to continue.\n");
        err = -5;
    }
    LocalFree( lpMsgBuf );
#endif
    return err;
}

void baSwap(bdaddr_t *dst, const bdaddr_t *src)
{
    register unsigned char *d = (unsigned char *) dst;
    register const unsigned char *s = (const unsigned char *) src;
    register int i;

    for (i = 0; i < 6; i++)
        d[i] = s[5-i];
}

int strToba(const char *str, bdaddr_t *ba){
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

int SendToNXT(br_comms_t* comms, const char str[], int datasize){
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
	int i;
    NXT_init(&_comms);
    /* initialize default speeds */
    for(i = 0; i<3; i++){
	motorSpeedRatio[i] = 0.25;
        motorSpeed[i] = motorSpeedRatio[i]*100;
    }
	
}

ChNXT::~ChNXT() {
    // if the user foget to disconnect
	//Message that turns off Motor Control Program
	//Bluetooth specific Bits
    sendMsg[0] = 0x02;      //Message Length LSB
    sendMsg[1] = 0x00;		//Message Length MSB
    
    //NXT Direct command for Stop Program
    sendMsg[2] = (unsigned char) 0x80;
    sendMsg[3] = 0x01;
	
	sendMessage(4);
	
    if (connected == 1)
        disconnect();
}

int ChNXT::connect(void) {
	int i;
    /* after getting the Bluetooth Address, try to connect to the NXT */
    getBluetoothAddress();
    
    if (NXT_connectWithAddress(&_comms, btAddress, 1) == 0) {
        connected = 1;
    } else {
        return 1;
    }
	
	//start the motor control program
	   //Bluetooth specific Bits
    sendMsg[0] = 0x15;      //Message Length LSB
    sendMsg[1] = 0x00;		//Message Length MSB
    
    //NXT Direct command for Start Program
    sendMsg[2] = (unsigned char) 0x80;
    sendMsg[3] = 0x00;
    
    //Program Name plus null character
    sendMsg[4] = 'M';
    sendMsg[5] = 'o';
    sendMsg[6] = 't';
    sendMsg[7] = 'o';
    sendMsg[8] = 'r';
    sendMsg[9] = 'C';
    sendMsg[10] = 'o';
    sendMsg[11] = 'n';
    sendMsg[12] = 't'; 
	sendMsg[13] = 'r';
	sendMsg[14] = 'o';
	sendMsg[15] = 'l';
    sendMsg[16] = '2'; 
    sendMsg[17] = '2'; 
	sendMsg[18] = '.';
	sendMsg[19] = 'r';
	sendMsg[20] = 'x';
	sendMsg[21] = 'e';
    sendMsg[22] = '\0'; 
    
	//for Message Debugging Purposes
    /*for(i=0; i < 23; i++){
        printf("%u ", (int)sendMsg[i]);
    }
	printf("\n");*/
	
	sendMessage(23);
	
	Sleep(2000);		//Delay to let the program start

    return 0;
}

int ChNXT::getBluetoothAddress(void){
    char path[MAX_PATH];
    FILE *stream;
#ifdef _WIN32
    /* get configuration file path in Windows */
    if(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path) != S_OK) {
        //Could not get the user's app data directory
    } else {
        //MessageBox((LPCTSTR)path, (LPCTSTR)"Test");
        //fprintf(fp, "%s", path); 
    }
    strcat(path, "\\nxt.config");

    /* open the configuration file*/
    stream = fopen(path, "r");
    if(stream == NULL) {
        /* The file doesn't exist. Gotta make the file */
        fprintf(stderr, 
                "ERROR: Your Ch NXT configuration file does not exist.\n"
                "Please create one by opening the NXT remote control, clicking on\n"
                "the 'Robot' menu entry, and selecting 'Configure Robot Bluetooth'.\n");
        return -1;
    }

    /* get bluetooth address */
    if(fgets(btAddress, 18, stream) == NULL) {
        return -4;
    }
    fclose(stream);
#else
    /* Mach or Linux */
#endif
    return 0;
}

int ChNXT::connectWithAddress(char usr_address[18], int channel) {
    if (connected == 0) {
        // copy bth address from user's input
        strcpy(btAddress, usr_address);
        if(NXT_connectWithAddress(&_comms, btAddress, 1) == 0){
            connected = 1;
        } else {
            return 1;
        }
    }
    return 0;
}

int ChNXT::disconnect(void) {
    stopAllMotors();
    stopAllSensors();
    connected = 0;
    return closesocket(_comms.socket);
}

int ChNXT::stopAllSensors(void){
    for (int i = 0; i < 4; i++){
        setSensor((nxtSensorId_t)i, 
                NXT_SENSORTYPE_NOSENSOR, NXT_SENSORMODE_RAWMODE);
    }
    return 0;
}

/* functions for nxt motors */
int ChNXT::setMotorSpeed(nxtMotorId_t motor, int speed){
    if(speed < 0 || speed >100){
        printf("Invalid speed.\n");
        return -1;
    }
    motorSpeed[motor] = (int)speed;
    return 0;
}

int ChNXT::setMotorSpeeds(int speed1, int speed2, int speed3){
    setMotorSpeed(NXT_MOTORA, speed1);
    setMotorSpeed(NXT_MOTORB, speed2);
    setMotorSpeed(NXT_MOTORC, speed3);
    return 0;
}

int ChNXT::setMotorSpeedRatio(nxtMotorId_t id, double ratio){
    checkMotorSpeedRatioValidation(ratio);

    motorSpeedRatio[id] = ratio;
    motorSpeed[id] = motorSpeedRatio[id] * 100;

    return 0;
}

int ChNXT::checkMotorSpeedRatioValidation(double &ratio){
    if(ratio < 0){
        ratio = 0;
    } else if(ratio > 1){
        ratio = 1;
    } else {
        ;
    }

    return 0;
}

int ChNXT::setMotorSpeedRatios(double ratio1, double ratio2,
        double ratio3){
    setMotorSpeedRatio(NXT_MOTORA, ratio1);
    setMotorSpeedRatio(NXT_MOTORB, ratio2);
    setMotorSpeedRatio(NXT_MOTORC, ratio3);
    return 0;
}

int ChNXT::setMotorRelativeZero(nxtMotorId_t id){
    int rec;
    sendMsg[0] = 0x04;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x80;
    sendMsg[3] = 0x0A;
    sendMsg[4] = (unsigned char) id;
    sendMsg[5] = TRUE; /* relative? */

    rec = sendMessage(6);
    
    Sleep(60);
    if (!rec) {
        printf("Fail to reset motor%d.\n", id+1);
        return 1;
    }
    return 0;
}

int ChNXT::setMotorToZero(nxtMotorId_t id){
    int rec;

    sendMsg[0] = 0x04;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x80;
    sendMsg[3] = 0x0A;
    sendMsg[4] = (unsigned char) id;
    sendMsg[5] = FALSE; /* relative? */

    rec = sendMessage(6);
    
    Sleep(60);
    if (!rec) {
        printf("Fail to reset motor%d.\n", id+1);
        return 1;
    }
    return 0;
}

int ChNXT::setMotorRelativeZeros(void){
    setMotorRelativeZero(NXT_MOTORA);
    setMotorRelativeZero(NXT_MOTORB);
    setMotorRelativeZero(NXT_MOTORC);
    return 0;
}

int ChNXT::setMotorZeros(void){
    setMotorToZero(NXT_MOTORA);
    setMotorToZero(NXT_MOTORB);
    setMotorToZero(NXT_MOTORC);
    return 0;
}

int ChNXT::setToZeros(void){
    setMotorToZero(NXT_MOTORA);
    setMotorToZero(NXT_MOTORB);
    setMotorToZero(NXT_MOTORC);
    return 0;
}

int ChNXT::moveMotorContinuousNB( nxtMotorId_t id, nxtMotorState_t dir ){
    int parsSpeed, direction;
	int res, i;
	char power[4];
	
	parsSpeed = motorSpeed[id] * dir;
	
	if(parsSpeed < 0)
		parsSpeed = motorSpeed[id]+100;
		
	sprintf(power, "%d", parsSpeed);
	
	//Bluetooth specific Bits
    sendMsg[0] = 0x11;      //Message Length LSB
    sendMsg[1] = 0x00;		//Message Length MSB
    
    //NXT Direct command for Message Write
    sendMsg[2] = (unsigned char) 0x80;	//No response
    sendMsg[3] = 0x09;	//Message Write Identifier
    sendMsg[4] = 0x01; //Inbox Number
    sendMsg[5] = 0x0d; //Message size
    
	//CLASSIC_MOTORCMD
	sendMsg[6] = '4';		//Classic Motorcmd Header
    sendMsg[7] = id + 48;  //port
    sendMsg[8] = power[0];   //Power
    sendMsg[9] = power[1];   //Power
    
    sendMsg[10] = power[2];   //Power
    sendMsg[11] = '0';   //Tacho
    sendMsg[12] = '0';	  //Tacho 
    sendMsg[13] = '0';   //Tacho

    sendMsg[14] = '0';  //Tacho
    sendMsg[15] = '0';  //Tacho
    sendMsg[16] = '0';  //Tacho
    sendMsg[17] = '6';  //Mode
    sendMsg[18] = 0;  //termination character
    res = sendMessage(19);
    
    /*for(i = 0; i < 19; i++){
        printf("%d ", sendMsg[i]);
    }*/

	if (res == 0){
        return 1;
	}

    return 0;
}

int ChNXT::checkMotorRunDirection(nxtMotorId_t id, int dir){
    if(dir > 0){
        runDirection[id] = 1;
    }else if(dir < 0){
        runDirection[id] = -1;
    }else{
        printf("Invalid direction.\n");
    }

    return 0;
}

int ChNXT::moveMotorNB(nxtMotorId_t id, double angle) {

	int parsSpeed, direction;
	int res, i;
	char power[4], tacho[7];
	int intAngle = (int)angle;
	
	resetErrorCorrection(id);	//Reset the Mindstorm error correction
	
	//Check angle sign to give sign to speed
	if(angle > 0)
		parsSpeed = motorSpeed[id];
	else
		parsSpeed = motorSpeed[id] + 100;
		
	sprintf(power, "%d", parsSpeed);		//Convert speed to char
	sprintf(tacho, "%d", abs(intAngle));	//convert angletacho to char
	

    //degrees = (int)abs(angle);

    //Bluetooth specific Bits
    sendMsg[0] = 0x11;      //Message Length LSB
    sendMsg[1] = 0x00;		//Message Length MSB
    
    //NXT Direct command for Message Write
    sendMsg[2] = (unsigned char) 0x80;	//No response
    sendMsg[3] = 0x09;	//Message Write header
    sendMsg[4] = 0x01; //Inbox Number
    sendMsg[5] = 0x0d; //Message size
    
    //Motor Control Program Command
    sendMsg[6] = '1';	// Command
    sendMsg[7] = id + 48;	// Port
    sendMsg[8] = power[0];   //Power
    sendMsg[9] = power[1];   //Power
    
    sendMsg[10] = power[2];   //Power
    sendMsg[11] = tacho[0];   //Tacho
    sendMsg[12] = tacho[1];	  //Tacho 
    sendMsg[13] = tacho[2];   //Tacho

    sendMsg[14] = tacho[3];  //Tacho
    sendMsg[15] = tacho[4];  //Tacho
    sendMsg[16] = tacho[5];  //Tacho
    sendMsg[17] = '7';  //Mode
    sendMsg[18] = 0;  //termination character
    
	//Debugging Message
    /*for(i=0; i < 19; i++){
        printf("%u ", (int)sendMsg[i]);
    }
	printf("\n");*/

    res = sendMessage(19);
	
    if (res == 0){
        return 1;
    }
    return 0;
}

int ChNXT::moveMotor(nxtMotorId_t id, double angle){
    moveMotorNB(id, angle);	//move motor with NB function
	Sleep(100);		//Delay to keep motor controller from getting overwhelmed
    return moveMotorWait(id);	//Wait till motor finishes
}

int ChNXT::moveMotorToNB(nxtMotorId_t id, double angle){
    int degrees;
    double currentPosition;
    double targetPosition = angle;
    double currentSpeedRatio;
    double speed;
    int count = 0;
    double offset = 1.0;
    
    getOutputState(id);		//Get internal motor position
    if(iRotationCount[id] > (int)angle){
        degrees = -(iRotationCount[id] - (int)angle); //Find angle to move
        moveMotorNB(id, degrees);
    }else if(iRotationCount[id] < angle){
	degrees = angle - iRotationCount[id];
        moveMotorNB(id, (double)degrees);	//Find angle to move
    }else{
	degrees = 0;
    }

    return 0;
}

int ChNXT::moveMotorTo(nxtMotorId_t id, double angle){
    moveMotorToNB(id, angle);	//Call NB function
	Sleep(30);		//delay to prevent bluetooth errors
    return moveMotorWait(id);	//wait till finished
}

int ChNXT::moveContinuousNB(nxtMotorState_t dir1,
	nxtMotorState_t dir2, nxtMotorState_t dir3){
    moveMotorContinuousNB(NXT_MOTORA, dir1);
    moveMotorContinuousNB(NXT_MOTORB, dir2);
    moveMotorContinuousNB(NXT_MOTORC, dir3);
    return 0;
}

int ChNXT::moveContinuousTime(nxtMotorState_t dir1,
	nxtMotorState_t dir2, nxtMotorState_t dir3, double seconds){
    moveMotorContinuousNB(NXT_MOTORA, dir1);
    moveMotorContinuousNB(NXT_MOTORB, dir2);
    moveMotorContinuousNB(NXT_MOTORC, dir3);
    Sleep(seconds * 1000);
    stopAllMotors();
    return 0;
}

int ChNXT::moveTo(double angle1, double angle2, double angle3){
    moveMotorToNB(NXT_MOTORA, angle1);
    moveMotorToNB(NXT_MOTORB, angle2);
    moveMotorToNB(NXT_MOTORC, angle3);

    return moveWait();
}

int ChNXT::move(double angle1, double angle2, double angle3){
    moveMotorNB(NXT_MOTORA, angle1);
    moveMotorNB(NXT_MOTORB, angle2);
    moveMotorNB(NXT_MOTORC, angle3);

    return moveWait();
}

int ChNXT::moveNB(double angle1, double angle2, double angle3){
    moveMotorNB(NXT_MOTORA, angle1);
    moveMotorNB(NXT_MOTORB, angle2);
    moveMotorNB(NXT_MOTORC, angle3);

    return 0;
}

int ChNXT::moveToNB(double angle1, double angle2, double angle3){
    moveMotorToNB(NXT_MOTORA, angle1);
    moveMotorToNB(NXT_MOTORB, angle2);
    moveMotorToNB(NXT_MOTORC, angle3);

    return 0;
}

int ChNXT::moveToZero(void){
    moveToNB(0, 0, 0);
    return moveWait();
}
 
int ChNXT::moveToZeroNB(void){
    moveToNB(0, 0, 0);
    return 0;
} //ChNXT::moveToZeroNB()

int ChNXT::stopOneMotor(nxtMotorId_t id){
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
}

int ChNXT::stopTwoMotors(nxtMotorId_t id1, nxtMotorId_t id2){
    stopOneMotor(id1);
    stopOneMotor(id2);
    return 0;
}

int ChNXT::stopAllMotors(void){
    stopOneMotor(NXT_MOTORA);
    stopOneMotor(NXT_MOTORB);
    stopOneMotor(NXT_MOTORC);
    return 0;
}

int ChNXT::getMotorAngle(nxtMotorId_t id, double &angle){
//int ChNXT::getMotorAngle(nxtMotorId_t id, int &angle){
    getOutputState(id);
//    angle = (double)iRotationCount[id];
    angle = iRotationCount[id];
    return 0;
}

int ChNXT::getMotorSpeed(nxtMotorId_t id, int &speed){
    speed = motorSpeed[id];
    return 0;
}

int ChNXT::getMotorSpeeds(int &speed1, int &speed2,
        int &speed3){
    speed1 = motorSpeed[1];
    speed2 = motorSpeed[2];
    speed3 = motorSpeed[3];
    return 0;
}

int ChNXT::getMotorSpeedRatio(nxtMotorId_t id, double &ratio){
    ratio = motorSpeedRatio[id];
    return 0;
}

int ChNXT::getMotorSpeedRatios(double &ratio1, double &ratio2,
        double &ratio3){
    ratio1 = motorSpeedRatio[1];
    ratio2 = motorSpeedRatio[2];
    ratio3 = motorSpeedRatio[3];
    return 0;
}

int ChNXT::getMotorState(nxtMotorId_t id, int &status){
	int check;
    check = isMotorReady(id);
    if(check == 1)
        status = 0;
    else
        status = 1;
    return 0;
}


int ChNXT::isConnected(void){
    return connected;
}

int ChNXT::isMoving(){
    int i;
    for(i = 0; i<3; i++){
        if(!isMotorReady((nxtMotorId_t)i));
            return 1;
    }
    return 0;
}

int ChNXT::moveMotorWait(nxtMotorId_t id){
    while(isMotorReady(id) == 0){
        Sleep(30); //delay to prevent connectivity problems
    }
    return 0;
}

int ChNXT::moveWait(){
    int i;
    for(i = 0; i<3; i++){
	if(moveMotorWait((nxtMotorId_t)i))
	    return -1;
    }
    return 0;
}

int ChNXT::setSensor(
        nxtSensorId_t id, 
        nxtSensorType_t type, 
        nxtSensorMode_t mode
        ){
    if (id > 3) {
        printf("Invalid port number: %d\n", id);
        return 1; //only ports 0..3
    }
    sensorOn[id] = 1; // 1 means sensor on
    sensorType[id] = type;
    sensorMode[id] = mode;
    if (!updateInputTypeMode(id)){
        return 1;
    }
    if (!initInput(id)){
        return 1;
    }
    return 0;
}

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
}

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
}

int ChNXT::playTone(int freq, int duration){
    sendMsg[0] =0x04;
    sendMsg[1] =0x00;
    sendMsg[2] =0x80;
    sendMsg[3] =0x03;
    sendMsg[4] =freq;
    sendMsg[5] =duration;
    return sendMessage(6);
}
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
}
*/
int ChNXT::vehicleRollForwardNB(double angle){
    if(angle < 0)
        angle = -angle;
    moveMotorNB(NXT_MOTORB, angle);
    moveMotorNB(NXT_MOTORC, angle);
    return 0;
}

int ChNXT::vehicleRollForward(double angle){
    if(angle < 0)
        angle = -angle;
    moveMotorNB(NXT_MOTORB, angle);
    moveMotorNB(NXT_MOTORC, angle);
    return vehicleMotionWait();
}

int ChNXT::vehicleRollBackwardNB(double angle){
    if(angle < 0)
        angle = -angle;
    moveMotorNB(NXT_MOTORB, -angle);
    moveMotorNB(NXT_MOTORC, -angle);
    return 0;
}

int ChNXT::vehicleRollBackward(double angle){
    if(angle < 0)
        angle = -angle;
    moveMotorNB(NXT_MOTORB, -angle);
    moveMotorNB(NXT_MOTORC, -angle);
    return vehicleMotionWait();
}

int ChNXT::vehicleRotateLeftNB(double angle){
    if(angle < 0)
        angle = -angle;
    moveMotorNB(NXT_MOTORB, angle);
    moveMotorNB(NXT_MOTORC, -angle);
    return 0;
}

int ChNXT::vehicleRotateLeft(double angle){
    if(angle < 0)
        angle = -angle;
    moveMotorNB(NXT_MOTORB, angle);
    moveMotorNB(NXT_MOTORC, -angle);
    return vehicleMotionWait();
}

int ChNXT::vehicleRotateRightNB(double angle){
    if(angle < 0){
        angle = -angle;
    }

    moveMotorNB(NXT_MOTORB, -angle);
    moveMotorNB(NXT_MOTORC, angle);
    return 0;
}

int ChNXT::vehicleRotateRight(double angle)
{
    /* check if the input angle is negative */
    if(angle < 0){
        angle = -angle;
    }

    moveMotorNB(NXT_MOTORB, -angle);
    moveMotorNB(NXT_MOTORC, angle);

    return vehicleMotionWait();
}

int ChNXT::vehicleMotionWait(void){
    moveMotorWait(NXT_MOTORB);
    moveMotorWait(NXT_MOTORC);
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

    moveMotorWait(NXT_MOTORA);
    moveMotorWait(NXT_MOTORB);
    moveMotorWait(NXT_MOTORC);

    return 0;
}

int ChNXT::motionMoveForward(void){
    moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);
    return 0;
}

int ChNXT::motionMoveBackward(void){
    moveMotorContinuousNB(NXT_MOTORB, NXT_BACKWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_BACKWARD);
    return 0;
}

int ChNXT::motionRotateLeft(void){
    moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_BACKWARD);
    return 0;
}

int ChNXT::motionRotateRight(void){
    moveMotorContinuousNB(NXT_MOTORB, NXT_BACKWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);
    return 0;
}

int ChNXT::motionTurnLeft(void){
    motorSpeed[NXT_MOTORC] = 0.7*motorSpeed[NXT_MOTORB];
    moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);
    return 0;
}

int ChNXT::motionTurnRight(void){
    motorSpeed[NXT_MOTORB] = 0.7*motorSpeed[NXT_MOTORC];
    moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);
    return 0;
}

int ChNXT::moveForward(void){
    moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);
    return 0;
}

int ChNXT::moveBackward(void){
    moveMotorContinuousNB(NXT_MOTORB, NXT_BACKWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_BACKWARD);
    return 0;
}

int ChNXT::rotateLeft(void){
    moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_BACKWARD);
    return 0;
}

int ChNXT::rotateRight(void){
    moveMotorContinuousNB(NXT_MOTORB, NXT_BACKWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);
    return 0;
}

int ChNXT::turnLeft(void){
    motorSpeed[NXT_MOTORC] = 0.7*motorSpeed[NXT_MOTORB];
    moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);
    return 0;
}

int ChNXT::turnRight(void){
    motorSpeed[NXT_MOTORB] = 0.7*motorSpeed[NXT_MOTORC];
    moveMotorContinuousNB(NXT_MOTORB, NXT_FORWARD);
    moveMotorContinuousNB(NXT_MOTORC, NXT_FORWARD);
    return 0;
}

int ChNXT::stopMotion(void){
    stopOneMotor(NXT_MOTORB);
    stopOneMotor(NXT_MOTORC);
    return 0;
}

/* internal functions */
int ChNXT::sendMessage(int length) {
    error = send(_comms.socket, (const char*) sendMsg, length, 0);
    if (error == 0){
        printf("failure sending!\n");
        return 0;
    }
    return 1;
}

int ChNXT::recvMessage(int length) {
    error = recv(_comms.socket, (char *)recvMsg, length, 0);
    if (error == 0) {
        printf("connection broken or no more charactors\n");
    }
    return error;
}

int ChNXT::getOutputState(nxtMotorId_t id){

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
    iTachoLimit[id] = (0xFF & recvMsg[11]) | ((0xFF & recvMsg[12]) << 8)
        | ((0xFF & recvMsg[13]) << 16)| ((0xFF & recvMsg[14]) << 24);
    iTachoCount[id] = (0xFF & recvMsg[15]) | ((0xFF & recvMsg[16]) << 8)
        | ((0xFF & recvMsg[17]) << 16)| ((0xFF & recvMsg[18]) << 24);
    iBlockCount[id] = (0xFF & recvMsg[19]) | ((0xFF & recvMsg[20]) << 8)
        | ((0xFF & recvMsg[21]) << 16)| ((0xFF & recvMsg[22]) << 24);
    iRotationCount[id] = (0xFF & recvMsg[23]) | ((0xFF & recvMsg[24]) << 8)
        | ((0xFF & recvMsg[25]) << 16)| ((0xFF & recvMsg[26]) << 24);
    return 0;
}

int ChNXT::pollInput(nxtSensorId_t id) {
    /****************************************************
     * returns 0 if communication failed and 1 if success
     * (NXT_error might still be set even then)
     * communication with NXT needs to be successfully
     * initiated BEFORE calling this routine!
     ***************************************************/
    int res;
    //special care for the ultrasound sensor
    if (i_sensorType[id] == NXT_SENSORTYPE_ULTRASONIC){
        return getUltrasonic(id);
		/*
    } else if(i_sensorType[id] == NXT_SENSORTYPE_COLORFULL){
        return getColorfull(id);
		*/
    } else {
        sendMsg[0] = 0x03; //three bytes follow
        sendMsg[1] = 0x00;
        sendMsg[2] = 0x00; //request response
        sendMsg[3] = 0x07; /* GETINPUTVALUES */
        sendMsg[4] = id; //from port 0 (1 on the brick)

        if (!sendMessage(5)) {
            error = -1; //communication error
            return 0;
        }

        Sleep(60); //wait 60ms for response
        res = recvMessage(18);
        if ((res == 18) && (recvMsg[2] == 0x02) && (recvMsg[3] == 0x07)) {
            //correct return message received
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
                        sensorValRaw[id]=((0xff & recvMsg[10]) | (recvMsg[11] << 8));
                        sensorValNorm[id] = (int)recvMsg[12] + ((int)recvMsg[13] << 8);
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
                || (i_sensorType[id] == NXT_SENSORTYPE_TOUCH)
                || (i_sensorType[id] == NXT_SENSORTYPE_COLORRED)
                || (i_sensorType[id] == NXT_SENSORTYPE_COLORGREEN)
                || (i_sensorType[id] == NXT_SENSORTYPE_COLORBLUE)
                ){
            return sensorValScaled[id];
        } else {
            return sensorValRaw[id];
        }
    }
//    return 1;
}

int ChNXT::updateInputTypeMode(nxtSensorId_t id) {
    int ret = 0;

    //was ultrasonic, de-init
    if (i_sensorType[id] == 0x0B) {
        ret = stopUltrasonic(id);
        if (ret == 0)
            return 0; //return if de-init failed
    }
    // set sensor type and mode
    if (sensorType[id] == NXT_SENSORTYPE_ULTRASONIC) {
        setUltrasonic(id);
		/*
    } else if(sensorType[id] == NXT_SENSORTYPE_COLORFULL){
        setColorfull(id);
		*/
    } else { // set other sensors
        sendMsg[0] = 0x05;
        sendMsg[1] = 0x00;
        sendMsg[2] = 0x80; /* no response */
        sendMsg[3] = 0x05;
        sendMsg[4] = id;
        sendMsg[5] = sensorType[id];
        sendMsg[6] = sensorMode[id];
        ret = sendMessage(7);
    }
    i_sensorType[id] = sensorType[id];
    i_sensorMode[id] = sensorMode[id];
    return ret;
}

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
}

int ChNXT::setColorfull(nxtSensorId_t id){
    sendMsg[0] = 0x05;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; /* require response */
    sendMsg[3] = id;
    sendMsg[5] = NXT_SENSORTYPE_COLORFULL;
    sendMsg[6] = NXT_SENSORMODE_RAWMODE;

    int res = sendMessage(7);
    if (res == 0){
        return 0;
    }
    Sleep(60);

    res = recvMessage(5);
    if((res != 5) || (recvMsg[4] != 0)){
        return 0;
    }
    Sleep(20);

    sendMsg[0] = 0x08;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x80; /* response not required */
    sendMsg[3] = 0x0F; /* LS write */
    sendMsg[4] = id;
    sendMsg[5] = 0x02; /* tx length */
    sendMsg[6] = 0x01; /* rx length */
    sendMsg[7] = 0x02; /* register address */
    sendMsg[8] = 0x42; /* color number */
    res = sendMessage(9);
    if(res == 0){
        return 0;
    }

    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0)){
        return 0;
    }

    return 1;
}

int ChNXT::setUltrasonic(nxtSensorId_t id) {
    int res;

    //set sensor to "digital" mode
    sendMsg[0] = 0x05; //five bytes follow
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; // response requested
    sendMsg[3] = 0x05; //setinputmode
    sendMsg[4] = id;
    sendMsg[5] = 0x0b; //lowspeed_9v type
    sendMsg[6] = NXT_SENSORMODE_RAWMODE; //rawmode mode
    res = sendMessage(7);
    if (res == 0)
        return 0;
    Sleep(60);

    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0)){
        return 0;
    }
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
    if (res == 0){
        return 0;
    }
    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0)){
        return 0;
    }
    return 1;
}

int ChNXT::stopColorfull(nxtSensorId_t id){

    return 1;
}
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
}

int ChNXT::getColorfull(nxtSensorId_t id){
    int res;

    sendMsg[0] = 0x03;
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00;
    sendMsg[3] = 0x10; /* LS Read */
    sendMsg[4] = id; 
    res = sendMessage(5);
    if(res == 0){
        return 1;
    }

    Sleep(60);
    res = recvMessage(22);
    if((res != 22) || (recvMsg[4] != 0)){
        return 1;
    }
    Sleep(60);

    sendMsg[0] = 0x07; //message length without first two bytes
    sendMsg[1] = 0x00;
    
    sendMsg[2] = 0x00; //0x80; //no response please (to LS write)
    sendMsg[3] = 0x0F; //LSWrite
    sendMsg[4] = id;
    sendMsg[5] = 0x02; //Tx Data length (two bytes sent - 02 42)
    sendMsg[6] = 0x06; //Rx Data length (1 byte reply expected)
    sendMsg[7] = 0x02; 
    sendMsg[8] = 0x46;
    res = sendMessage(9);
    if (res == 0) {
        return 1;
    }

    Sleep(60);

    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0)) {
        return 1;
    }

    Sleep(50);

    sendMsg[0] = 0x03; //message length without first two bytes
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; //response please
    sendMsg[3] = 0x0E; //LSGetStatus
    sendMsg[4] = id; //port number 0..3
    res = sendMessage(5);

    if (res == 0) {
        return 1;
    }

    Sleep(50);

    //if 'idle', send "read 1 I2C reply byte" and read response
    res = recvMessage(4 + 2);
    if (res != 6) {
        return 1;
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

        return sensorValRaw[id];
    }
    return 0;
}

int ChNXT::getUltrasonic(nxtSensorId_t id) {
//#if 0
    int res;
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
        return 1 ;
    }
    Sleep(60);
    res = recvMessage(20 + 2);
    if ((res != 22) || (recvMsg[4] != 0)) {
        return 1;
    }
    Sleep(60);

    //send 0x01 0x02 0x42, to retrieve 0x01 bytes
    //from read a continuous measurement distance (0x42)
    //from address 0x02
    sendMsg[0] = 0x07; //message length without first two bytes
    sendMsg[1] = 0x00;
    sendMsg[2] = 0x00; //0x80; //no response please (to LS write)
    sendMsg[3] = 0x0F; //LSWrite
    sendMsg[4] = id;
    sendMsg[5] = 0x02; //Tx Data length (two bytes sent - 02 42)
    sendMsg[6] = 0x01; //Rx Data length (1 byte reply expected)
    sendMsg[7] = 0x02; //address for "read sonar"
    sendMsg[8] = 0x42; //read distance
    res = sendMessage(9);
    if (res == 0) {
        return 1;
    }

    Sleep(60);

    res = recvMessage(5);
    if ((res != 5) || (recvMsg[4] != 0)) {
        return 1;
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
        return 1;
    }

    Sleep(50);

    //if 'idle', send "read 1 I2C reply byte" and read response
    res = recvMessage(4 + 2);
    if (res != 6) {
        return 1;
    }

//#endif
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

    return 0;
}

int ChNXT::test(void) {
//    int i;
//    int res;
    /*
    getOutputState(NXT_MOTORB);
    printf("isMoving = %d\n", iRunState[NXT_MOTORB]);
    printf("tacholimit = %d\n", iTachoLimit[NXT_MOTORB]);
    printf("tachocount = %d\n", iTachoCount[NXT_MOTORB]);
    printf("blockcount = %d\n", iBlockCount[NXT_MOTORB]);
    printf("rotationcount = %d\n", iRotationCount[NXT_MOTORB]);
    */
    double currentPosition;
    double targetPosition = 360.0;
    double offset = 1.0;
    getMotorAngle(NXT_MOTORA, currentPosition);
    do{
        if(abs(currentPosition - targetPosition) < 30){
            setMotorSpeedRatio(NXT_MOTORA, 0.01);
        }

        if(currentPosition > targetPosition + offset){
            moveMotorContinuousNB(NXT_MOTORA, NXT_BACKWARD);
        }else if(currentPosition < targetPosition - offset){
            moveMotorContinuousNB(NXT_MOTORA, NXT_FORWARD);
        }

        getMotorAngle(NXT_MOTORA, currentPosition);
    } while((currentPosition > targetPosition + offset) || (currentPosition < targetPosition - offset));
    stopOneMotor(NXT_MOTORA);
    getMotorAngle(NXT_MOTORA, currentPosition);
    printf("target angle = %lf, current angle = %lf\n",
            targetPosition, currentPosition);
//    setOutputState(NXT_MOTORC, MOTORON | BRAKE | REGULATED, 0x01, 0x00, 0x20, 720, 0);
    return 0;
}

int ChNXT::isMotorReady(nxtMotorId_t id){ //return 1 if true, 0 if not
	int res, i, rtnVal;
	do{
		//Bluetooth specific Bits
		sendMsg[0] = 0x07;      //Message Length LSB
		sendMsg[1] = 0x00;
    
		//NXT Direct command for Message Write
		sendMsg[2] = (unsigned char) 0x80;
		sendMsg[3] = 0x09;
		sendMsg[4] = 0x01; //Inbox Number
		sendMsg[5] = 0x03; //Message size
	
		//ISMOTORREADY message
		sendMsg[6] = '3'; //Header identifying command
		sendMsg[7] = id + 48;  //port number
		sendMsg[8] = '\0';
	
		/*printf("Message Write:\n");
		for(i = 0; i < 9; i++){
			printf("%d ", sendMsg[i]);
		}
		printf("\n");*/
	
		//send
		res = sendMessage(9);

		if (res == 0) {
			return 1;
		}
	
		//delay
		Sleep(30);
	
		//Message Read
		//Bluetooth specific Bits
		sendMsg[0] = 0x05;      //Message Length LSB
		sendMsg[1] = 0x00;
    
		//NXT Direct command for Message Read
		sendMsg[2] = (unsigned char) 0x00;
		sendMsg[3] = 0x13;
		sendMsg[4] = 0x00; //Inbox Number
		sendMsg[5] = 0x00; //Inbox Number
		sendMsg[6] = 0x01;
	
		/*printf("Message Read:\n");
		for(i = 0; i < 7; i++){
			printf("%d ", sendMsg[i]);
		}
		printf("\n");*/
	
		res = sendMessage(7);
	
		Sleep(30);
	
		res = recvMessage(66);
	
		/*printf("Recieved Message:\n");
		for(i = 0; i < 66; i++){
			printf("%d ", recvMsg[i]);
		}
		printf("\n");*/
	}while((recvMsg[4] != 0) || (recvMsg[7] != id + 48));

	rtnVal = recvMsg[8] - 48;
	
	return rtnVal;
}

int ChNXT::resetErrorCorrection(nxtMotorId_t id){
	int res;
	//Bluetooth specific Bits
	sendMsg[0] = 0x07;      //Message Length LSB
	sendMsg[1] = 0x00;
    
	//NXT Direct command for Message Write
	sendMsg[2] = (unsigned char) 0x80;
	sendMsg[3] = 0x09;
	sendMsg[4] = 0x01; //Inbox Number
	sendMsg[5] = 0x03; //Message size
	
	//reset specific bytes
	sendMsg[6] = '2'; //Header
	sendMsg[7] = id + 48; //Reset All
	sendMsg[8] = 0; //null
	
	res = sendMessage(9);
	
	Sleep(15);

    if (res == 0) {
        return 1;
    }
	return 0;
}

int ChNXT::setTwoWheelRobotSpeed(double speed, double radius){
	int motorspeed;
	motorspeed = speed/radius * 18/3.14;
	if(motorspeed > 100)
		motorspeed = 100;
	if(motorspeed < -100)
		motorspeed = 100;
	setMotorSpeed(NXT_MOTORA, motorspeed);
	setMotorSpeed(NXT_MOTORB, motorspeed);
	setMotorSpeed(NXT_MOTORC, motorspeed);
	return 0;
}

//int LSWrite(nxtSensorId_t id, int txDataLength, int rxDataLength, char *data);
//int LSRead(nxtSensorId_t id); 				//probably need a way to return more
//int LSGetStatus(nxtSensorId_t id);
