#include "stdafx.h"
#include "CListenSocket.h"
#include"ChatServerDlg.h"

CListenSocket::CListenSocket()
{
}


CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	//AfxMessageBox(_T("有人连接我"));

	((CChatServerDlg*)AfxGetMainWnd())->OnAccept();
	CSocket::OnAccept(nErrorCode);
}
