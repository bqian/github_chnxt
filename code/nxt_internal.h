#if !defined _NXT_INTERNAL_H && !defined _MOBOT_INTERNAL_H_
#define _NXT_INTERNAL_H
#include "nxt.h"

#ifndef _CH_
#include "thread_macros.h"
#endif

#ifndef _CH_
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "irprops.lib")
#pragma comment(lib, "shell32.lib")
#endif /* Not _CH_ */

#ifndef _WIN32
#ifndef _llvm_
#include <stdint.h>
#else
typedef unsigned char uint8_t;
#endif // _llvm_
typedef struct sockaddr_rc sockaddr_t;
#else
typedef unsigned char uint8_t;
typedef unsigned __int32 uint32_t;
#define AF_BLUETOOTH AF_BTH
#define BTPROTO_RFCOMM BTHPROTO_RFCOMM
typedef SOCKADDR_BTH sockaddr_t;
#endif

#define DEG2RAD(x) ((x) * M_PI / 180.0)
#define RAD2DEG(x) ((x) * 180.0 / M_PI)

#ifndef BR_COMMS_S
#define BR_COMMS_S
typedef struct br_comms_s
{
  int socket;
  int connected;
#ifdef _WIN32
  HANDLE hSerial;
#endif
#ifndef __MACH__
  sockaddr_t addr;
#endif
  double jointSpeeds[4];
  double jointSpeedRatios[3];
  double jointSafetyAngle[3];
  double maxSpeed[4];
  THREAD_T thread;
  MUTEX_T* commsLock;
  int motionInProgress;
  int motionArgInt;
  double motionArgDouble;
  int recordingInProgress[4];

  THREAD_T commsThread;
  uint8_t recvBuf[64];
  int recvBuf_ready;
  MUTEX_T* recvBuf_lock;
  COND_T*  recvBuf_cond;
  int recvBuf_bytes;
  int commsBusy;
  MUTEX_T* commsBusy_lock;
  COND_T* commsBusy_cond;

  MUTEX_T* callback_lock;
  int callbackEnabled;
  void (*buttonCallback)(void* robot, int button, int buttonDown);
  void* nxt;
  char* configFilePath;
} br_comms_t;
#endif

#ifndef CALLBACK_ARG_S
#define CALLBACK_ARG_S
typedef struct callbackArg_s
{
  br_comms_t* comms;
  int button;
  int buttonDown;
} callbackArg_t;
#endif

/* Run Mode for Motors */
enum {
    RM_IDLE       = 0x00,
    RM_MOTORON    = 0x01,
    RM_BRAKE      = 0x02,
    RM_REGULATED  = 0x04
};

/* Regulation Mode for Motors */
enum {
    REM_MOTOR_IDLE  = 0x00,
    REM_MOTOR_SPEED = 0x01,
    REM_MOTOR_SYNC  = 0x02
};

/* Run State for Motors */
enum {
    RS_IDLE     = 0x00,
    RS_RAMPUP   = 0x10,
    RS_RUNNING  = 0x20,
    RS_RAMPDOWN = 0x40
};

#ifndef ROBOT_JOINTS_E
#define ROBOT_JOINTS_E
typedef enum mobot_joints_e {
  ROBOT_ZERO,
  ROBOT_JOINT1,
  ROBOT_JOINT2,
  ROBOT_JOINT3,
  ROBOT_JOINT4,
  ROBOT_NUM_JOINTS = 4
} robotJointId_t;
#endif

#ifndef ROBOT_JOINT_STATE_E
#define ROBOT_JOINT_STATE_E
typedef enum robotJointState_e
{
    ROBOT_NEUTRAL = 0,
    ROBOT_FORWARD,
    ROBOT_BACKWARD,
    ROBOT_HOLD,
} robotJointState_t;
#endif

#ifndef ROBOT_JOINT_DIRECTION_E
#define ROBOT_JOINT_DIRECTION_E
typedef enum mobot_motor_direction_e
{
  ROBOT_JOINT_DIR_AUTO,
  ROBOT_JOINT_DIR_FORWARD,
  ROBOT_JOINT_DIR_BACKWARD
} motorDirection_t;
#endif

#ifndef _CH_

#define DEF_MOTOR_SPEED 45
#define DEF_MOTOR_MAXSPEED 120

#ifndef C_ONLY
#ifdef __cplusplus
extern "C" {
#endif
#endif

#ifdef _WIN32

#ifdef _CH_
#define DLLIMPORT
#else
#define DLLIMPORT __declspec(dllexport)
#endif

#else /* Not _WIN32 */
#define DLLIMPORT
#endif /* _WIN32 */

DLLIMPORT int NXT_connectWithAddress(
    br_comms_t* comms, const char* address, int channel);
DLLIMPORT int NXT_init(br_comms_t* comms);
DLLIMPORT const char* NXT_getConfigFilePath();
int SendToNXT(br_comms_t* comms, const char str[], int datasize);
/*
DLLIMPORT int Mobot_blinkLED(br_comms_t* comms, double delay, int numBlinks);
DLLIMPORT int Mobot_connect(br_comms_t* comms);
#ifndef _WIN32
DLLIMPORT int Mobot_connectWithTTY(br_comms_t* comms, const char* ttyfilename);
#endif
DLLIMPORT int Mobot_connectWithAddress(
    br_comms_t* comms, const char* address, int channel);
DLLIMPORT int Mobot_disconnect(br_comms_t* comms);
DLLIMPORT int Mobot_enableButtonCallback(br_comms_t* comms, void* mobot, void (*buttonCallback)(void* mobot, int button, int buttonDown));
DLLIMPORT int Mobot_init(br_comms_t* comms);
DLLIMPORT int Mobot_isConnected(br_comms_t* comms);
DLLIMPORT int Mobot_isMoving(br_comms_t* comms);
DLLIMPORT int Mobot_getButtonVoltage(br_comms_t* comms, double *voltage);
DLLIMPORT int Mobot_getEncoderVoltage(br_comms_t* comms, int pinNumber, double *voltage);
DLLIMPORT int Mobot_getJointAngle(br_comms_t* comms, robotJointId_t id, double *angle);
DLLIMPORT int Mobot_getJointAngleAbs(br_comms_t* comms, robotJointId_t id, double *angle);
DLLIMPORT int Mobot_getJointAngleTime(br_comms_t* comms, robotJointId_t id, double *time, double *angle);
DLLIMPORT int Mobot_getJointAnglesTime(br_comms_t* comms, 
                                       double *time, 
                                       double *angle1, 
                                       double *angle2, 
                                       double *angle3, 
                                       double *angle4);
DLLIMPORT int Mobot_getJointAngles(br_comms_t* comms, 
                                       double *angle1, 
                                       double *angle2, 
                                       double *angle3, 
                                       double *angle4);
DLLIMPORT int Mobot_getJointAnglesAbsTime(br_comms_t* comms, 
                                       double *time, 
                                       double *angle1, 
                                       double *angle2, 
                                       double *angle3, 
                                       double *angle4);
DLLIMPORT int Mobot_getJointAnglesAbs(br_comms_t* comms, 
                                       double *angle1, 
                                       double *angle2, 
                                       double *angle3, 
                                       double *angle4);
DLLIMPORT int Mobot_getJointDirection(br_comms_t* comms, robotJointId_t id, robotJointState_t *dir);
DLLIMPORT int Mobot_getJointMaxSpeed(br_comms_t* comms, robotJointId_t, double *maxSpeed);
DLLIMPORT int Mobot_getJointSafetyAngle(br_comms_t* comms, double *angle);
DLLIMPORT int Mobot_getJointSafetyAngleTimeout(br_comms_t* comms, double *seconds);
DLLIMPORT int Mobot_getJointSpeed(br_comms_t* comms, robotJointId_t id, double *speed);
DLLIMPORT int Mobot_getJointSpeedRatio(br_comms_t* comms, robotJointId_t id, double *ratio);
DLLIMPORT int Mobot_getJointSpeedRatios(br_comms_t* comms, 
                                        double *ratio1, 
                                        double *ratio2, 
                                        double *ratio3, 
                                        double *ratio4);
DLLIMPORT int Mobot_getJointState(br_comms_t* comms, robotJointId_t id, robotJointState_t *state);
DLLIMPORT int Mobot_getStatus(br_comms_t* comms);
DLLIMPORT int Mobot_getVersion(br_comms_t* comms);
DLLIMPORT int Mobot_move(br_comms_t* comms,
                               double angle1,
                               double angle2,
                               double angle3,
                               double angle4);
DLLIMPORT int Mobot_moveNB(br_comms_t* comms,
                               double angle1,
                               double angle2,
                               double angle3,
                               double angle4);
DLLIMPORT int Mobot_moveContinuousNB(br_comms_t* comms,
                                  robotJointState_t dir1,
                                  robotJointState_t dir2,
                                  robotJointState_t dir3,
                                  robotJointState_t dir4);
DLLIMPORT int Mobot_moveContinuousTime(br_comms_t* comms,
                                  robotJointState_t dir1,
                                  robotJointState_t dir2,
                                  robotJointState_t dir3,
                                  robotJointState_t dir4,
                                  double seconds);
DLLIMPORT int Mobot_moveJoint(br_comms_t* comms, robotJointId_t id, double angle);
DLLIMPORT int Mobot_moveJointNB(br_comms_t* comms, robotJointId_t id, double angle);
DLLIMPORT int Mobot_moveJointContinuousNB(br_comms_t* comms, robotJointId_t id, robotJointState_t dir);
DLLIMPORT int Mobot_moveJointContinuousTime(br_comms_t* comms, 
                                            robotJointId_t id, 
                                            robotJointState_t dir, 
                                            double seconds);
DLLIMPORT int Mobot_moveJointTo(br_comms_t* comms, robotJointId_t id, double angle);
DLLIMPORT int Mobot_moveJointToAbs(br_comms_t* comms, robotJointId_t id, double angle);
DLLIMPORT int Mobot_moveJointToDirect(br_comms_t* comms, robotJointId_t id, double angle);
DLLIMPORT int Mobot_moveJointToNB(br_comms_t* comms, robotJointId_t id, double angle);
DLLIMPORT int Mobot_moveJointToAbsNB(br_comms_t* comms, robotJointId_t id, double angle);
DLLIMPORT int Mobot_moveJointToDirectNB(br_comms_t* comms, robotJointId_t id, double angle);
DLLIMPORT int Mobot_moveJointWait(br_comms_t* comms, robotJointId_t id);
DLLIMPORT int Mobot_moveTo(br_comms_t* comms,
                               double angle1,
                               double angle2,
                               double angle3,
                               double angle4);
DLLIMPORT int Mobot_moveToAbs(br_comms_t* comms,
                               double angle1,
                               double angle2,
                               double angle3,
                               double angle4);
DLLIMPORT int Mobot_moveToDirect(br_comms_t* comms,
                               double angle1,
                               double angle2,
                               double angle3,
                               double angle4);
DLLIMPORT int Mobot_moveToNB(br_comms_t* comms,
                               double angle1,
                               double angle2,
                               double angle3,
                               double angle4);
DLLIMPORT int Mobot_moveToAbsNB(br_comms_t* comms,
                               double angle1,
                               double angle2,
                               double angle3,
                               double angle4);
DLLIMPORT int Mobot_moveToDirectNB(br_comms_t* comms,
                               double angle1,
                               double angle2,
                               double angle3,
                               double angle4);
DLLIMPORT int Mobot_moveToZero(br_comms_t* comms);
DLLIMPORT int Mobot_moveToZeroNB(br_comms_t* comms);
DLLIMPORT int Mobot_moveWait(br_comms_t* comms);
DLLIMPORT int Mobot_recordAngle(br_comms_t* comms, 
                                robotJointId_t id, 
                                double* time, 
                                double* angle, 
                                int num, 
                                double timeInterval);
DLLIMPORT int Mobot_recordAngles(br_comms_t* comms, 
                                 double *time, 
                                 double* angle1, 
                                 double* angle2,
                                 double* angle3,
                                 double* angle4,
                                 int num,
                                 double timeInterval);
DLLIMPORT int Mobot_recordWait(br_comms_t* comms);
DLLIMPORT int Mobot_setJointDirection(br_comms_t* comms, robotJointId_t id, robotJointState_t dir);
DLLIMPORT int Mobot_setJointSafetyAngle(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_setJointSafetyAngleTimeout(br_comms_t* comms, double seconds);
DLLIMPORT int Mobot_setJointSpeed(br_comms_t* comms, robotJointId_t id, double speed);
DLLIMPORT int Mobot_setJointSpeedRatio(br_comms_t* comms, robotJointId_t id, double ratio);
DLLIMPORT int Mobot_setJointSpeeds(br_comms_t* comms, 
                                   double speeds1, 
                                   double speeds2, 
                                   double speeds3, 
                                   double speeds4);
DLLIMPORT int Mobot_setJointSpeedRatios(br_comms_t* comms, 
                                        double ratio1, 
                                        double ratio2, 
                                        double ratio3, 
                                        double ratio4);
DLLIMPORT int Mobot_getJointSpeeds(br_comms_t* comms, 
                                   double *speed1, 
                                   double *speed2, 
                                   double *speed3, 
                                   double *speed4);
DLLIMPORT int Mobot_setMotorPower(br_comms_t* comms, robotJointId_t id, int power);
DLLIMPORT int Mobot_setTwoWheelRobotSpeed(br_comms_t* comms, double speed, double radius, char unit[]);
DLLIMPORT int Mobot_stop(br_comms_t* comms);
DLLIMPORT int Mobot_moveJointToPIDNB(br_comms_t* comms, robotJointId_t id, double angle);
*/
/* compound motion functions */
/*
DLLIMPORT int Mobot_motionArch(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionInchwormLeft(br_comms_t* comms, int num);
DLLIMPORT int Mobot_motionInchwormRight(br_comms_t* comms, int num);
DLLIMPORT int Mobot_motionRollBackward(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionRollForward(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionSkinny(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionStand(br_comms_t* comms);
DLLIMPORT int Mobot_motionTumbleRight(br_comms_t* comms, int num);
DLLIMPORT int Mobot_motionTumbleLeft(br_comms_t* comms, int num);
DLLIMPORT int Mobot_motionTurnLeft(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionTurnRight(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionUnstand(br_comms_t* comms);
*/

/* Non-Blocking compound motion functions */
/*
DLLIMPORT int Mobot_motionArchNB(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionInchwormLeftNB(br_comms_t* comms, int num);
DLLIMPORT int Mobot_motionInchwormRightNB(br_comms_t* comms, int num);
DLLIMPORT int Mobot_motionRollBackwardNB(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionRollForwardNB(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionSkinnyNB(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionStandNB(br_comms_t* comms);
DLLIMPORT int Mobot_motionTumbleRightNB(br_comms_t* comms, int num);
DLLIMPORT int Mobot_motionTumbleLeftNB(br_comms_t* comms, int num);
DLLIMPORT int Mobot_motionTurnLeftNB(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionTurnRightNB(br_comms_t* comms, double angle);
DLLIMPORT int Mobot_motionUnstandNB(br_comms_t* comms);
DLLIMPORT int Mobot_motionWait(br_comms_t* comms);
*/

/* Utility Functions */
int SendToIMobot(br_comms_t* comms, uint8_t cmd, const void* data, int datasize);
int RecvFromIMobot(br_comms_t* comms, uint8_t* buf, int size);
void* commsEngine(void* arg);
void* callbackThread(void* arg);

#endif /* Not _CH_ */

#ifdef _WIN32
typedef struct bdaddr_s {
  UINT8 b[6];
} bdaddr_t;
int strToba(const char *str, bdaddr_t *ba);
void baSwap(bdaddr_t *dst, const bdaddr_t *src);
#endif

/* Hide all of the C-style structs and API from CH */
#ifndef C_ONLY
#ifdef __cplusplus
}
#endif
#endif


#endif
