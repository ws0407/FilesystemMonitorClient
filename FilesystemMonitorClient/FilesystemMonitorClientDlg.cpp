
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

using namespace std;
SCANNER_MESSAGE data_get;
HINSTANCE m_hModule;
pInitiaCommunicationPort pInit = NULL;
pSendMessage Client_SendMessage = NULL;
pGetMessage Client_GetMessage = NULL;



CFilesystemMonitorClientDlg* pLogin;	//定义一个全局变量，用于向另外的对话框传递信息
void thread01();


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

	m_hModule = LoadLibrary("UserDll-1.dll");
	if (m_hModule == NULL)
	{
		MessageBox("缺少UserDLL-1.dll");
	}

	Client_SendMessage = (pGetMessage)GetProcAddress(m_hModule, "NPSendMessage");

	pLogin = this;

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

	//初始化列表
	num_records = 0;
	is_start = false;

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
	list_record.InsertColumn(5, _T("时间"), LVCFMT_CENTER, rt.Width() / 5.5, 1);
	
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
		is_start = true;
		GetDlgItem(IDOK)->SetWindowText("暂停");

		Client_SendMessage((PVOID)ENUM_PASS);

		// list_record.DeleteAllItems();
		// 写开始的操作
		thread task01(thread01);
		task01.detach();
	}
	else if (text == "暂停") {
		// 写暂停的操作
		Client_SendMessage((PVOID)ENUM_BLOCK);
		is_start = false;
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
	// OnBnClickedOk();


	INT_PTR nRes;
	Shell myDlg;
	nRes = myDlg.DoModal();  // 弹出对话框
}


void CFilesystemMonitorClientDlg::OnStop()
{
	// TODO: 在此添加命令处理程序代码
	//GetDlgItem(ID_STOP)->EnableWindow(false);
	//GetDlgItem(ID_START)->EnableWindow(true);

	GetDlgItem(IDOK)->SetWindowText("开始");

}


void CFilesystemMonitorClientDlg::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	// GetDlgItem(ID_STOP)->EnableWindow(true);
	//GetDlgItem(ID_START)->EnableWindow(false);

	GetDlgItem(IDOK)->SetWindowText("暂停");

}


void thread01() {
	// 接受message，传递信息

	Client_GetMessage = (pGetMessage)GetProcAddress(m_hModule, "NPGetMessage");
	OperationInfo message;
	CString filePath = "log\\log.txt";

	DWORD hResult = 0;
	hResult = Client_GetMessage(&data_get);
	if (hResult != S_OK)
	{
		printf("get message error");
	}
	else
	{
		message.operation_type = data_get.info.operation_type;
		strcpy(message.path, data_get.info.path);
		strcpy(message.process, data_get.info.process);
		strcpy(message.time, data_get.info.time);
		strcpy(message.user, data_get.info.user);
	}

	while (pLogin->is_start) {
		Sleep(200);
		char szNum[16] = {};

		int row = pLogin->num_records > 100 ? 100 : pLogin->num_records;
		sprintf(szNum, "%d", pLogin->num_records);

		if (pLogin->num_records > 100) {
			pLogin->list_record.DeleteItem(0);
		}
		pLogin->list_record.InsertItem(row, "");

		pLogin->list_record.SetItemText(row, 0, szNum);

		sprintf(szNum, "%d", message.operation_type);
		pLogin->list_record.SetItemText(row, 1, szNum);
		pLogin->list_record.SetItemText(row, 2, message.path);
		pLogin->list_record.SetItemText(row, 3, message.user);
		pLogin->list_record.SetItemText(row, 4, message.process);
		pLogin->list_record.SetItemText(row, 5, message.time);
		pLogin->list_record.EnsureVisible(pLogin->list_record.GetItemCount() - 1, false);
		(pLogin->num_records)++;

		CFile logFile(_T(filePath), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		char logMessage[1024] = { "\0" };

		sprintf(logMessage, "%d\t%d\t%s\t%s\t%s\t%s\n", pLogin->num_records,
			message.operation_type, message.user, message.path, message.process, message.time);

		logFile.SeekToEnd();
		logFile.Write(logMessage, strlen(logMessage));
		logFile.Close();
	}

}

