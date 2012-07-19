#include "gait.h"
#include <stdlib.h>

Motion::Motion(enum motion_type_e motion_type, double angles[4])
{
  int i;
  for(i = 0; i < 4; i++) {
    _angles[i] = angles[i];
  }
  _motion_type = motion_type;
}

Motion::Motion(enum motion_type_e motion_type, double angles[4], unsigned char motorMask)
{
  int i;
  for(i = 0; i < 4; i++) {
    _angles[i] = angles[i];
  }
  _motion_type = motion_type;
  _motor_mask = motorMask;
}

const double* Motion::getAngles() const
{
  return _angles;
}

enum motion_type_e Motion::getType() const
{
  return _motion_type;
}

Motion & Motion::operator= (const Motion &rhs)
{
  _motion_type = rhs._motion_type;
  for(int i = 0; i < 4; i++) {
    _angles[i] = rhs._angles[i];
  }
  _motor_mask = rhs._motor_mask;
  return *this;
}

#ifndef _WIN32
Gait::Gait(const char* name) 
#else
Gait::Gait(const WCHAR* name)
#endif
{
  _numMotions = 0;
  _motions = (Motion*)malloc(sizeof(Motion) * MOTION_ALLOC_SIZE);
  _numMotionsAllocated = MOTION_ALLOC_SIZE;
#ifndef _WIN32
  _name = strdup(name);
#else
  _name = (WCHAR*)malloc((wcslen(name)+1) * sizeof(WCHAR));
  wcscpy(_name, name);
#endif
}

int Gait::addMotion(Motion* motion)
{
  /* Allocated more space if needbe */
  if(_numMotions >= _numMotionsAllocated) {
    _numMotionsAllocated += MOTION_ALLOC_SIZE;
    _motions = (Motion*)realloc(_motions, _numMotionsAllocated);
  }

  _motions[_numMotions] = *motion;
  _numMotions++;

  return 0;
}

int Gait::getNumMotions()
{
  return _numMotions;
}

const Motion* Gait::getMotion(int index)
{
  if(index >= _numMotions || index < 0) {
    return NULL;
  } else {
    return &_motions[index];
  }
}
