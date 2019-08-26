#include "stdafx.h"
#include "CClientSocket.h"
#include"ChatServerDlg.h"

CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	//接收消息
	Command cmd;

	Receive(&cmd,sizeof(cmd));

	CString strIPaddress;
	UINT uPort;

	//获取主对话框窗口指针
	CChatServerDlg* pMainDlg = (CChatServerDlg*)AfxGetMainWnd();

	switch (cmd.cmd) 
	{
	case LOGIN: 
	{
		//获取客户端IP地址
		GetPeerName(strIPaddress, uPort);
		//接收用户名
		wchar_t szUsername[30] = { 0 };
		Receive(szUsername, sizeof(szUsername));
		//将其显示到界面
		pMainDlg->m_list.InsertItem(0, szUsername);
		pMainDlg->m_list.SetItemText(0, 1, strIPaddress);
		CString strPort;
		strPort.Format(_T("%d"), uPort);
		pMainDlg->m_list.SetItemText(0, 2, strPort);
	}
		break;
	case SEND:
		break;
	}
	CSocket::OnReceive(nErrorCode);
}
