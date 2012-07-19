#pragma once
#include "afxwin.h"
#include "configFile.h"


// ConfigFileDialog dialog

class ConfigFileDialog : public CDialog
{
	DECLARE_DYNAMIC(ConfigFileDialog)

public:
	ConfigFileDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ConfigFileDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonMoveup();
	afx_msg void OnBnClickedButtonMovedown();
	afx_msg void OnBnClickedButtonRemove();
  void Refresh();
	CEdit _edit_AddressBox;
	CListBox _listbox_Addresses;

  ConfigFile _configFile;
  char _path[MAX_PATH];
};
