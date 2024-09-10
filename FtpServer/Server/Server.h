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
	//��ӭ����
	bool welcome();
	//��������к���
	void running();
	//�����������
	int commandParse(char* instruck, std::string &paramter);
	//�ļ����պ���
	bool receiveFile(std::string filename);
	//�ļ�����
	bool sendFile(std::string filename);



private:
	//SOCKET server;
	int maxSize;
	char buf[1024];
	std::string storePath;

	SOCKET sockClient, sockServer;
	sockaddr_in severAddr;//��������ַ
	sockaddr_in ClientAddr;//�ͻ��˵�ַ 

	int addrLen;		//��ַ����
	char fileName[20];	//�ļ���
	char m_path[256];	//�ļ���
	char order[20];		//����
	char rbuff[1024];	//���ջ�����
	char sbuff[1024];	//���ͻ�����

	char m_sendOneAllData[1024];
	char m_recvOneAllData[1024];
};

