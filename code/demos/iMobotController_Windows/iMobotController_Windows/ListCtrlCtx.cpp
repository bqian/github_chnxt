// ListCtrlCtx.cpp : implementation file
//

#include "stdafx.h"
#include "iMobotController_Windows.h"
#include "ListCtrlCtx.h"


// CListCtrlCtx

IMPLEMENT_DYNAMIC(CListCtrlCtx, CListCtrl)

CListCtrlCtx::CListCtrlCtx()
{
	ContextMenu_cb = NULL;
}

CListCtrlCtx::~CListCtrlCtx()
{
}

afx_msg void CListCtrlCtx::OnContextMenu(CWnd *pWnd, CPoint pos)
{
	if(ContextMenu_cb == NULL) { return; }
	ContextMenu_cb(pos, ContextMenuArg);
}

void CListCtrlCtx::setContextMenuCallback(void (*callback)(CPoint point, void* arg), void* arg) {
	ContextMenu_cb = callback;
	ContextMenuArg = arg;
}

BEGIN_MESSAGE_MAP(CListCtrlCtx, CListCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// CListCtrlCtx message handlers


