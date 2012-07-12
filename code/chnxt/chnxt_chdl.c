#include <chnxt.h>
#include <ch.h>

EXPORTCH int connect_chdl(void *varg) {
    int retval;
    retval = connect();
    return retval;
}

EXPORTCH int connectWithAddress_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    char *usr_addr;
    int channel;
    int retval;

    Ch_VaStart(interp, ap, varg);
    usr_addr = Ch_VaArg(interp, ap, char *);
    channel = Ch_VaArg(interp, ap, int);
    retval = connectWithAddress(usr_addr, channel);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int disconnect_chdl(void *varg) {
    int retval;
    retval = disconnect();
    return retval;
}

EXPORTCH int setJointZero_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = setJointZero(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setJointZeros_chdl(void *varg) {
    int retval;
    retval = setJointZeros();
    return retval;
}

EXPORTCH int moveJointContinuousNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    nxtJointState_t dir;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    dir = Ch_VaArg(interp, ap, nxtJointState_t);
    retval = moveJointContinuousNB(id, dir);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int degrees;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    degrees = Ch_VaArg(interp, ap, int);
    retval = moveJointNB(id, degrees);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointToNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    angle = Ch_VaArg(interp, ap, int);
    retval = moveJointToNB(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int degrees1;
    int degrees2;
    int degrees3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    degrees1 = Ch_VaArg(interp, ap, int);
    degrees2 = Ch_VaArg(interp, ap, int);
    degrees3 = Ch_VaArg(interp, ap, int);
    retval = moveNB(degrees1, degrees2, degrees3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveToNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle1;
    int angle2;
    int angle3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle1 = Ch_VaArg(interp, ap, int);
    angle2 = Ch_VaArg(interp, ap, int);
    angle3 = Ch_VaArg(interp, ap, int);
    retval = moveToNB(angle1, angle2, angle3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveToZeroNB_chdl(void *varg) {
    int retval;
    retval = moveToZeroNB();
    return retval;
}

EXPORTCH int moveJoint_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int degrees;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    degrees = Ch_VaArg(interp, ap, int);
    retval = moveJoint(id, degrees);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointTo_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    angle = Ch_VaArg(interp, ap, int);
    retval = moveJointTo(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int move_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle1;
    int angle2;
    int angle3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle1 = Ch_VaArg(interp, ap, int);
    angle2 = Ch_VaArg(interp, ap, int);
    angle3 = Ch_VaArg(interp, ap, int);
    retval = move(angle1, angle2, angle3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveTo_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle1;
    int angle2;
    int angle3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle1 = Ch_VaArg(interp, ap, int);
    angle2 = Ch_VaArg(interp, ap, int);
    angle3 = Ch_VaArg(interp, ap, int);
    retval = moveTo(angle1, angle2, angle3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveToZero_chdl(void *varg) {
    int retval;
    retval = moveToZero();
    return retval;
}

EXPORTCH int moveContinuousNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointState_t dir1;
    nxtJointState_t dir2;
    nxtJointState_t dir3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    dir1 = Ch_VaArg(interp, ap, nxtJointState_t);
    dir2 = Ch_VaArg(interp, ap, nxtJointState_t);
    dir3 = Ch_VaArg(interp, ap, nxtJointState_t);
    retval = moveContinuousNB(dir1, dir2, dir3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveContinuousTime_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointState_t dir1;
    nxtJointState_t dir2;
    nxtJointState_t dir;
    int millSeconds;
    int retval;

    Ch_VaStart(interp, ap, varg);
    dir1 = Ch_VaArg(interp, ap, nxtJointState_t);
    dir2 = Ch_VaArg(interp, ap, nxtJointState_t);
    dir = Ch_VaArg(interp, ap, nxtJointState_t);
    millSeconds = Ch_VaArg(interp, ap, int);
    retval = moveContinuousTime(dir1, dir2, dir, millSeconds);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointWait_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = moveJointWait(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveWait_chdl(void *varg) {
    int retval;
    retval = moveWait();
    return retval;
}

EXPORTCH int isConnected_chdl(void *varg) {
    int retval;
    retval = isConnected();
    return retval;
}

EXPORTCH int isMoving_chdl(void *varg) {
    int retval;
    retval = isMoving();
    return retval;
}

EXPORTCH int isJointMoving_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = isJointMoving(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointAngle_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int *angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    angle = Ch_VaArg(interp, ap, int *);
    retval = getJointAngle(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointSpeedRatio_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    double *ratio;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    ratio = Ch_VaArg(interp, ap, double *);
    retval = getJointSpeedRatio(id, ratio);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointSpeedRatios_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    double *ratio1;
    double *ratio2;
    double *ratio3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    ratio1 = Ch_VaArg(interp, ap, double *);
    ratio2 = Ch_VaArg(interp, ap, double *);
    ratio3 = Ch_VaArg(interp, ap, double *);
    retval = getJointSpeedRatios(ratio1, ratio2, ratio3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointState_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int *status;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    status = Ch_VaArg(interp, ap, int *);
    retval = getJointState(id, status);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopOneJoint_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = stopOneJoint(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopTwoJoints_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id1;
    nxtJointId_t id2;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id1 = Ch_VaArg(interp, ap, nxtJointId_t);
    id2 = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = stopTwoJoints(id1, id2);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopAllJoints_chdl(void *varg) {
    int retval;
    retval = stopAllJoints();
    return retval;
}

EXPORTCH int stopMotion_chdl(void *varg) {
    int retval;
    retval = stopMotion();
    return retval;
}

EXPORTCH int setSensor_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtSensorId_t id;
    nxtSensorType_t type;
    nxtSensorMode_t mode;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtSensorId_t);
    type = Ch_VaArg(interp, ap, nxtSensorType_t);
    mode = Ch_VaArg(interp, ap, nxtSensorMode_t);
    retval = setSensor(id, type, mode);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getSensor_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtSensorId_t id;
    int *value;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtSensorId_t);
    value = Ch_VaArg(interp, ap, int *);
    retval = getSensor(id, value);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointStates_chdl(void *varg) {
    int retval;
    retval = getJointStates();
    return retval;
}

EXPORTCH int setJointSpeedRatio_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    nxtJointId_t id;
    double ratio;
    int retval;

    Ch_VaStart(interp, ap, varg);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    ratio = Ch_VaArg(interp, ap, double);
    retval = setJointSpeedRatio(id, ratio);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setJointSpeedRatios_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    double ratio1;
    double ratio2;
    double ratio3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    ratio1 = Ch_VaArg(interp, ap, double);
    ratio2 = Ch_VaArg(interp, ap, double);
    ratio3 = Ch_VaArg(interp, ap, double);
    retval = setJointSpeedRatios(ratio1, ratio2, ratio3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleMoveForwardNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle = Ch_VaArg(interp, ap, int);
    retval = vehicleMoveForwardNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleMoveBackwardNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle = Ch_VaArg(interp, ap, int);
    retval = vehicleMoveBackwardNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRotateLeftNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle = Ch_VaArg(interp, ap, int);
    retval = vehicleRotateLeftNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRotateRightNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle = Ch_VaArg(interp, ap, int);
    retval = vehicleRotateRightNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleMoveForward_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle = Ch_VaArg(interp, ap, int);
    retval = vehicleMoveForward(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleMoveBackward_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle = Ch_VaArg(interp, ap, int);
    retval = vehicleMoveBackward(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRotateLeft_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle = Ch_VaArg(interp, ap, int);
    retval = vehicleRotateLeft(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRotateRight_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    int angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    angle = Ch_VaArg(interp, ap, int);
    retval = vehicleRotateRight(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleMotionWait_chdl(void *varg) {
    int retval;
    retval = vehicleMotionWait();
    return retval;
}
