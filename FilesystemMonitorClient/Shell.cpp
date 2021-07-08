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
	DDX_Control(pDX, IDC_LIST1, list_rules);
	DDX_Control(pDX, IDC_EDIT_TITLE, rule_title);
	DDX_Control(pDX, IDC_EDIT_RULE, rule);
}


BEGIN_MESSAGE_MAP(Shell, CDialogEx)
	ON_BN_CLICKED(IDOK, &Shell::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Shell::OnBnClickedCancel)
	ON_STN_CLICKED(IDC_STATIC_NEW, &Shell::OnStnClickedStaticNew)
	ON_STN_CLICKED(IDC_STATIC_TITLE, &Shell::OnStnClickedStaticTitle)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_RULES, &Shell::OnNMRClickListRules)
	ON_EN_SETFOCUS(IDC_EDIT_TITLE, &Shell::OnEnSetfocusEditTitle)
	ON_EN_SETFOCUS(IDC_EDIT_RULE, &Shell::OnEnSetfocusEditRule)
END_MESSAGE_MAP()


// Shell 消息处理程序


void Shell::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();


	MessageBox("添加规则成功", "提示", MB_ICONINFORMATION | MB_OK);
}


void Shell::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void Shell::OnStnClickedStaticNew()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Shell::OnStnClickedStaticTitle()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Shell::OnNMRClickListRules(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1) {
		CPoint pt;
		GetCursorPos(&pt);
		CMenu menu;
		menu.LoadMenu(IDR_MENU2);
		int nItem = list_rules.GetSelectionMark();

		CMenu* popmenu;
		popmenu = menu.GetSubMenu(0);
		popmenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);

	}


	*pResult = 0;
}


BOOL Shell::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//添加列表信息
	CRect rt;
	GetClientRect(&rt);
	list_rules.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
		LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	list_rules.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rt.Width() / 7.5, 1);
	list_rules.InsertColumn(1, _T("规则名"), LVCFMT_CENTER, rt.Width() / 3, 1);
	list_rules.InsertColumn(2, _T("规则"), LVCFMT_CENTER, rt.Width() / 2, 1);

	list_rules.InsertItem(0, "");
	list_rules.SetItemText(0, 0, "1");
	list_rules.SetItemText(0, 1, "test1");
	list_rules.SetItemText(0, 2, "test1");

	list_rules.InsertItem(1, "");
	list_rules.SetItemText(1, 0, "2");
	list_rules.SetItemText(1, 1, "test2");
	list_rules.SetItemText(1, 2, "test2");

	//
	rule_title.SetWindowTextA("规则标题");
	rule.SetWindowTextA("规则内容");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Shell::OnEnSetfocusEditTitle()
{
	// TODO: 在此添加控件通知处理程序代码
	rule_title.SetWindowTextA("");
}


void Shell::OnEnSetfocusEditRule()
{
	// TODO: 在此添加控件通知处理程序代码
	rule.SetWindowTextA("");
}
