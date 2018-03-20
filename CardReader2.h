// CardReader2.h: interface for the CCardReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARDREADER2_H__58D4E5C7_26F6_4803_A185_36BFAAB128B1__INCLUDED_)
#define AFX_CARDREADER2_H__58D4E5C7_26F6_4803_A185_36BFAAB128B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WINSCARD.H"

class CCardReader  
{
public:
	CCardReader();
	virtual ~CCardReader();

	//��������׼����
	int GetReader(void);

	int IsCardOn(unsigned short *pnCardType);

	//�����ź����
	int GetBalance(unsigned long *pnCardNo, unsigned int *pnBalance);

	//д���
	int SetBalance(unsigned long nCardNo, unsigned int nBalance);

private:

	//���������
	HANDLE m_hReader;
	//�ƺ�
	void Close(void);
};

#endif // !defined(AFX_CARDREADER2_H__58D4E5C7_26F6_4803_A185_36BFAAB128B1__INCLUDED_)
