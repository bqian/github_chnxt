#ifndef _GAIT_H_
#define _GAIT_H_
#include <mobot.h>

#define MOTION_ALLOC_SIZE 8

typedef enum motion_type_e {
  MOTION_POSE,
  MOTION_MOVE
} motion_type_t;

/* A Motion may be a pose or a move */
class Motion {
  public:
  Motion(enum motion_type_e motion_type, double angles[4]);
  Motion(enum motion_type_e motion_type, double angles[4], unsigned char motorMask);
  const double* getAngles() const;
  enum motion_type_e getType() const;
  inline unsigned char getMotorMask() const {return _motor_mask;}

  Motion & operator= (const Motion &rhs);

  private:
  motion_type_t _motion_type;
  double _angles[4];
  unsigned char _motor_mask;
};

class Gait {
  public:
#ifndef _WIN32
  Gait(const char* name);
#else
  Gait(const WCHAR* name);
#endif

  int addMotion(Motion *motion);
  int getNumMotions();
  const Motion* getMotion(int index);
#ifndef _WIN32
  inline const char* getName() {return _name;}
#else
  inline const WCHAR* getName() {return _name;}
#endif

  private:
  int _numMotions;
  int _numMotionsAllocated;

  Motion *_motions;
#ifndef _WIN32
  char* _name;
#else
  WCHAR* _name;
#endif

};

#endif
