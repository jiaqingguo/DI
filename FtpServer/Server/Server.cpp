#include "Server.h"
#include "Tool.h"


#include <fstream>


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

#define RECV_PORT 4312	//���ն˿�
#define SEND_PORT 4302	//���Ͷ˿�
#pragma comment(lib, "wsock32.lib")



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
	char path[1000];
	GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼

	strcat(path, "\\");
	strcat(path, fileName);
	cout << path << endl;
	bool flag = CreateDirectory(path, NULL);
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
	char path[1000];
	GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼

	strcat(path, "\\");
	strcat(path, fileName);
	cout << path << endl;
	if (remove(path) == 0)
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
			break;
		}
	}
	//closesocket(datatcps);
	cout << "���ͳɹ�" << endl;
	return 1;
}
int Server::sendFileList(SOCKET datatcps) {
	HANDLE hff;								//����һ���߳�
	WIN32_FIND_DATA fd;						//�����ļ�
	hff = FindFirstFile("*", &fd);			//�����ļ����Ѵ������ļ���������Զ�ȡ��WIN32_FIND_DATA�ṹ��ȥ 
	if (hff == INVALID_HANDLE_VALUE) {		//��������
		const char* errStr = "�г��ļ��б�ʱ��������\n";
		cout << *errStr << endl;
		if (send(datatcps, errStr, strlen(errStr), 0) == SOCKET_ERROR) {
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
	}
//	closesocket(datatcps);
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
	memcpy(m_FileInformation.fileDir, dir, 20);

	memcpy(fileRecord1, &m_FileInformation, sizeof(m_FileInformation));

	cout << m_FileInformation.fileName << endl;

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
	net_Resource.lpLocalName = TEXT("z:");  //ӳ��ɱ���������z:
	net_Resource.lpProvider = NULL;
	//net_Resource.lpRemoteName = TEXT("\\\\192.168.196.254\\share"); // \\servername\������Դ��
	net_Resource.lpRemoteName = TEXT("\\\\data\\share"); // \\servername\������Դ��
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
}

bool Server::welcome()
{
	char *welcome = "Welcome, my friend\n";

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
		if (ret == 0)
		{
			continue;
		}
		else if (ret < 0)
		{
			return;
		}
		cout << endl << "��ȡ��ִ�е����" << rbuff << endl;
		if (strncmp(rbuff, "get", 3) == 0)
		{
			char fileName[256];	//�ļ���
			strcpy(fileName, rbuff + 4);
			FILE* file;//����һ���ļ�����ָ��
			//���������ļ�����
			file = fopen(fileName, "rb");//�����ƴ��ļ���ֻ�����
			if (file != NULL)
			{
				memset(sbuff, '/0', sizeof(sbuff));
				sprintf(sbuff, "get %s", fileName);
				int size = strlen(sbuff);
				int ret = send(sockServer, sbuff, sizeof(sbuff), 0);
				if (ret <=0) {
					fclose(file);
					return ;
				}
				else {//���������������Ӵ�������
					//string msg = " ---�����ļ��ɹ�---";
					//TimeSave("E:\\jh\\Time_Server.txt", msg);
					if (!sendFile(sockServer, file)) {
						return;
					}
					else
					{
						cout << "111111111" << endl;
					}

					/*memset(sbuff, '\0', sizeof(sbuff));
					sprintf(sbuff, "get-end");
					size = strlen(sbuff);
					send(sockServer, sbuff, size, 0);*/
					fclose(file);
				}

			}
			else {
				strcpy(sbuff, "�޷����ļ�\n");
				if (send(sockServer, sbuff, sizeof(sbuff), 0)) {
					return ;
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
			if (str_.size() > 1)
			{
				cout << str_[str_.size() - 1] << endl;
				string str_name = str_[str_.size() - 1];
				strcpy(fileName, str_name.c_str());
			}
			else
			{
				strcpy(fileName, rbuff + 4);
			}
			//string msg = " ---�յ���ȡ����---";
			//TimeSave("E:\\jh\\Time_Server.txt", msg);


			fd = fopen(fileName, "wb");
			if (fd == NULL)
			{
				cout << "�޷����ļ�" << fileName << endl;
				return ;
			}
			sprintf(sbuff, "put %s", fileName);
			if (!send(sockServer, sbuff, sizeof(sbuff), 0))
			{
				fclose(fd);
				return ;
			}

			memset(sbuff, '\0', sizeof(rbuff));
			cout << "careate file start save" << endl;
			while ((cnt = recv(sockServer, rbuff, sizeof(rbuff), 0)) > 0)
			{
				if (strncmp(rbuff, "put-end", 7) == 0)
				{
					break;
				}
				fwrite(rbuff, sizeof(char), cnt, fd);//��cnt�����ݳ���Ϊchar�����ݴ�rbuff���뵽fdָ����ļ�
				memset(rbuff, '\0', sizeof(rbuff));
				if (cnt < 1024)
				{
					break;
				}
			}
			cout << " file  save finsh" << endl;
			//string msg = " ---�ɹ��յ��ͻ����ϴ��ļ�����---";
			//TimeSave("E:\\Time_Server_Put.txt", msg);
			//cout << "�ɹ�����ļ�" << fileName << endl;
			fclose(fd);
			//msg = " ------------------";
			//TimeSave("E:\\jh\\Time_Server_Put.txt", msg);
			string  timeddd = GetTimeString();
			cout << timeddd << endl;
		}//put
		else if (strncmp(rbuff, "pwd", 3) == 0) {
			char path[1000];
			//strcpy(sbuff, "D:\\AjhwtWork");//���Լ�ѡ��ľ���·��
			GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼			
			strcpy(sbuff, path);
			int size = strlen(sbuff);
			send(sockServer, sbuff, size, 0);
		}//pwd
		else if (strncmp(rbuff, "ls", 2) == 0) {
			strcpy(sbuff, rbuff);
			int size = strlen(sbuff);
			send(sockServer, sbuff, size, 0);
			sendFileList(sockServer);

			memset(sbuff, '\0', sizeof(sbuff));
			sprintf(sbuff, "ls-end");
			size = strlen(sbuff);
			send(sockServer, sbuff, size, 0);
		}//ls
		else if (strncmp(rbuff, "cd", 2) == 0) {
			strcpy(fileName, rbuff + 3);
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);
			SetCurrentDirectory(fileName);//���õ�ǰĿ¼ 
		}//cd
		else if (strncmp(rbuff, "mkdir", 5) == 0)
		{
			strcpy(fileName, rbuff + 6);
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//���ͻ���Ϣ
			mkdir(fileName);
		}//mkdir
		else if (strncmp(rbuff, "del", 3) == 0) { // ɾ�����ļ���;
			strcpy(fileName, rbuff + 4);//���Ҫɾ���ļ���
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//���ͻ���Ϣ
			delFile(fileName);
		}//del
		else if (strncmp(rbuff, "Fdel", 4) == 0) {//ɾ��ĳ���ļ�
			strcpy(fileName, rbuff + 5);//���Ҫɾ���ļ���
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//���ͻ���Ϣ
			delFile1(fileName);
		}//Fdel
		else if (strncmp(rbuff, "fldel", 5) == 0) {//ɾ��ĳ���ļ����������ļ�
			char path[1000];
			strcpy(path, rbuff + 6);//���Ҫɾ���ļ���
			strcpy(sbuff, rbuff);
			send(sockServer, sbuff, sizeof(sbuff), 0);//���ͻ���Ϣ

			//GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼
			//strcat(path, "\\");
			//strcat(path, fileName);
			cout << path << endl;
			string str = path;
			delete_listFiles(path); // ɾ���ļ����µ��ļ�;

			char* lastBackslash = strrchr(path, '\\');
			if (lastBackslash != nullptr)
			{
				// ��ȡ�ļ�������
				size_t fileNameLength = strlen(lastBackslash + 1);

				// �����µ�char�������洢�ļ���
				char* dirName = new char[fileNameLength + 1];
				strcpy(dirName, lastBackslash + 1);

				// �����µ�char�������洢·��
				char* directory = new char[lastBackslash - path + 1];
				strncpy(directory, path, lastBackslash - path);
				directory[lastBackslash - path] = '\0';

				std::cout << "�ļ���: " << dirName << std::endl;
				std::cout << "·��: " << directory << std::endl;


				SetCurrentDirectory(directory);

				bool flag = RemoveDirectory(path); // ɾ���ļ��б���;
				if (!flag)
				{
					cout << "ɾ�����ļ��У�" << fileName << "ʧ��" << endl;

				}

				// �ͷŶ�̬������ڴ�
				delete[] dirName;
				delete[] directory;

			}
		}//Fdel
		else if (strncmp(rbuff, "user", 4) == 0) {
			char tbuff[1024];
			strcpy(tbuff, rbuff + 5);
			strcat(tbuff, " ");
			memset(rbuff, '\0', sizeof(rbuff));
			strcpy(sbuff, "�ɹ���ȡ�û���\0");
			send(sockServer, sbuff, sizeof(sbuff), 0);

			recv(sockServer, rbuff, sizeof(rbuff), 0);
			cout << endl << "��ȡ��ִ�е����" << rbuff << endl;
			strcat(tbuff, rbuff + 5);
			if (strcmp(tbuff, namePassword) == 0) {//��֤�Ƿ���ȷ���������ݸ��ͻ���
				send(sockServer, "right\0", sizeof(sbuff), 0);
			}
			else {
				send(sockServer, "wrong\0", sizeof(sbuff), 0);
			}
		}//user pass
		//closesocket(sockServer);
	}
	//welcome();

	//while (true) {
	//	if (recv(server, buf, maxSize, 0) == 0) {
	//		std::cout << "recv() Faied!\n";
	//	}

	//	std::string paramter;
	//	int cmd = commandParse(buf, paramter);

	//	switch (cmd) {
	//	case 0:
	//		std::cout << "Command is invalid\n";
	//		break;

	//	case 1:
	//		std::cout << "Start receive the file from client.\n";
	//		receiveFile(paramter);
	//		break;

	//	case 2:
	//		std::cout << "Start send file to client.\n";
	//		sendFile(paramter);
	//		break;

	//	default:
	//		std::cout << "Command is invalid\n";
	//	}
	//}
}

int Server::commandParse(char* instruck, std::string &paramter)
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
	recv(sockServer, buf, 1024, 0);
	int fileSize = atoi(buf);
	std::cout << "File's size is:" << fileSize << std::endl;

	int len = 1;
	int recvCount = 0;
	//ͳ���ļ�����ʣ�µĴ�С
	int remain = fileSize;
	while (true) {
		memset(buf, 0, maxSize);
		len = recv(sockServer, buf, 1024, 0);
		storeFile.write(buf, 1024);
		if (len == SOCKET_ERROR) {
			std::cout << "Receive occur error\n";
		}

		//���ʣ�µ�С�ڵ���0��˵���ļ�������ϣ��˳�ѭ��
		remain -= 1024;
		if(remain <= 0) {
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
