#pragma once

#include "Winsock.h"
#include "windows.h"
#include "time.h"
#include "stdio.h"
#include <iostream>

#include <vector>
#include <string>
using namespace std;
#pragma comment(lib, "wsock32.lib")	//����ws2_32.dll������Windows SocketsӦ�ó���ӿڣ� ����֧��Internet������Ӧ�ó���

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

	DWORD startSock();							//����winsock����ʼ��
	DWORD createSocket();						//����socket
	DWORD callServer();							//������������

	DWORD mkdir(char fileName[]);				//�����ļ���
	void help();								//�˵�
	void list(SOCKET sockfd);					//�г�Զ����ǰĿ¼
	DWORD sendTCP(char data[]);					//����Ҫִ�е������������
	int user();									//�ϴ��û���
	int pass();									//�ϴ�����
	int sendFile(SOCKET datatcps, FILE* file);	//put ���͸�Զ��һ���ļ�
	bool newConnection();
	//void execute_ls();//��ȡ��ǰ�ļ����� ִ��ls
	void execute_ls(const std::string  strDirPath);//��ȡָ��·�����ļ����� ִ��ls
	string Gets_CurrentPath();//��ȡ��ǰ·��
	void execute_getFile(string rec_name);//ִ�� get name
	void execute_getFile(string filePath,string NewFilePath);//ִ�� get name
	void execute_putFile(string sendfileName);//ִ�� put �ϴ�
	void execute_putFile(string localFilePath,std::string NewFilePath);//ִ�� put �ϴ�
	//void execute_cdFloder(string floderName);//ִ�� �����ļ�������
	void execute_cdGoback();//������һ��Ŀ¼
	void execute_mkdirFolder(string folder);//�½��ļ���
	void execute_delFolder(string folder);//ɾ���ļ���
	void execute_Filedelete(string folder);//ɾ���ļ�
	void execute_deleteFileList(string folder);//ɾ��ĳ���ļ����������ļ�
	bool  execute_rename(const std::string  oldDir,const std::string newDir);

	vector<string> Gets_FolderName();//��ȡ�ļ�������
	vector<vector<string>> Gets_FileName();//��ȡ�ļ�����

	
private:
	SOCKET sockClient;		//�ͻ��˶���
	sockaddr_in serverAddr;	//��������ַ
	char inputIP[20];		//�洢����ķ�����IP
	char fileName[128];		//�ļ���
	char rbuff[1024];		//���ջ�����
	char sbuff[1024];		//���ͻ�����
	bool checkFlag;			//��־�Ƿ�ͨ����½

	FileInformation m_FileInformation;
	vector<string> vecName;//����ļ������Ƶ�vector
	vector<vector<string>> vecFileName;//����ļ����ƺ��ļ�ʱ��
	
};