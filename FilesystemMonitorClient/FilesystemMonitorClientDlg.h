
// FilesystemMonitorClientDlg.h: 头文件
//

#include <vector>
#include <stdarg.h>
#include <string>
#include <time.h>
#include "Shell.h"
#include <thread>
#include <WinSock2.h>
#include <fltUser.h>

#pragma comment(lib, "ws2_32.lib")

#pragma once

#define MAX_RECORD 1024
#define MAX_FILENAME_LEN 128
#define Bufsize 1024


typedef int (*pSendMessage)(PVOID pInBufffer);
typedef int (*pGetMessage)(PVOID pInBufffer);
typedef int (*pInitiaCommunicationPort)();




typedef struct {
	char time[32];
	short operation_type;
	char user[32];
	char process[32];
	char path[256];
} OperationInfo;


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
	CBrush brush;
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
	OperationInfo records[1024];
	int num_records;
	bool is_start;
		

	afx_msg void OnShell();
	afx_msg void OnStop();
	afx_msg void OnStart();

};

typedef struct _SCANNER_MESSAGE
{
	FILTER_MESSAGE_HEADER MessageHeader;

	OperationInfo info;

	OVERLAPPED Ovlp;
} SCANNER_MESSAGE, * PSCANNER_MESSAGE;
