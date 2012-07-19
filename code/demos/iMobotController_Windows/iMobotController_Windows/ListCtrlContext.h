#pragma once
#include "afxcmn.h"

class CListCtrlContext :
	public CListCtrl
{
public:
	CListCtrlContext(void);
	~CListCtrlContext(void);

	afx_msg void OnContextMenu(CWnd* wnd, CPoint pos);
};
