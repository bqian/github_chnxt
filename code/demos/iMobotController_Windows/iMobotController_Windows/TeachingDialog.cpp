// TeachingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "iMobotController_Windows.h"
#include "TeachingDialog.h"

CTeachingDialog *g_teachingDialog;
RobotManager CTeachingDialog::_robotManager;
// CTeachingDialog dialog

IMPLEMENT_DYNAMIC(CTeachingDialog, CDialog)

CTeachingDialog::CTeachingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTeachingDialog::IDD, pParent)
{
  haltPlayFlag = 0;
  isPlaying = 0;
  char path[MAX_PATH];
  /* Read the config file */
  if(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path) != S_OK) 
  {
    /* Could not get the user's app data directory */
  } else {
    //MessageBox((LPCTSTR)path, (LPCTSTR)"Test");
    //fprintf(fp, "%s", path); 
  }
  strcat(path, "\\Barobo.config");
  _robotManager.read(path);
  listctrl_recordedMotions.setContextMenuCallback(&CTeachingDialog::OnRecordedMotionContextMenu, this);
}

CTeachingDialog::~CTeachingDialog()
{
}

void CTeachingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AVAILABLEBOTS, listctrl_availableBots);
	DDX_Control(pDX, IDC_LIST_CONNECTEDBOTS, listctrl_connectedBots);
	DDX_Control(pDX, IDC_LIST_RECORDEDMOTIONS, listctrl_recordedMotions);
	DDX_Control(pDX, IDC_EDIT_TEACHING_DELAY, edit_teachingDelay);
	DDX_Control(pDX, IDC_CHECK_TEACHING_LOOPED, button_teachingLoopCheck);
	/* Set up the list ctrls */
	listctrl_availableBots.InsertColumn(
		0, 
		TEXT("Mobot Address"),
		LVCFMT_LEFT,
		120,
		-1);
	listctrl_connectedBots.InsertColumn(
		0,
		TEXT("Mobot Address"),
		LVCFMT_LEFT,
		120,
		-1);
	listctrl_recordedMotions.InsertColumn(
		0,
		TEXT("Recorded Motions"),
		LVCFMT_LEFT,
		120,
		-1);
	//listctrl_availableBots.InsertItem(0, TEXT("Test Item"));
	refresh();
	DDX_Control(pDX, IDC_BUTTON_play, button_play);
	DDX_Control(pDX, IDC_BUTTON_stop, button_stop);
  DDX_Control(pDX, IDC_BUTTONCLEARALL, button_clear);
}


BEGIN_MESSAGE_MAP(CTeachingDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TEACHING_CONNECT, &CTeachingDialog::OnBnClickedButtonTeachingConnect)
	ON_BN_CLICKED(IDC_BUTTON_TEACHING_MOVEUP, &CTeachingDialog::OnBnClickedButtonTeachingMoveup)
	ON_BN_CLICKED(IDC_BUTTON_TEACHING_MOVEDOWN, &CTeachingDialog::OnBnClickedButtonTeachingMovedown)
	ON_BN_CLICKED(IDC_BUTTON_TEACHING_DISCONNECT, &CTeachingDialog::OnBnClickedButtonTeachingDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_TEACHING_RECORD, &CTeachingDialog::OnBnClickedButtonTeachingRecord)
	ON_BN_CLICKED(IDC_BUTTON_TEACHING_ADDDELAY, &CTeachingDialog::OnBnClickedButtonTeachingAdddelay)
	ON_BN_CLICKED(IDC_BUTTON_TEACHING_DELETEPOS, &CTeachingDialog::OnBnClickedButtonTeachingDeletepos)
	ON_BN_CLICKED(IDC_BUTTON_TEACHING_SAVE, &CTeachingDialog::OnBnClickedButtonTeachingSave)
	ON_BN_CLICKED(IDC_BUTTON_play, &CTeachingDialog::OnBnClickedButtonplay)
	ON_BN_CLICKED(IDC_BUTTON_stop, &CTeachingDialog::OnBnClickedButtonstop)
  ON_BN_CLICKED(IDC_BUTTONCLEARALL, &CTeachingDialog::OnBnClickedButtonclear)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_RECORDEDMOTIONS, &CTeachingDialog::OnLvnItemchangedListRecordedmotions)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_RECORDEDMOTIONS, &CTeachingDialog::OnLvnItemActivateListRecordedmotions)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_RECORDEDMOTIONS, &CTeachingDialog::OnLvnEndlabeleditListRecordedmotions)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_RECORDEDMOTIONS, &CTeachingDialog::OnNMRClickListRecordedmotions)
	ON_COMMAND(ID_RENAME_REMOVE, &CTeachingDialog::OnContextRename)
	ON_COMMAND(ID_RENAME_REMOVE32782, &CTeachingDialog::OnContextRemove)
  ON_COMMAND(ID_RECORDED_MOVEUP, &CTeachingDialog::OnRecordPopupMoveup)
  ON_COMMAND(ID_RECORDED_MOVEDOWN, &CTeachingDialog::OnRecordPopupMovedown)
  ON_COMMAND(ID_RECORDED_GOTOPOSE, &CTeachingDialog::OnRecordedGotopose)
END_MESSAGE_MAP()


// CTeachingDialog message handlers

void CTeachingDialog::OnBnClickedButtonTeachingConnect()
{
	// TODO: Add your control notification handler code here
	/* Get the selected item */
	int index;
	index = listctrl_availableBots.GetSelectionMark();
	if(index == -1) {
		return;
	}
	_robotManager.connect(index);
	refresh();
}

void CTeachingDialog::OnBnClickedButtonTeachingMoveup()
{
	int connectIndex = listctrl_connectedBots.GetSelectionMark();
	if(connectIndex == -1) {return;}
	if(connectIndex == 0) {return;}
	_robotManager.moveUp(connectIndex);
	refresh();
	listctrl_connectedBots.SetSelectionMark(connectIndex-1);
}

void CTeachingDialog::OnBnClickedButtonTeachingMovedown()
{
	int connectIndex = listctrl_connectedBots.GetSelectionMark();
	if(connectIndex == -1) {return;}
	if(connectIndex >= (_robotManager.numConnected()-1)) {return;}
	_robotManager.moveDown(connectIndex);
	refresh();
	listctrl_connectedBots.SetSelectionMark(connectIndex+1);
}

void CTeachingDialog::OnBnClickedButtonTeachingDisconnect()
{
	int connectIndex;
	connectIndex = listctrl_connectedBots.GetSelectionMark();
	if(connectIndex == -1) { return; }
	_robotManager.disconnect(connectIndex);
	refresh();
}

void CTeachingDialog::OnBnClickedButtonTeachingRecord()
{
	int i;
	for(i = 0; i < _robotManager.numConnected(); i++) {
		_robotManager.getMobot(i)->record();
	}
	refreshRecordedMotions(-1);
}

void CTeachingDialog::OnBnClickedButtonTeachingAdddelay()
{
	// TODO: Add your control notification handler code here
	TCHAR buf[80];
	edit_teachingDelay.GetLine(0, buf, 80);
	if(_tcslen(buf) <= 0) { return; }
	double delay;
	_stscanf(buf, TEXT("%lf"), &delay);
	if(delay <= 0) {return;}
	int i;
	for(i = 0; i < _robotManager.numConnected(); i++) {
		_robotManager.getMobot(i)->addDelay(delay);
	}
	refreshRecordedMotions(-1);
}

void CTeachingDialog::OnBnClickedButtonTeachingDeletepos()
{
	/* Get the highlighted line */
	int index;
	index = listctrl_recordedMotions.GetSelectionMark();
	if(index < 0) return;
	DeleteRecordedMotion(index);
}

void CTeachingDialog::DeleteRecordedMotion(int index)
{
	int i;
	for(i = 0; i < _robotManager.numConnected(); i++) {
		_robotManager.getMobot(i)->removeMotion(index);
	}
	refreshRecordedMotions(-1);
}

void CTeachingDialog::OnBnClickedButtonTeachingSave()
{
  bool looped;
  if(button_teachingLoopCheck.GetCheck() == BST_CHECKED) {
    looped = true;
  } else {
    looped = false;
  }
  /* Pop up the save file dialog */
  CFileDialog dlgFile(
      false,
      _T(".ch"),
      NULL,
      OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
      _T("Ch Programs (*.ch)|*.ch|Text Files|*.txt|All Files (*.*)|*.*||"));
  if( dlgFile.DoModal() == IDOK ) {
    CString pathname = dlgFile.GetPathName();
    FILE *fp = _tfopen((LPCTSTR)pathname, _T("w"));
    if(fp == NULL) {
			MessageBox( 
          TEXT("Could not save to file."), 
          TEXT("Error"), 
          MB_OK | MB_ICONINFORMATION );
      return;
    }
    CString *program = _robotManager.generateProgram(looped);
    _ftprintf(fp, (LPCTSTR)*program);
    fclose(fp);
    delete program;
  }
}

void CTeachingDialog::refresh()
{
	int i;
	USES_CONVERSION;
	/* Clear the list controls */
	listctrl_availableBots.DeleteAllItems();
	/* Populate available bots listctrl */
	for(i = 0; i < _robotManager.numEntries(); i++) {
		if(!_robotManager.isConnected(i)) {
			listctrl_availableBots.InsertItem(
				listctrl_availableBots.GetItemCount(),
				A2T(_robotManager.getEntry(i))
				);
		}
	}
	/* Populate connected bots listctrl */
	listctrl_connectedBots.DeleteAllItems();
	for(i = 0; i < _robotManager.numConnected(); i++) {
		listctrl_connectedBots.InsertItem(
			i,
			A2T(_robotManager.getConnected(i))
			);
	}
}

void CTeachingDialog::refreshRecordedMotions(int highlightedIndex)
{
	/* Pick the first connect robot in the list, go through all the motions.. */
	TCHAR buf[200];
	if(_robotManager.numConnected() <= 0) {
		return;
	}
	listctrl_recordedMotions.DeleteAllItems();
	int i;
	CRecordMobot *mobot;
	mobot = _robotManager.getMobot(0);
	for(i = 0; i < mobot->numMotions(); i++) {
		if(i == highlightedIndex) {
			swprintf(buf, TEXT("%s <--"), mobot->getMotionName(i)); 
			listctrl_recordedMotions.InsertItem(
				listctrl_recordedMotions.GetItemCount(),
				buf
				);
		} else {
			listctrl_recordedMotions.InsertItem(
				listctrl_recordedMotions.GetItemCount(),
				mobot->getMotionName(i)
				);
		}
	}
	if(highlightedIndex >= 0) {
		listctrl_recordedMotions.SetHotItem(highlightedIndex);
	}
}

void CTeachingDialog::OnBnClickedButtonplay()
{
	THREAD_T thread;
	button_play.EnableWindow(false);
	THREAD_CREATE(&thread, playThread, this);
}

void* playThread(void* arg)
{
	CTeachingDialog *teachingDialog;
	teachingDialog = (CTeachingDialog*)arg;
  teachingDialog->isPlaying = true;
	RobotManager* robotManager;
	robotManager = teachingDialog->getRobotManager();
	int i, j, done;
	done = 0;
	for(i = 0; !done ; i++) {
		teachingDialog->refreshRecordedMotions(i);
		for(j = 0; j < robotManager->numConnected(); j++) {
			if(robotManager->getMobot(j)->getMotionType(i) == MOTION_SLEEP) {
				robotManager->getMobot(j)->play(i);
				break;
			}
			if(robotManager->getMobot(j)->play(i)) {
				if(teachingDialog->button_teachingLoopCheck.GetCheck() == BST_CHECKED) {
					i = -1;
					break;
				}	else {
					done = 1;
					break;
				}
			}
		}
		for(j = 0; j < robotManager->numConnected(); j++) {
			robotManager->getMobot(j)->moveWait();
		}
		if(teachingDialog->haltPlayFlag) {
			teachingDialog->haltPlayFlag = 0;
			break;
		}
	}
	for(j = 0; j < robotManager->numConnected(); j++) {
		robotManager->getMobot(j)->stop();
	}
  teachingDialog->isPlaying = false;
	teachingDialog->button_play.EnableWindow(true);
	teachingDialog->refreshRecordedMotions(-1);
	return NULL;
}

RobotManager* CTeachingDialog::getRobotManager()
{
	return &_robotManager;
}
void CTeachingDialog::OnBnClickedButtonstop()
{
	haltPlayFlag = 1;
}

void CTeachingDialog::OnLvnItemchangedListRecordedmotions(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CTeachingDialog::OnLvnItemActivateListRecordedmotions(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	/*
	listctrl_recordedMotions.EditLabel(
		listctrl_recordedMotions.GetSelectionMark() );
		*/
}

void CTeachingDialog::OnLvnEndlabeleditListRecordedmotions(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	int i;
	int index = pDispInfo->item.iItem;
	for(i = 0; i < _robotManager.numConnected(); i++) {
		_robotManager.getMobot(i)->setMotionName(
			index,
			pDispInfo->item.pszText );
	}
	refreshRecordedMotions(-1);
	*pResult = 0;
}

void CTeachingDialog::OnNMRClickListRecordedmotions(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CTeachingDialog::OnRecordedMotionContextMenu(CPoint point, void *arg)
{
	CTeachingDialog *dlg = (CTeachingDialog*)arg;
	CPoint cl_point;
	cl_point = point;
	dlg->listctrl_recordedMotions.ScreenToClient(&cl_point);
	/* We want to pop up a context menu on the cursor, if it is over an item */
	int i, index = -1;
	CRect rect;
	for(i = 0; i < dlg->listctrl_recordedMotions.GetItemCount(); i++) {
		dlg->listctrl_recordedMotions.GetItemRect(i, &rect, LVIR_BOUNDS);
		if(rect.PtInRect(cl_point)) {
			index = i;
			break;
		}
	}
	if(index == -1) {return;}
	dlg->contextMenuIndex = index;
	CMenu mnuPopupMain;
	mnuPopupMain.LoadMenu(IDR_MENU_RECORDEDMOTIONPOPUP);
	CMenu *mnuPopup = mnuPopupMain.GetSubMenu(0);
	mnuPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, dlg);
}

void CTeachingDialog::OnContextRename()
{
	listctrl_recordedMotions.EditLabel(contextMenuIndex);
}

void CTeachingDialog::OnContextRemove()
{
	DeleteRecordedMotion(contextMenuIndex);
}
/*
void CTeachingDialog::MoveMotionUp(int index)
{
} */
void CTeachingDialog::OnRecordPopupMoveup()
{
  int i;
  for(i = 0; i < _robotManager.numConnected(); i++) {
    _robotManager.getMobot(i)->moveMotion(contextMenuIndex, contextMenuIndex-1);
  }
  refreshRecordedMotions(-1);
}

void CTeachingDialog::OnRecordPopupMovedown()
{
  int i;
  for(i = 0; i < _robotManager.numConnected(); i++) {
    _robotManager.getMobot(i)->moveMotion(contextMenuIndex, contextMenuIndex+1);
  }
  refreshRecordedMotions(-1);
}

void CTeachingDialog::OnRecordedGotopose()
{
  int i;
  refreshRecordedMotions(contextMenuIndex);
  for(i = 0; i < _robotManager.numConnected(); i++) {
    _robotManager.getMobot(i)->play(contextMenuIndex);
  }
}

void CTeachingDialog::OnMobotButton(CMobot *robot, int button, int buttonDown)
{
  /* Button A: Record Motion 
   * Button B: Playback / Stop
   * Both Buttons: Reset motions */
  static unsigned int lastState = 0;
  unsigned int newState;
  static bool debounce = false;
  int i;

  /* Calculate the new state */
  if(buttonDown) {
    robot->blinkLED(0.1, 2);
    newState = lastState | (1<<button);
  } else {
    newState = lastState & ~(1<<button);
  }
  if(debounce) {
    /* Must wait until all buttons are up */
    if(newState == 0) {
      debounce = false;
      lastState = newState;
      return;
    } else {
      lastState = newState;
      return;
    }
  }

  /* If a button release event is detected, use the last state to determine the action */
  if(buttonDown == 0) {
    if(lastState == 0x01) {
      /* Button A press/release */
      for(i = 0; i < g_teachingDialog->_robotManager.numConnected(); i++) {
		    g_teachingDialog->_robotManager.getMobot(i)->record();
	    }
	    g_teachingDialog->refreshRecordedMotions(-1);
    }
    if(lastState == 0x02) {
      /* Button B press/release */
      /* If it is not playing play. Otherwise, stop. */
      if(g_teachingDialog->isPlaying) {
        g_teachingDialog->haltPlayFlag = 1;
      } else {
        g_teachingDialog->OnBnClickedButtonplay();
      }
    }
    if(lastState == 0x03) {
      /* Buttons A/B Pressed, one released */
      debounce = true;
      g_teachingDialog->OnBnClickedButtonclear();
    }
  }
  lastState = newState;
}

void CTeachingDialog::OnBnClickedButtonclear()
{
  int i;
	for(i = 0; i < _robotManager.numConnected(); i++) {
		_robotManager.getMobot(i)->clearAllMotions();
	}
	refreshRecordedMotions(-1);
}