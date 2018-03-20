// Ini.cpp : implementation file
//

#include "stdafx.h"
#include "Ini.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CIni::CIni()
{
}

int CIni::_memmem(char *pMain, int nMainLen, char *pSub, int nSubLen)
{
	int n;

	for(n = 0; n < nMainLen - nSubLen; n++)
	{
		if(memcmp(&pMain[n], pSub, nSubLen)) continue;
		return n;
	}

	return -1;
}

CString CIni::GetString(CString sFile, char *sSection, char *sKey)
{
	CString sRet = "";
	CFile file;
	BOOL b = file.Open(sFile, CFile::modeRead | CFile::shareDenyNone);
	if(!b) return sRet;

	int nFileLen = (int)file.GetLength();
	if(nFileLen == 0)
	{
		file.Close();
		return sRet;
	}

	char *pBuf = new char[nFileLen];
	if(pBuf == NULL)
	{
		file.Close();
		return sRet;
	}
	file.Read(pBuf, nFileLen);
	file.Close();

	for(;;)
	{
		int nSecBegin;
		int nSecEnd;
		int nKeyBegin;
		int nKeyEnd;

		b = _GetValue(pBuf, nFileLen, sSection, sKey,
			&nSecBegin, &nSecEnd, &nKeyBegin, &nKeyEnd);
		if(!b) break;

		int nKeyLen2 = nKeyEnd - nKeyBegin;
		char *sValue = new char[nKeyLen2 + 1];
		if(sValue == NULL) break;
		memcpy(sValue, &pBuf[nKeyBegin], nKeyLen2);
		sValue[nKeyLen2] = '\0';
		sRet = sValue;
		delete[] sValue;
		break;
	}

	delete[] pBuf;
	return sRet;
}

BOOL CIni::SetString(CString sFile, char *sSection, char *sKey, char *sValue)
{
	BOOL b;
	CFile file;

	b = file.Open(sFile, CFile::typeBinary | CFile::modeCreate
		| CFile::modeNoTruncate | CFile::modeReadWrite
		| CFile::shareDenyNone);
	if(!b)
	{
		return FALSE;
	}

	int nFileLen = (int)file.GetLength();
	char *pBuf = NULL;
	
	if(nFileLen > 0)
	{
		pBuf = new char[nFileLen];
		if(pBuf == NULL)
		{
			file.Close();
			return FALSE;
		}
		file.SeekToBegin();
		file.Read(pBuf, nFileLen);
	}

	int nSecBegin;
	int nSecEnd;
	int nKeyBegin;
	int nKeyEnd;

	char *pBuf2 = NULL;

	b = _GetValue(pBuf, nFileLen, sSection, sKey,
		&nSecBegin, &nSecEnd, &nKeyBegin, &nKeyEnd);
	if(nSecBegin == -1)
	{
		//需要添加Section
		file.SeekToEnd();
		if(nFileLen == 0
			|| nFileLen >= 2 && pBuf[nFileLen - 2] == '\r' && pBuf[nFileLen - 1] == '\n')
		{
			pBuf2 = new char[1 + strlen(sSection) + 3
				+ strlen(sKey) + 1 + strlen(sValue) + 1];
			sprintf(pBuf2, "[%s]\r\n%s=%s", sSection, sKey, sValue);
		}
		else
		{
			pBuf2 = new char[3 + strlen(sSection) + 3
				+ strlen(sKey) + 1 + strlen(sValue) + 1];
			sprintf(pBuf2, "\r\n[%s]\r\n%s=%s", sSection, sKey, sValue);
		}
		file.Write(pBuf2, strlen(pBuf2));
		delete[] pBuf2;
	}
	else if(nKeyBegin == -1)
	{
		//增加一个Key
		file.Seek(nSecEnd, CFile::begin);
		if(nSecEnd == nFileLen)
		{
			//最后一个Section
			pBuf2 = new char[2 + strlen(sKey) + 1 + strlen(sValue) + 1];
			sprintf(pBuf2, "\r\n%s=%s", sKey, sValue);
		}
		else
		{
			pBuf2 = new char[strlen(sKey) + 1 + strlen(sValue) + 3];
			sprintf(pBuf2, "%s=%s\r\n", sKey, sValue);
		}
		file.Write(pBuf2, strlen(pBuf2));
		delete[] pBuf2;
		file.Write(&pBuf[nSecEnd], nFileLen - nSecEnd);
	}
	else
	{
		//替换Value
		file.Seek(nKeyBegin, CFile::begin);
		file.Write(sValue, strlen(sValue));
		file.Write(&pBuf[nKeyEnd], nFileLen - nKeyEnd);
	}

	if(nFileLen > 0) delete[] pBuf;
    int nFileLen2 = file.GetPosition();
    if(nFileLen2 < nFileLen)
    {
        //文件变小了，要重新写文件
        pBuf = new char[nFileLen2];
		if(pBuf == NULL)
		{
			file.Close();
			return FALSE;
		}

        file.SeekToBegin();
		file.Read(pBuf, nFileLen2);
        file.Close();
	    b = file.Open(sFile, CFile::typeBinary | CFile::modeCreate
		    | CFile::modeWrite
		    | CFile::shareDenyWrite);
	    if(!b)
	    {
            delete[] pBuf;
		    return FALSE;
	    }
        file.Write(pBuf, nFileLen2);
        delete[] pBuf;
    }
	file.Close();
	return TRUE;
}

BOOL CIni::_GetValue(char *pBuf, int nBufLen, char *sSection, char *sKey,
                     int *pnSecBegin, int *pnSecEnd,
                     int *pnKeyBegin, int *pnKeyEnd)
{
	BOOL bRet = FALSE;
	*pnSecBegin = -1;
	*pnKeyBegin = -1;

	if(pBuf == NULL || nBufLen == 0) return bRet;

	for(;;)
	{
		//寻找[Section]

		int nSecLen = strlen(sSection);
		char *sSection2 = new char[nSecLen + 5];
		if(sSection2 == NULL) break;
		strcpy(sSection2, "[");
		strcat(sSection2, sSection);
		strcat(sSection2, "]\r\n");

		int nSecBegin = 0;
		int nSecEnd;
		BOOL bFound;

		int nTemp;
		
		bFound = FALSE;
		for(;;)
		{
			if(nSecBegin >= nBufLen)
			{
				break;
			}
			
			nTemp = _memmem(&pBuf[nSecBegin], nBufLen - nSecBegin,
				sSection2, strlen(sSection2));
			if(nTemp == -1)
			{
				//没有找到这个Section
				break;
			}

			//绝对位置
			nSecBegin += nTemp;

			//在sSection2之前，没有内容，或者内容是\r\n才是
			if(nSecBegin == 0)
			{
				//确实是
			}
			else if(nSecBegin >= 2 && pBuf[nSecBegin - 2] == '\r'
				&& pBuf[nSecBegin - 1] == '\n')
			{
				//确实是
			}
			else
			{
				//假的，继续找
				nSecBegin += strlen(sSection2);
				continue;
			}

			nSecBegin += strlen(sSection2) - 2;
			//nSecBegin是从[Section]之后开始, 也就是从\r\n开始
			bFound = TRUE;
			break;
		}

		delete[] sSection2;
		if(!bFound) break;

		//在nSecBegin和nSecEnd之前，就是这个Section的管辖范围

		char *pTemp;
		
		pTemp = (char *)memchr(&pBuf[nSecBegin], '[', nBufLen - nSecBegin);
		if(pTemp == NULL)
		{
			//这是最后一个Section
			nSecEnd = nBufLen;
		}
		else
		{
			nSecEnd = pTemp - pBuf;
		}
		int nSecLen2 = nSecEnd - nSecBegin;
		*pnSecBegin = nSecBegin;
		*pnSecEnd = nSecEnd;

		//找Key=

		int nKeyBegin = nSecBegin;
		int nKeyEnd;

		int nKeyLen = strlen(sKey);
		char *sKey2 = new char[nKeyLen + 4];
		if(sKey2 == NULL) break;
		strcpy(sKey2, "\r\n");
		strcat(sKey2, sKey);
		strcat(sKey2, "=");
		
		bFound = FALSE;
		for(;;)
		{
			if(nKeyBegin >= nSecEnd)
			{
				break;
			}
			
			nTemp = _memmem(&pBuf[nKeyBegin], nSecEnd - nKeyBegin,
				sKey2, strlen(sKey2));
			if(nTemp == -1)
			{
				//没有找到这个Key
				break;
			}
			nKeyBegin += nTemp;

			nKeyBegin += strlen(sKey2);//nKeyBegin是从=之后开始
			bFound = TRUE;
			break;
		}

		delete[] sKey2;
		if(!bFound) break;

		//nKeyEnd是遇到\r\n或者nBufLen之前
		pTemp = (char *)memchr(&pBuf[nKeyBegin], '\r', nSecEnd - nKeyBegin);
		if(pTemp == NULL)
		{
			//这是最后一个Key
			nKeyEnd = nSecEnd;
		}
		else
		{
			nKeyEnd = pTemp - pBuf;
		}
		int nKenLen2 = nKeyEnd - nKeyBegin;

		*pnKeyBegin = nKeyBegin;
		*pnKeyEnd = nKeyEnd;
		bRet = TRUE;
		break;
	}

	return bRet;
}
