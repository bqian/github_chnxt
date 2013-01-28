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

EXPORTCH int setMotorToZero_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    retval = chnxt->setMotorToZero(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setMotorZeros_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->setMotorZeros();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setToZeros_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->setToZeros();
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveMotorContinuousNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    nxtMotorState_t dir;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    dir = Ch_VaArg(interp, ap, nxtMotorState_t);
    retval = chnxt->moveMotorContinuousNB(id, dir);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveMotorNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveMotorNB(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveMotorToNB_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveMotorToNB(id, angle);
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

EXPORTCH int moveMotor_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveMotor(id, angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveMotorTo_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    double angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    angle = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveMotorTo(id, angle);
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
    nxtMotorState_t dir1;
    nxtMotorState_t dir2;
    nxtMotorState_t dir3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    dir1 = Ch_VaArg(interp, ap, nxtMotorState_t);
    dir2 = Ch_VaArg(interp, ap, nxtMotorState_t);
    dir3 = Ch_VaArg(interp, ap, nxtMotorState_t);
    retval = chnxt->moveContinuousNB(dir1, dir2, dir3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveContinuousTime_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorState_t dir1;
    nxtMotorState_t dir2;
    nxtMotorState_t dir;
    double seconds;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    dir1 = Ch_VaArg(interp, ap, nxtMotorState_t);
    dir2 = Ch_VaArg(interp, ap, nxtMotorState_t);
    dir = Ch_VaArg(interp, ap, nxtMotorState_t);
    seconds = Ch_VaArg(interp, ap, double);
    retval = chnxt->moveContinuousTime(dir1, dir2, dir, seconds);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int moveMotorWait_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    retval = chnxt->moveMotorWait(id);
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

/*EXPORTCH int isMotorMoving_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    retval = chnxt->isMotorMoving(id);
    Ch_VaEnd(interp, ap);
    return retval;
}*/

EXPORTCH int getMotorAngle_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    double *angle;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    angle = Ch_VaArg(interp, ap, double*);
    retval = chnxt->getMotorAngle(id, *angle);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getMotorSpeed_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    int *speed;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    speed = Ch_VaArg(interp, ap, int *);
    retval = chnxt->getMotorSpeed(id, *speed);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getMotorSpeeds_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int *speed1;
    int *speed2;
    int *speed3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    speed1 = Ch_VaArg(interp, ap, int *);
    speed2 = Ch_VaArg(interp, ap, int *);
    speed3 = Ch_VaArg(interp, ap, int *);
    retval = chnxt->getMotorSpeeds(*speed1, *speed2, *speed3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getMotorSpeedRatio_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    double *ratio;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    ratio = Ch_VaArg(interp, ap, double *);
    retval = chnxt->getMotorSpeedRatio(id, *ratio);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getMotorSpeedRatios_chdl(void *varg) {
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
    retval = chnxt->getMotorSpeedRatios(*ratio1, *ratio2, *ratio3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int getMotorState_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    int *status;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    status = Ch_VaArg(interp, ap, int *);
    retval = chnxt->getMotorState(id, *status);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopOneMotor_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    retval = chnxt->stopOneMotor(id);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopTwoMotors_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id1;
    nxtMotorId_t id2;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id1 = Ch_VaArg(interp, ap, nxtMotorId_t);
    id2 = Ch_VaArg(interp, ap, nxtMotorId_t);
    retval = chnxt->stopTwoMotors(id1, id2);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int stopAllMotors_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    retval = chnxt->stopAllMotors();
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

EXPORTCH int setMotorSpeed_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    int speed;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    speed = Ch_VaArg(interp, ap, int);
    retval = chnxt->setMotorSpeed(id, speed);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setMotorSpeeds_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    int speed1;
    int speed2;
    int speed3;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    speed1 = Ch_VaArg(interp, ap, int);
    speed2 = Ch_VaArg(interp, ap, int);
    speed3 = Ch_VaArg(interp, ap, int);
    retval = chnxt->setMotorSpeeds(speed1, speed2, speed3);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setMotorSpeedRatio_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
    class ChNXT *chnxt;
    nxtMotorId_t id;
    double ratio;
    int retval;

    Ch_VaStart(interp, ap, varg);
    chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    id = Ch_VaArg(interp, ap, nxtMotorId_t);
    ratio = Ch_VaArg(interp, ap, double);
    retval = chnxt->setMotorSpeedRatio(id, ratio);
    Ch_VaEnd(interp, ap);
    return retval;
}

EXPORTCH int setMotorSpeedRatios_chdl(void *varg) {
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
    retval = chnxt->setMotorSpeedRatios(ratio1, ratio2, ratio3);
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

EXPORTCH int setTwoWheelRobotSpeed_chdl(void *varg) {
    ChInterp_t interp;
    ChVaList_t ap;
	class ChNXT *chnxt;
	
    nxtMotorId_t id;
    double speed, radius;
    int retval;

    Ch_VaStart(interp, ap, varg);
	chnxt = Ch_VaArg(interp, ap, class ChNXT *);
    speed = Ch_VaArg(interp, ap, double);
    radius = Ch_VaArg(interp, ap, double);
    retval = chnxt->setTwoWheelRobotSpeed(speed, radius);
    Ch_VaEnd(interp, ap);
    return retval;
}

