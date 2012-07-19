#include "StdAfx.h"
#include "RecordMobot.h"

CRecordMobot::CRecordMobot(TCHAR *name)
{
	_numMotions = 0;
	_motions = (struct motion_s**)malloc(sizeof(struct motion_s*) * 100);
	_numMotionsAllocated = 100;
	_tcscpy(_name, name);
}

CRecordMobot::~CRecordMobot(void)
{
	free(_motions);
}

int CRecordMobot::connectWithAddress(const char address[], int channel)
{
  strcpy(_address, address);
  return CMobot::connectWithAddress(address, channel);
}

const char* CRecordMobot::getAddress()
{
  return _address;
}

int CRecordMobot::record(void)
{
	/* Get the robots positions */
	double angles[4];
	getJointAnglesAbs(angles[0], angles[1], angles[2], angles[3]);
	struct motion_s* motion;
	motion = (struct motion_s*)malloc(sizeof(struct motion_s));
	motion->motionType = MOTION_POS;
	motion->data.pos[0] = angles[0];
	motion->data.pos[1] = angles[1];
	motion->data.pos[2] = angles[2];
	motion->data.pos[3] = angles[3];
	motion->name = _tcsdup(TEXT("Pose"));
	_motions[_numMotions] = motion;
	_numMotions++;
	
	return 0;
}

int CRecordMobot::addDelay(double seconds)
{
	struct motion_s* motion;
	motion = (struct motion_s*)malloc(sizeof(struct motion_s));
	motion->motionType = MOTION_SLEEP;
	motion->data.sleepDuration = seconds;
	motion->name = _tcsdup(TEXT("Delay"));
	_motions[_numMotions] = motion;
	_numMotions++;
	return 0;
}

int CRecordMobot::play(int index)
{
	if (index < 0 || index >= _numMotions) {
		return -1;
	}
	if(_motions[index]->motionType == MOTION_POS) {
		return moveToAbsNB(
			_motions[index]->data.pos[0],
			_motions[index]->data.pos[1],
			_motions[index]->data.pos[2],
			_motions[index]->data.pos[3]
		);
	} else if (_motions[index]->motionType == MOTION_SLEEP) {
		Sleep(_motions[index]->data.sleepDuration * 1000);
		return 0;
	}
}

int CRecordMobot::getMotionType(int index)
{
	if (index < 0 || index >= _numMotions) {
		return -1;
	}
	return _motions[index]->motionType;
}

int CRecordMobot::getMotionString(int index, TCHAR* buf)
{
  switch(_motions[index]->motionType) {
    case MOTION_POS:
      swprintf(buf, TEXT("%s.moveToNB(%.2lf, %.2lf, %.2lf, %.2lf);"),
          _name,
          _motions[index]->data.pos[0],
          _motions[index]->data.pos[1],
          _motions[index]->data.pos[2],
          _motions[index]->data.pos[3] );
      break;
    case MOTION_SLEEP:
      swprintf(buf, TEXT("msleep(%d);"), (int)(_motions[index]->data.sleepDuration * 1000));
      break;
  }
	return 0;
}

const TCHAR* CRecordMobot::getMotionName(int index)
{
	if(index < 0 || index >= _numMotions) {
		return NULL;
	}
	return _motions[index]->name;
}

int CRecordMobot::setMotionName(int index, const TCHAR* name)
{
	if(index < 0 || index >= _numMotions) {
		return -1;
	}
	free (_motions[index]->name);
	_motions[index]->name = _tcsdup(name);
	return 0;
}

int CRecordMobot::removeMotion(int index, bool releaseData)
{
	if(index < 0 || index >= numMotions()) {
		return -1;
	}
	/* Free the motion */
  if(releaseData) {
    free(_motions[index]);
  }
	/* Shift everything lower than the motion up by one */
	int i;
	for(i = index+1; i < _numMotions; i++) {
		_motions[i-1] = _motions[i];
	}
	_numMotions--;
	return 0;
}

int CRecordMobot::clearAllMotions()
{
  int i;
  for(i = 0; i < _numMotions; i++) {
    free(_motions[i]);
  }
  _numMotions = 0;
  return 0;
}

int CRecordMobot::moveMotion(int fromindex, int toindex)
{
  if(fromindex < 0 || fromindex >= _numMotions) {
    return -1;
  }
  if(toindex < 0 || toindex >= _numMotions) {
    return -1;
  }
  if(fromindex == toindex) {
    return 0;
  }
  /* Save the motion at fromindex */
  struct motion_s* motion = _motions[fromindex];
  /* Now, remove _motions[fromindex] */
  removeMotion(fromindex, false);
  //if(toindex > fromindex) {toindex--;}
  /* Make a space for the new motion at 'toindex' */
  int i;
  for(i = _numMotions - 1; i >= toindex; i--) {
    _motions[i+1] = _motions[i];
  }
  _motions[toindex] = motion;
  _numMotions++;
  
  return 0;
}

int CRecordMobot::numMotions()
{
	return _numMotions;
}
