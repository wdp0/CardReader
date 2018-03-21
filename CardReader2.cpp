// CardReader2.cpp: implementation of the CCardReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CardReader.h"
#include "CardReader2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "hcrf32.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCardReader::CCardReader()
{
	m_hReader = NULL;
}

CCardReader::~CCardReader()
{
	Close();
}

void CCardReader::Close(void)
{
	if(m_hReader)
	{
		hc_exit(m_hReader);
		m_hReader = NULL;
	}
}

//将读卡器准备好
int CCardReader::GetReader(void)
{
	HANDLE hReader = hc_init(100, 115200);

	if((signed int)hReader > 0)
	{
		m_hReader = hReader;
		return TRUE;
	}

	return FALSE;
}

//卡在吗
int CCardReader::IsCardOn(unsigned short *pnCardType)
{
	unsigned short nCardType = -1;
	int nRet = -1;

	if(!m_hReader)
	{
		return FALSE;
	}
#define REQUEST_ALL		(1)
#define REQUEST_IDLE	(0)

	nRet = rf_request(m_hReader, REQUEST_ALL, (unsigned __int16 *)&nCardType);
	if(nRet)
	{
		//没有检测到卡
		return FALSE;
	}

	*pnCardType = nCardType;
	return TRUE;
}

//读卡号和余额
int CCardReader::GetBalance(unsigned long *pnCardNo, unsigned int *pnBalance)
{
	unsigned short nCardType = -1;
	unsigned long nCardNo = 0;
	int nRet = -1;
	unsigned int n = 0;
	unsigned int n2 = 0;

	if(!IsCardOn(&nCardType))
	{
		//没有检测到卡
		return FALSE;
	}

	nRet = rf_anticoll(m_hReader, 0, pnCardNo);
	if(nRet)
	{
		return FALSE;
	}

	unsigned char nSize = 0;
	nRet = rf_select(m_hReader, *pnCardNo, &nSize);
	if(nRet)
	{
		return FALSE;
	}
	//读操作使用的密码
	static const unsigned char KEY_FOR_READ[] = {'G', 'A', 'U', 'T', 'O', '\0'};
#define BLOCK_NUM		(4)

	nRet = rf_authentication_key(m_hReader, 0, BLOCK_NUM, (unsigned char *)KEY_FOR_READ);
	if(nRet)
	{
		return FALSE;
	}

	unsigned char acData[16] = {0};

	nRet = rf_read(m_hReader, BLOCK_NUM, acData);
	if(nRet)
	{
		return FALSE;
	}

	n = *((unsigned int *)acData);
	n2 = *((unsigned int *)(acData + 4));
	if((~n) != n2)
	{
		//有异常
		*pnBalance = n;
	}
	else
	{
		*pnBalance = n;
	}

	nRet = rf_halt(m_hReader);

	return TRUE;
}

//写余额
int CCardReader::SetBalance(unsigned long nCardNo, unsigned int nBalance)
{
	unsigned long nCardNo2 = 0;
	unsigned int nBalance2 = 0;
	unsigned short nCardType = -1;
	int nRet = -1;
	unsigned int n = 0;

	nRet = rf_request(m_hReader, REQUEST_ALL, (unsigned __int16 *)&nCardType);
	if(nRet)
	{
		return FALSE;
	}

	nRet = rf_anticoll(m_hReader, 0, &nCardNo2);
	if(nRet)
	{
		return FALSE;
	}
	//比较卡号是否相同
	if(nCardNo != nCardNo2)
	{
		//中途换卡了
		return FALSE;
	}

	unsigned char nSize = 0;
	nRet = rf_select(m_hReader, nCardNo, &nSize);
	if(nRet)
	{
		return FALSE;
	}
	static const unsigned char KEY_FOR_WRITE[] = {'G', 'A', 'U', 'T', 'O', '\0'};
	nRet = rf_authentication_key(m_hReader, 0, BLOCK_NUM, (unsigned char *)KEY_FOR_WRITE);
	if(nRet)
	{
		return FALSE;
	}

	unsigned char acData[16] = {0};
	memcpy(acData, &nBalance, sizeof(nBalance));
	n = ~nBalance;
	memcpy(acData + 4, &n, sizeof(n));
	nRet = rf_write(m_hReader, BLOCK_NUM, acData);
	if(nRet)
	{
		return FALSE;
	}
	nRet = rf_halt(m_hReader);

	return TRUE;
}
