#pragma once

#include "Winsock.h"
#include "windows.h"
#include "time.h"
#include "stdio.h"
#include <iostream>

#include <vector>
#include <string>
using namespace std;
#pragma comment(lib, "wsock32.lib")	//加载ws2_32.dll，它是Windows Sockets应用程序接口， 用于支持Internet和网络应用程序。

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

class FtpClientClass
{
public:
	FtpClientClass();
	~FtpClientClass();

	DWORD startSock();							//启动winsock并初始化
	DWORD createSocket();						//创建socket
	DWORD callServer();							//发送连接请求

	DWORD mkdir(char fileName[]);				//创建文件夹
	void help();								//菜单
	void list(SOCKET sockfd);					//列出远方当前目录
	DWORD sendTCP(char data[]);					//发送要执行的命令至服务端
	int user();									//上传用户名
	int pass();									//上传密码
	int sendFile(SOCKET datatcps, FILE* file);	//put 传送给远方一个文件
	bool newConnection();
	//void execute_ls();//获取当前文件名称 执行ls
	void execute_ls(const std::string  strDirPath);//获取指定路径的文件名称 执行ls
	string Gets_CurrentPath();//获取当前路径
	void execute_getFile(string rec_name);//执行 get name
	void execute_getFile(string filePath,string NewFilePath);//执行 get name
	void execute_putFile(string sendfileName);//执行 put 上传
	void execute_putFile(string localFilePath,std::string NewFilePath);//执行 put 上传
	//void execute_cdFloder(string floderName);//执行 进入文件夹命令
	void execute_cdGoback();//返回上一级目录
	void execute_mkdirFolder(string folder);//新建文件夹
	void execute_delFolder(string folder);//删除文件夹
	void execute_Filedelete(string folder);//删除文件
	void execute_deleteFileList(string folder);//删除某个文件夹内所有文件
	bool  execute_rename(const std::string  oldDir,const std::string newDir);

	vector<string> Gets_FolderName();//获取文件夹名称
	vector<vector<string>> Gets_FileName();//获取文件名称

	
private:
	SOCKET sockClient;		//客户端对象
	sockaddr_in serverAddr;	//服务器地址
	char inputIP[20];		//存储输入的服务器IP
	char fileName[128];		//文件名
	char rbuff[1024];		//接收缓冲区
	char sbuff[1024];		//发送缓冲区
	bool checkFlag;			//标志是否通过登陆

	FileInformation m_FileInformation;
	vector<string> vecName;//存放文件夹名称的vector
	vector<vector<string>> vecFileName;//存放文件名称和文件时间
	
};