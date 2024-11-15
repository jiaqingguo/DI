//#include "stdafx.h"
#include <fstream>

#include "FtpClientClass.h"
#include "Util/UtilTool.h"

#define RECV_PORT 4312	//接收端口
#define SEND_PORT 4302	//发送端口
using namespace std;
#pragma warning(disable : 4996) 
//#include "Util/UtilTool.h"

void TimeSave(string data, string source)
{
	FILE * lOG;
	lOG = fopen(data.c_str(), "a");
	string  timeddd = UtilTool::GetTimeString() + source;
	fprintf(lOG, "%s  ", timeddd.c_str());
	fprintf(lOG, "\n");
	fclose(lOG);
}
FtpClientClass::FtpClientClass(std::string serverIp, unsigned short ServerPort)
{
	checkFlag = false;
	strcpy(inputIP, serverIp.c_str());
	m_serverPort = ServerPort;
}
FtpClientClass::~FtpClientClass()
{

}
//启动winsock并初始化
DWORD FtpClientClass::startSock()
{
	//启动winsock并初始化
	WSADATA WSAData;
	char a[20];
	memset(a, 0, sizeof(a));
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) { //加载winsock版本
		cout << "sock初始化失败" << endl;
		return -1;
	}
	//if (strncmp(inputIP, a, sizeof(a)) == 0) {
	//	cout << "请输入要连接的服务器IP：";
	//	cin >> inputIP;
	//}ls
	//strcpy(inputIP, "127.0.0.1");
	//strcpy(inputIP, "192.168.0.158");
//	strcpy(inputIP, "192.168.1.23"); /*给数组赋字符串*/ 
	//设置地址结构
	serverAddr.sin_family = AF_INET;					//表明底层是使用的哪种通信协议来递交数据的，AF_INET表示使用 TCP/IPv4 地址族进行通信
	serverAddr.sin_addr.s_addr = inet_addr(inputIP);	//指定服务器IP，十进制转化成二进制IPV4地址
	serverAddr.sin_port = htons(m_serverPort);				//设置端口号，htons用于将主机字节序改为网络字节序
	return 1;
}
//创建socket
DWORD FtpClientClass::createSocket()
{
	//创建socket
	//要使用套接字，首先必须调用socket()函数创建一个套接字描述符，就如同操作文件时，首先得调用fopen()函数打开一个文件。
	sockClient = socket(AF_INET, SOCK_STREAM, 0);//当scoket函数成功调用时返回一个新的SOCKET(Socket Descriptor) //SOCK_STREAM（流式套接字）:Tcp连接，提供序列化的、可靠的、双向连接的字节流。支持带外数据传输
	if (sockClient == SOCKET_ERROR) {
		cout << "创建socket失败" << endl;
		WSACleanup();//终止Ws2_32.dll 的使用
		return -1;
	}

	// 设置发送缓冲区大小
	/*if (setsockopt(sListen, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<const char*>(&send_buffer_size), sizeof(send_buffer_size)) == SOCKET_ERROR) {
		std::cerr << "Failed to set send buffer size." << std::endl;
		closesocket(sListen);
		WSACleanup();
		return;
	}*/
	int buffer_size = 1024 * 1024 * 1024;
	// 设置接收缓冲区大小
	if (setsockopt(sockClient, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char*>(&buffer_size), sizeof(buffer_size)) == SOCKET_ERROR) {
		std::cerr << "Failed to set receive buffer size." << std::endl;
		closesocket(buffer_size);
		WSACleanup();
		return 0;
	}
	return 1;
}
//发送连接请求
DWORD FtpClientClass::callServer()
{
	//发送连接请求
	createSocket();
	if (connect(sockClient, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {//connect()创建与指定外部端口的连接
		//cout << "连接失败" << endl;
		//memset(inputIP, 0, sizeof(inputIP));10049
		int errorCode = WSAGetLastError();
		cout << "连接失败，错误代码: " << WSAGetLastError() << endl;
		return -1;
	}
	return 1;
}
//创建文件夹
DWORD FtpClientClass::mkdir(char fileName[])
{
	//wstring kj;

	//UtilTool::setWstring(kj,StoreOptions[i].c_str());
	//COptionUI * optical_fiber1 = static_cast<COptionUI*>(m_pm.FindControl(kj.c_str()));

	//char path[1000];
	//LPCWSTR path;
	//GetCurrentDirectory(sizeof(path), path);//找到当前进程的当前目录

	//strcat(path, "\\");
	//strcat(path, fileName);
	//cout << path << endl;
	//bool flag = CreateDirectory(path, NULL);
	//if (flag)
	//{
	//	cout << "创建文件：" << fileName << "成功" << endl;
	//	return 1;
	//}
	//else
	//{
	//	cout << "创建文件：" << fileName << "失败" << endl;
	//	return 0;
	//}
	return 1;
}
//菜单
void FtpClientClass::help()
{
	//帮助菜单
	cout << "        _______________________________________________  " << endl
		<< "       |                FTP帮助菜单                     |   " << endl
		<< "       | 1、get 下载文件 [输入格式: get 文件名 ]        |   " << endl
		<< "       | 2、put 上传文件 [输入格式：put 文件名]         |   " << endl
		<< "       | 3、pwd 显示当前文件夹的绝对路径                |   " << endl
		<< "       | 4、ls  显示远方当前目录的文件                  |   " << endl
		<< "       | 5、cd  改变远方当前目录和路径                  |   " << endl
		<< "       |         进入下级目录: cd 路径名                |   " << endl
		<< "       |         进入上级目录: cd ..                    |   " << endl
		<< "       | 6、mkdir 新建文件夹 [输入格式：mkdir 文件名]   |   " << endl
		<< "       | 7、del 删除文件夹 [输入格式：del 文件名]       |   " << endl
		<< "       | 8、? 或者 help 进入帮助菜单                    |   " << endl
		<< "       | 9、quit 退出FTP                                |   " << endl
		<< "       |________________________________________________|    " << endl;
}
//列出远方当前目录
int FtpClientClass::list(SOCKET sockfd)
{
	vecFileName.clear();
	vecDirName.clear();
	vector<string> eachDirData;
	vector<string> eachFile;
	//列出远方当前目录
	int iCurRecvSize;
	memset(sbuff, '\0', sizeof(sbuff));
	char recvBuf[1024];
	char time[300];
	while (1)
	{
		// 接收数据大小（int 类型）
		int iAllDataSize = 0;
		size_t bytes_received = recv(sockClient, reinterpret_cast<char*>(&iAllDataSize), sizeof(iAllDataSize), 0);
		if (bytes_received <= 0 || iAllDataSize == 0) {
			break; // 如果接收失败或数据大小为 0，则退出循环
		}
		int recv_size = iAllDataSize;
		char combinedBuf[sizeof(m_FileInformation)]; // 用于组合完整数据
		int combinedBufstart = 0;
		while (1)
		{
			//memset(rbuff, 0, sizeof(rbuff));
			memset(recvBuf, 0, sizeof(recvBuf));
			//iRecvSize = recv(sockClient, recvBuf, sizeof(m_FileInformation), 0);
			iCurRecvSize = recv(sockClient, recvBuf, recv_size, 0);
			if (iCurRecvSize == SOCKET_ERROR) {
				cout << "读取时发生错误" << endl;
				return -2;
				//exit(1);
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
				memcpy(combinedBuf, recvBuf, iCurRecvSize);
				break;
			}

		}
		memset(&m_FileInformation, 0, sizeof(m_FileInformation));
		memcpy(&m_FileInformation, combinedBuf, sizeof(m_FileInformation));
		//显示数据
		//rbuff[iCurRecvSize] = '\0';
		//cout << "list=====m_FileInformation.fileName: " << m_FileInformation.fileName << endl;
		string name(m_FileInformation.fileName);
		string fileDir(m_FileInformation.fileDir);
		sprintf(time, "%04d-%02d-%02d %02d:%02d", m_FileInformation.fileYear, m_FileInformation.fileMonth, m_FileInformation.fileDay,
			m_FileInformation.fileHour, m_FileInformation.fileMinute);
		string str_time(time);
		if (name == "." || name == "..")
		{
			//cout << "不要.和.." << endl;
		}
		else
		{
			if (fileDir == "<DIR>")
			{
				eachDirData.clear();
				eachDirData.push_back(name);
				eachDirData.push_back(str_time);
				vecDirName.push_back(eachDirData);
				//vecDirName.push_back(name);
				cout << "< DIR > " << name << endl;
			}
			else
			{
				eachFile.clear();
				eachFile.push_back(name);
				eachFile.push_back(str_time);
				vecFileName.push_back(eachFile);
				cout << "< FILE > " << name << endl;
			}


		}

		cout << name << fileDir << "----------------" << endl;
	}
	return 1;
}
//发送要执行的命令至服务端
DWORD FtpClientClass::sendTCP(char data[])
{
	//发送要执行的命令至服务端
	int length = send(sockClient, data, strlen(data), 0);
	if (length <= 0)
	{
		cout << "发送命令至服务端失败" << endl;
		closesocket(sockClient);//当不使用socket()创建的套接字时，应该调用closesocket()函数将它关闭，就如同调用fclose()函数关闭一个文件，用来进行套接字资源的释放。
		WSACleanup();
		return -1;
	}
	return 1;
}

DWORD FtpClientClass::sendTCP(char data[], int sendSize)
{
	//发送要执行的命令至服务端
	int length = send(sockClient, data, sendSize, 0);
	if (length <= 0) {
		cout << "发送命令至服务端失败" << endl;
		closesocket(sockClient);//当不使用socket()创建的套接字时，应该调用closesocket()函数将它关闭，就如同调用fclose()函数关闭一个文件，用来进行套接字资源的释放。
		WSACleanup();
		return -1;
	}
	return 1;
}
bool FtpClientClass::sendTcpOneAll()
{

	//int data_size=；
	int dataSize = strlen(m_sendOneAllData);
	send(sockClient, reinterpret_cast<const char*>(&dataSize), sizeof(dataSize), 0);
	int length = send(sockClient, m_sendOneAllData, dataSize, 0);
	if (length <= 0) {
		cout << "发送命令至服务端失败" << endl;
		closesocket(sockClient);//当不使用socket()创建的套接字时，应该调用closesocket()函数将它关闭，就如同调用fclose()函数关闭一个文件，用来进行套接字资源的释放。
		WSACleanup();
		return false;
	}

	return true;
}
bool FtpClientClass::recvTcpOneAll()
{
	memset(m_recvOneAllData, 0, sizeof(m_recvOneAllData));
	// 接收数据大小（int 类型）
	int iAllDataSize = 0;
	size_t bytes_received = recv(sockClient, reinterpret_cast<char*>(&iAllDataSize), sizeof(iAllDataSize), 0);
	if (bytes_received <= 0) {
		return false; // 如果接收失败，则退出
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
		//iRecvSize = recv(sockClient, recvBuf, sizeof(m_FileInformation), 0);
		iCurRecvSize = recv(sockClient, recvBuf, recv_size, 0);
		if (iCurRecvSize == SOCKET_ERROR) {
			cout << "读取时发生错误" << endl;
			return false;
			//exit(1);
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
	memcpy(m_recvOneAllData, combinedBuf, sizeof(m_recvOneAllData));

	return true;
}
//上传用户名
int FtpClientClass::user()
{
	char operation[10], name[20];		//操作与文件名
	char order[30] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order
	cout << "请输入用户名指令（user 用户名）：";
	cin >> operation;
	cin >> name;
	strcat(order, operation), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);									//发送指令
	if (sendTCP(buff) == -1)									//发送指令
	{
		return 0;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	cout << rbuff << endl;
	return 1;

}
//上传密码
int FtpClientClass::pass()
{
	char operation[10], name[20];		//操作与文件名
	char order[30] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order
	cout << "请输入密码指令（pass 密码）：";
	cin >> operation;
	cin >> name;
	strcat(order, operation), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);									//发送指令
	if (sendTCP(buff) == -1)									//发送指令
	{
		return 0;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	cout << rbuff << endl;
	if (strcmp(rbuff, "wrong") == 0) {
		return 0;
	}
	return 1;

}
//put 传送给远方一个文件
int FtpClientClass::sendFile(SOCKET datatcps, FILE* file)
{
	//put 传送给远方一个文件
	cout << "正在传输文件…" << endl;
	memset(sbuff, '\0', sizeof(sbuff));
	while (1)
	{ //从文件中循环读取数据并发送
		int len = fread(sbuff, 1, sizeof(sbuff), file); //fread从file文件读取sizeof(sbuff)长度的数据到sbuff，返回成功读取的数据个数
		if (send(datatcps, sbuff, len, 0) == SOCKET_ERROR)
		{
			cout << "与客户端的连接中断" << endl;
			//	closesocket(datatcps);
			return 0;
		}

		if (len == 0)
		{
			sprintf(sbuff, "put-end", sbuff);
			//sendTCP(sbuff);									//发送指令
			if (sendTCP(sbuff) == -1)									//发送指令
			{
				return 0;
			}
			break;
		}
		else if (len < sizeof(sbuff))
		{
			break;
		}

	}
	//	closesocket(datatcps);
	cout << "传输完成" << endl;
	return true;
}
int FtpClientClass::sendFileData(SOCKET datatcps, std::ifstream& file)
{
	// 发送文件数据
	int iSendMax = 10240;
	char buffer[10240]; // 一次最多发送 10240 字节

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
		if (data_size > iSendMax) {
			data_size = iSendMax;
		}

		// 发送数据大小（int 类型）和实际数据
		send(datatcps, reinterpret_cast<const char*>(&data_size), sizeof(data_size), 0);
		send(datatcps, buffer, data_size, 0);
	}
	// 发送结束信号
	int end_signal = 0; // 0 作为结束信号
	send(datatcps, reinterpret_cast<const char*>(&end_signal), sizeof(end_signal), 0);
	return 1;
}
bool FtpClientClass::newConnection()
{
	////启动winsock并初始化
	if (startSock() == -1)
	{
		return false;
	}

	if (callServer() == -1)
	{	//发送连接请求失败
		cout << "发送连接请求失败!!!";
		return false;
	}
	return true;
}
////获取当前文件名称
//void FtpClientClass::execute_ls()
//{
//	
//	char operation[10], name[20];		//操作与文件名
//	char order[30] = "\0";				//输入的命令
//	char buff[80];						//用来存储经过字符串格式化的order
//
//	//startSock();				//启动winsock并初始化
//	//if (callServer() == -1) 
//	//{	//发送连接请求失败
//	//	cout << "发送连接请求失败!!!";
//	//}
//	memset(buff, 0, sizeof(buff));
//	memset(rbuff, 0, sizeof(rbuff));
//	memset(sbuff, 0, sizeof(sbuff));
//	memset(order, 0, sizeof(order));
//
//	strcat(order, "ls");
//	sprintf(buff, order);
//	sendTCP(buff);									//发送指令
//	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
//	cout << rbuff << endl;	//pwd的
//	list(sockClient);
//
//	//for (int i = 0; i < vecName.size(); i++)
//	//{
//	//	cout << "vecName[i]: " << vecName[i] << endl;//打印容器的内容
//	//	ret_vec.push_back(vecName[i]);
//	//}
//	//vecName.push_back();
//	//closesocket(sockClient);	//关闭连接
//	//WSACleanup();				//释放Winsock
//}

int FtpClientClass::execute_ls(const std::string strDirPath)
{
	char operation[10], name[20];		//操作与文件名
	char order[260] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order

	//startSock();				//启动winsock并初始化
	//if (callServer() == -1) 
	//{	//发送连接请求失败
	//	cout << "发送连接请求失败!!!";
	//}
	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));
	memset(order, 0, sizeof(order));

	//strcat(order, "ls");
	sprintf(order, "ls %s", strDirPath.c_str());
	sprintf(buff, order);
	//sendTCP(buff);									//发送指令
	if (sendTCP(buff) == -1)									//发送指令
	{
		return 0;
	}
	//int size =recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息
	//cout << rbuff << endl;	
	//if(ls - falied)

	return list(sockClient);
}

////获取当前路径
//string FtpClientClass::Gets_CurrentPath()
//{
//	memset(rbuff, 0, sizeof(rbuff));
//	string str_path;
//
//	char operation[10], name[20];		//操作与文件名
//	char order[30] = "\0";				//输入的命令
//	char buff[80];						//用来存储经过字符串格式化的order
//
//	//startSock();				//启动winsock并初始化
//	//if (callServer() == -1) 
//	//{	//发送连接请求失败
//	//	cout << "发送连接请求失败!!!";
//	//}
//
//	memset(order, 0, sizeof(order));
//	memset(buff, 0, sizeof(buff));
//	strcat(order, "pwd");
//	sprintf(buff, order);
//	//sendTCP(buff);									//发送指令
//	if (sendTCP(buff) == -1)									//发送指令
//	{
//		return "";
//	}
//	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
//	cout << rbuff << endl;							//pwd功能在这里已经实现
//	str_path = rbuff;
//
////	closesocket(sockClient);	//关闭连接
//	//WSACleanup();				//释放Winsock
//	return str_path;
//}

bool FtpClientClass::Gets_CurrentPath(std::string& strRootPath)
{
	memset(rbuff, 0, sizeof(rbuff));
	string str_path;

	char operation[10], name[20];		//操作与文件名
	char order[30] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order

	memset(order, 0, sizeof(order));
	memset(buff, 0, sizeof(buff));
	strcat(order, "pwd");
	sprintf(buff, order);

	//if (sendTCP(buff) == -1)									//发送指令
	//{
	//	return false;
	//}
	//recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	//cout << rbuff << endl;							//pwd功能在这里已经实现
	//strRootPath = rbuff;

	//return true;

	if (sendTCP(buff) == -1)									//发送指令
	{
		return false;
	}
	/*if (!sendTcpOneAll())
	{
		return false;
	}*/
	if (recvTcpOneAll())
	{

		strRootPath = m_recvOneAllData;
		return true;
	}

	//return false;
}
//下载文件
void FtpClientClass::execute_getFile(string rec_name)
{
	char operation[10], name[1024];		//操作与文件名
	char order[1024] = "\0";				//输入的命令
	char buff[1024];						//用来存储经过字符串格式化的order
	FILE *fd1, *fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
	int cnt;

	//startSock();				//启动winsock并初始化
	//if (callServer() == -1) 
	//{	//发送连接请求失败
	//	cout << "发送请求失败!!!" << endl;
	//}

	//发送连接请求成功，初始化数据

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	string str_name = rec_name;
	strcpy(name, str_name.c_str());
	//将指令整合进order，并存放进buff
	strcat(order, "get"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);									//发送指令
	if (sendTCP(buff) == -1)									//发送指令
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	cout << rbuff << endl;							//pwd功能在这里已经实现
	if (strncmp(rbuff, "get", 3) == 0)
	{			///下载功能
		//callServer();
		fd1 = fopen(name, "wb");                    //用二进制的方式打开文件，wb表示打开或新建一个二进制文件（只允许写数据）
		if (fd1 == NULL)
		{
			cout << "打开或者新建 " << name << "文件失败" << endl;
			//return 1;
		}
		memset(rbuff, '\0', sizeof(rbuff));
		while ((cnt = recv(sockClient, rbuff, sizeof(rbuff), 0)) > 0) {
			fwrite(rbuff, 1, cnt, fd1);    //C 库函数 size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) 把 ptr 所指向的数组中的数据写入到给定流 stream 中。
			memset(rbuff, '\0', sizeof(rbuff));
			if (cnt < 1024)
			{
				break;
			} //C 库函数 size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) 把 ptr 所指向的数组中的数据写入到给定流 stream 中。
		}
		//string msg = " ---收到文件后---";
		//TimeSave("E:\\jh\\Time_Client.txt", msg);

		//closesocket(sockClient);
		fclose(fd1);


	}//get


//	closesocket(sockClient);	//关闭连接
//	WSACleanup();				//释放Winsock
}


int FtpClientClass::execute_getFile(string filePath, string NewFilePath)
{


	char buff[1024];						//用来存储经过字符串格式化的order
	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//string str_name = filePath;

	//将指令整合进order，并存放进buff
	strcat(buff, "get"), strcat(buff, " "), strcat(buff, filePath.c_str());
	if (sendTCP(buff) == -1)									//发送指令
	{
		return 0;
	}

	std::ofstream file(NewFilePath, std::ios::binary);
	char buffer[10240]; // 接收缓冲区

	while (true)
	{
		// 接收数据大小（int 类型）
		int data_size=0;

		//size_t bytes_received = recv(sockClient, reinterpret_cast<char*>(&data_size), sizeof(data_size), 0);
		//int data_size = 0;
		char *char_int = new char[4];
		//int s = sizeof(data_size);
		//int s = sizeof(data_size);
		size_t bytes_received = 0;
		//bytes_received = recv(sockClient, reinterpret_cast<char*>(&data_size), 4, 0);
		bytes_received = recv(sockClient, char_int, 4, 0);
		memcpy(&data_size, char_int, 4);
		/*char buf[4] = { 0 };
		buf[0] = char_int[3];
		buf[1] = char_int[2];
		buf[2] = char_int[1];
		buf[3] = char_int[0];
		memcpy(&data_size, buf, 4);*/
		
		//cout << "char_int : " << char_int << endl;
		cout << "data_size: " << data_size << endl;
		if (bytes_received <= 0 || data_size == 0) {
			break; // 如果接收失败或数据大小为 0，则退出循环
		}
		
		if (data_size > 10240)
		{
			int a = 0;
		}
		int recv_size = data_size;
		while (1)
		{
			// 接收实际数据
			memset(buffer, 0, sizeof(buffer));
			///*if (recv_size > 10240)
			//{
			//	
			//	cout << "---------------------- recv_size : " << recv_size << " : " << recv_size << endl;
			//}*/
			int bytes_received = 0;
			bytes_received = recv(sockClient, buffer, recv_size, 0);
			cout << "bytes_received and recv_size : " << bytes_received << " : " << recv_size << endl;
			if (bytes_received < 0)
			{
				cout << "execute_getFile() 连接失败，错误代码: " << WSAGetLastError() << endl;
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
	//WSACleanup();
	file.close();
	std::cout << "文件接收完毕，连接关闭。" << std::endl;
	return 1;



}
//执行 put 上传
void FtpClientClass::execute_putFile(string sendfileName)
{
	char operation[10], name[1024];		//操作与文件名
	char order[1024] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order
	FILE *fd1, *fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));


	string str_name = sendfileName;
	strcpy(name, str_name.c_str());
	//将指令整合进order，并存放进buff
	strcat(order, "put"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);									//发送指令
	if (sendTCP(buff) == -1)									//发送指令
	{
		return;
	}
	//recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	recvTcpOneAll();
	cout << rbuff << endl;							//pwd功能在这里已经实现
	if (strncmp(rbuff, "put", 3) == 0)
	{ ///上传功能
		strcpy(fileName, rbuff + 4);
		fd2 = fopen(fileName, "rb");				//打开一个二进制文件，文件必须存在，只允许读
		if (fd2)
		{ //成功打开
			if (!sendFile(sockClient, fd2))
			{
				cout << "发送失败" << endl;

			}

			fclose(fd2);
		}
		else {
			strcpy(sbuff, "无法打开文件\n");
			if (send(sockClient, sbuff, sizeof(sbuff), 0)) {

			}
		}
	}//put
	cout << "上传成功!!!" << endl;

	//	closesocket(sockClient);	//关闭连接
		//WSACleanup();				//释放Winsock

}
//void FtpClientClass::execute_putFile(string localFilePath, std::string NewFilePath)
//{
//	char operation[10], name[1024];		//操作与文件名
//	char order[1024] = "\0";				//输入的命令
//	char buff[80];						//用来存储经过字符串格式化的order
//	FILE* fd1, * fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
//	int cnt;
//
//	memset(buff, 0, sizeof(buff));
//	memset(rbuff, 0, sizeof(rbuff));
//	memset(sbuff, 0, sizeof(sbuff));
//
//
//	string str_name = localFilePath;
//	strcpy(name, str_name.c_str());
//	//将指令整合进order，并存放进buff
//	strcat(order, "put"), strcat(order, " "), strcat(order, NewFilePath.c_str());
//	sprintf(buff, order);
//	//sendTCP(buff);									//发送指令
//	if (sendTCP(buff) == -1)									//发送指令
//	{
//		return;
//	}
//	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
//	cout << rbuff << endl;							//pwd功能在这里已经实现
//	if (strncmp(rbuff, "put", 3) == 0)
//	{ ///上传功能
//		strcpy(fileName, rbuff + 4);
//		fd2 = fopen(localFilePath.c_str(), "rb");				//打开一个二进制文件，文件必须存在，只允许读
//		if (fd2)
//		{ //成功打开
//			if (!sendFile(sockClient, fd2))
//			{
//				cout << "发送失败" << endl;
//
//			}
//
//			fclose(fd2);
//		}
//		else {
//			strcpy(sbuff, "无法打开文件\n");
//			if (send(sockClient, sbuff, sizeof(sbuff), 0)) {
//
//			}
//		}
//	}//put
//	cout << "上传成功!!!" << endl;
//}

bool FtpClientClass::execute_putFile(string localFilePath, std::string NewFilePath)
{
	char buff[1024];						//用来存储经过字符串格式化的order
	int cnt;


	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//将指令整合进order，并存放进buff
	memset(buff, 0, sizeof(buff));
	strcat(buff, "put"), strcat(buff, " "), strcat(buff, NewFilePath.c_str());

	if (sendTCP(buff) == -1)									//发送指令
	{
		return false;
	}
	//int size= recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	recvTcpOneAll();
	//cout << rbuff << size <<endl;							//pwd功能在这里已经实现
	if (strncmp(m_recvOneAllData, "put", 3) == 0)
	{ ///上传功能
		//strcpy(fileName, rbuff + 4);
		std::ifstream fileStream(localFilePath, std::ios::binary);
		if (fileStream.is_open())
		{
			if (sendFileData(sockClient, fileStream) == 1)
			{
				cout << "发送文件数据完成" << endl;

			}



			fileStream.close();

		}
		else
		{
			strcpy(sbuff, "无法打开文件\n");
			if (send(sockClient, sbuff, sizeof(sbuff), 0))
			{

			}
			std::cerr << "无法打开文件: " << localFilePath << std::endl;
			return false;
		}

	}//put
	cout << "上传成功!!!" << endl;
	return true;
}

//执行 进入文件夹命令
//void FtpClientClass::execute_cdFloder(string floderName)
//{
//	char operation[1024], name[1024];		//操作与文件名
//	char order[1024] = "\0";				//输入的命令
//	char buff[1024];						//用来存储经过字符串格式化的order
//	FILE *fd1, *fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
//	int cnt;
//
//	memset(buff, 0, sizeof(buff));
//	memset(rbuff, 0, sizeof(rbuff));
//	memset(sbuff, 0, sizeof(sbuff));
//	
//	//startSock();				//启动winsock并初始化
//	//if (callServer() == -1) 
//	//{	//发送连接请求失败
//	//	cout << "发送连接请求失败!!!";
//	//}
//
//	string str_name = floderName;
//	strcpy(name,str_name.c_str());
//
//
//	//memset(order1, 0, sizeof(order));
//	//memset(buff, 0, sizeof(buff));
//	strcat(order, "cd"), strcat(order, " "), strcat(order, name);
//	sprintf(buff, order);
//	sendTCP(buff);	
//	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
//	cout << rbuff << endl;	//pwd的
//	//closesocket(sockClient);	//关闭连接
//	//WSACleanup();				//释放Winsock
//}
//返回上一级目录
void FtpClientClass::execute_cdGoback()
{
	char operation[10], name[1024];		//操作与文件名
	char order[1024] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order
	FILE *fd1, *fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//startSock();				//启动winsock并初始化
	//if (callServer() == -1) 
	//{	//发送连接请求失败
	//	cout << "发送连接请求失败!!!";
	//}

	string str_name = "..";
	strcpy(name, str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "cd"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);	
	if (sendTCP(buff) == -1)									//发送指令
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	cout << rbuff << endl;	//pwd的
	//closesocket(sockClient);	//关闭连接
	//WSACleanup();				//释放Winsock
}
;//新建文件夹
void FtpClientClass::execute_mkdirFolder(string folder)
{
	char operation[10], name[1024];		//操作与文件名
	char order[1024] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order
	FILE *fd1, *fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//startSock();				//启动winsock并初始化
	//if (callServer() == -1) 
	//{	//发送连接请求失败
	//	cout << "发送连接请求失败!!!";
	//}

	string str_name = folder;
	strcpy(name, str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "mkdir"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);	
	if (sendTCP(buff) == -1)									//发送指令
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	cout << rbuff << endl;	//pwd的
	//closesocket(sockClient);	//关闭连接
	//WSACleanup();				//释放Winsock

}
//删除空文件夹
void FtpClientClass::execute_delFolder(string folder)
{
	char operation[10], name[1024];		//操作与文件名
	char order[1024] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order
	FILE *fd1, *fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//startSock();				//启动winsock并初始化
	//if (callServer() == -1) 
	//{	//发送连接请求失败
	//	cout << "发送连接请求失败!!!";
	//}

	string str_name = folder;
	strcpy(name, str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "del"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);	
	if (sendTCP(buff) == -1)									//发送指令
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	cout << rbuff << endl;	//pwd的
	//closesocket(sockClient);	//关闭连接
	//WSACleanup();				//释放Winsock

}

//删除某个文件
void FtpClientClass::execute_Filedelete(string folder)
{
	char operation[10], name[1024];		//操作与文件名
	char order[1024] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order
	FILE *fd1, *fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//startSock();				//启动winsock并初始化
	//if (callServer() == -1) 
	//{	//发送连接请求失败
	//	cout << "发送连接请求失败!!!";
	//}

	string str_name = folder;
	strcpy(name, str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "Fdel"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//	sendTCP(buff);	
	if (sendTCP(buff) == -1)									//发送指令
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	cout << rbuff << endl;	//pwd的
	//closesocket(sockClient);	//关闭连接
//	WSACleanup();				//释放Winsock

}
//删除某个文件
void FtpClientClass::execute_deleteFileList(string folder)
{
	char operation[10], name[1024];		//操作与文件名
	char order[1024] = "\0";				//输入的命令
	char buff[80];						//用来存储经过字符串格式化的order
	FILE *fd1, *fd2;					//File协议主要用于访问本地计算机中的文件，fd指针指向要访问的目标文件 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//startSock();				//启动winsock并初始化
	//if (callServer() == -1) 
	//{	//发送连接请求失败
	//	cout << "发送连接请求失败!!!";
	//}

	string str_name = folder;
	strcpy(name, str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "fldel"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);	
	if (sendTCP(buff) == -1)									//发送指令
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	cout << rbuff << endl;	//pwd的
//	closesocket(sockClient);	//关闭连接
//	WSACleanup();				//释放Winsock

}

bool FtpClientClass::execute_rename(const std::string oldDir, const std::string newDir)
{
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	strcat(sbuff, "rename ");
	strcat(sbuff, oldDir.c_str());
	strcat(sbuff, "|");
	strcat(sbuff, newDir.c_str());
	//sendTCP(sbuff);
	if (sendTCP(sbuff) == -1)									//发送指令
	{
		return false;
	}

	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	if (strcmp(rbuff, "rename-ok") == 0) {
		return true;
	}
	return false;
}

bool FtpClientClass::execute_compress(const std::vector<std::string> vecPath, const std::string newZip)
{

	memset(sbuff, 0, sizeof(sbuff));

	strcat(sbuff, "compress");
	if (sendTCP(sbuff, sizeof(sbuff)) == -1)									//发送指令
	{
		return false;
	}

	// 循环发送要压缩的路径
	for (const auto& strPath : vecPath)
	{
		memset(sbuff, 0, sizeof(sbuff));
		sprintf(sbuff, strPath.c_str());
		if (sendTCP(sbuff, sizeof(sbuff)) == -1)
		{
			return false;
		}
	}
	// 发送路径结束标志
	memset(sbuff, 0, sizeof(sbuff));
	strcat(sbuff, "compress-zipname ");
	strcat(sbuff, newZip.c_str());
	if (sendTCP(sbuff) == -1)
	{
		return false;
	}

	memset(rbuff, 0, sizeof(rbuff));
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	if (strncmp(rbuff, "compress-ok", 11) == 0) {
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

// 解压文件;
bool FtpClientClass::execute_uncompress(const std::vector<std::string> vecPath)
{
	memset(sbuff, 0, sizeof(sbuff));

	strcat(sbuff, "uncompress");
	if (sendTCP(sbuff, sizeof(sbuff)) == -1)									//发送指令
	{
		return false;
	}

	// 循环发送要压缩的路径
	for (const auto& strPath : vecPath)
	{
		memset(sbuff, 0, sizeof(sbuff));
		sprintf(sbuff, strPath.c_str());
		if (sendTCP(sbuff, sizeof(sbuff)) == -1)
		{
			return false;
		}
	}
	// 发送路径结束标志
	memset(sbuff, 0, sizeof(sbuff));
	strcat(sbuff, "uncompress-paths-end");
	if (sendTCP(sbuff) == -1)
	{
		return false;
	}

	memset(rbuff, 0, sizeof(rbuff));
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//接收信息 
	if (strncmp(rbuff, "uncompress-ok", 13) == 0) {
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

// 获取文件夹名称
/*vector<string>*/ 	vector<vector<string>> FtpClientClass::Gets_FolderName()
{
	return vecDirName;
}
// 获取文件名称
vector<vector<string>> FtpClientClass::Gets_FileName()
{
	return vecFileName;
}

