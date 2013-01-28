// iMobotController_WindowsDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "gait.h"
#include <mobot.h>
#include <nxt.h>
#include "afxcmn.h"
#include <math.h>

#define IDT_TIMER1 100

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef enum button_e
{
//  B_PLAY, // Play Gait
  B_M1F, // Motor forward
  B_M2F,
  B_M3F,
//  B_M4F,
  B_M1S, // Motor stop
  B_M2S,
  B_M3S,
//  B_M4S,
  B_M1B, // Motor Backward
  B_M2B,
  B_M3B,
//  B_M4B,
  B_FORWARD, // Roll commands
  B_STOP,
  B_LEFT,
  B_RIGHT,
  B_BACK,
  B_WALKFOR, // Walk commands
  B_WALKSTOP,
  B_WALKBACK,
  B_ARMUP,   // machine commands
  B_ARMDOWN,
  B_ARMLEFT,
  B_ARMRIGHT,
  B_ARMSTOP,
  B_CLAWOPEN,
  B_CLAWCLOSE,
  S_M1S, // Sliders, motor 1 speed
  S_M2S,
  S_M3S,
//  S_M4S,
  S_M1P, // Motor position sliders
  S_M2P, 
  S_M3P, 
//  S_M4P, 
  B_SETPOS,
  B_MOVE,
  B_SETSPD,
  B_RESETTOZERO,
  B_MOVETOZERO,
  B_NUMBUTTONS
} buttonId_t;

// CiMobotController_WindowsDlg dialog
class CiMobotController_WindowsDlg : public CDialog
{
public:
// Construction
	CiMobotController_WindowsDlg(CWnd* pParent = NULL);	// motionStandard constructor

// Dialog Data
	enum { IDD = IDD_IMOBOTCONTROLLER_WINDOWS_DIALOG };

	CMobot iMobotComms;
	ChNXT nxtComms;
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	bool isConnected;
	Gait* m_gaits[50];
	int m_numGaits;
public:
  int m_positions[4]; // Store last known slider position
  int m_speeds[4];    // Store last known slider position
  int m_clawStatus;   // Store last known claw status
  double m_speedRatios[3]; // Store last known slider position
  void InitIcons();
  void InitGaits();
  void InitSliders();
  void InitSensorComboBox();
  void UpdateSliders();
  void UpdateSpeedSliders(int i, double speed);
  void UpdateSensorValues();
  void SetAsDisconnected(void);
//  void UpdateSpeedSliders(int i, double speedRatio);
  int addGait(Gait* gait);
  int poseJoints(const double *angles, unsigned char motorMask);
  int moveJoints(const double *angles, unsigned char motorMask);
//  int addSensor(char sensorType[]);
  
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	CButton m_button_Motor1Forward;
	CButton m_button_Motor2Forward;
	CButton m_button_Motor3Forward;
	CButton m_button_Motor1Stop;
	CButton m_button_Motor2Stop;
	CButton m_button_Motor3Stop;
	CButton m_button_Motor1Backward;
	CButton m_button_Motor2Backward;
	CButton m_button_Motor3Backward;
	CListBox m_list_gaits;
	CEdit m_edit_Motor1Position;
	CEdit m_edit_Motor2Position;
	CEdit m_edit_Motor3Position;
public:
	CEdit *m_edit_MotorPositions[4];
	CEdit *m_edit_MotorSpeeds[4];
	CEdit m_edit_Address;
	CEdit m_edit_Channel;
	CSliderCtrl m_slider_Speed1;
	CSliderCtrl m_slider_Speed2;
	CSliderCtrl m_slider_Speed3;
	CSliderCtrl *m_slider_Speeds[4];
	CSliderCtrl m_slider_Position1;
	CSliderCtrl m_slider_Position2;
	CSliderCtrl m_slider_Position3;
	CSliderCtrl *m_slider_Positions[4];
//	afx_msg void OnBnClickedButtonplay();
//  void handlerPlay(void);
	afx_msg void OnBnClickedButtonconnect();
	afx_msg void OnLbnSelchangeListgaits();
	// Picture of the iMobot joints
	CStatic m_staticicon_iMobotPicture;
	afx_msg void OnStnClickedStaticImobotPicture();
	CButton m_button_rollForward;
	CButton m_button_rollStop;
	CButton m_button_rollBack;
	CButton m_button_rollLeft;
	CButton m_button_rollRight;
	afx_msg void OnBnClickedButtonMotor1forward();
	afx_msg void OnBnClickedButtonMotor2forward();
	afx_msg void OnBnClickedButtonMotor3forward();
//	afx_msg void OnBnClickedButtonMotor4forward();
  void handlerM1F();
  void handlerM2F();
  void handlerM3F();
	afx_msg void OnBnClickedButtonMotor1stop();
	afx_msg void OnBnClickedButtonMotor2stop();
	afx_msg void OnBnClickedButtonMotor3stop();
  void handlerM1S();
  void handlerM2S();
  void handlerM3S();
	afx_msg void OnBnClickedButtonMotor1backward();
	afx_msg void OnBnClickedButtonMotor2backward();
	afx_msg void OnBnClickedButtonMotor3backward();
  void handlerM1B();
  void handlerM2B();
  void handlerM3B();
	afx_msg void OnBnClickedButtonrollforward();
	afx_msg void OnBnClickedButtonrollstop();
	afx_msg void OnBnClickedButtonrollleft();
	afx_msg void OnBnClickedButtonrollright();
	afx_msg void OnBnClickedButtonrollback();
  void handlerFORWARD();
  void handlerSTOP();
  void handlerLEFT();
  void handlerRIGHT();
  void handlerBACK();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void OnOK();


// Implementation
//protected:

public:
	afx_msg void OnNMCustomdrawSliderposition2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTRBNThumbPosChangingSliderposition2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTRBNThumbPosChangingSliderposition1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTRBNThumbPosChangingSliderposition3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTRBNThumbPosChangingSliderposition4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRobotConfigurerobotbluetooth();
	CEdit m_edit_MotorSpeed1;
	CEdit m_edit_MotorSpeed2;
	CEdit m_edit_MotorSpeed3;
	CEdit m_edit_setpos1;
	CEdit m_edit_setpos2;
	CEdit m_edit_setpos3;
	afx_msg void OnBnClickedButtonGopos();
	void handlerSETPOS();
	afx_msg void OnRobotConnecttoarobot();
	afx_msg void OnConnectDisconnectfromrobot();
	afx_msg void OnHelpHelp();
	afx_msg void OnHelpAboutrobotcontroller();
	afx_msg void OnFileExit();
    afx_msg void OnBnClickedButtonResettozero();
	afx_msg void OnBnClickedButtonMovetozero();
	void handlerRESETTOZERO();
    void handlerMOVETOZERO();
    afx_msg void OnBnClickedButtonSetspd();
  void handlerSETSPD();
  CEdit m_edit_setspd1;
  CEdit m_edit_setspd2;
  CEdit m_edit_setspd3;
  afx_msg void OnBnClickedButtonMove();
  void handlerMOVE();
  afx_msg void OnHelpDemos();
//  afx_msg void OnTeachingmodeTeachingmodedialog();
  afx_msg void OnNMCustomdrawSliderposition1(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMCustomdrawSliderspeed1(NMHDR *pNMHDR, LRESULT *pResult);
  CComboBox m_combo_Sensor1type;
  CComboBox m_combo_Sensor2type;
  CComboBox m_combo_Sensor3type;
  CComboBox m_combo_Sensor4type;
  CComboBox *m_combo_SensorTypes[4];
  CEdit m_edit_Sensor1value;
  CEdit m_edit_Sensor2value;
  CEdit m_edit_Sensor3value;
  CEdit m_edit_Sensor4value;
  CEdit *m_edit_SensorValues[4];
  void handlerSETSENSOR(int i);
  afx_msg void OnCbnSelchangeComboSensor1type();
  afx_msg void OnCbnSelchangeComboSensor2type();
  afx_msg void OnCbnSelchangeComboSensor3type();
  afx_msg void OnCbnSelchangeComboSensor4type();
  /*
  afx_msg void OnCbnEditupdateComboSensor1type();
  afx_msg void OnCbnEditupdateComboSensor2type();
  afx_msg void OnCbnEditupdateComboSensor3type();
  afx_msg void OnCbnEditupdateComboSensor4type();
  */
/*
  afx_msg void OnBnClickedButtonrotateright();
  afx_msg void OnBnClickedButtonrotateleft();
  afx_msg void OnBnClickedButtonrotatestop();
  CButton m_button_rotateLeft;
  CButton m_button_rotateStop;
  CButton m_button_rotateRight;
  */
  afx_msg void OnBnClickedButtonwalkforward();
  afx_msg void OnBnClickedButtonwalkstop();
  afx_msg void OnBnClickedButtonwalkbackward();
  void handlerWALKFOR(void);
  void handlerWALKSTOP(void);
  void handlerWALKBACK(void);
  CButton m_button_walkForward;
  CButton m_button_walkStop;
  CButton m_button_walkBackward;
  afx_msg void OnStnClickedStaticMachine();
  CButton m_botton_moveArmUp;
  CButton m_botton_moveStop;
  CButton m_botton_moveArmDown;
  CButton m_botton_rotateArmLeft;
  CButton m_botton_rotateArmRight;
  afx_msg void OnBnClickedButtonmovearmup();
  afx_msg void OnBnClickedButtonrotatearmleft();
  afx_msg void OnBnClickedButtonmovestop();
  afx_msg void OnBnClickedButtonrotatearmright();
  afx_msg void OnBnClickedButtonmovearmdown();
  void handlerARMUP();
  void handlerARMDOWN();
  void handlerARMLEFT();
  void handlerARMRIGHT();
  afx_msg void OnBnClickedRadioclawopen();
  afx_msg void OnBnClickedRadioclawclose();
  void handlerCLAWCLOSE();
  void handlerCLAWOPEN();
  CStatic m_static_connectionStatus;
private:
	CBitmap BmpConnected;
	CBitmap BmpDisconnected;
};

DWORD WINAPI HandlerThread(void*);

typedef struct buttonState_s
{
  int clicked;
  void (CiMobotController_WindowsDlg::*handlerFunc)(void);
} buttonState_t;

extern buttonState_t g_buttonState[B_NUMBUTTONS];

typedef struct comboBoxState_s
{
	int changed;
	void (CiMobotController_WindowsDlg::*handlerFunc)(void);
} comboBoxState_t;

extern comboBoxState_t g_comboBoxState[4];