// CardReader.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CardReader.h"
#include "CardReaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCardReaderApp

BEGIN_MESSAGE_MAP(CCardReaderApp, CWinApp)
	//{{AFX_MSG_MAP(CCardReaderApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardReaderApp construction

CCardReaderApp::CCardReaderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCardReaderApp object

CCardReaderApp theApp;
CString g_sEXEFilePath = _T("");
CString g_sIniFile = _T("");
CString g_sLogFile = _T("");

CString g_sDBFile = _T("");

/////////////////////////////////////////////////////////////////////////////
// CCardReaderApp initialization

BOOL CCardReaderApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	char szFileName[MAX_PATH];
	GetModuleFileName(NULL, szFileName, sizeof(szFileName));
	g_sEXEFilePath = szFileName;

	g_sIniFile = g_sEXEFilePath.Left(g_sEXEFilePath.ReverseFind('\\'));
	g_sIniFile += "\\set.ini";
	g_sLogFile = g_sEXEFilePath.Left(g_sEXEFilePath.ReverseFind('\\'));
	g_sLogFile += "\\Log.log";

	g_sDBFile = g_sEXEFilePath.Left(g_sEXEFilePath.ReverseFind('\\'));
	g_sDBFile += "\\record.csv";

	CCardReaderDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
