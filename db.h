#if !defined(AFX_DB_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA63__INCLUDED_)
#define AFX_DB_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// db.h : header file
//
extern CString g_sDBFile;

class CDB : public CObject
{
public:
	static int Insert(CString &s);
	static BOOL IsDBOK(void);
protected:

private:
	static int WriteDB(const char *s);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA63__INCLUDED_)
