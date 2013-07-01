#ifndef _NXT_H
#define _NXT_H

#ifdef _CH_
#pragma package <chnxt>
#ifdef _WIN32_
#define _WIN32
#include <stdint.h>
#define UINT8 uint8_t
#else
#pragma package <chbluetooth>
#endif /* _WIN32_ */
#endif /* _CH_ */

#include <stdio.h>

#ifndef _CH_
#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#ifndef __MACH__
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#endif /* _MACH_ */
#else
#include <winsock2.h>
#include <Ws2bth.h>
#endif /* not if _WIN32 */
#include "nxt_internal.h"
#endif /* not _CH_ */

#ifndef NXT_MOTORS_E
#define NXT_MOTORS_E
typedef enum nxt_motors_e{
    NXT_MOTORA = 0, // PORT_A
    NXT_MOTORB = 1, // PORT_B
    NXT_MOTORC = 2  // PORT_C
} nxtMotorId_t;
#endif /* NXT_MOTORS_E */

#ifndef NXT_MOTOR_STATE_E
#define NXT_MOTOR_STATE_E
typedef enum nxt_motor_state_e{
    NXT_FORWARD = 1,
    NXT_BACKWARD = -1,
} nxtMotorState_t;
#endif


/* Ports for Sensors */
#ifndef NXT_SENSORS_E
#define NXT_SENSORS_E
typedef enum nxt_sensors_e{
    NXT_SENSORPORT1 = 0,
    NXT_SENSORPORT2 = 1,
    NXT_SENSORPORT3 = 2,
    NXT_SENSORPORT4 = 3
} nxtSensorId_t;
#endif

/* Types for Sensors */
#ifndef NXT_SENSOR_TYPE_E
#define NXT_SENSOR_TYPE_E
typedef enum nxt_sensor_type_e{
    NXT_SENSORTYPE_NOSENSOR        = 0x00,
    NXT_SENSORTYPE_SWITCH          = 0x01,
    NXT_SENSORTYPE_TEMPERATURE     = 0x02, /* RCX temperature sensor */
    NXT_SENSORTYPE_LIGHT_ACTIVE    = 0x05, 
    NXT_SENSORTYPE_LIGHT_INACTIVE  = 0x06,
    NXT_SENSORTYPE_SOUND_DB        = 0x07, /* Sound sensor (unadjusted) */
    NXT_SENSORTYPE_SOUND_DBA       = 0x08, /* Sound sensor (adjusted) */
    NXT_SENSORTYPE_LOWSPEED        = 0x0A,
    NXT_SENSORTYPE_LOWSPEED_9V     = 0x0B, 
    NXT_SENSORTYPE_HIGHSPEED       = 0x0C, /* No useage now */
    NXT_SENSORTYPE_COLORFULL       = 0x0D, /* Color sensor mode */
    NXT_SENSORTYPE_COLORRED        = 0x0E,
    NXT_SENSORTYPE_COLORGREEN      = 0x0F,
    NXT_SENSORTYPE_COLORBLUE       = 0x10,
    NXT_SENSORTYPE_COLORNONE       = 0x11
} nxtSensorType_t;
#define NXT_SENSORTYPE_TOUCH NXT_SENSORTYPE_SWITCH
#define NXT_SENSORTYPE_ULTRASONIC NXT_SENSORTYPE_LOWSPEED_9V
#endif

/* Modes for Sensors */
#ifndef NXT_SENSOR_MODE_E
#define NXT_SENSOR_MODE_E
typedef enum nxt_sensor_mode_e{
    NXT_SENSORMODE_RAWMODE           = 0x00,
    NXT_SENSORMODE_BOOLEANMODE	     = 0x20,
    NXT_SENSORMODE_TRANSITIONCNTMODE = 0x40,
    NXT_SENSORMODE_PERIODCOUNTERMODE = 0x60,
    NXT_SENSORMODE_PCTFULLSCALEMODE  = 0x80, /* Percentage Mode */
    NXT_SENSORMODE_CELSIUSMODE       = 0xA0,
    NXT_SENSORMODE_FAHRENHEITMODE    = 0xC0
} nxtSensorMode_t;
#endif

class ChNXT {
    public:
        ChNXT();
        ~ChNXT();
        /* functions for BTH connection */
        int connect(void);
        int connectWithAddress(char usr_addr[18], int channel);
        int disconnect(void);
        /* functions for a single motor(motor) */
        int setMotorRelativeZero(nxtMotorId_t id);
        int setMotorToZero(nxtMotorId_t id);
        int setMotorRelativeZeros(void);
        int setMotorZeros(void);
        int resetToZeros(void);
        int setToZeros(void);
        int moveMotorContinuousNB(nxtMotorId_t id, 
                nxtMotorState_t dir); 
        int moveMotorNB(nxtMotorId_t id, double angle);
        int moveMotorToNB(nxtMotorId_t id, double angle);
        int moveNB(double angle1, double angle2, double angle3);
        int moveToNB(double angle1, double angle2, double angle3);
        int moveToZeroNB(void);
        int moveMotor(nxtMotorId_t id, double angle);
        int moveMotorTo(nxtMotorId_t id, double angle);
        int move(double angle1, double angle2, double angle3);
        int moveTo(double angle1, double angle2, double angle3);
        int moveToZero(void);
        int moveContinuousNB(nxtMotorState_t dir1,
                nxtMotorState_t dir2, 
                nxtMotorState_t dir3);
        int moveContinuousTime(nxtMotorState_t dir1,
                nxtMotorState_t dir2, 
                nxtMotorState_t dir, 
                double seconds);
        int moveMotorWait(nxtMotorId_t id);
        int moveWait(void);
        /* functions for checking status */
        int isConnected(void);
        int isMoving(void);
        int isMotorMoving(nxtMotorId_t id);
        double getMotorPosition(nxtMotorId_t id);
        int getMotorAngle(nxtMotorId_t id, double &angle);
        //int getMotorAngle(nxtMotorId_t id, int &angle);
		int getMotorMaxSpeed(nxtMotorId_t id, int &speed);
		int getMotorSpeed(nxtMotorId_t id, int &speed);
		int getMotorSpeeds(int &speed1, int &speed2, int &speed3);
        int getMotorSpeedRatio(nxtMotorId_t id, double &ratio);
        int getMotorSpeedRatios(double &ratio1, 
                double &ratio2,
                double &ratio3);
        int getMotorState(nxtMotorId_t id, int &status);
        int stopOneMotor(nxtMotorId_t id);
        int stopTwoMotors(nxtMotorId_t id1, nxtMotorId_t id2);
        int stopAllMotors(void);
        int stopMotion(void);
        /* functions for sensors */
        int setSensor(nxtSensorId_t id, 
                nxtSensorType_t type,
                nxtSensorMode_t mode);
        int getSensor(nxtSensorId_t id, int &value);
        //int getMotorStates(int *status1, int *status2, int *status3);
        /* other functions */
        int printMess(void);
        int playTone(int freq, int duration);
        /* set Motors'(motors') speeds */
        int setMotorSpeed(nxtMotorId_t id, int speed);
        int setMotorSpeeds(int speed1, int speed2, int speed3);
        int setMotorSpeedRatio(nxtMotorId_t id, double ratio);
        int setMotorSpeedRatios(double ratio1, double ratio2,
                double ratio3);
        /* functions for viecle configuration */
        int vehicleRollForwardNB(double angle);
        int vehicleRollBackwardNB(double angle);
        int vehicleRotateLeftNB(double angle);
        int vehicleRotateRightNB(double angle);
        int vehicleRollForward(double angle);
        int vehicleRollBackward(double angle);
        int vehicleRotateLeft(double angle);
        int vehicleRotateRight(double angle);
        int vehicleMotionWait(void);
        int motionMoveForward(void);
        int motionMoveBackward(void);
        int motionRotateLeft(void);
        int motionRotateRight(void);
        int motionTurnLeft(void);
        int motionTurnRight(void);
        int moveForward(void);
        int moveBackward(void);
        int rotateLeft(void);
        int rotateRight(void);
        int turnLeft(void);
        int turnRight(void);
        int setTwoWheelRobotSpeed(double speed, double radius);
        /* functions for humanoid configuration */
        int humanoidWalkForwardNB(double angle);
        int humanoidWalkBackwardNB(double angle);
        int humanoidWalkForward(double angle);
        int humanoidWalkBackward(double angle);
        int humanoidMotionWait(void);
        /* print infromation */
        int printDeviceInfo(void);
        int printMotorInfo(nxtMotorId_t id);
        int printSensorInfo(int port);
        /* testing function */
        int test(void);
#ifndef _CH_
    private:
        int getBluetoothAddress(void);
        int getConfigFilePath(void);
        /* functions for communication */
        int sendMessage(int length);
        int recvMessage(int length);
        /* functions for actuators */
        //int setOutputState(nxtMotorId_t id,  unsigned char mode,
        //unsigned char regulationMode, char turnRatio,
        //unsigned char runState, unsigned int tachoLimit, int reply);
        int getOutputState(nxtMotorId_t port);
        int checkMotorRunDirection(nxtMotorId_t id, int dir);
        int checkMotorSpeedRatioValidation(double &ratio);
        //int getTacho(int port);
        /* functions for sensors */
        int initInput(nxtSensorId_t id);
        int pollInput(nxtSensorId_t id);
        int updateInputTypeMode(nxtSensorId_t id);
        int setUltrasonic(nxtSensorId_t id);
        int getUltrasonic(nxtSensorId_t id);
        int stopUltrasonic(nxtSensorId_t id);
        int setColorfull(nxtSensorId_t id);
        int getColorfull(nxtSensorId_t id);
        int stopColorfull(nxtSensorId_t id);
        int stopAllSensors(void);
        /* variables for communication*/
        br_comms_t _comms;
        //SOCKET sock;
        //SOCKADDR_BTH sa;
        char configFilePath[512];
        char btAddress[18];
        unsigned char sendMsg[256];
        char recvMsg[256];
        /* variables for sensors */
        int sensorOn[4];
        int sensorType[4];
        int sensorMode[4];
        int i_sensorType[4];
        int i_sensorMode[4];
        int sensorValRaw[4];
        int sensorValNorm[4];
        int sensorValScaled[4];
        int sensorValCalib[4];
        /* variables for actuators */
        int motorOn[3];
        int motorSpeed[3];
        double motorSpeedRatio[3];
        double motorPosRaw[3];
        double motorPosCum[3];
        int iRunState[3];
        int runDirection[3];
        int iTachoLimit[3];
        int iTachoCount[3];
        int iBlockCount[3];
        int iRotationCount[3];
        /* other variables */
        int connected;
        int error;
		int isMotorReady(nxtMotorId_t id);
		int resetErrorCorrection(nxtMotorId_t id);
		//int LSWrite(nxtSensorId_t id, int txDataLength, int rxDataLength, char *data);
		//int LSRead(nxtSensorId_t id); 				//probably need a way to return more
		//int	LSGetStatus(nxtSensorId_t id);
#else
    public:
        static void *g_chnxt_dlhandle;
        static int g_chnxt_dlcount;
#endif /* Not _CH_ */
};

#ifdef _CH_
extern void delay(double seconds);
#endif

#ifdef _CH_
void * ChNXT::g_chnxt_dlhandle = NULL;
int ChNXT::g_chnxt_dlcount = 0;
#pragma importf "chnxt.chf"
#endif

#endif /* header guard */
