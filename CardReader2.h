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

	//½«¶Á¿¨Æ÷×¼±¸ºÃ
	int GetReader(void);

	int IsCardOn(unsigned short *pnCardType);

	//¶Á¿¨ºÅºÍÓà¶î
	int GetBalance(unsigned long *pnCardNo, unsigned int *pnBalance);

	//Ð´Óà¶î
	int SetBalance(unsigned long nCardNo, unsigned int nBalance);

private:

	//¶Á¿¨Æ÷¾ä±ú
	HANDLE m_hReader;
	//ÉÆºó
	void Close(void);
};

#endif // !defined(AFX_CARDREADER2_H__58D4E5C7_26F6_4803_A185_36BFAAB128B1__INCLUDED_)
