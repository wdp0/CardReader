// CardReader.h : main header file for the CARDREADER application
//

#if !defined(AFX_CARDREADER_H__A1EB938E_A677_49CC_A662_50BC8062EE50__INCLUDED_)
#define AFX_CARDREADER_H__A1EB938E_A677_49CC_A662_50BC8062EE50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCardReaderApp:
// See CardReader.cpp for the implementation of this class
//

class CCardReaderApp : public CWinApp
{
public:
	CCardReaderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardReaderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCardReaderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDREADER_H__A1EB938E_A677_49CC_A662_50BC8062EE50__INCLUDED_)
