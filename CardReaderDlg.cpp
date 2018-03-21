// CardReaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CardReader.h"
#include "CardReaderDlg.h"
#include "DB.h"
#include "Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardReaderDlg dialog

CCardReaderDlg::CCardReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardReaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCardReaderDlg)
	m_sRecharge = _T("");
	m_sBalance = _T("");
	m_nTimerID = 0;
	m_bTimerPause = TRUE;
	m_nCardNo = 0;
	m_nBalance = 0;
	m_sCardNo = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCardReaderDlg)
	DDX_Text(pDX, IDC_EDIT_RECHARGE, m_sRecharge);
	DDX_Text(pDX, IDC_EDIT_BALANCE, m_sBalance);
	DDX_Text(pDX, IDC_EDIT_CARDNO, m_sCardNo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCardReaderDlg, CDialog)
	//{{AFX_MSG_MAP(CCardReaderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_RECHARGE, OnButtonRecharge)
	ON_BN_CLICKED(ID_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(ID_BUTTON_CHANGE_PASS, OnButtonChangePass)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardReaderDlg message handlers

BOOL CCardReaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if(TRUE != m_reader.GetReader())
	{
		MessageBox("请先连接读卡器！");
		PostQuitMessage(0);
		return TRUE;
	}
	
	// TODO: Add extra initialization here
	m_nTimerID = SetTimer(1, 500, NULL);
	if(m_nTimerID)
	{
		m_bTimerPause = FALSE;
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCardReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCardReaderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCardReaderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCardReaderDlg::OnButtonRecharge() 
{
	//充值
	unsigned int nRecharge = 0;
	CString s = _T("");

	UpdateData();
	
	sscanf(m_sRecharge, "%d", &nRecharge);
	//检查
	if(nRecharge <= 0)
	{
		MessageBox("输入的数字不正确！");
		return;
	}
#define RECHARGE_MAX	(365UL * 24 * 60)	/*一年的分钟数*/
	if(nRecharge > RECHARGE_MAX)
	{
		s.Format("输入的数字太大！\r\n不能大于%d！", RECHARGE_MAX);
		MessageBox(s);
		return;
	}

	m_bTimerPause = TRUE;
	if(!m_reader.SetBalance(m_nCardNo, m_nBalance + nRecharge))
	{
		MessageBox("写卡失败!");
		m_bTimerPause = FALSE;
		return;
	}

	//写数据库
	CString sRecord = _T("");
	sRecord.Format("%u,%d", m_nCardNo, nRecharge);
	CDB::Insert(sRecord);

	MessageBox("写卡成功!");

	m_bTimerPause = FALSE;
}

void CCardReaderDlg::OnButtonClear() 
{
	//清空
	m_bTimerPause = TRUE;
	if(!m_reader.SetBalance(m_nCardNo, 0))
	{
		MessageBox("写卡失败!");
		m_bTimerPause = FALSE;
		return;
	}
	//写数据库
	CString sRecord = _T("");
	sRecord.Format("%u,0", m_nCardNo);
	CDB::Insert(sRecord);

	MessageBox("写卡成功!");

	m_bTimerPause = FALSE;
}

void CCardReaderDlg::OnButtonChangePass() 
{
	// TODO: Add your control notification handler code here
	
}

void CCardReaderDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bTimerPause)
	{
		return;
	}

	UpdateData();
	m_nCardNo = 0;
	m_nBalance = 0;
	m_sCardNo = _T("");
	m_sBalance = _T("");

	unsigned short nCardType = -1;
	if(!m_reader.IsCardOn(&nCardType))
	{
		//没有检测到卡
		UpdateData(FALSE);
		return;
	}

	//查询余额
	unsigned int nBalance = 0;
	if(m_reader.GetBalance(&m_nCardNo, &m_nBalance))
	{
		m_sCardNo.Format("%u", m_nCardNo);
		m_sBalance.Format("%d", m_nBalance);
	}
	UpdateData(FALSE);

	CDialog::OnTimer(nIDEvent);
}

BOOL CCardReaderDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_nTimerID)
	{
		KillTimer(m_nTimerID);
		m_nTimerID = 0;
	}
	
	return CDialog::DestroyWindow();
}
