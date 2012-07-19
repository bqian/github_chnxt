#include "StdAfx.h"
#include "ListCtrlContext.h"

CListCtrlContext::CListCtrlContext(void)
{
	CListCtrl();
}

CListCtrlContext::~CListCtrlContext(void)
{
}

void CListCtrlContext::OnContextMenu(CWnd* wnd, CPoint pos)
{
	int i;
	i = 1;
	CWnd::OnContextMenu(wnd, pos);
}