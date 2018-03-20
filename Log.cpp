// Ini.cpp : implementation file
//

#include "stdafx.h"
#include "Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CLog::WriteLog(CString sFile, CString *pS)
{
	return WriteLogWithTime(sFile, pS->GetBuffer(pS->GetLength()));
}

int CLog::WriteLogWithTime(CString sFile, char *s)
{
    char sBuf[256];
    SYSTEMTIME t;
    int nRet;

    GetLocalTime(&t);
    sprintf(sBuf, "%04d/%02d/%02d %02d:%02d:%02d ",
        t.wYear, t.wMonth, t.wDay,
        t.wHour, t.wMinute, t.wSecond);
    nRet = WriteLog(sFile, sBuf);
    if(nRet != 1)
    {
        return nRet;
    }
    nRet = WriteLog(sFile, s);
    if(nRet != 1)
    {
        return nRet;
    }
    return WriteLog(sFile, "\r\n");
}

int CLog::WriteLog(CString sFile, char *s)
{
	BOOL b;
	CFile file;

	b = file.Open(sFile, CFile::typeBinary | CFile::modeCreate
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
