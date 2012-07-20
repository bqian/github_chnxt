#include "../nxt.h"
#include <ch.h>

EXPORTCH void ChNXT_ChNXT_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *c = new ChNXT();

    Ch_VaStart(interp, ap, varg);
    Ch_CppChangeThisPointer(interp, c, sizeof(ChNXT));
    Ch_VaEnd(interp, ap);
}

EXPORTCH void ChNXT_dChNXT_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *c;

    Ch_VaStart(interp, ap, varg);
    c = Ch_VaArg(interp, ap, class ChNXT *);
    if(Ch_CppIsArrayElement(interp))
	c->~ChNXT();
    else
	delete c;
    Ch_VaEnd(interp, ap);
    return;
}

EXPORTCH int connect_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->connect();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int connectWithAddress_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    char *usr_addr;
    int channel;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    usr_addr = Ch_VaArg(interp, ap, char *);
    channel = Ch_VaArg(interp, ap, int);
    retval = chnxt->connectWithAddress(usr_addr, channel);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int disconnect_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->disconnect();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setJointZero_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = chnxt->setJointZero(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setJointZeros_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->setJointZeros();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointContinuousNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    nxtJointState_t dir;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    dir = Ch_VaArg(interp, ap, nxtJointState_t);
    retval = chnxt->moveJointContinuousNB(id, dir);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveJointNB(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointToNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveJointToNB(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle1;
    double angle2;
    double angle3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle1 = Ch_VaArg(interp, ap, double);
    angle2 = Ch_VaArg(interp, ap, double);
    angle3 = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveNB(angle1, angle2, angle3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveToNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle1;
    double angle2;
    double angle3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle1 = Ch_VaArg(interp, ap, double);
    angle2 = Ch_VaArg(interp, ap, double);
    angle3 = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveToNB(angle1, angle2, angle3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveToZeroNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->moveToZeroNB();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJoint_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveJoint(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointTo_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveJointTo(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int move_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle1;
    double angle2;
    double angle3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle1 = Ch_VaArg(interp, ap, double);
    angle2 = Ch_VaArg(interp, ap, double);
    angle3 = Ch_VaArg(interp, ap, double);
    retval = chnxt->move(angle1, angle2, angle3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveTo_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle1;
    double angle2;
    double angle3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle1 = Ch_VaArg(interp, ap, double);
    angle2 = Ch_VaArg(interp, ap, double);
    angle3 = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveTo(angle1, angle2, angle3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveToZero_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->moveToZero();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveContinuousNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointState_t dir1;
    nxtJointState_t dir2;
    nxtJointState_t dir3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    dir1 = Ch_VaArg(interp, ap, nxtJointState_t);
    dir2 = Ch_VaArg(interp, ap, nxtJointState_t);
    dir3 = Ch_VaArg(interp, ap, nxtJointState_t);
    retval = chnxt->moveContinuousNB(dir1, dir2, dir3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveContinuousTime_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointState_t dir1;
    nxtJointState_t dir2;
    nxtJointState_t dir;
    double seconds;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    dir1 = Ch_VaArg(interp, ap, nxtJointState_t);
    dir2 = Ch_VaArg(interp, ap, nxtJointState_t);
    dir = Ch_VaArg(interp, ap, nxtJointState_t);
    seconds = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveContinuousTime(dir1, dir2, dir, seconds);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveJointWait_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = chnxt->moveJointWait(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveWait_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->moveWait();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int isConnected_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->isConnected();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int isMoving_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->isMoving();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int isJointMoving_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = chnxt->isJointMoving(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointAngle_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    double *angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    angle = Ch_VaArg(interp, ap, double*);
    retval = chnxt->getJointAngle(id, *angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointSpeedRatio_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    double *ratio;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    ratio = Ch_VaArg(interp, ap, double *);
    retval = chnxt->getJointSpeedRatio(id, *ratio);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointSpeedRatios_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double *ratio1;
    double *ratio2;
    double *ratio3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    ratio1 = Ch_VaArg(interp, ap, double *);
    ratio2 = Ch_VaArg(interp, ap, double *);
    ratio3 = Ch_VaArg(interp, ap, double *);
    retval = chnxt->getJointSpeedRatios(*ratio1, *ratio2, *ratio3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getJointState_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    int *status;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    status = Ch_VaArg(interp, ap, int *);
    retval = chnxt->getJointState(id, *status);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopOneJoint_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = chnxt->stopOneJoint(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopTwoJoints_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id1;
    nxtJointId_t id2;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id1 = Ch_VaArg(interp, ap, nxtJointId_t);
    id2 = Ch_VaArg(interp, ap, nxtJointId_t);
    retval = chnxt->stopTwoJoints(id1, id2);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopAllJoints_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->stopAllJoints();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopMotion_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->stopMotion();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setSensor_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtSensorId_t id;
    nxtSensorType_t type;
    nxtSensorMode_t mode;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtSensorId_t);
    type = Ch_VaArg(interp, ap, nxtSensorType_t);
    mode = Ch_VaArg(interp, ap, nxtSensorMode_t);
    retval = chnxt->setSensor(id, type, mode);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getSensor_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtSensorId_t id;
    int *value;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtSensorId_t);
    value = Ch_VaArg(interp, ap, int *);
    retval = chnxt->getSensor(id, *value);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setJointSpeedRatio_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtJointId_t id;
    double ratio;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtJointId_t);
    ratio = Ch_VaArg(interp, ap, double);
    retval = chnxt->setJointSpeedRatio(id, ratio);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setJointSpeedRatios_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double ratio1;
    double ratio2;
    double ratio3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    ratio1 = Ch_VaArg(interp, ap, double);
    ratio2 = Ch_VaArg(interp, ap, double);
    ratio3 = Ch_VaArg(interp, ap, double);
    retval = chnxt->setJointSpeedRatios(ratio1, ratio2, ratio3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRollForwardNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->vehicleRollForwardNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRollBackwardNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->vehicleRollBackwardNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRotateLeftNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->vehicleRotateLeftNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRotateRightNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->vehicleRotateRightNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int humanoidWalkForwardNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->humanoidWalkForwardNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int humanoidWalkBackwardNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->humanoidWalkBackwardNB(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRollForward_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->vehicleRollForward(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRollBackward_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->vehicleRollBackward(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRotateLeft_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->vehicleRotateLeft(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleRotateRight_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->vehicleRotateRight(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int vehicleMotionWait_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->vehicleMotionWait();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int humanoidWalkForward_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->humanoidWalkForward(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int humanoidWalkBackward_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->humanoidWalkBackward(angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int humanoidMotionWait_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->vehicleMotionWait();
    Ch_VaEnd(interp, ap);
    return retval;
}
