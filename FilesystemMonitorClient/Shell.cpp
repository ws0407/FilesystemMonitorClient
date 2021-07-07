// Shell.cpp: 实现文件
//

#include "pch.h"
#include "FilesystemMonitorClient.h"
#include "Shell.h"
#include "afxdialogex.h"


// Shell 对话框

IMPLEMENT_DYNAMIC(Shell, CDialogEx)

Shell::Shell(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHELL_DIALOG, pParent)
{

}

Shell::~Shell()
{
}

void Shell::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMMaND, edit_cmd);
}


BEGIN_MESSAGE_MAP(Shell, CDialogEx)
	ON_BN_CLICKED(IDOK, &Shell::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Shell::OnBnClickedCancel)
END_MESSAGE_MAP()


// Shell 消息处理程序


void Shell::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	MessageBox("命令执行成功", "提示", MB_ICONINFORMATION | MB_OK);
}


void Shell::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
