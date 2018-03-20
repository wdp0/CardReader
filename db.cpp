// db.cpp : implementation file
//

#include "stdafx.h"
#include "DB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CDB::Insert(CString &s)
{
    char sBuf[256];
    SYSTEMTIME t;
    int nRet;

    GetLocalTime(&t);
    sprintf(sBuf, "%04d/%02d/%02d %02d:%02d:%02d,",
        t.wYear, t.wMonth, t.wDay,
        t.wHour, t.wMinute, t.wSecond);
    nRet = WriteDB(sBuf);
    if(nRet != 1)
    {
        return nRet;
    }
    nRet = WriteDB((LPCTSTR)s);
    if(nRet != 1)
    {
        return nRet;
    }
    return WriteDB("\r\n");
}

int CDB::WriteDB(const char *s)
{
	BOOL b;
	CFile file;

	b = file.Open(g_sDBFile, CFile::typeBinary | CFile::modeCreate
		| CFile::modeNoTruncate | CFile::modeWrite
		| CFile::shareDenyWrite);
	if(!b)
	{
		return -1;
	}

	file.SeekToEnd();
	file.Write(s, strlen(s));
	file.Close();
	return 1;
}
