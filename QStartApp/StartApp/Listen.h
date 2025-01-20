#pragma once
#include "pch.h"

#define ServerName "AppStartServer"

/*
* ���سɹ��ص�
*/
//using LoadingProgressCallBack = std::function<void()>;
typedef  void (*LoadingProgressCallBack)();

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
	void startProgram(const std::string&);

	/*
	* ͨ���ű���������
	*/
	void startProgramFromBat(const std::string&);

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

	/*
	* ͨ�����̻�ȡ���ھ��
	*/
	HWND getMainWin(DWORD);

	/*
	* 
	*/
	bool queryProcessId(HANDLE);

	/*
	* ���������ɹ��ص�
	*/
	void setSuccessCallBack(LoadingProgressCallBack callBack) { _successCallBack = callBack; };

	/*
	* ����Զ�̳���ر�ʱ�ص�
	*/
	void setClosCallBack(LoadingProgressCallBack callBack) { _closeCallBack = callBack; };

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
	HWND _currentHWND = 0;

	std::string _userName = "";

	std::thread* _threads;

	LoadingProgressCallBack _successCallBack = nullptr;

	LoadingProgressCallBack _closeCallBack = nullptr;
};

