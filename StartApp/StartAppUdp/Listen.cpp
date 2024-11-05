#define _CRT_SECURE_NO_WARNINGS//��
#include "Listen.h"

HWND g_CurrentHWND = 0;
int Pnum = 0;//����������

//��ȡ��ǰ��Ծ�Ĵ���
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	if (GetParent(hWnd) == NULL && IsWindowVisible(hWnd))  //�ж��Ƿ񶥲㴰�ڲ��ҿɼ�
	{
		Pnum++;
		char WindowTitle[100] = { 0 };
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

//��ȡ�û�ID
std::string getUserName() 
{
	const int MAX_LEN = 255;
	char szBuffer[MAX_LEN+1];
	DWORD len = MAX_LEN+1;
	if (GetUserName(szBuffer, &len)) //�û���������szBuffer��,len���û����ĳ���
	{
		std::cout << "user name:" << szBuffer << std::endl;
		return szBuffer;
	}
	std::cout << "user name:" << std::endl;
	return "";
}

//���ھ��ת�ַ���
std::string HWNDtoStr(HWND hwnd) 
{
	std::stringstream ss;
	ss << hwnd;
	return ss.str();
}

//�ַ���ת���ھ��
HWND StrToHWND(const std::string& str) 
{
	HWND hwnd = NULL;
	sscanf(str.c_str(), "%p", &hwnd); // �����ַ�����һ����Ч��ָ���ʾ
	return hwnd;
}

//ͨ�����ƻ�ȡ����ID
DWORD FindProcessIDByName(const std::string& processName)//0 not found ; other found; processName "processName.exe"
{
	PROCESSENTRY32 pe32;
	//��ʹ������ṹǰ�����������Ĵ�С
	pe32.dwSize = sizeof(pe32);
	//��ϵͳ�����еĽ����ĸ�����
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	//�������̿��գ�������ʾÿ�����̵���Ϣ
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		if (pe32.szExeFile == processName)//��������
		{
			::CloseHandle(hProcessSnap);
			return pe32.th32ProcessID;//����ID
		}
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	//��Ҫ���������snapshot����
	::CloseHandle(hProcessSnap);
	return 0;
}

//��Ҫ�ر� ����̫��ʹ �����ڲ��ɣ�
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

//�رս���
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

//��ȡ�ӽ��� ������ֱ�Ӱѹرս��̺����Ž�ȥ�� ��ȡ��ֱ�ӹر�
BOOL CALLBACK ListChildProcesses(DWORD processId) {
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapShot, &pe32)) {
		do {
			if (pe32.th32ParentProcessID == processId) {
				std::cout << "�ӽ���ID: " << pe32.th32ProcessID << L", ������: " << pe32.szExeFile << std::endl;
				CloseProcessByID(pe32.th32ProcessID);
			}
		} while (Process32Next(hSnapShot, &pe32));
	}
	CloseHandle(hSnapShot);
	return TRUE;
}

//�жϽ����Ƿ��Ƴ�
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

//ͨ������ID��ȡ���ھ�� ������ѭ���е���
HWND getMainHWND(DWORD dword)
{
	g_CurrentHWND = 0;
	::EnumWindows(EnumWindowsProc, dword);
	std::cerr << "EnumWindows:" << std::endl;
	return g_CurrentHWND;
}

//��������
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
	// ��������̨����
	bRet = CreateProcess(
		NULL,               // ��������ָ��Ӧ�ó�����
		strCmdLine.GetBuffer(),  // �����в���������������cmd.exe
		NULL,               // ��ȫ����
		NULL,               // �̰߳�ȫ����
		FALSE,              // ָ����ǰ���̵ľ���Ƿ��½��̼̳�
		CREATE_NEW_CONSOLE, // ����һ���µĴ��ڣ�����̨��
		NULL,               // �½��̵Ļ�������
		NULL,               // �½��̵ĵ�ǰĿ¼��
		&si,                // ָ��STARTUPINFO�ṹ��ָ��
		&pi                 // ָ��PROCESS_INFORMATION�ṹ��ָ��
	);

	if (bRet) 
	{
		// �ȴ��½��̽���
		//WaitForSingleObject(pi.hProcess, INFINITE); 

		// �ȴ���������
		::WaitForInputIdle(pi.hProcess, INFINITE);

		// �رս��̺��߳̾��
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
	//��ʼ��winsock2����
	WSADATA  wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
		std::cout << "WSAStartup error:" << GetLastError() << std::endl;
		return 0;
	}

	//1.����UDP���ݱ��׽���
	_sokket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_sokket == INVALID_SOCKET) {
		std::cout << "socket  error:" << GetLastError() << std::endl;
		return 0;
	}

	//2.�󶨵�Ip��ַ�Ͷ˿�
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(1020);//�����ֽ���
	_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	//inet_pton(AF_INET, "127.0.0.1", &_addr.sin_addr);//ip��ַת�����ֽ���

	_len = sizeof(SOCKADDR);
	if (bind(_sokket, (SOCKADDR*)&_addr, _len) == SOCKET_ERROR) {
		std::cout << "bind error:" << GetLastError() << std::endl;
		return 0;
	}

	int nNetTimeout = 5000; //5��
	//����ʱ��
	if (setsockopt(_sokket, SOL_SOCKET, SO_RCVTIMEO, (char*)&nNetTimeout, sizeof(int)) == SOCKET_ERROR) {
		std::cout << "setsockopt error:" << GetLastError() << std::endl;
		return 0;
	}

	//3.���ܻ��߷�������recvfrom, sendto ,��ͬ��TCP�� recv�� send
	int   ret = -1;
	memset(&_addrClient, 0, sizeof(_addrClient));
	return 1;
}

void Listen::run()
{
	do {
		char buf[1024] = { 0 };
		//Ĭ���������ģ�Ҳ����˵�����û�����ݹ�������һֱ�ȴ�

		int ret = recvfrom(_sokket, buf, 1024, 0, (SOCKADDR*)&_addrClient, &_len);
		//���ܿͻ��˵ĵ�ַ
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

	//�ر��׽���
	::closesocket(_sokket);
	//����winsock2����
	::WSACleanup();
}

void Listen::startProgram(const std::string& strPath)
{

	if (isExistProcess(_dwProcessId))//��ʱΪ�˽����¼����������� ������ûɶ����
	{
		std::cerr<<"PID:" << _dwProcessId << "Already started" << "......" << std::endl;
		return;
	}

	bool isStart = false;
	if (strPath != "")
	{
		// Ӧ�ó���·��
		LPCSTR applicationPath = strPath.c_str();
		std::cerr << "start application:" << strPath << "......" << std::endl;
		CREATE_STARTUPINFO(si, pi)
		if (CreateProcess(applicationPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			// �ȴ���������
			WaitForInputIdle(pi.hProcess, INFINITE);
			_dwProcessId = pi.dwProcessId;//��ȡ����ID

			std::cerr << "start application......" << std::endl;
			Sleep(200);//��ʱ����������
			std::cerr << "success to start application......" << std::endl;
			isStart = true;
			// �ȴ��½��̽���
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

void Listen::hwndListen()
{
	bool isWindow = false;//Ӧ�ó����Ƿ�������ʱ�Ѿ��򿪴���
	unsigned long long time = 0;
	while (_dwProcessId !=0)
	{
		//����߳�ID
		if (!::isExistProcess(_dwProcessId))
		{
			::ListChildProcesses(_dwProcessId);
			::CloseProcessByID(_dwProcessId);
			//::exit(0);
			break;
		}

		//��ⴰ�ھ��
		if (::IsWindow(_currentHWND) == FALSE)//���Ӧ�ó��򴰿�δ�򿪻����仯
		{
			if (isWindow)//��������Ѿ��򿪹� �Ǿ�֤����ʱ���ڷ����仯
			{
				_currentHWND = getMainHWND(_dwProcessId);

				if (_currentHWND != 0)//ͨ���߳�ID��ȡ�µĴ��ھ��
				{
					time = 0;
					::Sleep(100);
					::ShowWindow(_currentHWND, SW_MAXIMIZE);
					std::cerr << "Window HWND:" << _currentHWND <<  "  " << _dwProcessId << std::endl;
				}
				else
				{
					if (time == 0)//��¼���ڷ����仯ʱ��
					{
						time = ::GetTickCount64();
					}
					else if (::GetTickCount64() - time >= 3000)//����3��رճ���
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
				if (_currentHWND != 0)//�ж�����ʱ�����Ƿ��Ѿ��򿪣���������ҳ���ڣ�
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