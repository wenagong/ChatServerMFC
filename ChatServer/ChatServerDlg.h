
// ChatServerDlg.h: 头文件
//

#pragma once
#include"CListenSocket.h"
#include"resource.h"

//class CListenSocket; //类的前置声明，或者包含头文件

// CChatServerDlg 对话框
class CChatServerDlg : public CDialogEx
{
// 构造
public:
	CChatServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CListenSocket *m_pListenSocket;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedClose();
	void OnAccept();
};
