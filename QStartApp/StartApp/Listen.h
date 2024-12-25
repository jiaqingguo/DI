#pragma once
#include "pch.h"

#define ServerName "AppStartServer"

class Listen
{
public:
	Listen();
	~Listen();

	/*
	* ��ʼ��UDP(����)
	*/
	bool init();

	/*
	* ����ѭ���ȴ���Ϣ(����)
	*/
	void run();

	/*
	* �������
	*/
	void startProgram(const std::string& strPath);

	/*
	* ͨ���ű���������
	*/
	void startProgramFromBat(const std::string& strPath);

	/*
	* �����������������ڱ仯�����磺VS����ʱ���������ĳ��������ҳ�����Ի�ȡ�Ĵ��ھ��������ҳ�����
	*/
	void hwndListen();

	/*
	* �رյ�ǰ�����ĳ���
	*/
	void closeProgram();


	/*
	* ��ʾ��ǰ�����ĳ���
	*/
	void showProgram();

	void InitResource(const TCHAR* userName, const TCHAR* password, const TCHAR* localDrive, const TCHAR* remotePath);
	void CancleResource();
protected:
	NETRESOURCE net_Resource;
	int _len = 0;

	int _static = 0;

	SOCKET  _sokket = 0;
	sockaddr_in  _addr;
	sockaddr_in  _addrClient;

	DWORD _dwProcessId = -1;//
	HWND _currentHWND;

	std::string _userName = "";

	std::thread _threads;
};

