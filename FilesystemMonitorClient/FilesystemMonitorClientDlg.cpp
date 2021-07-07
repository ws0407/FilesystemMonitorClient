﻿
// FilesystemMonitorClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FilesystemMonitorClient.h"
#include "FilesystemMonitorClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFilesystemMonitorClientDlg 对话框



CFilesystemMonitorClientDlg::CFilesystemMonitorClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILESYSTEMMONITORCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFilesystemMonitorClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RECORD, list_record);
}

BEGIN_MESSAGE_MAP(CFilesystemMonitorClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFilesystemMonitorClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFilesystemMonitorClientDlg::OnBnClickedCancel)
	ON_COMMAND(ID_SHELL, &CFilesystemMonitorClientDlg::OnShell)
	ON_COMMAND(ID_STOP, &CFilesystemMonitorClientDlg::OnStop)
	ON_COMMAND(ID_START, &CFilesystemMonitorClientDlg::OnStart)
END_MESSAGE_MAP()


// CFilesystemMonitorClientDlg 消息处理程序

BOOL CFilesystemMonitorClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。


	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//添加列表信息
	CRect rt;
	GetClientRect(&rt);
	list_record.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
		LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	list_record.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rt.Width() / 12, 1);
	list_record.InsertColumn(1, _T("操作类型"), LVCFMT_CENTER, rt.Width() / 10, 1);
	list_record.InsertColumn(2, _T("文件路径"), LVCFMT_CENTER, rt.Width() / 2.75, 1);
	list_record.InsertColumn(3, _T("用户"), LVCFMT_CENTER, rt.Width() / 10, 1);
	list_record.InsertColumn(4, _T("进程"), LVCFMT_CENTER, rt.Width() / 8, 1);
	list_record.InsertColumn(5, _T("时间"), LVCFMT_CENTER, rt.Width() / 5, 1);



	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFilesystemMonitorClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFilesystemMonitorClientDlg::OnPaint()
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
HCURSOR CFilesystemMonitorClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFilesystemMonitorClientDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	GetDlgItem(IDOK)->GetWindowText(text);
	if (text == "开始") {
		list_record.DeleteAllItems();
		// 写开始的操作


		GetDlgItem(IDOK)->SetWindowText("暂停");
	}
	else if (text == "暂停") {
		// 写暂停的操作


		GetDlgItem(IDOK)->SetWindowText("开始");
	}
}


void CFilesystemMonitorClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CFilesystemMonitorClientDlg::OnShell()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;
	Shell myDlg;
	nRes = myDlg.DoModal();  // 弹出对话框
}


void CFilesystemMonitorClientDlg::OnStop()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(ID_STOP)->EnableWindow(false);
	GetDlgItem(ID_START)->EnableWindow(true);

	GetDlgItem(IDOK)->SetWindowText("开始");

}


void CFilesystemMonitorClientDlg::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	// GetDlgItem(ID_STOP)->EnableWindow(true);
	//GetDlgItem(ID_START)->EnableWindow(false);

	GetDlgItem(IDOK)->SetWindowText("暂停");

}