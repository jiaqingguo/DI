#pragma once
#include "pch.h"

class Listen
{
public:
	Listen();
	~Listen();

	/*
	* 初始化UDP(弃用)
	*/
	bool init();

	/*
	* 启动循环等待消息(弃用)
	*/
	void run();

	/*
	* 启动软件
	*/
	void startProgram(const std::string& strPath);

	/*
	* 监听启动程序主窗口变化（例如：VS启动时首先启动的程序的启动页，所以获取的窗口句柄是启动页句柄）
	*/
	void hwndListen();

	/*
	* 关闭当前启动的程序
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

