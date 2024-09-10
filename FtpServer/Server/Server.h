#pragma once

#include <Winsock2.h>
#include <string>

//using namespace std;

class Server
{
public:
	Server(SOCKET s);
	~Server();


	std::string GetTimeString();
	void TimeSave(std::string data, std::string source);
	DWORD startSock();
	DWORD createSocket();
	DWORD mkdir(char fileName[]);
	DWORD delFile(char fileName[]);
	DWORD delFile1(char fileName[]);
	int sendFileRecord(SOCKET datatcps, WIN32_FIND_DATA* pfd);
	int sendFileList(SOCKET datatcps);
	int sendFileList(SOCKET datatcps, char fileName[]);
	int sendFile(SOCKET datatcps, FILE* file);
	int sendFileData(SOCKET datatcps, std::ifstream& file);
	void delete_listFiles(std::string dir);
	DWORD connectProcess();
	bool sendTcpOneAll();
	int recvTcpOneAll();

	void InitResource();
	//欢迎函数
	bool welcome();
	//服务端运行函数
	void running();
	//命令解析函数
	int commandParse(char* instruck, std::string &paramter);
	//文件接收函数
	bool receiveFile(std::string filename);
	//文件发送
	bool sendFile(std::string filename);



private:
	//SOCKET server;
	int maxSize;
	char buf[1024];
	std::string storePath;

	SOCKET sockClient, sockServer;
	sockaddr_in severAddr;//服务器地址
	sockaddr_in ClientAddr;//客户端地址 

	int addrLen;		//地址长度
	char fileName[20];	//文件名
	char m_path[256];	//文件名
	char order[20];		//命令
	char rbuff[1024];	//接收缓冲区
	char sbuff[1024];	//发送缓冲区

	char m_sendOneAllData[1024];
	char m_recvOneAllData[1024];
};

