#pragma once
#include "FilesystemMonitorClientDlg.h"

#include <vector>
using namespace std;

typedef int (*pSendMessage)(PVOID pInBufffer);
typedef int (*pGetMessage)(PVOID pInBufffer);


// Shell 对话框

class Shell : public CDialogEx
{
	DECLARE_DYNAMIC(Shell)

public:
	Shell(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Shell();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHELL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CFont font;
	CBrush brush;
	CImageList m_IconList;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit edit_cmd;

	afx_msg void OnStnClickedStaticNew();
	CListCtrl list_rules;
	CEdit rule_title;
	CEdit rule;
	int num_rules;
	

	vector<int> rules;

	afx_msg void OnStnClickedStaticTitle();
	afx_msg void OnNMRClickListRules(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnSetfocusEditTitle();
	afx_msg void OnEnSetfocusEditRule();

	afx_msg void RefreshEditRule();
	afx_msg void OnLinkDetail();
	afx_msg void OnLinkModify();
	afx_msg void OnLinkDelete();
	afx_msg void OnBnClickedButtonRefresh();
};
