#pragma once
#include "pch.h"

#define ServerName "AppStartServer"

/*
* 加载成功回调
*/
//using LoadingProgressCallBack = std::function<void()>;
typedef  void (*LoadingProgressCallBack)();

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
	void startProgram(const std::string&);

	/*
	* 通过脚本启动程序
	*/
	void startProgramFromBat(const std::string&);

	/*
	* 监听启动程序主窗口变化（例如：VS启动时首先启动的程序的启动页，所以获取的窗口句柄是启动页句柄）
	*/
	void hwndListen();

	/*
	* 关闭当前启动的程序
	*/
	void closeProgram();

	/*
	* 显示当前启动的程序
	*/
	void showProgram();

	/*
	* 通过进程获取窗口句柄
	*/
	HWND getMainWin(DWORD);

	/*
	* 
	*/
	bool queryProcessId(HANDLE);

	/*
	* 设置启动成功回调
	*/
	void setSuccessCallBack(LoadingProgressCallBack callBack) { _successCallBack = callBack; };

	/*
	* 设置远程程序关闭时回调
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

