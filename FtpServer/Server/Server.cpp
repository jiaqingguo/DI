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

#define RECV_PORT 4312	//���ն˿�
#define SEND_PORT 4302	//���Ͷ˿�
#pragma comment(lib, "wsock32.lib")

namespace fs = std::filesystem;

char namePassword[1024] = "zwj 123456";	//�û���������





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
//***************��������***************

//FileInformation m_FileInformation;
//***************��������***************
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

	str += pattern;//��չ�ַ����Է������
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

DWORD Server::startSock() {//��ʼ��winsock
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		cout << "��ʼ��ʧ��" << endl;
		return -1;
	}
	return 1;
}
DWORD Server::createSocket() {
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClient == SOCKET_ERROR) {
		cout << "����ʧ��" << endl;
		WSACleanup();
		return -1;
	}
	severAddr.sin_family = AF_INET;
	severAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	severAddr.sin_port = htons(RECV_PORT);
	if (bind(sockClient, (struct sockaddr FAR*) & severAddr, sizeof(severAddr)) == SOCKET_ERROR) {
		//bind�������ڽ�socket�͵�ַ�ṹ��
		cout << "��ʧ��" << endl;
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
		cout << "�����ļ���" << fileName << "�ɹ�" << endl;
		return 1;
	}
	else
	{
		cout << "�����ļ���" << fileName << "ʧ��" << endl;
		return 0;
	}


}
//ɾ�����ļ���
DWORD Server::delFile(char fileName[]) {
	char path[1000];
	GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼

	strcat(path, "\\");
	strcat(path, fileName);
	// cout<<path<<endl;
	bool flag = RemoveDirectory(path);
	if (flag)
	{
		cout << "ɾ�����ļ��У�" << fileName << "�ɹ�" << endl;
		return 1;
	}
	else
	{
		cout << "ɾ�����ļ��У�" << fileName << "ʧ��" << endl;
		return 0;
	}

}
//ɾ��ĳ���ļ�
DWORD Server::delFile1(char fileName[])
{
	//char path[1000];
 //	GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼

	/*strcat(path, "\\");
	strcat(path, fileName);
	cout << path << endl;*/
	if (remove(fileName) == 0)
	{
		cout << "ɾ���ɹ�" << endl;
		return 1;
	}
	else
	{
		cout << "ɾ��ʧ��" << endl;
		return 0;
	}
}

void Server::delete_listFiles(string dir)
{

	//��Ŀ¼�������"\\*.*"���е�һ������
	string newDir = dir + "\\*.*";
	//���ڲ��ҵľ��
	intptr_t handle;
	struct _finddata_t fileinfo;
	//��һ�β���
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		cout << "���ļ�" << endl;
		//	system("pause");
		return;
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//���Ϊ�ļ��У������ļ���·�����ٴα���
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
			newDir = dir + "\\" + fileinfo.name;
			delete_listFiles(newDir.c_str());//�ȱ���ɾ���ļ����µ��ļ�����ɾ���յ��ļ���
			cout << newDir.c_str() << endl;
			if (_rmdir(newDir.c_str()) == 0) {//ɾ�����ļ���
				cout << "delete empty dir success" << endl;
			}
			else {
				cout << "delete empty dir error" << endl;
			}
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			cout << file_path.c_str() << endl;
			if (remove(file_path.c_str()) == 0) {//ɾ���ļ�
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
	addrLen = sizeof(ClientAddr);//addrLen�Ƕ����ַ�ĳ��� 
	if (listen(sockClient, 10) < 0) {//���׽��ֽ��뱻������״̬������2Ϊ������е���󳤶�
		cout << "����ʧ��" << endl;
		return -1;
	}

}
int Server::sendFileList(SOCKET datatcps, char dirPath[])
{
	HANDLE hff;								//����һ���߳�
	WIN32_FIND_DATA fd;						//�����ļ�
	hff = FindFirstFile(dirPath, &fd);			//�����ļ����Ѵ������ļ���������Զ�ȡ��WIN32_FIND_DATA�ṹ��ȥ 
	if (hff == INVALID_HANDLE_VALUE)
	{		//��������
		/*const char* errStr = "ls-falied\n";
		cout << *errStr << endl;
		if (send(datatcps, errStr, strlen(errStr), 0) == SOCKET_ERROR)
		{
			cout << "����ʧ��" << endl;
		}*/
		//closesocket(datatcps);
		return 0;
	}
	BOOL flag = TRUE;
	while (flag)
	{//�����ļ���Ϣ
		if (!sendFileRecord(datatcps, &fd))
		{
			//closesocket(datatcps);
			return 0;
		}
		flag = FindNextFile(hff, &fd);//������һ���ļ�
		// �رվ��
		//FindClose(hff);
	}
	// �رվ��
	FindClose(hff);
	return 1;
}
int Server::sendFile(SOCKET datatcps, FILE* file) {
	cout << "���ڷ����ļ���" << endl;
	memset(sbuff, '\0', sizeof(sbuff));
	while (1)
	{//���ļ���ѭ����ȡ���ݲ��������ͻ���
		int len = fread(sbuff, 1, sizeof(sbuff), file);//��fileָ��ָ����ļ��е����ݶ�ȡ��sbuff��
		if (send(datatcps, sbuff, len, 0) == SOCKET_ERROR)
		{
			cout << "����ʧ��" << endl;
			//closesocket(datatcps);
			return 0;
		}
		if (len == 0)
		{
			sprintf(sbuff, "get-end", sbuff);
			send(datatcps, sbuff, strlen(sbuff), 0);					//����ָ��
			break;
		}
		else if (len < sizeof(sbuff)) {//�ļ����ͽ���
			sprintf(sbuff, "get-end", sbuff);
			send(datatcps, sbuff, strlen(sbuff), 0);					//����ָ��
			break;
		}
	}
	cout << "���ͳɹ�" << endl;
	return 1;

}

int Server::sendFileData(SOCKET datatcps, std::ifstream& file)
{
	// �����ļ�����
	char buffer[10240]; // һ����෢�� 10240 �ֽ�
	cout << "�ļ����ݿ�ʼ��ȡ" << endl;
	while (file)
	{

		memset(buffer, 0, sizeof(buffer));
		file.read(buffer, sizeof(buffer));
		std::streamsize bytes_read = file.gcount();

		// ����Ҫ���͵�ʵ�ʴ�С
		int data_size = static_cast<int>(bytes_read);
		if (data_size == 0) {
			break; // �ļ��Ѷ���
		}
		// �����ȡ���ֽ������� 10240��������Ϊ 10240
		if (data_size > 10240) {
			data_size = 10240;
		}

		cout << "send buffer value  " << strlen(buffer) << " " << sendSize << endl;

	}
}
int Server::sendFileList(SOCKET datatcps) {
	HANDLE hff;								//����һ���߳�
	WIN32_FIND_DATA fd;						//�����ļ�
	hff = FindFirstFile("*", &fd);			//�����ļ����Ѵ������ļ���������Զ�ȡ��WIN32_FIND_DATA�ṹ��ȥ 
	if (hff == INVALID_HANDLE_VALUE)
	{		//��������
		const char* errStr = "�г��ļ��б�ʱ��������\n";
		cout << *errStr << endl;
		if (send(datatcps, errStr, strlen(errStr), 0) == SOCKET_ERROR)
		{
			cout << "����ʧ��" << endl;
		}
		//closesocket(datatcps);
		return 0;
	}
	BOOL flag = TRUE;
	while (flag)
	{//�����ļ���Ϣ
		if (!sendFileRecord(datatcps, &fd))
		{
			//closesocket(datatcps);
			return 0;
		}
		flag = FindNextFile(hff, &fd);//������һ���ļ�
		 // �رվ��
		FindClose(hff);
	}

	return 1;
}
int Server::sendFileRecord(SOCKET datatcps, WIN32_FIND_DATA* pfd) {//���͵�ǰ���ļ���¼
	char fileRecord[MAX_PATH + 32];
	char fileRecord1[1024];
	FILETIME ft;						//�ļ��Ľ���ʱ��
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
	//	//ͨ��datatcps�ӿڷ���fileRecord���ݣ��ɹ����ط��͵��ֽ���
	//	cout << "����ʧ��" << endl;
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
		//ͨ��datatcps�ӿڷ���fileRecord���ݣ��ɹ����ط��͵��ֽ���   
		cout << "����ʧ��" << endl;
		return 0;
	}
	//cout << "strlen(fileRecord1) " << strlen(fileRecord)<< "-----------------------------------"<< endl;
	return 1;
}

void Server::InitResource()
{

	TCHAR szPasswd[] = TEXT("jinghang123");          //������Դ��Ȩ�û�������
	TCHAR szUserName[] = TEXT("jinghang");        //������Դ��Ȩ���û�

	//TCHAR szPasswd[] = TEXT("langdifeng123");          //������Դ��Ȩ�û�������
	//TCHAR szUserName[] = TEXT("langdifeng");        //������Դ��Ȩ���û�
	NETRESOURCE net_Resource;
	net_Resource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
	net_Resource.dwScope = RESOURCE_CONNECTED;
	net_Resource.dwType = RESOURCETYPE_ANY;
	net_Resource.dwUsage = 0;
	net_Resource.lpComment = TEXT("");
	net_Resource.lpLocalName = TEXT("Y:");  //ӳ��ɱ���������z:
	net_Resource.lpProvider = NULL;
	//net_Resource.lpRemoteName = TEXT("\\\\192.168.196.254\\share"); // \\servername\������Դ��
	net_Resource.lpRemoteName = TEXT("\\\\192.168.0.250\\share"); // \\servername\������Դ��
	DWORD dwFlags = CONNECT_UPDATE_PROFILE;
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);

	DWORD dw = WNetAddConnection2(&net_Resource, szPasswd, szUserName, dwFlags);
	switch (dw)
	{
	case ERROR_SUCCESS:
		ShellExecute(NULL, TEXT("open"), TEXT("z:"), NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_ACCESS_DENIED:
		wprintf(TEXT(L"û��Ȩ���ʣ�"));
		break;
	case ERROR_ALREADY_ASSIGNED:
		ShellExecute(NULL, TEXT("open"), TEXT("z:"), NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_INVALID_ADDRESS:
		wprintf(TEXT(L"IP��ַ��Ч"));
		break;
	case ERROR_NO_NETWORK:
		wprintf(TEXT(L"���粻�ɴ�!"));
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
	cout << "~Server() ִ������" << endl;
}

bool Server::welcome()
{
	char* welcome = "Welcome, my friend\n";

	//������Ϣ���ͻ���
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
			cout << endl << "��ȡ��ִ�е����0" << rbuff << endl;
			return;
		}
		else if (ret < 0)
		{
			cout << endl << "��ȡ��ִ�е����" << ret << endl;
			closesocket(sockServer);
			return;
		}
		cout << endl << "��ȡ��ִ�е����" << rbuff << endl;
		if (strncmp(rbuff, "get", 3) == 0)
		{
			char fileName[256];	//�ļ���
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
				{//���������������Ӵ�������
					if (!sendFileData(sockServer, fileStream))
					{
						cout << "�����ļ�����ʧ��" << endl;
						return;
					}
					else
					{
						cout << "�����ļ��������" << endl;
					}

					fileStream.close();
				}

			}
			else
			{

				// ���ͽ����ź�
				int end_signal = 0; // 0 ��Ϊ�����ź�
				send(sockServer, reinterpret_cast<const char*>(&end_signal), sizeof(end_signal), 0);

				/*strcpy(sbuff, "openFailed\n");
				if (send(sockServer, sbuff, sizeof(sbuff), 0))
				{
					cout << "openFailed send sucess" << endl;
				}
				else {
					cout << "openFailed send failed" << endl;
				}*/
				//	std::cerr << "�޷����ļ�: " << file_path << std::endl;	
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
				cout << "����putָ��" << endl;
			}

			memset(rbuff, '\0', sizeof(rbuff));
			cout << "careate file start save" << endl;
			std::ofstream file(path, std::ios::binary);
			//char buffer[10240]; // ���ջ�����

			while (true)
			{
				// �������ݴ�С��int ���ͣ�
				int data_size = -1;
				int bytes_received = recv(sockServer, reinterpret_cast<char*>(&data_size), sizeof(data_size), 0);
				if (bytes_received <= 0 ) {
					cout << "����ʧ�ܣ��������: " << WSAGetLastError() << endl;
					std::cout << bytes_received<< data_size<<" ---����ʧ�ܻ�Ҫ���ܵ����ݴ�СΪ 0�����˳�ѭ��    put������������������\n";
					break; // �������ʧ�ܻ����ݴ�СΪ 0�����˳�ѭ��
				}
				else if (data_size == 0)
				{
					
					break; // ���ݴ�СΪ 0�����˳�ѭ��
				}
				int recv_size = data_size;
				// ����ʵ������
				char buffer[10240]; // ���ջ�����;
				while (1)
				{
					
					memset(buffer, 0, sizeof(buffer));
					bytes_received = recv(sockServer, buffer, recv_size, 0);
					if (bytes_received == -1)
					{
						cout <<"����ֵ:"<< bytes_received<< " ����ʧ�ܣ��������: " << WSAGetLastError() << endl;
						std::cout << "----2����ʧ��  put������������������\n";
						closesocket(sockServer);
						break;
					}
					// �����յ�������д���ļ�
					file.write(buffer, bytes_received);

					if (bytes_received < recv_size)
					{
						recv_size = recv_size - bytes_received;
					}
					else
					{
						break; // �������ȫ����ɣ��˳�ѭ��;
					}
				}
			}

			file.close();
			std::cout << "�ļ�������ϣ����ӹرա�" << std::endl;
			cout << " put ����ִ�����" << endl;

			cout << GetTimeString() << endl;
		}//put
		else if (strncmp(rbuff, "pwd", 3) == 0) {
			//
			////strcpy(sbuff, "T:\\�����\\CS");//���Լ�ѡ��ľ���·��
			// GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼			
			//strcpy(sbuff, path);
			//int size = strlen(sbuff);
			//send(sockServer, sbuff, size, 0);
			memset(m_sendOneAllData, 0, sizeof(m_sendOneAllData));
			//strcpy(sbuff, "T:\\�����\\CS");//���Լ�ѡ��ľ���·��
			GetCurrentDirectory(sizeof(m_sendOneAllData), m_sendOneAllData);//�ҵ���ǰ���̵ĵ�ǰĿ¼

			if (sendTcpOneAll() <= 0)
			{

			}
			cout << "pwd ִ�н���" << endl;
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
				cout << endl << "ls-end ִ����ɣ�" << endl;
			}
			else {
				memset(sbuff, '\0', sizeof(sbuff));
				sprintf(sbuff, "ls-falied");
				int size = strlen(sbuff);
				send(sockServer, sbuff, size, 0);
				cout << endl << "ls-falied ִ����ɣ�" << endl;
			}*/

		}//ls
		else if (strncmp(rbuff, "cd", 2) == 0) {
			char fileName[20];	//�ļ���
			strcpy(fileName, rbuff + 3);
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);
			SetCurrentDirectory(fileName);//���õ�ǰĿ¼ 
			cout << "cd ִ�н���" << endl;
		}//cd
		else if (strncmp(rbuff, "mkdir", 5) == 0)
		{
			char m_path[256];
			memset(m_path, '\0', sizeof(m_path));
			strcpy(m_path, rbuff + 6);
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//���ͻ���Ϣ
			mkdir(m_path);
			//mkdir("T:\\�����\\CS\\2222.txt");
		}//mkdir
		else if (strncmp(rbuff, "del", 3) == 0) { // ɾ�����ļ���;
			char fileName[20];	//�ļ���
			strcpy(fileName, rbuff + 4);//���Ҫɾ���ļ���
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//���ͻ���Ϣ
			delFile(fileName);
		}//del
		else if (strncmp(rbuff, "Fdel", 4) == 0) {//ɾ��ĳ���ļ�
			char m_path[256];
			memset(m_path, '\0', sizeof(m_path));
			strcpy(m_path, rbuff + 5);//���Ҫɾ���ļ���
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//���ͻ���Ϣ
			delFile1(m_path);
		}//Fdel
		else if (strncmp(rbuff, "fldel", 5) == 0) {//ɾ��ĳ���ļ����������ļ�
			char path[260];
			strcpy(path, rbuff + 6);//���Ҫɾ���ļ���
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//���ͻ���Ϣ

			//GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼
			//strcat(path, "\\");
			//strcat(path, fileName);
			cout << path << endl;
			string str = path;
			delete_listFiles(path); // ɾ���ļ����µ��ļ�;

			bool flag = RemoveDirectory(path); // ɾ���ļ��б���;
			if (!flag)
			{
				cout << "ɾ���ļ��У�" << path << "ʧ��" << endl;

			}
			else
			{
				cout << "ɾ���ļ��У�" << path << "�ɹ�" << endl;
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
			cout << "fldel ִ�н���" << endl;
		}//Fdel
		else if (strncmp(rbuff, "rename", 6) == 0) // �ļ���������;
		{
			char tbuff[1024];
			strcpy(tbuff, rbuff + 7);

			// ����һ�����޸ĵ�char���飬������������
			char* buffer = new char[strlen(tbuff) + 1];
			strcpy(buffer, tbuff);

			// ʹ��strtok�ָ��ַ���
			char* firstPart = strtok(buffer, "|");  // ��ȡ��һ������
			char* secondPart = strtok(nullptr, "|"); // ��ȡ�ڶ�������

			// ���ָ������ת��Ϊstd::string
			std::string oldPath = firstPart ? firstPart : ""; // ����Ƿ�Ϊ��
			std::string newPath = secondPart ? secondPart : "";

			bool bRet = true;
			memset(sbuff, '\0', sizeof(sbuff));

			try {
				// �����ļ��Ƿ����
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
			cout << "rename ִ�н���" << endl;
		}
		else if (strncmp(rbuff, "compress", 8) == 0) // ѹ��;
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
					std::cout << "�ͻ������˳� ������������������\n";
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
			cout << "compress ִ�н���" << endl;
		}
		else if (strncmp(rbuff, "uncompress", 10) == 0) // ��ѹ;
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
					std::cout << "�ͻ������˳� ������������������\n";
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
				// ����ļ�·���Ƿ��� .zip ��β
				if (path.extension() == ".zip")
				{
					// ���ز��� .zip ��׺����·��
					fs::path newDir = path.parent_path() / path.stem(); // ��Ӹ�Ŀ¼�������µ�Ŀ¼��
					std::string strDir = newDir.string();
					std::cout << "��ѹ " << path << "   " << strDir << std::endl;
					extractZip(path, strDir);
				}

			}

			memset(sbuff, 0, sizeof(sbuff));
			sprintf(sbuff, "uncompress-ok");
			send(sockServer, sbuff, strlen(sbuff), 0);
			cout << "uncompress ִ�н���" << endl;
		}
		else if (strncmp(rbuff, "user", 4) == 0) {
			char tbuff[1024];
			strcpy(tbuff, rbuff + 5);
			strcat(tbuff, " ");
			memset(rbuff, '\0', sizeof(rbuff));
			strcpy(sbuff, "�ɹ���ȡ�û���\0");
			send(sockServer, sbuff, sizeof(sbuff), 0);

			int recvSize = recv(sockServer, rbuff, sizeof(rbuff), 0);
			if (recvSize == -1)
			{
				std::cout << "�ͻ������˳� ������������������\n";
				closesocket(sockServer);
				return;
			}
			cout << endl << "��ȡ��ִ�е����" << rbuff << endl;
			strcat(tbuff, rbuff + 5);
			if (strcmp(tbuff, namePassword) == 0) {//��֤�Ƿ���ȷ���������ݸ��ͻ���
				send(sockServer, "right\0", sizeof(sbuff), 0);
			}
			else {
				send(sockServer, "wrong\0", sizeof(sbuff), 0);
			}
		}//user pass

	}
	cout << "Server::runing() ���н���" << endl;
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

	//int data_size=��
	int dataSize = strlen(m_sendOneAllData);
	send(sockServer, reinterpret_cast<const char*>(&dataSize), sizeof(dataSize), 0);
	int length = send(sockServer, m_sendOneAllData, dataSize, 0);
	if (length <= 0) {
		cout << "���������������ʧ��" << endl;
		closesocket(sockServer);//����ʹ��socket()�������׽���ʱ��Ӧ�õ���closesocket()���������رգ�����ͬ����fclose()�����ر�һ���ļ������������׽�����Դ���ͷš�
		WSACleanup();
		return length;
	}

	return length;
}
int Server::recvTcpOneAll()
{
	memset(m_recvOneAllData, 0, sizeof(m_recvOneAllData));
	// �������ݴ�С��int ���ͣ�
	int iAllDataSize = 0;
	size_t bytes_received = recv(sockServer, reinterpret_cast<char*>(&iAllDataSize), sizeof(iAllDataSize), 0);
	if (bytes_received <= 0) {
		return bytes_received; // �������ʧ�ܣ����˳�
	}
	int recv_size = iAllDataSize;
	char combinedBuf[sizeof(m_recvOneAllData)];// ���������������
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
			cout << "��ȡʱ��������" << endl;
			return -1;

		}
		else if (iCurRecvSize == 0)
		{
			continue;
		}

		if (iCurRecvSize < recv_size) //iAllDataSize��ֵӦ����540
		{
			recv_size = recv_size - iCurRecvSize;
			// �����յ������ݸ��Ƶ���ϻ�����
			memcpy(combinedBuf + combinedBufstart, recvBuf, iCurRecvSize);
			combinedBufstart += iCurRecvSize; // �����ѽ������ݵ��ܴ�С
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
	//�������ϴ��ļ�����ͬ���ļ�
	std::string filePath = storePath + filename;
	std::ofstream storeFile(filePath, std::ios_base::binary);
	if (!storeFile) {
		std::cout << "Create file failed\n";
	}

	//�Ƚ����ļ���С��Ϣ
	memset(buf, 0, maxSize);
	int recvSize = recv(sockServer, buf, 1024, 0);
	if (recvSize == -1)
	{
		std::cout << "�ͻ������˳� ������������������\n";
		return false;
	}
	int fileSize = atoi(buf);
	std::cout << "File's size is:" << fileSize << std::endl;

	int len = 1;
	int recvCount = 0;
	//ͳ���ļ�����ʣ�µĴ�С
	int remain = fileSize;
	while (true) {
		memset(buf, 0, maxSize);
		len = recv(sockServer, buf, 1024, 0);
		if (len = -1)
		{
			std::cout << "�ͻ������˳� ������������������\n";
			return false;
		}
		storeFile.write(buf, 1024);
		if (len == SOCKET_ERROR) {
			std::cout << "Receive occur error\n";
		}

		//���ʣ�µ�С�ڵ���0��˵���ļ�������ϣ��˳�ѭ��
		remain -= 1024;
		if (remain <= 0) {
			//if (strlen(buf) == 0) {
			break;
		}

		recvCount += strlen(buf);
		std::cout << "Receive " << recvCount << " bytes\n";
	}

	//�رղ������ļ�
	storeFile.close();
	std::cout << "Write file successful\n";

	return false;
}

bool Server::sendFile(std::string filename)
{
	return false;
}
