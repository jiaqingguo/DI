﻿//#ifndef FINGERDLG_H
//#define FINGERDLG_H
//
//#pragma once
//
////#include <afxwin.h>
////#include "Resource.h"
//#include <QDebug>
//#include <QMessagebox>
//#include <iostream>
//#include <string>
//#include <databaseDI.h>
////#include "zkfinger.h"
//
////#include "libxzkfp/include/zkinterface.h"
////#include "libxzkfp/include/libzkfperrdef.h"
////#include "libxzkfp/include/libzkfptype.h"
//#include "libxzkfp/include/libzkfp.h"
//
//
////#ifdef _WIN64
////#pragma comment(lib, "libxzkfp/x64lib/libzkfp.lib")
////#else
////#pragma comment(lib, "libxzkfp/x86lib/libzkfp.lib")
////#endif
//
//#define ENROLLCNT 3
//#define MAX_TEMPLATE_SIZE 2048
//
//extern HANDLE m_hDevice;    //设备操作实例句柄
//extern bool m_bIdentify;
//extern bool m_bRegister;
//extern int m_enrollIdx;
//extern int m_score;
//
//class fingerDlg : public QDialog
//{
//	Q_OBJECT
//public:
//	HANDLE hDBCache; //缓冲区的句柄
//	HANDLE hThreadWork;
//	unsigned char* pImgBuf;
//	int imgFPWidth;
//	int imgFPHeight;
//	bool bStopThread;
//	unsigned char arrPreRegTemps[ENROLLCNT][MAX_TEMPLATE_SIZE];  //3  2048   存储指纹
//	unsigned int arrPreTempsLen[3];
//	int Tid;   //指纹 ID（>0 的 32 位无符号整数）
//	int nFakeFunOn;
//
//	fingerDlg(QDialog* pParent = NULL);	// 标准构造函数
//
//	~fingerDlg();
//
//	void finger_init();
//
//	void DoRegister(unsigned char* temp, int len);
//	void DoVerify(unsigned char *temp, int len);
//
//	static DWORD WINAPI ThreadCapture(LPVOID lParam);
//
//	//ZkFinger *m_zkfinger = nullptr;
//	//void DoRegister2(unsigned char* temp, int len);
//	//void DoVerify2(unsigned char *temp, int len);
//	QByteArray QStringToChar(const QString& str);
//	QString CharToQString(const unsigned char* buffer, int length);
//
//signals:
//	void login_succ();
//	void regist_succ();
//	void no_regist_finger();
////private slots:
////	void onCapture();
//
//
//
//
//
//};
//#endif
