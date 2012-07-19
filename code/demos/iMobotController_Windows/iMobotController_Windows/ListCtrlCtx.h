#pragma once


// CListCtrlCtx

class CListCtrlCtx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlCtx)

public:
	CListCtrlCtx();
	virtual ~CListCtrlCtx();
	afx_msg void OnContextMenu(CWnd *pWnd, CPoint pos);
	void setContextMenuCallback(void (*callback)(CPoint point, void *arg), void* arg);

protected:
	DECLARE_MESSAGE_MAP()
	void (*ContextMenu_cb)(CPoint point, void *arg);
	void* ContextMenuArg;
};


