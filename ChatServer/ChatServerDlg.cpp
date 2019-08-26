
// ChatServerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"
#include"CClientSocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatServerDlg 对话框



CChatServerDlg::CChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pListenSocket = NULL; //初始化
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTM_START, &CChatServerDlg::OnBnClickedStart)
	ON_BN_CLICKED(BTM_CLOSE, &CChatServerDlg::OnBnClickedClose)
END_MESSAGE_MAP()


// CChatServerDlg 消息处理程序

BOOL CChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_list.InsertColumn(0, _T("昵称"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("IP地址"), LVCFMT_CENTER, 200);
	m_list.InsertColumn(2, _T("端口号"), LVCFMT_LEFT, 100);

	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//点击开启服务器模块
void CChatServerDlg::OnBnClickedStart()
{
	m_pListenSocket = new CListenSocket; 

	//创建套接字
	//Create()
	//1.端口号：0->65535，1024以下一般为系统应用，一般取1024以上
	//2.套接字类型：TCP(SOCK_STREAM)/UDP(SOCEK_DGREAM)
	if (FALSE==m_pListenSocket->Create(6080, SOCK_STREAM)) 
	{
		CString str;
		str.Format(_T("创建套接字失败.错误代码：%d"), GetLastError());
		MessageBox(str);
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		return;
	}

	//将套接字设置为监听模式
	if (FALSE==m_pListenSocket->Listen()) 
	{
		CString str;
		str.Format(_T("监听失败.错误代码：%d"), GetLastError());
		MessageBox(str);
		delete m_pListenSocket;
		m_pListenSocket = NULL;
		return;
	}

	//调整按钮的状态
	GetDlgItem(BTM_START)->EnableWindow(FALSE);
	GetDlgItem(BTM_CLOSE)->EnableWindow(TRUE);

}

//关闭服务器模块
void CChatServerDlg::OnBnClickedClose()
{
	if (m_pListenSocket) {
		m_pListenSocket->Close();
		delete m_pListenSocket;
		m_pListenSocket = NULL;

		//调整按钮的状态
		GetDlgItem(BTM_START)->EnableWindow(TRUE);
		GetDlgItem(BTM_CLOSE)->EnableWindow(FALSE);
	}
}

void CChatServerDlg::OnAccept()
{
	CClientSocket* pSocket =  new CClientSocket;
	m_pListenSocket->Accept(*pSocket);

	//接收
}