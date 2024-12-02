#pragma once
#include "pch.h"

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
	* �����������������ڱ仯�����磺VS����ʱ���������ĳ��������ҳ�����Ի�ȡ�Ĵ��ھ��������ҳ�����
	*/
	void hwndListen();

	/*
	* �رյ�ǰ�����ĳ���
	*/
	void closeProgram();
protected:

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

