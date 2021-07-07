﻿#pragma once


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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit edit_cmd;

};