#ifndef _ROBOT_MANAGER_H_
#define _ROBOT_MANAGER_H_

#include <string.h>
#include <string>
//#include <atlstr.h>
#include <afx.h>

#include "configFile.h"
#include <mobot.h>
#include "RecordMobot.h"

#define MAX_CONNECTED 100
template class __declspec(dllimport) CStringT<TCHAR, StrTraitMFC<TCHAR, ChTraitsCRT<TCHAR> > >;
template class __declspec(dllimport) CSimpleStringT<TCHAR>;
using namespace std;
class RobotManager : public ConfigFile
{
  public:
    RobotManager();
    ~RobotManager();
    bool isConnected(int index);
    void setConnected(int index, bool connected);
    int connect(int availableIndex);
    int disconnect(int connectIndex);
    int moveUp(int connectIndex);
    int moveDown(int connectIndex);
    int numConnected();
    const char* getConnected(int connectIndex);
    int availableIndexToIndex(int index);
    int numAvailable();
    CRecordMobot* getMobot(int connectIndex);
    CString* generateProgram(bool looped = false);
  private:
    bool _connected[MAX_CONNECTED]; /* Index by ConfigFile */
    CRecordMobot *_mobots[MAX_CONNECTED];
    /* _connectAddresses is an array of pointers to 
       ConfigFile::_addresses */
    char *_connectedAddresses[MAX_CONNECTED];
};

#endif
