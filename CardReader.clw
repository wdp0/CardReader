; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCardReaderDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CardReader.h"

ClassCount=3
Class1=CCardReaderApp
Class2=CCardReaderDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DIALOG_LOGIN
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_CARDREADER_DIALOG
Resource5=IDD_DIALOG_CHANGE_PASS

[CLS:CCardReaderApp]
Type=0
HeaderFile=CardReader.h
ImplementationFile=CardReader.cpp
Filter=N

[CLS:CCardReaderDlg]
Type=0
HeaderFile=CardReaderDlg.h
ImplementationFile=CardReaderDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_CARDNO

[CLS:CAboutDlg]
Type=0
HeaderFile=CardReaderDlg.h
ImplementationFile=CardReaderDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CARDREADER_DIALOG]
Type=1
Class=CCardReaderDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_CARDNO,edit,1342179456
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_BALANCE,edit,1342179456
Control5=IDC_EDIT_RECHARGE,edit,1342251136
Control6=ID_BUTTON_RECHARGE,button,1342242816
Control7=ID_BUTTON_CLEAR,button,1342242816
Control8=ID_BUTTON_CHANGE_PASS,button,1342242816
Control9=IDC_EDIT_INFO,edit,1342179456

[DLG:IDD_DIALOG_LOGIN]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_RECHARGE,edit,1342242976
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_CHANGE_PASS]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_RECHARGE,edit,1342242976
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_RECHARGE2,edit,1342242976
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_RECHARGE3,edit,1342242976

