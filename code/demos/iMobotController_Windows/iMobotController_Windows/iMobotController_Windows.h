// iMobotController_Windows.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CiMobotController_WindowsApp:
// See iMobotController_Windows.cpp for the implementation of this class
//

class CiMobotController_WindowsApp : public CWinApp
{
public:
	CiMobotController_WindowsApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CiMobotController_WindowsApp theApp;
