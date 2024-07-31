// Server_FtpTest2_1.cpp : 定义控制台应用程序的入口点。
//
//出现C2664错误把属性->常规->字符集改成"使用多字节字符集"
// Server_FtpTest2_1.cpp : 定义控制台应用程序的入口点。
//
//出现C2664错误把属性->常规->字符集改成"使用多字节字符集"
#include "stdafx.h"

#include <iostream>
#include <vector>

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
#pragma comment(lib, "Mpr.lib")
using namespace std;

#define RECV_PORT 4312	//接收端口
#define SEND_PORT 4302	//发送端口
#pragma comment(lib, "wsock32.lib")

SOCKET sockClient, sockServer;
sockaddr_in severAddr;//服务器地址
sockaddr_in ClientAddr;//客户端地址 

int addrLen;		//地址长度
char fileName[20];	//文件名
char order[20];		//命令
char rbuff[1024];	//接收缓冲区
char sbuff[1024];	//发送缓冲区

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
string GetTimeString();
void TimeSave(string data, string source);
DWORD startSock();
DWORD createSocket();
int sendFileRecord(SOCKET datatcps, WIN32_FIND_DATA *pfd);
int sendFileList(SOCKET datatcps);
int sendFile(SOCKET datatcps, FILE* file);
DWORD connectProcess();
//FileInformation m_FileInformation;
//***************函数声明***************
string GetTimeString() {
	SYSTEMTIME st;
	GetLocalTime(&st);
	char temp[100];
	sprintf_s(temp, "%04d-%02d-%02d-%02d-%02d-%02d-%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	string str = temp;
	return str;
}

void TimeSave(string data, string source)
{
	FILE * lOG;
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

DWORD startSock() {//初始化winsock
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		cout << "初始化失败" << endl;
		return -1;
	}
	return 1;
}
DWORD createSocket() {
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClient == SOCKET_ERROR) {
		cout << "创建失败" << endl;
		WSACleanup();
		return -1;
	}
	severAddr.sin_family = AF_INET;
	severAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	severAddr.sin_port = htons(RECV_PORT);
	if (bind(sockClient, (struct sockaddr FAR*)&severAddr, sizeof(severAddr)) == SOCKET_ERROR) {
		//bind函数用于将socket和地址结构绑定
		cout << "绑定失败" << endl;
		return -1;
	}
	return 1;
}
DWORD mkdir(char fileName[])
{
	char path[1000];
	GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录

	strcat(path, "\\");
	strcat(path, fileName);
	cout << path << endl;
	bool flag = CreateDirectory(path, NULL);
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
DWORD delFile(char fileName[]) {
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
DWORD delFile1(char fileName[]) 
{
	char path[1000];
	GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录

	strcat(path, "\\");
	strcat(path, fileName);
	cout<<path<<endl;
	if(remove(path)==0)
    {
        cout<<"删除成功"<<endl;
		return 1;
    }
    else
    {
        cout<<"删除失败"<<endl;
		return 0;
    }
}

void delete_listFiles(string dir) 
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
		system("pause");
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
		else{
			string file_path = dir + "\\" + fileinfo.name;
			cout << file_path.c_str() << endl;
			if (remove(file_path.c_str()) == 0) {//删除文件
				cout << "delete file success" << endl;
			}else{
				cout << "delete file error" << endl;
			}
		}
	} while (!_findnext(handle, &fileinfo));
 
	_findclose(handle);
	return;
}
DWORD connectProcess() {
	addrLen = sizeof(ClientAddr);//addrLen是对象地址的长度 
	if (listen(sockClient, 10) < 0) {//让套接字进入被动监听状态，参数2为请求队列的最大长度
		cout << "监听失败" << endl;
		return -1;
	}
	char chInput[512];
	sprintf(chInput, "int:%d\n", 500);
	OutputDebugString(chInput);

	cout << "服务器正在监听中…" << endl;
	while (1) {
		//accept取出队列头部的连接请求
		//sockclient是处于监听的套接字
		//ClientAddr 是监听的对象地址
		sockServer = accept(sockClient, (struct sockaddr FAR*)&ClientAddr, &addrLen);
		while (1) {
			memset(rbuff, 0, sizeof(rbuff));
			memset(sbuff, 0, sizeof(sbuff));
			if (recv(sockServer, rbuff, sizeof(rbuff), 0) <= 0) {
				break;
			}
			cout << endl << "获取并执行的命令：" << rbuff << endl;
			if (strncmp(rbuff, "get", 3) == 0) 
			{
				strcpy(fileName, rbuff + 4);
				FILE* file;//定义一个文件访问指针
				//处理下载文件请求
				file = fopen(fileName, "rb");//二进制打开文件，只允许读
				if (file) {
					sprintf(sbuff, "get %s", fileName);
					if (!send(sockServer, sbuff, sizeof(sbuff), 0)) {
						fclose(file);
						return 0;
					}
					else {//创建额外数据连接传送数据
						//string msg = " ---发送文件成功---";
						//TimeSave("E:\\jh\\Time_Server.txt", msg);
						if (!sendFile(sockServer, file)) {
							return 0;
						}
						else
						{
							cout << "111111111" << endl;
						}


						fclose(file);
					}

				}
				else {
					strcpy(sbuff, "无法打开文件\n");
					if (send(sockServer, sbuff, sizeof(sbuff), 0)) {
						return 0;
					}
					else {
						cout << "2222222222222" << endl;
					}
				}
			}//get
			else if (strncmp(rbuff, "put", 3) == 0) {
				FILE* fd;
				int cnt;
				string str_rbuff = rbuff;

				vector<string> str_;
				string pattern = "\\";
				str_ = my_split(rbuff, pattern);
				if(str_.size() > 1)
				{
					cout << str_[str_.size() - 1] << endl;
					string str_name =  str_[str_.size() - 1];
					strcpy(fileName, str_name.c_str());
				}else
				{
					strcpy(fileName, rbuff + 4);
				}
				//string msg = " ---收到获取命令---";
				//TimeSave("E:\\jh\\Time_Server.txt", msg);

				
				fd = fopen(fileName, "wb");
				if (fd == NULL) 
				{
					cout << "无法打开文件" << fileName << endl;
					return 0;
				}
				sprintf(sbuff, "put %s", fileName);
				if (!send(sockServer, sbuff, sizeof(sbuff), 0))
				{
					fclose(fd);
					return 0;
				}

				memset(sbuff, '\0', sizeof(rbuff));

				while ((cnt = recv(sockServer, rbuff, sizeof(rbuff), 0)) > 0)
				{
					fwrite(rbuff, sizeof(char), cnt, fd);//把cnt个数据长度为char的数据从rbuff输入到fd指向的文件

				}
				//string msg = " ---成功收到客户端上传文件请求---";
				//TimeSave("E:\\Time_Server_Put.txt", msg);
				//cout << "成功获得文件" << fileName << endl;
				fclose(fd);
				//msg = " ------------------";
				//TimeSave("E:\\jh\\Time_Server_Put.txt", msg);
				string  timeddd = GetTimeString();
				cout << timeddd << endl;
			}//put
			else if (strncmp(rbuff, "pwd", 3) == 0) {
				char path[1000];
				//strcpy(sbuff, "D:\\AjhwtWork");//我自己选择的绝对路径
				GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录			
				strcpy(sbuff, path);
				send(sockServer, sbuff, sizeof(sbuff), 0);
			}//pwd
			else if (strncmp(rbuff, "ls", 2) == 0) {
				strcpy(sbuff, rbuff);
				send(sockServer, sbuff, sizeof(sbuff), 0);
				sendFileList(sockServer);
			}//ls
			else if (strncmp(rbuff, "cd", 2) == 0) {
				strcpy(fileName, rbuff + 3);
				strcpy(sbuff, rbuff);
				send(sockServer, sbuff, sizeof(sbuff), 0);
				SetCurrentDirectory(fileName);//设置当前目录 
			}//cd
			else if (strncmp(rbuff, "mkdir", 5) == 0) 
			{
				strcpy(fileName, rbuff + 6);
				strcpy(sbuff, rbuff);
				send(sockServer, sbuff, sizeof(sbuff), 0);//发送回信息
				mkdir(fileName);
			}//mkdir
			else if (strncmp(rbuff, "del", 3) == 0) {
				strcpy(fileName, rbuff + 4);//获得要删的文件名
				strcpy(sbuff, rbuff);
				send(sockServer, sbuff, sizeof(sbuff), 0);//发送回信息
				delFile(fileName);
			}//del
			else if (strncmp(rbuff, "Fdel", 4) == 0) {//删除某个文件
				strcpy(fileName, rbuff + 5);//获得要删的文件名
				strcpy(sbuff, rbuff);
				send(sockServer, sbuff, sizeof(sbuff), 0);//发送回信息
				delFile1(fileName);
			}//Fdel
			else if (strncmp(rbuff, "fldel", 5) == 0) {//删除某个文件夹内所有文件
				strcpy(fileName, rbuff + 6);//获得要删的文件名
				strcpy(sbuff, rbuff);
				send(sockServer, sbuff, sizeof(sbuff), 0);//发送回信息
				char path[1000];
				GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录
				strcat(path, "\\");
				strcat(path, fileName);
				cout<<path<<endl;
				string str = path;
				delete_listFiles(path);
			}//Fdel
			else if (strncmp(rbuff, "user", 4) == 0) {
				char tbuff[1024];
				strcpy(tbuff, rbuff + 5);
				strcat(tbuff, " ");
				memset(rbuff, '\0', sizeof(rbuff));
				strcpy(sbuff, "成功获取用户名\0");
				send(sockServer, sbuff, sizeof(sbuff), 0);

				recv(sockServer, rbuff, sizeof(rbuff), 0);
				cout << endl << "获取并执行的命令：" << rbuff << endl;
				strcat(tbuff, rbuff + 5);
				if (strcmp(tbuff, namePassword) == 0) {//验证是否正确并返回数据给客户端
					send(sockServer, "right\0", sizeof(sbuff), 0);
				}
				else {
					send(sockServer, "wrong\0", sizeof(sbuff), 0);
				}
			}//user pass
			closesocket(sockServer);
		}
	}
}
int sendFile(SOCKET datatcps, FILE* file) {
	cout << "正在发送文件…" << endl;
	memset(sbuff, '\0', sizeof(sbuff));
	while (1) {//从文件中循环读取数据并发送至客户端
		int len = fread(sbuff, 1, sizeof(sbuff), file);//把file指针指向的文件中的内容读取到sbuff中
		if (send(datatcps, sbuff, len, 0) == SOCKET_ERROR) {
			cout << "连接失败" << endl;
			closesocket(datatcps);
			return 0;
		}
		if (len < sizeof(sbuff)) {//文件传送结束
			break;
		}
	}
	closesocket(datatcps);
	cout << "发送成功" << endl;
	return 1;
}
int sendFileList(SOCKET datatcps) {
	HANDLE hff;								//建立一个线程
	WIN32_FIND_DATA fd;						//搜索文件
	hff = FindFirstFile("*", &fd);			//查找文件来把待操作文件的相关属性读取到WIN32_FIND_DATA结构中去 
	if (hff == INVALID_HANDLE_VALUE) {		//发生错误
		const char *errStr = "列出文件列表时发生错误\n";
		cout << *errStr << endl;
		if (send(datatcps, errStr, strlen(errStr), 0) == SOCKET_ERROR) {
			cout << "发送失败" << endl;
		}
		closesocket(datatcps);
		return 0;
	}
	BOOL flag = TRUE;
	while (flag) 
	{//发送文件信息
		if (!sendFileRecord(datatcps, &fd)) 
		{
			closesocket(datatcps);
			return 0;
		}
		flag = FindNextFile(hff, &fd);//查找下一个文件
	}
	closesocket(datatcps);
	return 1;
}
int sendFileRecord(SOCKET datatcps, WIN32_FIND_DATA *pfd) {//发送当前的文件记录
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
	const char *dir = pfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "<DIR>" : " ";
	m_FileInformation.fileYear = lastWriteTime.wYear;
	m_FileInformation.fileMonth = lastWriteTime.wMonth;
	m_FileInformation.fileDay = lastWriteTime.wDay;
	m_FileInformation.fileHour = lastWriteTime.wHour;
	m_FileInformation.fileMinute = lastWriteTime.wMinute;
	m_FileInformation.FileSizeLow = pfd->nFileSizeLow;
	memcpy(m_FileInformation.fileName,pfd->cFileName,sizeof(pfd->cFileName));
	memcpy(m_FileInformation.fileDir,dir,20);

	memcpy(fileRecord1, &m_FileInformation, sizeof(m_FileInformation));

	cout << m_FileInformation.fileName << endl;

	if (send(datatcps, fileRecord1, sizeof(m_FileInformation), 0) == SOCKET_ERROR) {
		//通过datatcps接口发送fileRecord数据，成功返回发送的字节数   
		cout << "发送失败" << endl;
		return 0;
	}
	//cout << "strlen(fileRecord1) " << strlen(fileRecord)<< "-----------------------------------"<< endl;
	return 1;
}

void InitResource()
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
	net_Resource.lpLocalName = TEXT("z:");  //映射成本地驱动器z:
	net_Resource.lpProvider = NULL;
	//net_Resource.lpRemoteName = TEXT("\\\\192.168.196.254\\share"); // \\servername\共享资源名
	net_Resource.lpRemoteName = TEXT("\\\\data\\share"); // \\servername\共享资源名
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
int main() 
{
	//char fileName_my[120] = "E:\\jh\\Test";
	//SetCurrentDirectory(fileName_my);//设置当前目录 

	char chInput[512];  

	char fileName_my[120] = "F:";// "E:\\1008";
	SetCurrentDirectory(fileName_my);//设置当前目录 

	sprintf(chInput, "int:%d\n", 500);  
	OutputDebugString(chInput);  
	if (startSock() == -1 || createSocket() == -1 || connectProcess() == -1) {
		return -1;
	}
	return 1;
}
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}

