#ifndef _NXT_H
#define _NXT_H

#ifndef _CH_
#include <winsock2.h>
#include <ws2bth.h>
#include "nxt_internal.h"
#endif /* not _CH_ */

#ifdef _CH_
#pragma package <chnxt>
#endif /* _CH_ */

#ifndef NXT_JOINTS_E
#define NXT_JOINTS_E
typedef enum nxt_joints_e{
    NXT_JOINT1 = 0, // PORT_A
    NXT_JOINT2 = 1, // PORT_B
    NXT_JOINT3 = 2  // PORT_C
} nxtJointId_t;
#endif /* NXT_JOINTS_E */

#ifndef NXT_JOINT_STATE_E
#define NXT_JOINT_STATE_E
typedef enum nxt_joint_state_e{
    NXT_FORWARD = 1,
    NXT_BACKWARD = -1,
} nxtJointState_t;
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
    NXT_SENSORTYPE_TOUCH           = 0x01,
    NXT_SENSORTYPE_TEMPERATURE     = 0x02,
    NXT_SENSORTYPE_LIGHT_ACTIVE    = 0x05,
    NXT_SENSORTYPE_LIGHT_INACTIVE  = 0x06,
    NXT_SENSORTYPE_SOUND_DB        = 0x07,
    NXT_SENSORTYPE_SOUND_DBA       = 0x08,
    NXT_SENSORTYPE_LOWSPEED        = 0x0A,
    NXT_SENSORTYPE_ULTRASONIC      = 0x0B // LOWSPEED_9V
} nxtSensorType_t;
#endif

/* Modes for Sensors */
#ifndef NXT_SENSOR_MODE_E
#define NXT_SENSOR_MODE_E
typedef enum nxt_sensor_mode_e{
    NXT_SENSORMODE_RAWMODE = 0x00,
    NXT_SENSORMODE_BOOLEANMODE = 0x20
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
        /* functions for a single joint(motor) */
        int setJointRelativeZero(nxtJointId_t id);
	int setJointZero(nxtJointId_t id);
        int setJointRelativeZeros(void);
	int setJointZeros(void);
        int moveJointContinuousNB(nxtJointId_t id, 
                                  nxtJointState_t dir); 
	int moveJointNB(nxtJointId_t id, double angle);
	int moveJointToNB(nxtJointId_t id, double angle);
	int moveNB(double angle1, double angle2, double angle3);
	int moveToNB(double angle1, double angle2, double angle3);
	int moveToZeroNB(void);
	int moveJoint(nxtJointId_t id, double angle);
        int moveJointTo(nxtJointId_t id, double angle);
        int move(double angle1, double angle2, double angle3);
        int moveTo(double angle1, double angle2, double angle3);
	int moveToZero(void);
        int moveContinuousNB(nxtJointState_t dir1,
	                     nxtJointState_t dir2, 
                             nxtJointState_t dir3);
        int moveContinuousTime(nxtJointState_t dir1,
		               nxtJointState_t dir2, 
                               nxtJointState_t dir, 
                               double seconds);
        int moveJointWait(nxtJointId_t id);
        int moveWait(void);
        /* functions for checking status */
        int isConnected(void);
        int isMoving(void);
        int isJointMoving(nxtJointId_t id);
        double getJointPosition(nxtJointId_t id);
        int getJointAngle(nxtJointId_t id, double &angle);
        int getJointSpeedRatio(nxtJointId_t id, double &ratio);
        int getJointSpeedRatios(double &ratio1, 
                                double &ratio2,
                                double &ratio3);
        int getJointState(nxtJointId_t id, int &status);
        int stopOneJoint(nxtJointId_t id);
        int stopTwoJoints(nxtJointId_t id1, nxtJointId_t id2);
        int stopAllJoints(void);
        int stopMotion(void);
        /* functions for sensors */
        int setSensor(nxtSensorId_t id, 
                      nxtSensorType_t type,
                      nxtSensorMode_t mode);
        int getSensor(nxtSensorId_t id, int &value);
	//int getJointStates(int *status1, int *status2, int *status3);
	/* other functions */
	int printMess(void);
	int playTone(int freq, int duration);
        /* set joints'(motors') speeds */
        int setJointSpeed(nxtJointId_t id, int speed);
        int setJointSpeeds(int speed1, int speed2, int speed3);
        int setJointSpeedRatio(nxtJointId_t id, double ratio);
        int setJointSpeedRatios(double ratio1, double ratio2,
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
        /* print infromation */
        int printDeviceInfo(void);
        int printJointInfo(nxtJointId_t id);
        int printSensorInfo(int port);
        /* testing function */
        int test(void);
#ifndef _CH_
    private:
        /* functions for communication */
        int sendMessage(int length);
        int recvMessage(int length);
        /* functions for actuators */
//        int setOutputState(nxtJointId_t id,  unsigned char mode,
//                unsigned char regulationMode, char turnRatio,
//                unsigned char runState, unsigned int tachoLimit, int reply);
        int getOutputState(nxtJointId_t port);
//        int getTacho(int port);
        /* functions for sensors */
        int initInput(nxtSensorId_t id);
        int pollInput(nxtSensorId_t id);
        int updateInputTypeMode(nxtSensorId_t id);
        int setUltrasonic(nxtSensorId_t id);
        int getUltrasonic(nxtSensorId_t id);
        int stopUltrasonic(nxtSensorId_t id);
        /* variables for communication*/
        SOCKET sock;
        SOCKADDR_BTH sa;
        char btAddress[18];
        char sendMsg[256];
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
        int jointSpeed[3];
        double jointSpeedRatio[3];
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