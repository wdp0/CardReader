// CardReaderDlg.h : header file
//

#if !defined(AFX_CARDREADERDLG_H__429B5762_982D_40EE_B685_D10E31A029FE__INCLUDED_)
#define AFX_CARDREADERDLG_H__429B5762_982D_40EE_B685_D10E31A029FE__INCLUDED_

#include "CardReader2.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCardReaderDlg dialog

class CCardReaderDlg : public CDialog
{
// Construction
public:
	CCardReaderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCardReaderDlg)
	enum { IDD = IDD_CARDREADER_DIALOG };
	CString	m_sRecharge;
	CString	m_sBalance;
	CString	m_sCardNo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardReaderDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCardReaderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonRecharge();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonChangePass();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CCardReader m_reader;
	BOOL m_bTimerPause;
	UINT m_nTimerID;
	unsigned long m_nCardNo;
	unsigned int m_nBalance;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDREADERDLG_H__429B5762_982D_40EE_B685_D10E31A029FE__INCLUDED_)
