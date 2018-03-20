#if !defined(AFX_INI_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA61__INCLUDED_)
#define AFX_INI_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ini.h : header file
//

extern CString g_sIniFile;

class CIni : public CObject
{
public:
	CIni();   // standard constructor

	static CString GetString(CString sFile, char *sSection, char *sKey);
	static BOOL SetString(CString sFile, char *sSection, char *sKey, char *sValue);
protected:

private:
	static int _memmem(char *pMain, int nMainLen, char *pSub, int nSubLen);
	static BOOL _GetValue(char *pBuf, int nBufLen, char *sSection, char *sKey,
		int *pnSecBegin, int *pnSecEnd,
		int *pnKeyBegin, int *pnKeyEnd);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INI_H__24DFCB2A_E2C6_48F8_99B3_EAF9A37CFA61__INCLUDED_)
