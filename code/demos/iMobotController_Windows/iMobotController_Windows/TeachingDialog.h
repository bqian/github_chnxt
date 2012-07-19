#pragma once
#include "robotManager.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "ListCtrlCtx.h"
#include "Resource.h"

#ifdef __cplusplus
extern "C" {
#endif

void* playThread(void *arg);

#ifdef __cplusplus
}
#endif


// CTeachingDialog dialog

class CTeachingDialog : public CDialog
{
	DECLARE_DYNAMIC(CTeachingDialog)

public:
	CTeachingDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTeachingDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_TEACHING };
  static RobotManager _robotManager;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl listctrl_availableBots;
	CListCtrl listctrl_connectedBots;
	CListCtrlCtx listctrl_recordedMotions;
	CEdit edit_teachingDelay;
	CButton button_teachingLoopCheck;
	afx_msg void OnBnClickedButtonTeachingConnect();
	afx_msg void OnBnClickedButtonTeachingMoveup();
	afx_msg void OnBnClickedButtonTeachingMovedown();
	afx_msg void OnBnClickedButtonTeachingDisconnect();
	afx_msg void OnBnClickedButtonTeachingRecord();
	afx_msg void OnBnClickedButtonTeachingAdddelay();
	afx_msg void OnBnClickedButtonTeachingDeletepos();
	void DeleteRecordedMotion(int index);
	afx_msg void OnBnClickedButtonTeachingSave();
	void refresh();
	void refreshRecordedMotions(int highlightedIndex);
	afx_msg void OnBnClickedButtonplay();
	RobotManager* getRobotManager();
	CButton button_play;
	CButton button_stop;
  CButton button_clear;
	afx_msg void OnBnClickedButtonstop();
  afx_msg void OnBnClickedButtonclear();
	int haltPlayFlag; /* If this flag is enabled, the current 
					  "play" operation should be canceled. */
  int isPlaying;
	afx_msg void OnLvnItemchangedListRecordedmotions(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateListRecordedmotions(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeleditListRecordedmotions(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListRecordedmotions(NMHDR *pNMHDR, LRESULT *pResult);
	static void OnRecordedMotionContextMenu(CPoint point, void *arg);
	int contextMenuIndex;
	afx_msg void OnContextRename();
	afx_msg void OnContextRemove();
  afx_msg void OnRecordPopupMoveup();
  afx_msg void OnRecordPopupMovedown();
  afx_msg void OnRecordedGotopose();
  static void OnMobotButton(CMobot *robot, int button, int buttonDown);
};

extern CTeachingDialog *g_teachingDialog;
