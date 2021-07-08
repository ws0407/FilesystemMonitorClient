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
	DDX_Control(pDX, IDC_LIST_RULES, list_rules);
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
	ON_COMMAND(ID_LINK_DETAIL, &Shell::OnLinkDetail)
	ON_COMMAND(ID_LINK_MODIFY, &Shell::OnLinkModify)
	ON_COMMAND(ID_LINK_DELETE, &Shell::OnLinkDelete)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &Shell::OnBnClickedButtonRefresh)
END_MESSAGE_MAP()


// Shell 消息处理程序

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
	// 设置字体

	font.CreatePointFont(150, "");

	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&font);
	// 
	//添加列表信息
	CRect rt;
	GetClientRect(&rt);
	list_rules.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
		LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	list_rules.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rt.Width() / 7.5, 1);
	list_rules.InsertColumn(1, _T("规则名"), LVCFMT_CENTER, rt.Width() / 3, 1);
	list_rules.InsertColumn(2, _T("规则"), LVCFMT_CENTER, rt.Width() / 2, 1);

	rule_title.SetWindowTextA("规则标题");
	rule.SetWindowTextA("规则内容");

	num_rules = 0;

	RefreshEditRule();

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

void Shell::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// CDialogEx::OnOK();

	CString _title;
	CString _rule;

	GetDlgItem(IDC_EDIT_TITLE)->GetWindowTextA(_title);
	GetDlgItem(IDC_EDIT_RULE)->GetWindowTextA(_rule);

	if (_title.Find(" ") >= 0) {
		MessageBox("规则添加失败！\n规则名内不能存在空格", "提示", MB_ICONWARNING | MB_OK);
	}
	else
	{
		CString rulePath = "rule\\rule.txt";
		CFile ruleFile(_T(rulePath), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
		char ruleMessage[1024] = { "\0" };

		ruleFile.SeekToEnd();
		ruleFile.Write(_title + " " + _rule + "\n", strlen(_title + " " + _rule + "\n"));
		ruleFile.Close();
		MessageBox("规则添加成功", "提示", MB_ICONINFORMATION | MB_OK);
		RefreshEditRule();
	}
}

void Shell::RefreshEditRule() {
	list_rules.DeleteAllItems();
	num_rules = 0;

	CString rulePath = "rule\\rule.txt";
	CString rules_str;
	CStdioFile ruleFile;
	ruleFile.Open(rulePath, CFile::modeRead);

	ruleFile.SeekToBegin();
	while (ruleFile.ReadString(rules_str)) {
		
		int index = rules_str.Find(" ");
		CString _title = rules_str.Left(index);
		// MessageBox(_title);
		CString _rule = rules_str.Right(rules_str.GetLength() - index);
		char szNum[32] = { '\0' };
		sprintf(szNum, "%d", num_rules + 1);
		list_rules.InsertItem(num_rules, "");
		list_rules.SetItemText(num_rules, 0, szNum);
		list_rules.SetItemText(num_rules, 1, _title);
		list_rules.SetItemText(num_rules, 2, _rule);
		num_rules++;
	}
	ruleFile.Close();

}

void Shell::OnLinkDetail()
{
	// TODO: 在此添加命令处理程序代码
	int nItem = list_rules.GetSelectionMark();
	CString _title = list_rules.GetItemText(nItem, 1);
	CString _rule = list_rules.GetItemText(nItem, 2);
	MessageBox("title: " + _title + "\nRule: " + _rule, "规则详情：", MB_ICONINFORMATION | MB_OK);
}


void Shell::OnLinkModify()
{
	// TODO: 在此添加命令处理程序代码
}


void Shell::OnLinkDelete()
{
	// TODO: 在此添加命令处理程序代码
	int nItem = list_rules.GetSelectionMark();
	CString rulePath = "rule\\rule.txt";
	CString rules_str, rule_line;
	CStdioFile ruleFile;
	ruleFile.Open(rulePath, CFile::modeReadWrite);

	ruleFile.SeekToBegin();
	int index = 0;
	while (ruleFile.ReadString(rule_line)) {
		if ((++index) != nItem+1)
			rules_str = rules_str + rule_line + "\n";
	}
	ruleFile.Close();
	ruleFile.Open(rulePath, CFile::modeCreate | CFile::modeReadWrite);
	ruleFile.Write(rules_str, rules_str.GetLength());
	ruleFile.Close();

	RefreshEditRule();
	MessageBox("规则已成功删除！", "提示", MB_ICONINFORMATION | MB_OK);
}


void Shell::OnBnClickedButtonRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	RefreshEditRule();
}
