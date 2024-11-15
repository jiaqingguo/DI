#include "Server.h"
#include "Tool.h"


#include <fstream>


#include <iostream>
#include <vector>
#include <filesystem>

#pragma warning(disable : 4996) 
#include "Winsock.h"
#undef  UNICODE
#include "windows.h"
#include <iostream>
#include <string>

#include <io.h>
#include <direct.h>
#include <string>
#include <tchar.h>
#include <WinNetWk.h>
#include <stdio.h>
#include "ZipFunction.h"
#pragma comment(lib, "Mpr.lib")
using namespace std;

#define RECV_PORT 4312	//接收端口
#define SEND_PORT 4302	//发送端口
#pragma comment(lib, "wsock32.lib")

namespace fs = std::filesystem;

char namePassword[1024] = "zwj 123456";	//用户名和密码





struct FileInformation
{
	int fileYear;
	int fileMonth;
	WORD fileDay;
	WORD fileHour;
	WORD fileMinute;
	DWORD FileSizeLow;
	char fileDir[260];
	char fileName[260];
};

FileInformation m_FileInformation;
//***************函数声明***************

//FileInformation m_FileInformation;
//***************函数声明***************
string Server::GetTimeString() {
	SYSTEMTIME st;
	GetLocalTime(&st);
	char temp[100];
	sprintf_s(temp, "%04d-%02d-%02d-%02d-%02d-%02d-%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	string str = temp;
	return str;
}

void Server::TimeSave(string data, string source)
{
	FILE* lOG;
	lOG = fopen(data.c_str(), "a");
	string  timeddd = GetTimeString() + source;
	fprintf(lOG, "%s  ", timeddd.c_str());
	fprintf(lOG, "\n");
	fclose(lOG);
}
vector<string> my_split(string str, string pattern)
{
	string::size_type pos;
	vector<string> result;

	str += pattern;//扩展字符串以方便操作
	int size = str.size();

	for (int i = 0; i < size; i++) {
		pos = str.find(pattern, i);
		if (pos < size) {
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

DWORD Server::startSock() {//初始化winsock
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		cout << "初始化失败" << endl;
		return -1;
	}
	return 1;
}
DWORD Server::createSocket() {
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClient == SOCKET_ERROR) {
		cout << "创建失败" << endl;
		WSACleanup();
		return -1;
	}
	severAddr.sin_family = AF_INET;
	severAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	severAddr.sin_port = htons(RECV_PORT);
	if (bind(sockClient, (struct sockaddr FAR*) & severAddr, sizeof(severAddr)) == SOCKET_ERROR) {
		//bind函数用于将socket和地址结构绑定
		cout << "绑定失败" << endl;
		return -1;
	}
	return 1;
}
DWORD Server::mkdir(char fileName[])
{
	//char path[1000];

	bool flag = CreateDirectory(fileName, NULL);
	if (flag)
	{
		cout << "创建文件：" << fileName << "成功" << endl;
		return 1;
	}
	else
	{
		cout << "创建文件：" << fileName << "失败" << endl;
		return 0;
	}


}
//删除空文件夹
DWORD Server::delFile(char fileName[]) {
	char path[1000];
	GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录

	strcat(path, "\\");
	strcat(path, fileName);
	// cout<<path<<endl;
	bool flag = RemoveDirectory(path);
	if (flag)
	{
		cout << "删除空文件夹：" << fileName << "成功" << endl;
		return 1;
	}
	else
	{
		cout << "删除空文件夹：" << fileName << "失败" << endl;
		return 0;
	}

}
//删除某个文件
DWORD Server::delFile1(char fileName[])
{
	//char path[1000];
 //	GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录

	/*strcat(path, "\\");
	strcat(path, fileName);
	cout << path << endl;*/
	if (remove(fileName) == 0)
	{
		cout << "删除成功" << endl;
		return 1;
	}
	else
	{
		cout << "删除失败" << endl;
		return 0;
	}
}

void Server::delete_listFiles(string dir)
{

	//在目录后面加上"\\*.*"进行第一次搜索
	string newDir = dir + "\\*.*";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		cout << "无文件" << endl;
		//	system("pause");
		return;
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//如果为文件夹，加上文件夹路径，再次遍历
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			newDir = dir + "\\" + fileinfo.name;
			delete_listFiles(newDir.c_str());//先遍历删除文件夹下的文件，再删除空的文件夹
			cout << newDir.c_str() << endl;
			if (_rmdir(newDir.c_str()) == 0) {//删除空文件夹
				cout << "delete empty dir success" << endl;
			}
			else {
				cout << "delete empty dir error" << endl;
			}
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			cout << file_path.c_str() << endl;
			if (remove(file_path.c_str()) == 0) {//删除文件
				cout << "delete file success" << endl;
			}
			else {
				cout << "delete file error" << endl;
			}
		}
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);
	return;
}

DWORD Server::connectProcess() {
	addrLen = sizeof(ClientAddr);//addrLen是对象地址的长度 
	if (listen(sockClient, 10) < 0) {//让套接字进入被动监听状态，参数2为请求队列的最大长度
		cout << "监听失败" << endl;
		return -1;
	}

}
int Server::sendFileList(SOCKET datatcps, char dirPath[])
{
	HANDLE hff;								//建立一个线程
	WIN32_FIND_DATA fd;						//搜索文件
	hff = FindFirstFile(dirPath, &fd);			//查找文件来把待操作文件的相关属性读取到WIN32_FIND_DATA结构中去 
	if (hff == INVALID_HANDLE_VALUE)
	{		//发生错误
		/*const char* errStr = "ls-falied\n";
		cout << *errStr << endl;
		if (send(datatcps, errStr, strlen(errStr), 0) == SOCKET_ERROR)
		{
			cout << "发送失败" << endl;
		}*/
		//closesocket(datatcps);
		return 0;
	}
	BOOL flag = TRUE;
	while (flag)
	{//发送文件信息
		if (!sendFileRecord(datatcps, &fd))
		{
			//closesocket(datatcps);
			return 0;
		}
		flag = FindNextFile(hff, &fd);//查找下一个文件
		// 关闭句柄
		//FindClose(hff);
	}
	// 关闭句柄
	FindClose(hff);
	return 1;
}
int Server::sendFile(SOCKET datatcps, FILE* file) {
	cout << "正在发送文件…" << endl;
	memset(sbuff, '\0', sizeof(sbuff));
	while (1)
	{//从文件中循环读取数据并发送至客户端
		int len = fread(sbuff, 1, sizeof(sbuff), file);//把file指针指向的文件中的内容读取到sbuff中
		if (send(datatcps, sbuff, len, 0) == SOCKET_ERROR)
		{
			cout << "连接失败" << endl;
			//closesocket(datatcps);
			return 0;
		}
		if (len == 0)
		{
			sprintf(sbuff, "get-end", sbuff);
			send(datatcps, sbuff, strlen(sbuff), 0);					//发送指令
			break;
		}
		else if (len < sizeof(sbuff)) {//文件传送结束
			sprintf(sbuff, "get-end", sbuff);
			send(datatcps, sbuff, strlen(sbuff), 0);					//发送指令
			break;
		}
	}
	cout << "发送成功" << endl;
	return 1;

}

int Server::sendFileData(SOCKET datatcps, std::ifstream& file)
{
	// 发送文件数据
	char buffer[10240]; // 一次最多发送 10240 字节
	cout << "文件数据开始读取" << endl;
	while (file)
	{

		memset(buffer, 0, sizeof(buffer));
		file.read(buffer, sizeof(buffer));
		std::streamsize bytes_read = file.gcount();

		// 计算要发送的实际大小
		int data_size = static_cast<int>(bytes_read);
		if (data_size == 0) {
			break; // 文件已读完
		}
		// 如果读取的字节数大于 10240，则设置为 10240
		if (data_size > 10240) {
			data_size = 10240;
		}

		cout << "send buffer value  " << strlen(buffer) << " " << sendSize << endl;

	}
}
int Server::sendFileList(SOCKET datatcps) {
	HANDLE hff;								//建立一个线程
	WIN32_FIND_DATA fd;						//搜索文件
	hff = FindFirstFile("*", &fd);			//查找文件来把待操作文件的相关属性读取到WIN32_FIND_DATA结构中去 
	if (hff == INVALID_HANDLE_VALUE)
	{		//发生错误
		const char* errStr = "列出文件列表时发生错误\n";
		cout << *errStr << endl;
		if (send(datatcps, errStr, strlen(errStr), 0) == SOCKET_ERROR)
		{
			cout << "发送失败" << endl;
		}
		//closesocket(datatcps);
		return 0;
	}
	BOOL flag = TRUE;
	while (flag)
	{//发送文件信息
		if (!sendFileRecord(datatcps, &fd))
		{
			//closesocket(datatcps);
			return 0;
		}
		flag = FindNextFile(hff, &fd);//查找下一个文件
		 // 关闭句柄
		FindClose(hff);
	}

	return 1;
}
int Server::sendFileRecord(SOCKET datatcps, WIN32_FIND_DATA* pfd) {//发送当前的文件记录
	char fileRecord[MAX_PATH + 32];
	char fileRecord1[1024];
	FILETIME ft;						//文件的建立时间
	FileTimeToLocalFileTime(&pfd->ftLastWriteTime, &ft);//Converts a file time to a local file time.

	SYSTEMTIME lastWriteTime;
	FileTimeToSystemTime(&ft, &lastWriteTime);
	memset(fileRecord1, 0, sizeof(fileRecord1));
	/*
	//const char *dir = pfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "<DIR>" : " ";
	//sprintf(fileRecord, "%04d-%02d-%02d %02d:%02d %5s %10d   %-20s\n",
	//	lastWriteTime.wYear,
	//	lastWriteTime.wMonth,
	//	lastWriteTime.wDay,
	//	lastWriteTime.wHour,
	//	lastWriteTime.wMinute,
	//	dir,
	//	pfd->nFileSizeLow,
	//	pfd->cFileName
	//);
	//if (send(datatcps, fileRecord, strlen(fileRecord), 0) == SOCKET_ERROR)
	//{
	//	//通过datatcps接口发送fileRecord数据，成功返回发送的字节数
	//	cout << "发送失败" << endl;
	//	return 0;
	//}
	*/
	const char* dir = pfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "<DIR>" : " ";
	m_FileInformation.fileYear = lastWriteTime.wYear;
	m_FileInformation.fileMonth = lastWriteTime.wMonth;
	m_FileInformation.fileDay = lastWriteTime.wDay;
	m_FileInformation.fileHour = lastWriteTime.wHour;
	m_FileInformation.fileMinute = lastWriteTime.wMinute;
	m_FileInformation.FileSizeLow = pfd->nFileSizeLow;
	memcpy(m_FileInformation.fileName, pfd->cFileName, sizeof(pfd->cFileName));
	memcpy(m_FileInformation.fileDir, dir, 5);

	memcpy(fileRecord1, &m_FileInformation, sizeof(m_FileInformation));

	cout << m_FileInformation.fileName << "    FileType:" << m_FileInformation.fileDir << endl;
	int size = sizeof(m_FileInformation);
	send(datatcps, reinterpret_cast<const char*>(&size), sizeof(int), 0);
	if (send(datatcps, fileRecord1, sizeof(m_FileInformation), 0) == SOCKET_ERROR) {
		//通过datatcps接口发送fileRecord数据，成功返回发送的字节数   
		cout << "发送失败" << endl;
		return 0;
	}
	//cout << "strlen(fileRecord1) " << strlen(fileRecord)<< "-----------------------------------"<< endl;
	return 1;
}

void Server::InitResource()
{

	TCHAR szPasswd[] = TEXT("jinghang123");          //共享资源授权用户的密码
	TCHAR szUserName[] = TEXT("jinghang");        //共享资源授权的用户

	//TCHAR szPasswd[] = TEXT("langdifeng123");          //共享资源授权用户的密码
	//TCHAR szUserName[] = TEXT("langdifeng");        //共享资源授权的用户
	NETRESOURCE net_Resource;
	net_Resource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
	net_Resource.dwScope = RESOURCE_CONNECTED;
	net_Resource.dwType = RESOURCETYPE_ANY;
	net_Resource.dwUsage = 0;
	net_Resource.lpComment = TEXT("");
	net_Resource.lpLocalName = TEXT("Y:");  //映射成本地驱动器z:
	net_Resource.lpProvider = NULL;
	//net_Resource.lpRemoteName = TEXT("\\\\192.168.196.254\\share"); // \\servername\共享资源名
	net_Resource.lpRemoteName = TEXT("\\\\192.168.0.250\\share"); // \\servername\共享资源名
	DWORD dwFlags = CONNECT_UPDATE_PROFILE;
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);

	DWORD dw = WNetAddConnection2(&net_Resource, szPasswd, szUserName, dwFlags);
	switch (dw)
	{
	case ERROR_SUCCESS:
		ShellExecute(NULL, TEXT("open"), TEXT("z:"), NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_ACCESS_DENIED:
		wprintf(TEXT(L"没有权访问！"));
		break;
	case ERROR_ALREADY_ASSIGNED:
		ShellExecute(NULL, TEXT("open"), TEXT("z:"), NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_INVALID_ADDRESS:
		wprintf(TEXT(L"IP地址无效"));
		break;
	case ERROR_NO_NETWORK:
		wprintf(TEXT(L"网络不可达!"));
		break;
	}

}


Server::Server(SOCKET s)
	:sockServer(s)
{
	maxSize = 1024;
	storePath = ".\\temp\\";
	//buf = new char[maxSize];
}


Server::~Server()
{
	cout << "~Server() 执行析构" << endl;
}

bool Server::welcome()
{
	char* welcome = "Welcome, my friend\n";

	//发送信息给客户端
	int iSend = send(sockServer, welcome, 1024, 0);
	if (iSend == SOCKET_ERROR) {
		std::cout << "send() Failed\n";
		return false;
	}

	return true;
}

void Server::running()
{

	while (1)
	{
		memset(rbuff, 0, sizeof(rbuff));
		memset(sbuff, 0, sizeof(sbuff));

		int ret = recv(sockServer, rbuff, sizeof(rbuff), 0);
		//int ret = recvTcpOneAll();
		//memcpy(&rbuff, m_recvOneAllData, sizeof(rbuff));


		if (ret == 0)
		{
			cout << endl << "获取并执行的命令：0" << rbuff << endl;
			return;
		}
		else if (ret < 0)
		{
			cout << endl << "获取并执行的命令：" << ret << endl;
			closesocket(sockServer);
			return;
		}
		cout << endl << "获取并执行的命令：" << rbuff << endl;
		if (strncmp(rbuff, "get", 3) == 0)
		{
			char fileName[256];	//文件名
			strcpy(fileName, rbuff + 4);

			std::ifstream fileStream(fileName, std::ios::binary);
			if (fileStream)
			{
				memset(sbuff, '/0', sizeof(sbuff));
				sprintf(sbuff, "get %s", fileName);
				//int size = strlen(sbuff);
			/*	int ret = send(sockServer, sbuff, sizeof(sbuff), 0);
				if (ret <=0)
				{
					closesocket(sockServer);
					return ;
				}
				else */
				{//创建额外数据连接传送数据
					if (!sendFileData(sockServer, fileStream))
					{
						cout << "发送文件数据失败" << endl;
						return;
					}
					else
					{
						cout << "发送文件数据完成" << endl;
					}

					fileStream.close();
				}

			}
			else
			{

				// 发送结束信号
				int end_signal = 0; // 0 作为结束信号
				send(sockServer, reinterpret_cast<const char*>(&end_signal), sizeof(end_signal), 0);

				/*strcpy(sbuff, "openFailed\n");
				if (send(sockServer, sbuff, sizeof(sbuff), 0))
				{
					cout << "openFailed send sucess" << endl;
				}
				else {
					cout << "openFailed send failed" << endl;
				}*/
				//	std::cerr << "无法打开文件: " << file_path << std::endl;	
			}
		}//get
		else if (strncmp(rbuff, "put", 3) == 0)
		{
			char path[256];
			int cnt;
			memset(path, '\0', sizeof(path));
			strcpy(path, rbuff + 4);
			memset(m_sendOneAllData, '\0', sizeof(sbuff));
			sprintf(m_sendOneAllData, "put %s", path);
			if (sendTcpOneAll()<=0)
			{
				closesocket(sockServer);
				return;
			}
			else
			{
				cout << "返回put指令" << endl;
			}

			memset(rbuff, '\0', sizeof(rbuff));
			cout << "careate file start save" << endl;
			std::ofstream file(path, std::ios::binary);
			//char buffer[10240]; // 接收缓冲区

			while (true)
			{
				// 接收数据大小（int 类型）
				int data_size = -1;
				int bytes_received = recv(sockServer, reinterpret_cast<char*>(&data_size), sizeof(data_size), 0);
				if (bytes_received <= 0 ) {
					cout << "连接失败，错误代码: " << WSAGetLastError() << endl;
					std::cout << bytes_received<< data_size<<" ---接收失败或要接受的数据大小为 0，则退出循环    put！！！！！！！！！\n";
					break; // 如果接收失败或数据大小为 0，则退出循环
				}
				else if (data_size == 0)
				{
					
					break; // 数据大小为 0，则退出循环
				}
				int recv_size = data_size;
				// 接收实际数据
				char buffer[10240]; // 接收缓冲区;
				while (1)
				{
					
					memset(buffer, 0, sizeof(buffer));
					bytes_received = recv(sockServer, buffer, recv_size, 0);
					if (bytes_received == -1)
					{
						cout <<"返回值:"<< bytes_received<< " 连接失败，错误代码: " << WSAGetLastError() << endl;
						std::cout << "----2接收失败  put！！！！！！！！！\n";
						closesocket(sockServer);
						break;
					}
					// 将接收到的数据写入文件
					file.write(buffer, bytes_received);

					if (bytes_received < recv_size)
					{
						recv_size = recv_size - bytes_received;
					}
					else
					{
						break; // 如果接收全部完成，退出循环;
					}
				}
			}

			file.close();
			std::cout << "文件接收完毕，连接关闭。" << std::endl;
			cout << " put 命令执行完成" << endl;

			cout << GetTimeString() << endl;
		}//put
		else if (strncmp(rbuff, "pwd", 3) == 0) {
			//
			////strcpy(sbuff, "T:\\贾庆国\\CS");//我自己选择的绝对路径
			// GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录			
			//strcpy(sbuff, path);
			//int size = strlen(sbuff);
			//send(sockServer, sbuff, size, 0);
			memset(m_sendOneAllData, 0, sizeof(m_sendOneAllData));
			//strcpy(sbuff, "T:\\贾庆国\\CS");//我自己选择的绝对路径
			GetCurrentDirectory(sizeof(m_sendOneAllData), m_sendOneAllData);//找到当前进程的当前目录

			if (sendTcpOneAll() <= 0)
			{

			}
			cout << "pwd 执行结束" << endl;
		}//pwd
		else if (strncmp(rbuff, "ls", 2) == 0) {
			char m_path[256];
			memset(m_path, 0, sizeof(m_path));
			strcpy(m_path, rbuff + 3);

			strcpy(sbuff, rbuff);
			/*int size = strlen(sbuff);
			send(sockServer, sbuff, 1024, 0);*/

			//sendFileList(sockServer);
			strcat(m_path, "\\*");
			int ret = sendFileList(sockServer, m_path);
			int sendSize = 0;
			send(sockServer, reinterpret_cast<const char*>(&sendSize), sizeof(int), 0);
			/*if (ret == 1)
			{
				memset(sbuff, '\0', sizeof(sbuff));
				sprintf(sbuff, "ls-end");
				int size = strlen(sbuff);
				send(sockServer, sbuff, size, 0);
				cout << endl << "ls-end 执行完成：" << endl;
			}
			else {
				memset(sbuff, '\0', sizeof(sbuff));
				sprintf(sbuff, "ls-falied");
				int size = strlen(sbuff);
				send(sockServer, sbuff, size, 0);
				cout << endl << "ls-falied 执行完成：" << endl;
			}*/

		}//ls
		else if (strncmp(rbuff, "cd", 2) == 0) {
			char fileName[20];	//文件名
			strcpy(fileName, rbuff + 3);
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);
			SetCurrentDirectory(fileName);//设置当前目录 
			cout << "cd 执行结束" << endl;
		}//cd
		else if (strncmp(rbuff, "mkdir", 5) == 0)
		{
			char m_path[256];
			memset(m_path, '\0', sizeof(m_path));
			strcpy(m_path, rbuff + 6);
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//发送回信息
			mkdir(m_path);
			//mkdir("T:\\贾庆国\\CS\\2222.txt");
		}//mkdir
		else if (strncmp(rbuff, "del", 3) == 0) { // 删除空文件夹;
			char fileName[20];	//文件名
			strcpy(fileName, rbuff + 4);//获得要删的文件名
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//发送回信息
			delFile(fileName);
		}//del
		else if (strncmp(rbuff, "Fdel", 4) == 0) {//删除某个文件
			char m_path[256];
			memset(m_path, '\0', sizeof(m_path));
			strcpy(m_path, rbuff + 5);//获得要删的文件名
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//发送回信息
			delFile1(m_path);
		}//Fdel
		else if (strncmp(rbuff, "fldel", 5) == 0) {//删除某个文件夹内所有文件
			char path[260];
			strcpy(path, rbuff + 6);//获得要删的文件名
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//发送回信息

			//GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录
			//strcat(path, "\\");
			//strcat(path, fileName);
			cout << path << endl;
			string str = path;
			delete_listFiles(path); // 删除文件夹下的文件;

			bool flag = RemoveDirectory(path); // 删除文件夹本身;
			if (!flag)
			{
				cout << "删除文件夹：" << path << "失败" << endl;

			}
			else
			{
				cout << "删除文件夹：" << path << "成功" << endl;
			}
			/*try 
			{
				if (fs::exists(path) && fs::is_directory(path))
				{
					fs::remove_all(path);
					std::cout << "Directory " << path << " deleted successfully." << std::endl;
				}
				else {
					std::cout << " delete Directory " << path << " does not exist." << std::endl;
				}
			}
			catch (const fs::filesystem_error& e) {
				std::cerr << "Error deleting directory: " << e.what() << std::endl;
			}*/
			cout << "fldel 执行结束" << endl;
		}//Fdel
		else if (strncmp(rbuff, "rename", 6) == 0) // 文件夹重命名;
		{
			char tbuff[1024];
			strcpy(tbuff, rbuff + 7);

			// 创建一个可修改的char数组，拷贝输入内容
			char* buffer = new char[strlen(tbuff) + 1];
			strcpy(buffer, tbuff);

			// 使用strtok分割字符串
			char* firstPart = strtok(buffer, "|");  // 获取第一个部分
			char* secondPart = strtok(nullptr, "|"); // 获取第二个部分

			// 将分割的内容转换为std::string
			std::string oldPath = firstPart ? firstPart : ""; // 检查是否为空
			std::string newPath = secondPart ? secondPart : "";

			bool bRet = true;
			memset(sbuff, '\0', sizeof(sbuff));

			try {
				// 检查旧文件是否存在
				if (fs::exists(oldPath) && fs::is_directory(oldPath))
				{
					// newPath
					fs::rename(oldPath, newPath);

					std::cout << "File renamed from " << oldPath << " to " << newPath << std::endl;
				}
				else {
					bRet = false;
					std::cerr << "Error: The file " << oldPath << " does not exist." << std::endl;
				}
			}
			catch (const fs::filesystem_error& e) {
				bRet = false;
				std::cerr << "Filesystem error: " << e.what() << std::endl;
			}
			catch (const std::exception& e) {
				bRet = false;
				std::cerr << "Error: " << e.what() << std::endl;
			}

			if (bRet)
			{
				sprintf(sbuff, "rename-ok");
			}
			else
			{
				sprintf(sbuff, "rename-false");
			}
			int size = strlen(sbuff);
			send(sockServer, sbuff, size, 0);
			cout << "rename 执行结束" << endl;
		}
		else if (strncmp(rbuff, "compress", 8) == 0) // 压缩;
		{
			//std::vector<std::string> vecPath;
			std::vector<fs::path> paths;
			std::string strZipPath;
			char buffer[1024];
			while (1)
			{
				memset(buffer, 0, sizeof(buffer));
				int recvSize = recv(sockServer, buffer, sizeof(buffer), 0);
				if (recvSize == -1)
				{
					std::cout << "客户端已退出 ！！！！！！！！！\n";
					//return;
				}
				if (strncmp(buffer, "compress-zipname", 16) == 0)
				{
					char zipPath[1024] = { 0 };

					strcpy(zipPath, buffer + 17);
					strZipPath = zipPath;
					break;
				}
				//std::string  strPath(buffer);
				paths.push_back(buffer);
			}

			memset(sbuff, 0, sizeof(sbuff));
			if (CompressMult2Zip(paths, strZipPath))
			{
				sprintf(sbuff, "compress-ok");
				send(sockServer, sbuff, strlen(sbuff), 0);
			}
			else
			{
				sprintf(sbuff, "compress-false");
				send(sockServer, sbuff, strlen(sbuff), 0);
			}
			cout << "compress 执行结束" << endl;
		}
		else if (strncmp(rbuff, "uncompress", 10) == 0) // 解压;
		{
			//std::vector<std::string> vecPath;
			std::vector<fs::path> paths;
			//std::string strZipPath;
			char buffer[1024];
			while (1)
			{
				memset(buffer, 0, sizeof(buffer));
				int recvSize = recv(sockServer, buffer, sizeof(buffer), 0);
				if (recvSize == -1)
				{
					std::cout << "客户端已退出 ！！！！！！！！！\n";
					//return;
				}
				if (strncmp(buffer, "uncompress-paths-end", 20) == 0)
				{
					/*char zipPath[1024] = { 0 };

					strcpy(zipPath, buffer + 17);
					strZipPath = zipPath;*/
					break;
				}
				//std::string  strPath(buffer);
				paths.push_back(buffer);
			}

			for (auto& path : paths)
			{
				// 检查文件路径是否以 .zip 结尾
				if (path.extension() == ".zip")
				{
					// 返回不带 .zip 后缀的新路径
					fs::path newDir = path.parent_path() / path.stem(); // 添加父目录并返回新的目录名
					std::string strDir = newDir.string();
					std::cout << "解压 " << path << "   " << strDir << std::endl;
					extractZip(path, strDir);
				}

			}

			memset(sbuff, 0, sizeof(sbuff));
			sprintf(sbuff, "uncompress-ok");
			send(sockServer, sbuff, strlen(sbuff), 0);
			cout << "uncompress 执行结束" << endl;
		}
		else if (strncmp(rbuff, "user", 4) == 0) {
			char tbuff[1024];
			strcpy(tbuff, rbuff + 5);
			strcat(tbuff, " ");
			memset(rbuff, '\0', sizeof(rbuff));
			strcpy(sbuff, "成功获取用户名\0");
			send(sockServer, sbuff, sizeof(sbuff), 0);

			int recvSize = recv(sockServer, rbuff, sizeof(rbuff), 0);
			if (recvSize == -1)
			{
				std::cout << "客户端已退出 ！！！！！！！！！\n";
				closesocket(sockServer);
				return;
			}
			cout << endl << "获取并执行的命令：" << rbuff << endl;
			strcat(tbuff, rbuff + 5);
			if (strcmp(tbuff, namePassword) == 0) {//验证是否正确并返回数据给客户端
				send(sockServer, "right\0", sizeof(sbuff), 0);
			}
			else {
				send(sockServer, "wrong\0", sizeof(sbuff), 0);
			}
		}//user pass

	}
	cout << "Server::runing() 运行结束" << endl;
}

int Server::commandParse(char* instruck, std::string& paramter)
{
	std::string string(buf);
	std::cout << string << std::endl;
	std::vector<std::string> command;
	Tool::splitString(string, command, std::string(" "));

	if (command.size() != 2) {
		paramter = "";
		return -1;
	}

	if (command[0] == "STOR") {
		paramter = command[1];
		return 1;
	}
	if (command[0] == "RETR") {
		paramter = command[1];
		return 2;
	}

	return -1;
}


int Server::sendTcpOneAll()
{

	//int data_size=；
	int dataSize = strlen(m_sendOneAllData);
	send(sockServer, reinterpret_cast<const char*>(&dataSize), sizeof(dataSize), 0);
	int length = send(sockServer, m_sendOneAllData, dataSize, 0);
	if (length <= 0) {
		cout << "发送命令至服务端失败" << endl;
		closesocket(sockServer);//当不使用socket()创建的套接字时，应该调用closesocket()函数将它关闭，就如同调用fclose()函数关闭一个文件，用来进行套接字资源的释放。
		WSACleanup();
		return length;
	}

	return length;
}
int Server::recvTcpOneAll()
{
	memset(m_recvOneAllData, 0, sizeof(m_recvOneAllData));
	// 接收数据大小（int 类型）
	int iAllDataSize = 0;
	size_t bytes_received = recv(sockServer, reinterpret_cast<char*>(&iAllDataSize), sizeof(iAllDataSize), 0);
	if (bytes_received <= 0) {
		return bytes_received; // 如果接收失败，则退出
	}
	int recv_size = iAllDataSize;
	char combinedBuf[sizeof(m_recvOneAllData)];// 用于组合完整数据
	memset(combinedBuf, 0, sizeof(m_recvOneAllData));
	int combinedBufstart = 0;
	int iCurRecvSize = 0;
	char recvBuf[1024];
	while (1)
	{
		//memset(rbuff, 0, sizeof(rbuff));
		memset(recvBuf, 0, sizeof(recvBuf));
		//iRecvSize = recv(sockServer, recvBuf, sizeof(m_FileInformation), 0);
		iCurRecvSize = recv(sockServer, recvBuf, recv_size, 0);
		if (iCurRecvSize == SOCKET_ERROR) {
			cout << "读取时发生错误" << endl;
			return -1;

		}
		else if (iCurRecvSize == 0)
		{
			continue;
		}

		if (iCurRecvSize < recv_size) //iAllDataSize的值应该是540
		{
			recv_size = recv_size - iCurRecvSize;
			// 将接收到的数据复制到组合缓冲区
			memcpy(combinedBuf + combinedBufstart, recvBuf, iCurRecvSize);
			combinedBufstart += iCurRecvSize; // 更新已接收数据的总大小
			continue;
		}
		else
		{
			//memcpy(combinedBuf, recvBuf, iCurRecvSize)
			memcpy(combinedBuf + combinedBufstart, recvBuf, iCurRecvSize);//????+ combinedBufstart
			break;
		}

	}
	memcpy(&m_recvOneAllData, combinedBuf, sizeof(m_recvOneAllData));

	return 1;
}

bool Server::receiveFile(std::string filename)
{
	//创建与上次文件名相同的文件
	std::string filePath = storePath + filename;
	std::ofstream storeFile(filePath, std::ios_base::binary);
	if (!storeFile) {
		std::cout << "Create file failed\n";
	}

	//先接收文件大小信息
	memset(buf, 0, maxSize);
	int recvSize = recv(sockServer, buf, 1024, 0);
	if (recvSize == -1)
	{
		std::cout << "客户端已退出 ！！！！！！！！！\n";
		return false;
	}
	int fileSize = atoi(buf);
	std::cout << "File's size is:" << fileSize << std::endl;

	int len = 1;
	int recvCount = 0;
	//统计文件传输剩下的大小
	int remain = fileSize;
	while (true) {
		memset(buf, 0, maxSize);
		len = recv(sockServer, buf, 1024, 0);
		if (len = -1)
		{
			std::cout << "客户端已退出 ！！！！！！！！！\n";
			return false;
		}
		storeFile.write(buf, 1024);
		if (len == SOCKET_ERROR) {
			std::cout << "Receive occur error\n";
		}

		//如果剩下的小于等于0，说明文件传输完毕，退出循环
		remain -= 1024;
		if (remain <= 0) {
			//if (strlen(buf) == 0) {
			break;
		}

		recvCount += strlen(buf);
		std::cout << "Receive " << recvCount << " bytes\n";
	}

	//关闭并保存文件
	storeFile.close();
	std::cout << "Write file successful\n";

	return false;
}

bool Server::sendFile(std::string filename)
{
	return false;
}
