
// FilesystemMonitorClientDlg.h: 头文件
//

#include <vector>
#include <stdarg.h>
#include <string>
#include <time.h>
#include <thread>
#include <WinSock2.h>
#include <fltUser.h>
#include <afxdb.h>

#pragma comment(lib, "ws2_32.lib")

#pragma once

#define MAX_RECORD 1024
#define MAX_FILENAME_LEN 128
#define Bufsize 1024


typedef int (*pSendMessage)(PVOID pInBufffer);
typedef int (*pGetMessage)(PVOID pInBufffer);
typedef int (*pInitiaCommunicationPort)();


typedef enum {
	ENUM_BLOCK = 0,
	ENUM_PASS,
	ENUM_RULE
}_MINI_COMMAND;

typedef struct Rule
{
	char user[256];
	char path[256];
}Rule;

typedef struct {
	char time[32];
	short operation_type;
	int process_id;
	char user[256];
	char path[256];
} OperationInfo;

typedef struct _COMMAND_MESSAGE {
	_MINI_COMMAND Command;
	Rule rules[5];
} COMMAND_MESSAGE, * PCOMMAND_MESSAGE;


// CFilesystemMonitorClientDlg 对话框
class CFilesystemMonitorClientDlg : public CDialogEx
{
// 构造
public:
	CFilesystemMonitorClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILESYSTEMMONITORCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CFont font;
	CImageList m_IconList;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListCtrl list_record;
	//vector<OperationInfo> records;
	OperationInfo records[1024];
	int num_records;
	bool is_start;
	HINSTANCE m_hModule;
	pInitiaCommunicationPort pInit = NULL;
	pSendMessage Client_SendMessage = NULL;
	pGetMessage Client_GetMessage = NULL;
		

	afx_msg void OnShell();
	afx_msg void OnStop();
	afx_msg void OnStart();
	afx_msg void OnExit();
	afx_msg void OnSave();

};

typedef struct _SCANNER_MESSAGE
{
	FILTER_MESSAGE_HEADER MessageHeader;

	OperationInfo info;

	OVERLAPPED Ovlp;
} SCANNER_MESSAGE, * PSCANNER_MESSAGE;
