#if !defined(AFX_LOG_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA63__INCLUDED_)
#define AFX_LOG_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ini.h : header file
//
extern CString g_sLogFile;

class CLog : public CObject
{
public:
	static int WriteLog(CString sFile, char *s);
	static int WriteLogWithTime(CString sFile, char *s);
	static int WriteLog(CString sFile, CString *pS);
protected:

private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOG_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA63__INCLUDED_)
