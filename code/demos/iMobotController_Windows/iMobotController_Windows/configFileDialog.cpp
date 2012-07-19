// onfigFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "iMobotController_Windows.h"
#include "configFileDialog.h"
#include <tchar.h>
#include <atlconv.h>


// ConfigFileDialog dialog

IMPLEMENT_DYNAMIC(ConfigFileDialog, CDialog)

ConfigFileDialog::ConfigFileDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ConfigFileDialog::IDD, pParent)
{
  //FILE *fp = fopen("/pathlog.txt", "w");
  /* Read the config file */
  if(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, _path) != S_OK) 
  {
    /* Could not get the user's app data directory */
  } else {
    //MessageBox((LPCTSTR)path, (LPCTSTR)"Test");
    //fprintf(fp, "%s", path); 
  }
  strcat(_path, "\\nxt.config");
  _configFile.read(_path);
}

BOOL ConfigFileDialog::OnInitDialog()
{
  CDialog::OnInitDialog();
  Refresh();
  return TRUE;
}

ConfigFileDialog::~ConfigFileDialog()
{
  /* Write the config file */
  _configFile.write();
}

void ConfigFileDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, _edit_AddressBox);
	DDX_Control(pDX, IDC_LIST2, _listbox_Addresses);
}


BEGIN_MESSAGE_MAP(ConfigFileDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &ConfigFileDialog::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOVEUP, &ConfigFileDialog::OnBnClickedButtonMoveup)
	ON_BN_CLICKED(IDC_BUTTON_MOVEDOWN, &ConfigFileDialog::OnBnClickedButtonMovedown)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &ConfigFileDialog::OnBnClickedButtonRemove)
END_MESSAGE_MAP()


// ConfigFileDialog message handlers

void ConfigFileDialog::OnBnClickedButtonAdd()
{
  /* Get the text from the correct edit and put it in the config file */
  USES_CONVERSION;
  TCHAR text[256];
  LPCSTR address;
  int count;
  memset(text, 0, sizeof(TCHAR)*256);
  ((DWORD*)text)[0] = 256;
  count = _edit_AddressBox.GetLine(0, text, 255);
  text[count] = (TCHAR)'\0';
  /* Convert from wide char to normal char */
  //size_t convertedChars = 0;
  //size_t origsize = wcslen(text)+1;
  //wcstombs_s(&convertedChars, address, origsize, text, _TRUNCATE);
  address = T2CA(text);
  _configFile.addEntry(address);
  Refresh();
}

void ConfigFileDialog::OnBnClickedButtonMoveup()
{
  /* Get the currently selected index */
  int index;
  for(int i = 0; i < _listbox_Addresses.GetCount(); i++) {
    if(_listbox_Addresses.GetSel(i) > 0) {
      index = i;
      break;
    }
  }
  _configFile.moveEntryUp(index);
  Refresh();
}

void ConfigFileDialog::OnBnClickedButtonMovedown()
{
  /* Get the currently selected index */
  int index;
  for(int i = 0; i < _listbox_Addresses.GetCount(); i++) {
    if(_listbox_Addresses.GetSel(i) > 0) {
      index = i;
      break;
    }
  }
  _configFile.moveEntryDown(index);
  Refresh();
}

void ConfigFileDialog::OnBnClickedButtonRemove()
{
  /* Get the currently selected index */
  int index;
  for(int i = 0; i < _listbox_Addresses.GetCount(); i++) {
    if(_listbox_Addresses.GetSel(i) > 0) {
      index = i;
      break;
    }
  }
  _configFile.remove(index);
  Refresh();
}

void ConfigFileDialog::Refresh()
{
  CString str;
  /* First, clear the listbox */
  _listbox_Addresses.ResetContent();
  /* Populate the listbox control */
  for(int i = 0; i < _configFile.numEntries(); i++) {
    str = _configFile.getEntry(i);
    _listbox_Addresses.InsertString(i, str);
  }
}
