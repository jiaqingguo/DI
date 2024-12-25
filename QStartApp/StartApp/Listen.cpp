#define _CRT_SECURE_NO_WARNINGS//别动

#include "Listen.h"

#include <vector>

#include <windows.h>
#include <winnetwk.h>

#pragma comment(lib, "Mpr.lib")


HWND g_CurrentHWND = 0;
int Pnum = 0;//父窗口数量

//获取当前活跃的窗口
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	if (GetParent(hWnd) == NULL && IsWindowVisible(hWnd))  //判断是否顶层窗口并且可见
	{
		Pnum++;
		char WindowTitle[100] = { 0 };
		//wchar_t WindowTitle[100] = { 0 };
		::GetWindowText(hWnd, WindowTitle, 100);
		//printf("-------------------------------------------\n");
		//printf("%d: %s\n", Pnum, WindowTitle);

		DWORD lpdwProcessId;
		::GetWindowThreadProcessId(hWnd, &lpdwProcessId);
		if (lpdwProcessId == lParam)
		{
			g_CurrentHWND = hWnd;
		}
	}
	return true;
}

//获取用户ID
std::string getUserName() 
{
	const int MAX_LEN = 255;
	char szBuffer[MAX_LEN+1];
	//wchar_t szBuffer[MAX_LEN + 1];
	DWORD len = MAX_LEN+1;
	if (GetUserName(szBuffer, &len)) //用户名保存在szBuffer中,len是用户名的长度
	{
		std::cout << "user name:" << szBuffer << std::endl;
		return szBuffer;
	}
	std::cout << "user name:" << std::endl;
	return "";
}

//窗口句柄转字符串
std::string HWNDtoStr(HWND hwnd) 
{
	std::stringstream ss;
	ss << hwnd;
	return ss.str();
}

//字符串转窗口句柄
HWND StrToHWND(const std::string& str) 
{
	HWND hwnd = NULL;
	sscanf(str.c_str(), "%p", &hwnd); // 假设字符串是一个有效的指针表示
	return hwnd;
}

//通过名称获取进程ID
DWORD FindProcessIDByName(const std::string& processName)//0 not found ; other found; processName "processName.exe"
{
	PROCESSENTRY32 pe32;
	//在使用这个结构前，先设置它的大小
	pe32.dwSize = sizeof(pe32);
	//给系统内所有的进程拍个快照
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	//遍历进程快照，轮流显示每个进程的信息
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		if (pe32.szExeFile == processName)//进程名称
		{
			::CloseHandle(hProcessSnap);
			return pe32.th32ProcessID;//进程ID
		}
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	//不要忘记清除掉snapshot对象
	::CloseHandle(hProcessSnap);
	return 0;
}

//将要关闭 （不太好使 后面在测测吧）
bool isProcessExiting(DWORD processId) {
	HANDLE hProcess = OpenProcess(SYNCHRONIZE, FALSE, processId);
	if (hProcess == NULL) {
		std::cerr << "OpenProcess failed: " << GetLastError() << std::endl;
		return false;
	}

	DWORD exitCode;
	if (GetExitCodeProcess(hProcess, &exitCode) == 0) {
		std::cerr << "GetExitCodeProcess failed: " << GetLastError() << std::endl;
		CloseHandle(hProcess);
		return false;
	}

	CloseHandle(hProcess);
	return exitCode != STILL_ACTIVE;
}

//关闭进程
BOOL CloseProcessByID(DWORD dwProcessId) {
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessId);
	if (hProcess == NULL) {
		std::cerr << "OpenProcess failed: " << GetLastError() << std::endl;
		return FALSE;
	}

	BOOL bRet = TerminateProcess(hProcess, 1);
	if (!bRet) {
		std::cerr << "TerminateProcess failed: " << GetLastError() << std::endl;
	}

	CloseHandle(hProcess);
	return bRet;
}

//获取子线程
std::vector<DWORD> getChildProcesses(DWORD processId)
{
	std::vector<DWORD> out;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapShot, &pe32)) {
		do {
			if (pe32.th32ParentProcessID == processId) {
				std::cout << "子进程ID: " << pe32.th32ProcessID << L", 进程名: " << pe32.szExeFile << std::endl;
				out.push_back(pe32.th32ProcessID);
			}
		} while (Process32Next(hSnapShot, &pe32));
	}
	CloseHandle(hSnapShot);
	return out;
}

//获取子进程 这里我直接把关闭进程函数放进去了 获取完直接关闭
BOOL CALLBACK ListChildProcesses(DWORD processId) {
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapShot, &pe32)) {
		do {
			if (pe32.th32ParentProcessID == processId) {
				std::cout << "子进程ID: " << pe32.th32ProcessID << L", 进程名: " << pe32.szExeFile << std::endl;
				CloseProcessByID(pe32.th32ProcessID);
			}
		} while (Process32Next(hSnapShot, &pe32));
	}
	CloseHandle(hSnapShot);
	return TRUE;
}

//判断进程是否推出
BOOL isExistProcess(DWORD process_id)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {

		if (pe.th32ProcessID == process_id)
		{
			return TRUE;
		}
	}
	CloseHandle(hSnapshot);
	return FALSE;
}

//通过进程ID获取窗口句柄 不建议循环中调用
HWND getMainHWND(DWORD dword)
{
	g_CurrentHWND = 0;
	::EnumWindows(EnumWindowsProc, dword);
	std::cerr << "EnumWindows:" << std::endl;
	return g_CurrentHWND;
}

//启动程序
bool start(const std::string& cmd)
{
	bool b = false;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	BOOL bRet = FALSE;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CString strCmdLine(cmd.c_str());
	// 创建控制台进程
	bRet = CreateProcess(
		NULL,               // 不在这里指定应用程序名
		strCmdLine.GetBuffer(),  // 命令行参数，这里是启动cmd.exe
		NULL,               // 安全属性
		NULL,               // 线程安全属性
		FALSE,              // 指定当前进程的句柄是否被新进程继承
		CREATE_NEW_CONSOLE, // 创建一个新的窗口（控制台）
		NULL,               // 新进程的环境变量
		NULL,               // 新进程的当前目录名
		&si,                // 指向STARTUPINFO结构的指针
		&pi                 // 指向PROCESS_INFORMATION结构的指针
	);

	if (bRet) 
	{
		// 等待新进程结束
		//WaitForSingleObject(pi.hProcess, INFINITE); 

		// 等待程序启动
		::WaitForInputIdle(pi.hProcess, INFINITE);

		// 关闭进程和线程句柄
		::CloseHandle(pi.hProcess);
		::CloseHandle(pi.hThread);
		b = true;
		std::cout << "Console process has been launched successfully." << std::endl;
	}
	else {
		std::cerr << "Failed to launch console process." << std::endl;
	}
	return b;
}

Listen::Listen()
{
	_userName = getUserName();
}

Listen::~Listen()
{
	closeProgram();
}

bool Listen::init()
{
	//初始化winsock2环境
	WSADATA  wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
		std::cout << "WSAStartup error:" << GetLastError() << std::endl;
		return 0;
	}

	//1.创建UDP数据报套接字
	_sokket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_sokket == INVALID_SOCKET) {
		std::cout << "socket  error:" << GetLastError() << std::endl;
		return 0;
	}

	//2.绑定到Ip地址和端口
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(1020);//网络字节序
	_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	//inet_pton(AF_INET, "127.0.0.1", &_addr.sin_addr);//ip地址转网络字节序

	_len = sizeof(SOCKADDR);
	if (bind(_sokket, (SOCKADDR*)&_addr, _len) == SOCKET_ERROR) {
		std::cout << "bind error:" << GetLastError() << std::endl;
		return 0;
	}

	int nNetTimeout = 5000; //5秒
	//接收时限
	if (setsockopt(_sokket, SOL_SOCKET, SO_RCVTIMEO, (char*)&nNetTimeout, sizeof(int)) == SOCKET_ERROR) {
		std::cout << "setsockopt error:" << GetLastError() << std::endl;
		return 0;
	}

	//3.接受或者发送数据recvfrom, sendto ,不同于TCP的 recv与 send
	memset(&_addrClient, 0, sizeof(_addrClient));
	return 1;
}

void Listen::run()
{
	do {
		char buf[1024] = { 0 };
		//默认是阻塞的，也就是说，如果没有数据过来，会一直等待

		int ret = recvfrom(_sokket, buf, 1024, 0, (SOCKADDR*)&_addrClient, &_len);
		//接受客户端的地址
		std::cout << "recvfrom " << ret << ":    " << buf << std::endl;
		if (ret != -1)
		{
			std::string str(buf);
			str = str.substr(1, str.length());
			size_t index = str.find('&');
			if (index!=-1)
			{
				std::string user = str.substr(0, index);
				if (user!=_userName)
				{
					continue;
				}
			}
			str = str.substr(index+1, str.length());
			
			if (buf[0]=='0')
			{
				std::cout << "closeProgram " << ret << ":    " << _dwProcessId  <<"......" << std::endl;
				closeProgram();
			}
			else if (buf[0] == '1'&& _static==0)
			{
				_static = 1;
				std::cout << "recvfrom " << ret << ":    " << buf <<"......" << std::endl;
				startProgram(str);
			}
		}
		Sleep(1000);
	} while (1);

	//关闭套接字
	::closesocket(_sokket);
	//清理winsock2环境
	::WSACleanup();
}

void Listen::startProgram(const std::string& strPath)
{
	if (isExistProcess(_dwProcessId))//当时为了解决登录黑屏问题添加 好像是没啥用了
	{
		std::cerr<<"PID:" << _dwProcessId << "Already started" << "......" << std::endl;
		return;
	}

	bool isStart = false;
	if (strPath != "")
	{
		// 应用程序路径
		LPCSTR applicationPath = strPath.c_str();
		std::cerr << "start application:" << strPath << "......" << std::endl;
		CREATE_STARTUPINFO(si, pi)
		if (CreateProcess(applicationPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			// 等待程序启动
			WaitForInputIdle(pi.hProcess, INFINITE);
			_dwProcessId = pi.dwProcessId;//获取进程ID

			std::cerr << "start application......" << std::endl;
			Sleep(200);//给时间启动窗口
			std::cerr << "success to start application......" << std::endl;
			isStart = true;
			// 等待新进程结束
			//WaitForSingleObject(pi.hProcess, INFINITE);
		}
		else
		{
			std::cerr << "Failed to start application......" << std::endl;
		}
		CLOSE_HANDLE(pi)
	}

	if (!isStart)
		::exit(0);

}

void Listen::startProgramFromBat(const std::string& strPath)
{

	int index = strPath.rfind("\\");
	if(index==-1)
		index = strPath.rfind("/");

	std::string directory = strPath.substr(0, index+1);

	// 定义并初始化SHELLEXECUTEINFO结构体
	SHELLEXECUTEINFO sei = { 0 };
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;  // 设置该标志位以获取进程句柄
	sei.lpFile = TEXT(strPath.c_str());  // 要打开的应用程序路径
	sei.lpDirectory = directory.c_str();
	// 使用ShellExecuteEx函数打开应用程序
	if (ShellExecuteEx(&sei))
	{
		// 获取进程ID
		DWORD pid = GetProcessId(sei.hProcess);
		
		std::vector<DWORD> dwProcessIds = getChildProcesses(pid);
		if (dwProcessIds.size()>0)
		{
			//Sleep(2000);//给时间启动窗口
			DWORD tmpId = dwProcessIds[0];//第一次拿倒的ID不是启动程序的ID
			//while (!::isExistProcess(tmpId))
			while (tmpId == dwProcessIds[0])
			{
				dwProcessIds = getChildProcesses(pid);
				if (tmpId != dwProcessIds[0])//当ID发生改变获取ID并跳出循环
				{

					_dwProcessId = dwProcessIds[dwProcessIds.size() - 1];
					std::cout << "id num: " << dwProcessIds.size() << std::endl;
					break;

				}
				tmpId = dwProcessIds[0];
			}
		}
		
		// 输出进程ID
		std::cout << "Process ID: " << _dwProcessId << std::endl;
		// 关闭进程句柄
		//CloseHandle(sei.hProcess);
	}
	else
	{
		// 打开应用程序失败
		std::cout << "Failed to open application." << std::endl;
	}

}

void Listen::hwndListen()
{
	bool isWindow = false;//应用程序是否在启动时已经打开窗口
	unsigned long long time = 0;
	while (_dwProcessId !=0)
	{
		//监测线程ID
		if (!::isExistProcess(_dwProcessId))
		{
			::ListChildProcesses(_dwProcessId);
			::CloseProcessByID(_dwProcessId);
			//::exit(0);
			break;
		}

		//监测窗口句柄
		if (::IsWindow(_currentHWND) == FALSE)//如果应用程序窗口未打开或发生变化
		{
			if (isWindow)//如果窗口已经打开过 那就证明此时窗口发生变化
			{
				_currentHWND = getMainHWND(_dwProcessId);

				if (_currentHWND != 0)//通过线程ID获取新的窗口句柄
				{
					time = 0;
					::Sleep(100);
					//::ShowWindow(_currentHWND, SW_MAXIMIZE);
					std::cerr << "Window HWND:" << _currentHWND <<  "  " << _dwProcessId << std::endl;
				}
				else
				{
					if (time == 0)//记录窗口发生变化时间
					{
						time = ::GetTickCount64();
					}
					else if (::GetTickCount64() - time >= 3000)//超过3秒关闭程序
					{
						::ListChildProcesses(_dwProcessId);
						::CloseProcessByID(_dwProcessId);
						//::exit(0);
						break;
					}
				}
			}
			else
			{
				_currentHWND = getMainHWND(_dwProcessId);
				if (_currentHWND != 0)//判断启动时窗口是否已经打开（包括启动页窗口）
				{
					//ShowWindow(_currentHWND, SW_MAXIMIZE);
					isWindow = true;
					//std::cerr << "Window Show" << _currentHWND <<"  " << _dwProcessId <<std::endl;
				}
			}
		}
		::Sleep(500);
	}
	//_threads.detach();
	_dwProcessId = -1;
	_currentHWND = 0;
	_static = 0;
	::exit(0);
}

void Listen::showProgram()
{
	HWND currentHWND = getMainHWND(_dwProcessId);
	if (currentHWND != 0)
	{
		if (::ShowWindow(currentHWND, SW_RESTORE))
		{
			std::cerr << "Sub Window HWND:" << currentHWND << " " << _dwProcessId << " Success_1" << std::endl;

		}
		else
		{
			std::cerr << "Sub Window HWND:" << currentHWND << " " << _dwProcessId << " Failed_1" << std::endl;
		}
		//RedrawWindow(currentHWND, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
		//UpdateWindow(currentHWND);
	}
	else
	{
		std::vector<DWORD> dwProcessIds = getChildProcesses(_dwProcessId);
		if (dwProcessIds.size()>0)
		{
			for (size_t i = 0; i < dwProcessIds.size(); i++)
			{
				_currentHWND = getMainHWND(dwProcessIds[i]);
				if (_currentHWND != 0) 
				{
					//if (::ShowWindow(currentHWND, SW_RESTORE))
					if(PostMessage(_currentHWND, WM_SYSCOMMAND, SC_RESTORE, 0))
					{
						std::cerr << "Sub Window HWND:" << _currentHWND << " " << dwProcessIds[i] << " Success_2" << std::endl;
					}
					else
					{
						std::cerr << "Sub Window HWND:" << _currentHWND << " " << dwProcessIds[i] << " Failed_2" << std::endl;
					}
				}
			}
			//RedrawWindow(_currentHWND, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
			//UpdateWindow(_currentHWND);
		}
	}
}

void Listen::closeProgram()
{
	if (_currentHWND != 0)
	{
		::ListChildProcesses(_dwProcessId);
		::CloseProcessByID(_dwProcessId);
		_dwProcessId = -1;
		_currentHWND = 0;
		_static = 0;
	}
}

void Listen::InitResource(const TCHAR* userName, const TCHAR* password, const TCHAR* localDrive, const TCHAR* remotePath)
{
//	NETRESOURCE net_Resource;

	// 初始化NETRESOURCE结构
	net_Resource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
	net_Resource.dwScope = RESOURCE_CONNECTED;
	net_Resource.dwType = RESOURCETYPE_DISK;
	net_Resource.dwUsage = 0;
	net_Resource.lpComment = NULL;
	net_Resource.lpLocalName = const_cast<TCHAR*>(localDrive); // 映射到本地驱动器
	net_Resource.lpProvider = NULL;
	net_Resource.lpRemoteName = const_cast<TCHAR*>(remotePath); // 共享资源的路径

	//DWORD dwFlags = CONNECT_UPDATE_PROFILE;

	// 取消已有连接
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);

	// 添加新连接
	DWORD dw = WNetAddConnection2(&net_Resource, password, userName, 0);
	switch (dw) {
	case ERROR_SUCCESS:
		//ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_ACCESS_DENIED:
		std::wcout << TEXT("没有权限访问！\n");
		break;
	case ERROR_ALREADY_ASSIGNED:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_INVALID_ADDRESS:
		std::wcout << TEXT("IP地址无效\n");
		break;
	case ERROR_NO_NETWORK:
		std::wcout << TEXT("网络不可达!\n");
		break;
	case ERROR_NO_TOKEN:
		std::wcout << TEXT("没有有效的凭据！请检查用户名和密码。\n");
		break;
	case ERROR_SESSION_CREDENTIAL_CONFLICT:
		std::wcout << TEXT("ERROR_SESSION_CREDENTIAL_CONFLICT。\n");
		break;
	default:
		std::wcout << TEXT("发生错误，错误代码: ") << dw << TEXT("\n");
		break;
	}
}

void Listen::CancleResource()
{
	// 取消已有连接
	DWORD result=WNetCancelConnection2("Y:", CONNECT_UPDATE_PROFILE, TRUE);

	// 检查返回值并打印结果
	if (result == NO_ERROR) {
		std::wcout << L"成功断开连接: " << net_Resource.lpLocalName << std::endl;
	}
	else {
		std::wcout << L"断开连接失败。错误代码: " << result << std::endl;
	}
}
