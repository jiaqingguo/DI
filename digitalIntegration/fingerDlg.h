#ifndef FINGERDLG_H
#define FINGERDLG_H

#pragma once

#include <afxwin.h>
#include "Resource.h"
#include <QDebug>
#include <QMessagebox>
#include <iostream>
#include <string>
#include <databaseDI.h>


#include "libxzkfp/include/zkinterface.h"
#include "libxzkfp/include/libzkfperrdef.h"
#include "libxzkfp/include/libzkfptype.h"
#include "libxzkfp/include/libzkfp.h"


#ifdef _WIN64
#pragma comment(lib, "libxzkfp/x64lib/libzkfp.lib")
#else
#pragma comment(lib, "libxzkfp/x86lib/libzkfp.lib")
#endif

#define ENROLLCNT 3
#define MAX_TEMPLATE_SIZE 2048

#define FP_THRESHOLD_CODE 1
#define FP_MTHRESHOLD_CODE 2

extern HANDLE m_hDevice;    //�豸����ʵ�����
//extern HANDLE m_hDBCache;   //���������
//extern HANDLE m_hThreadWork;
//extern int m_imgFPWidth;
//extern int m_imgFPHeight;

extern bool m_bIdentify;
extern bool m_bRegister;
//extern bool m_bStopThread;
extern int m_enrollIdx;
extern int m_score;

//extern unsigned char m_arrPreRegTemps[ENROLLCNT][MAX_TEMPLATE_SIZE];  //3  2048   �洢ָ��
//extern unsigned int m_arrPreTempsLen[3];
//extern int m_Tid;   //ָ�� ID��>0 �� 32 λ�޷���������


//extern unsigned char* m_pImgBuf;

//Last register template, use for verify   ��һ��ע��ģ�壬������֤
//extern unsigned char m_szLastRegTemplate[MAX_TEMPLATE_SIZE];
//extern int m_nLastRegTempLen;
//extern int m_nFakeFunOn;

class fingerDlg : public QDialog
{
	//Q_OBJECT
public:
	HANDLE hDBCache; //�������ľ��
	//HANDLE hDevice;
	HANDLE hThreadWork;
	//bool bRegister;
	unsigned char* pImgBuf ;
	int imgFPWidth;
	int imgFPHeight;
	bool bStopThread;

	//bool bIdentify;
	//int enrollIdx;

	unsigned char arrPreRegTemps[ENROLLCNT][MAX_TEMPLATE_SIZE];  //3  2048   �洢ָ��
	unsigned int arrPreTempsLen[3];
	int Tid ;   //ָ�� ID��>0 �� 32 λ�޷���������


	//Last register template, use for verify   ��һ��ע��ģ�壬������֤
	unsigned char szLastRegTemplate[MAX_TEMPLATE_SIZE];
	unsigned char szLastRegTemplate2[MAX_TEMPLATE_SIZE];
	int nLastRegTempLen;
	int nLastRegTempLen2;
	int nFakeFunOn;

	fingerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
	// �Ի�������
	enum { IDD = IDD_LIBZKFPDEMO_DIALOG };


	void finger_init();

	void DoRegister(unsigned char* temp, int len);
	void DoVerify(unsigned char *temp, int len);

	//���ݱ��ļ��ж���ı���ʹ�õĺ���
	//void finger_passing_arguments(HANDLE &hDevice, bool bRegister);

	static DWORD WINAPI ThreadCapture(LPVOID lParam);

	

};
#endif
