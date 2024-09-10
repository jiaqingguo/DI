//#include "stdafx.h"
#include <fstream>

#include "FtpClientClass.h"
#include "Util/UtilTool.h"

#define RECV_PORT 4312	//���ն˿�
#define SEND_PORT 4302	//���Ͷ˿�
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
//����winsock����ʼ��
DWORD FtpClientClass::startSock()
{
	//����winsock����ʼ��
	WSADATA WSAData;
	char a[20];
	memset(a, 0, sizeof(a));
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) { //����winsock�汾
		cout << "sock��ʼ��ʧ��" << endl;
		return -1;
	}
	//if (strncmp(inputIP, a, sizeof(a)) == 0) {
	//	cout << "������Ҫ���ӵķ�����IP��";
	//	cin >> inputIP;
	//}ls
	//strcpy(inputIP, "127.0.0.1");
	//strcpy(inputIP, "192.168.0.158");
//	strcpy(inputIP, "192.168.1.23"); /*�����鸳�ַ���*/ 
	//���õ�ַ�ṹ
	serverAddr.sin_family = AF_INET;					//�����ײ���ʹ�õ�����ͨ��Э�����ݽ����ݵģ�AF_INET��ʾʹ�� TCP/IPv4 ��ַ�����ͨ��
	serverAddr.sin_addr.s_addr = inet_addr(inputIP);	//ָ��������IP��ʮ����ת���ɶ�����IPV4��ַ
	serverAddr.sin_port = htons(m_serverPort);				//���ö˿ںţ�htons���ڽ������ֽ����Ϊ�����ֽ���
	return 1;
}
//����socket
DWORD FtpClientClass::createSocket()
{
	//����socket
	//Ҫʹ���׽��֣����ȱ������socket()��������һ���׽���������������ͬ�����ļ�ʱ�����ȵõ���fopen()������һ���ļ���
	sockClient = socket(AF_INET, SOCK_STREAM, 0);//��scoket�����ɹ�����ʱ����һ���µ�SOCKET(Socket Descriptor) //SOCK_STREAM����ʽ�׽��֣�:Tcp���ӣ��ṩ���л��ġ��ɿ��ġ�˫�����ӵ��ֽ�����֧�ִ������ݴ���
	if (sockClient == SOCKET_ERROR) {
		cout << "����socketʧ��" << endl;
		WSACleanup();//��ֹWs2_32.dll ��ʹ��
		return -1;
	}
	return 1;
}
//������������
DWORD FtpClientClass::callServer()
{
	//������������
	createSocket();
	if (connect(sockClient, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {//connect()������ָ���ⲿ�˿ڵ�����
		//cout << "����ʧ��" << endl;
		//memset(inputIP, 0, sizeof(inputIP));
		int errorCode = WSAGetLastError();
		cout << "����ʧ�ܣ��������: " << WSAGetLastError() << endl;
		return -1;
	}
	return 1;
}
//�����ļ���
DWORD FtpClientClass::mkdir(char fileName[])
{
	//wstring kj;

	//UtilTool::setWstring(kj,StoreOptions[i].c_str());
	//COptionUI * optical_fiber1 = static_cast<COptionUI*>(m_pm.FindControl(kj.c_str()));

	//char path[1000];
	//LPCWSTR path;
	//GetCurrentDirectory(sizeof(path), path);//�ҵ���ǰ���̵ĵ�ǰĿ¼

	//strcat(path, "\\");
	//strcat(path, fileName);
	//cout << path << endl;
	//bool flag = CreateDirectory(path, NULL);
	//if (flag)
	//{
	//	cout << "�����ļ���" << fileName << "�ɹ�" << endl;
	//	return 1;
	//}
	//else
	//{
	//	cout << "�����ļ���" << fileName << "ʧ��" << endl;
	//	return 0;
	//}
	return 1;
}
//�˵�
void FtpClientClass::help()
{
	//�����˵�
	cout << "        _______________________________________________  " << endl
		<< "       |                FTP�����˵�                     |   " << endl
		<< "       | 1��get �����ļ� [�����ʽ: get �ļ��� ]        |   " << endl
		<< "       | 2��put �ϴ��ļ� [�����ʽ��put �ļ���]         |   " << endl
		<< "       | 3��pwd ��ʾ��ǰ�ļ��еľ���·��                |   " << endl
		<< "       | 4��ls  ��ʾԶ����ǰĿ¼���ļ�                  |   " << endl
		<< "       | 5��cd  �ı�Զ����ǰĿ¼��·��                  |   " << endl
		<< "       |         �����¼�Ŀ¼: cd ·����                |   " << endl
		<< "       |         �����ϼ�Ŀ¼: cd ..                    |   " << endl
		<< "       | 6��mkdir �½��ļ��� [�����ʽ��mkdir �ļ���]   |   " << endl
		<< "       | 7��del ɾ���ļ��� [�����ʽ��del �ļ���]       |   " << endl
		<< "       | 8��? ���� help ��������˵�                    |   " << endl
		<< "       | 9��quit �˳�FTP                                |   " << endl
		<< "       |________________________________________________|    " << endl;
}
//�г�Զ����ǰĿ¼
int FtpClientClass::list(SOCKET sockfd)
{
	vecFileName.clear();
	vecDirName.clear();
	vector<string> eachDirData;
	vector<string> eachFile;
	//�г�Զ����ǰĿ¼
	int iCurRecvSize;
	memset(sbuff, '\0', sizeof(sbuff));
	char recvBuf[1024];
	char time[300];
	while (1) 
	{
		// �������ݴ�С��int ���ͣ�
		int iAllDataSize = 0;
		size_t bytes_received = recv(sockClient, reinterpret_cast<char*>(&iAllDataSize), sizeof(iAllDataSize), 0);
		if (bytes_received <= 0 || iAllDataSize == 0) {
			break; // �������ʧ�ܻ����ݴ�СΪ 0�����˳�ѭ��
		}
		int recv_size = iAllDataSize;
		char combinedBuf[sizeof(m_FileInformation)]; // ���������������
		int combinedBufstart = 0;
		while (1)
		{
			//memset(rbuff, 0, sizeof(rbuff));
			memset(recvBuf, 0, sizeof(recvBuf));
			//iRecvSize = recv(sockClient, recvBuf, sizeof(m_FileInformation), 0);
			iCurRecvSize = recv(sockClient, recvBuf, recv_size, 0);
			if (iCurRecvSize == SOCKET_ERROR) {
				cout << "��ȡʱ��������" << endl;
				return -2;
				//exit(1);
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
				memcpy(combinedBuf, recvBuf, iCurRecvSize);
				break;
			}

		}
		memcpy(&m_FileInformation, combinedBuf, sizeof(m_FileInformation));
		//��ʾ����
		//rbuff[iCurRecvSize] = '\0';
		cout << "list=====m_FileInformation.fileName: " << m_FileInformation.fileName << endl;
		string name(m_FileInformation.fileName);
		string fileDir(m_FileInformation.fileDir);
		sprintf(time, "%04d-%02d-%02d %02d:%02d", m_FileInformation.fileYear, m_FileInformation.fileMonth, m_FileInformation.fileDay,
			m_FileInformation.fileHour, m_FileInformation.fileMinute);
		string str_time(time);
		if (name == "." || name == "..")
		{
			cout << "��Ҫ.��.." << endl;
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
			}
			else
			{
				eachFile.clear();
				eachFile.push_back(name);
				eachFile.push_back(str_time);
				vecFileName.push_back(eachFile);
			}


		}
	
		//cout << "rbuff " << recvBuf << "----------------"<< endl;
	}
	return 1;
}
//����Ҫִ�е������������
DWORD FtpClientClass::sendTCP(char data[])
{
	//����Ҫִ�е������������
	int length = send(sockClient, data, strlen(data), 0);
	if (length <= 0) 
	{
		cout << "���������������ʧ��" << endl;
		closesocket(sockClient);//����ʹ��socket()�������׽���ʱ��Ӧ�õ���closesocket()���������رգ�����ͬ����fclose()�����ر�һ���ļ������������׽�����Դ���ͷš�
		WSACleanup();
		return -1;
	}
	return 1;
}

DWORD FtpClientClass::sendTCP(char data[],int sendSize)
{
	//����Ҫִ�е������������
	int length = send(sockClient, data, sendSize, 0);
	if (length <= 0) {
		cout << "���������������ʧ��" << endl;
		closesocket(sockClient);//����ʹ��socket()�������׽���ʱ��Ӧ�õ���closesocket()���������رգ�����ͬ����fclose()�����ر�һ���ļ������������׽�����Դ���ͷš�
		WSACleanup();
		return -1;
	}
	return 1;
}
bool FtpClientClass::sendTcpOneAll()
{

	//int data_size=��
	int dataSize = strlen(m_sendOneAllData);
	send(sockClient, reinterpret_cast<const char*>(&dataSize), sizeof(dataSize), 0);
	int length = send(sockClient, m_sendOneAllData, dataSize, 0);
	if (length <= 0) {
		cout << "���������������ʧ��" << endl;
		closesocket(sockClient);//����ʹ��socket()�������׽���ʱ��Ӧ�õ���closesocket()���������رգ�����ͬ����fclose()�����ر�һ���ļ������������׽�����Դ���ͷš�
		WSACleanup();
		return false;
	}

	return true;
}
bool FtpClientClass::recvTcpOneAll()
{
	memset(m_recvOneAllData, 0, sizeof(m_recvOneAllData));
	// �������ݴ�С��int ���ͣ�
	int iAllDataSize = 0;
	size_t bytes_received = recv(sockClient, reinterpret_cast<char*>(&iAllDataSize), sizeof(iAllDataSize), 0);
	if (bytes_received <= 0 ) {
		return false; // �������ʧ�ܣ����˳�
	}
	int recv_size = iAllDataSize;
	char combinedBuf[sizeof(m_recvOneAllData)];// ���������������
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
			cout << "��ȡʱ��������" << endl;
			return false;
			//exit(1);
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
	
	return true;
}
//�ϴ��û���
int FtpClientClass::user()
{
	char operation[10], name[20];		//�������ļ���
	char order[30] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order
	cout << "�������û���ָ�user �û�������";
	cin >> operation;
	cin >> name;
	strcat(order, operation), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);									//����ָ��
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return 0;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;
	return 1;

}
//�ϴ�����
int FtpClientClass::pass()
{
	char operation[10], name[20];		//�������ļ���
	char order[30] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order
	cout << "����������ָ�pass ���룩��";
	cin >> operation;
	cin >> name;
	strcat(order, operation), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);									//����ָ��
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return 0;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;
	if (strcmp(rbuff, "wrong") == 0) {
		return 0;
	}
	return 1;

}
//put ���͸�Զ��һ���ļ�
int FtpClientClass::sendFile(SOCKET datatcps, FILE* file)
{
	//put ���͸�Զ��һ���ļ�
	cout << "���ڴ����ļ���" << endl;
	memset(sbuff, '\0', sizeof(sbuff));
	while (1) 
	{ //���ļ���ѭ����ȡ���ݲ�����
		int len = fread(sbuff, 1, sizeof(sbuff), file); //fread��file�ļ���ȡsizeof(sbuff)���ȵ����ݵ�sbuff�����سɹ���ȡ�����ݸ���
		if (send(datatcps, sbuff, len, 0) == SOCKET_ERROR) 
		{
			cout << "��ͻ��˵������ж�" << endl;
		//	closesocket(datatcps);
			return 0;
		}
		
		if (len == 0)
		{
			sprintf(sbuff, "put-end", sbuff);
			//sendTCP(sbuff);									//����ָ��
			if (sendTCP(sbuff) == -1)									//����ָ��
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
	cout << "�������" << endl;
	return true;
}
int FtpClientClass::sendFileData(SOCKET datatcps, std::ifstream& file)
{
	// �����ļ�����
	char buffer[10240]; // һ����෢�� 10240 �ֽ�

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

		// �������ݴ�С��int ���ͣ���ʵ������
		send(datatcps, reinterpret_cast<const char*>(&data_size), sizeof(data_size), 0);
		send(datatcps, buffer, data_size, 0);

	}
	// ���ͽ����ź�
	int end_signal = 0; // 0 ��Ϊ�����ź�
	send(datatcps, reinterpret_cast<const char*>(&end_signal), sizeof(end_signal), 0);
	return 1;
}
bool FtpClientClass::newConnection()
{
	////����winsock����ʼ��
	if(startSock() == -1)
	{
		return false;
	}
			
	if (callServer() == -1) 
	{	//������������ʧ��
		cout << "������������ʧ��!!!";
		return false;
	}
	return true;
}
////��ȡ��ǰ�ļ�����
//void FtpClientClass::execute_ls()
//{
//	
//	char operation[10], name[20];		//�������ļ���
//	char order[30] = "\0";				//���������
//	char buff[80];						//�����洢�����ַ�����ʽ����order
//
//	//startSock();				//����winsock����ʼ��
//	//if (callServer() == -1) 
//	//{	//������������ʧ��
//	//	cout << "������������ʧ��!!!";
//	//}
//	memset(buff, 0, sizeof(buff));
//	memset(rbuff, 0, sizeof(rbuff));
//	memset(sbuff, 0, sizeof(sbuff));
//	memset(order, 0, sizeof(order));
//
//	strcat(order, "ls");
//	sprintf(buff, order);
//	sendTCP(buff);									//����ָ��
//	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
//	cout << rbuff << endl;	//pwd��
//	list(sockClient);
//
//	//for (int i = 0; i < vecName.size(); i++)
//	//{
//	//	cout << "vecName[i]: " << vecName[i] << endl;//��ӡ����������
//	//	ret_vec.push_back(vecName[i]);
//	//}
//	//vecName.push_back();
//	//closesocket(sockClient);	//�ر�����
//	//WSACleanup();				//�ͷ�Winsock
//}

int FtpClientClass::execute_ls(const std::string strDirPath)
{
	char operation[10], name[20];		//�������ļ���
	char order[260] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order

	//startSock();				//����winsock����ʼ��
	//if (callServer() == -1) 
	//{	//������������ʧ��
	//	cout << "������������ʧ��!!!";
	//}
	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));
	memset(order, 0, sizeof(order));

	//strcat(order, "ls");
	sprintf(order, "ls %s", strDirPath.c_str());
	sprintf(buff, order);
	//sendTCP(buff);									//����ָ��
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return 0;
	}
	//int size =recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ
	//cout << rbuff << endl;	
	//if(ls - falied)
	
	return list(sockClient);
}

////��ȡ��ǰ·��
//string FtpClientClass::Gets_CurrentPath()
//{
//	memset(rbuff, 0, sizeof(rbuff));
//	string str_path;
//
//	char operation[10], name[20];		//�������ļ���
//	char order[30] = "\0";				//���������
//	char buff[80];						//�����洢�����ַ�����ʽ����order
//
//	//startSock();				//����winsock����ʼ��
//	//if (callServer() == -1) 
//	//{	//������������ʧ��
//	//	cout << "������������ʧ��!!!";
//	//}
//
//	memset(order, 0, sizeof(order));
//	memset(buff, 0, sizeof(buff));
//	strcat(order, "pwd");
//	sprintf(buff, order);
//	//sendTCP(buff);									//����ָ��
//	if (sendTCP(buff) == -1)									//����ָ��
//	{
//		return "";
//	}
//	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
//	cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
//	str_path = rbuff;
//
////	closesocket(sockClient);	//�ر�����
//	//WSACleanup();				//�ͷ�Winsock
//	return str_path;
//}

bool FtpClientClass::Gets_CurrentPath(std::string& strRootPath)
{
	memset(rbuff, 0, sizeof(rbuff));
	string str_path;

	char operation[10], name[20];		//�������ļ���
	char order[30] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order

	memset(order, 0, sizeof(order));
	memset(buff, 0, sizeof(buff));
	strcat(order, "pwd");
	sprintf(buff, order);

	//if (sendTCP(buff) == -1)									//����ָ��
	//{
	//	return false;
	//}
	//recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	//cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
	//strRootPath = rbuff;

	//return true;

	if (sendTCP(buff) == -1)									//����ָ��
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
//�����ļ�
void FtpClientClass::execute_getFile(string rec_name)
{
	char operation[10], name[1024];		//�������ļ���
	char order[1024] = "\0";				//���������
	char buff[1024];						//�����洢�����ַ�����ʽ����order
	FILE *fd1, *fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
	int cnt;

	//startSock();				//����winsock����ʼ��
	//if (callServer() == -1) 
	//{	//������������ʧ��
	//	cout << "��������ʧ��!!!" << endl;
	//}

	//������������ɹ�����ʼ������

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	string str_name = rec_name;
	strcpy(name,str_name.c_str());
	//��ָ�����Ͻ�order������Ž�buff
	strcat(order, "get"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);									//����ָ��
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
	if (strncmp(rbuff, "get", 3) == 0) 
	{			///���ع���
		//callServer();
		fd1 = fopen(name, "wb");                    //�ö����Ƶķ�ʽ���ļ���wb��ʾ�򿪻��½�һ���������ļ���ֻ����д���ݣ�
		if (fd1 == NULL)
		{
			cout << "�򿪻����½� " << name << "�ļ�ʧ��" << endl;
			//return 1;
		}
		memset(rbuff, '\0', sizeof(rbuff));
		while ((cnt = recv(sockClient, rbuff, sizeof(rbuff), 0)) > 0) {
			fwrite(rbuff, 1, cnt, fd1);    //C �⺯�� size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) �� ptr ��ָ��������е�����д�뵽������ stream �С�
			memset(rbuff, '\0', sizeof(rbuff));
			if (cnt < 1024)
			{
				break;
			} //C �⺯�� size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) �� ptr ��ָ��������е�����д�뵽������ stream �С�
		}
		//string msg = " ---�յ��ļ���---";
		//TimeSave("E:\\jh\\Time_Client.txt", msg);

		//closesocket(sockClient);
		fclose(fd1);


	}//get


//	closesocket(sockClient);	//�ر�����
//	WSACleanup();				//�ͷ�Winsock
}
//int FtpClientClass::execute_getFile(string filePath, string NewFilePath)
//{
//	char operation[10], name[1024];		//�������ļ���
//	char order[1024] = "\0";				//���������
//	char buff[1024];						//�����洢�����ַ�����ʽ����order
//	FILE* fd1, * fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
//	int cnt;
//
//	char buff_test[100];
//
//
//	//������������ɹ�����ʼ������
//
//	memset(buff, 0, sizeof(buff));
//	memset(rbuff, 0, sizeof(rbuff));
//	memset(sbuff, 0, sizeof(sbuff));
//
//	string str_name = filePath;
//	strcpy(name, filePath.c_str());
//	//��ָ�����Ͻ�order������Ž�buff
//	strcat(order, "get"), strcat(order, " "), strcat(order, name);
//	sprintf(buff, order);
//	if (sendTCP(buff) == -1)									//����ָ��
//	{
//		return 0;
//	}
//	while (1)
//	{
//		int num=recv(sockClient, rbuff, 1024, 0);		//������Ϣ 
//		cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
//		if (strncmp(rbuff, "openFailed", 10) == 0)
//		{
//			return 1;
//		}
//		if (strncmp(rbuff, "get", 3) == 0)
//		{			///���ع���
//			
//			fd1 = fopen(NewFilePath.c_str(), "wb");                    //�ö����Ƶķ�ʽ���ļ���wb��ʾ�򿪻��½�һ���������ļ���ֻ����д���ݣ�
//			if (fd1 == NULL)
//			{
//				cout << "�򿪻����½� " << NewFilePath << "�ļ�ʧ��" << endl;
//				//return 1;
//			}
//			memset(rbuff, 0, sizeof(rbuff));
//			int size = 0;
//			while ((cnt = recv(sockClient, rbuff, 1024, 0)) > 0) 
//			{
//
//				if (strncmp(rbuff , "get-end", 7) == 0)
//				{
//					break;
//				}
//				if (strncmp(rbuff + cnt - 7, "get-end", 7) == 0)
//				{
//					// ?????????????????   ���ܻ����˷��͵����һ���޷������ļ���get-end;
//					memset(rbuff + cnt, 0, sizeof(rbuff) - cnt);
//					fwrite(rbuff, 1, cnt, fd1);
//					break;
//				}
//				fwrite(rbuff, 1, cnt, fd1);
//				memset(rbuff, 0, sizeof(rbuff));
//				
//			}
//			
//			fclose(fd1);
//
//			return 0;
//		}//get
//	}
//	
//	return 0;
//}

int FtpClientClass::execute_getFile(string filePath, string NewFilePath)
{

	char buff[1024];						//�����洢�����ַ�����ʽ����order
	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//string str_name = filePath;
	
	//��ָ�����Ͻ�order������Ž�buff
	strcat(buff, "get"), strcat(buff, " "), strcat(buff, filePath.c_str());
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return 0;
	}
	while (1)
	{
		int num = recv(sockClient, rbuff, 1024, 0);		//������Ϣ 
//		cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
		if (strncmp(rbuff, "openFailed", 10) == 0)
		{
			return -1;
		}
		if (strncmp(rbuff, "get", 3) == 0)
		{
			std::ofstream file(NewFilePath, std::ios::binary);
			char buffer[10240]; // ���ջ�����

			while (true)
			{
				// �������ݴ�С��int ���ͣ�
				int data_size;

				size_t bytes_received = recv(sockClient, reinterpret_cast<char*>(&data_size), sizeof(data_size), 0);

				if (bytes_received <= 0 || data_size == 0) {
					break; // �������ʧ�ܻ����ݴ�СΪ 0�����˳�ѭ��
				}

				int recv_size = data_size;
				while (1)
				{
					// ����ʵ������
					memset(buffer, 0, sizeof(buffer));
					bytes_received = recv(sockClient, buffer, recv_size, 0);

					// �����յ�������д���ļ�
					file.write(buffer, bytes_received);
					
					if (bytes_received < data_size)
					{
						recv_size = data_size - bytes_received;

					}
					else
					{
						break; // �������ȫ����ɣ��˳�ѭ��;
					}
				}



			}

			file.close();
			std::cout << "�ļ�������ϣ����ӹرա�" << std::endl;
			return 1;
		}
	}
	
	
}
//ִ�� put �ϴ�
void FtpClientClass::execute_putFile(string sendfileName)
{
	char operation[10], name[1024];		//�������ļ���
	char order[1024] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order
	FILE *fd1, *fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));


	string str_name = sendfileName;
	strcpy(name,str_name.c_str());
	//��ָ�����Ͻ�order������Ž�buff
	strcat(order, "put"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);									//����ָ��
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
	if (strncmp(rbuff, "put", 3) == 0) 
	{ ///�ϴ�����
		strcpy(fileName, rbuff + 4);
		fd2 = fopen(fileName, "rb");				//��һ���������ļ����ļ�������ڣ�ֻ�����
		if (fd2)
		{ //�ɹ���
			if (!sendFile(sockClient, fd2)) 
			{
				cout << "����ʧ��" << endl;
				
			}
		
			fclose(fd2);
		}
		else {
			strcpy(sbuff, "�޷����ļ�\n");
			if (send(sockClient, sbuff, sizeof(sbuff), 0)) {
				
			}
		}
	}//put
	cout << "�ϴ��ɹ�!!!" << endl;

//	closesocket(sockClient);	//�ر�����
	//WSACleanup();				//�ͷ�Winsock

}
//void FtpClientClass::execute_putFile(string localFilePath, std::string NewFilePath)
//{
//	char operation[10], name[1024];		//�������ļ���
//	char order[1024] = "\0";				//���������
//	char buff[80];						//�����洢�����ַ�����ʽ����order
//	FILE* fd1, * fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
//	int cnt;
//
//	memset(buff, 0, sizeof(buff));
//	memset(rbuff, 0, sizeof(rbuff));
//	memset(sbuff, 0, sizeof(sbuff));
//
//
//	string str_name = localFilePath;
//	strcpy(name, str_name.c_str());
//	//��ָ�����Ͻ�order������Ž�buff
//	strcat(order, "put"), strcat(order, " "), strcat(order, NewFilePath.c_str());
//	sprintf(buff, order);
//	//sendTCP(buff);									//����ָ��
//	if (sendTCP(buff) == -1)									//����ָ��
//	{
//		return;
//	}
//	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
//	cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
//	if (strncmp(rbuff, "put", 3) == 0)
//	{ ///�ϴ�����
//		strcpy(fileName, rbuff + 4);
//		fd2 = fopen(localFilePath.c_str(), "rb");				//��һ���������ļ����ļ�������ڣ�ֻ�����
//		if (fd2)
//		{ //�ɹ���
//			if (!sendFile(sockClient, fd2))
//			{
//				cout << "����ʧ��" << endl;
//
//			}
//
//			fclose(fd2);
//		}
//		else {
//			strcpy(sbuff, "�޷����ļ�\n");
//			if (send(sockClient, sbuff, sizeof(sbuff), 0)) {
//
//			}
//		}
//	}//put
//	cout << "�ϴ��ɹ�!!!" << endl;
//}

void FtpClientClass::execute_putFile(string localFilePath, std::string NewFilePath)
{
	char buff[1024];						//�����洢�����ַ�����ʽ����order
	int cnt;

	
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));

	//��ָ�����Ͻ�order������Ž�buff
	memset(buff, 0, sizeof(buff));
	strcat(buff, "put"), strcat(buff, " "), strcat(buff, NewFilePath.c_str());
	
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return;
	}
	int size= recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << size <<endl;							//pwd�����������Ѿ�ʵ��
	if (strncmp(rbuff, "put", 3) == 0)
	{ ///�ϴ�����
		//strcpy(fileName, rbuff + 4);
		std::ifstream fileStream(localFilePath, std::ios::binary);
		if (fileStream.is_open())
		{
			if (!sendFileData(sockClient, fileStream))
			{
				cout << "�����ļ�����" << endl;
				return;
			}
			else
			{
				cout << "�����ļ��������" << endl;
			}


			fileStream.close();

		}
		else
		{
			strcpy(sbuff, "�޷����ļ�\n");
			if (send(sockClient, sbuff, sizeof(sbuff), 0)) 
			{

			}
			//	std::cerr << "�޷����ļ�: " << file_path << std::endl;

		}
		
	}//put
	cout << "�ϴ��ɹ�!!!" << endl;
}

//ִ�� �����ļ�������
//void FtpClientClass::execute_cdFloder(string floderName)
//{
//	char operation[1024], name[1024];		//�������ļ���
//	char order[1024] = "\0";				//���������
//	char buff[1024];						//�����洢�����ַ�����ʽ����order
//	FILE *fd1, *fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
//	int cnt;
//
//	memset(buff, 0, sizeof(buff));
//	memset(rbuff, 0, sizeof(rbuff));
//	memset(sbuff, 0, sizeof(sbuff));
//	
//	//startSock();				//����winsock����ʼ��
//	//if (callServer() == -1) 
//	//{	//������������ʧ��
//	//	cout << "������������ʧ��!!!";
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
//	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
//	cout << rbuff << endl;	//pwd��
//	//closesocket(sockClient);	//�ر�����
//	//WSACleanup();				//�ͷ�Winsock
//}
//������һ��Ŀ¼
void FtpClientClass::execute_cdGoback()
{
	char operation[10], name[1024];		//�������ļ���
	char order[1024] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order
	FILE *fd1, *fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));
	
	//startSock();				//����winsock����ʼ��
	//if (callServer() == -1) 
	//{	//������������ʧ��
	//	cout << "������������ʧ��!!!";
	//}

	string str_name = "..";
	strcpy(name,str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "cd"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);	
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	//closesocket(sockClient);	//�ر�����
	//WSACleanup();				//�ͷ�Winsock
}
;//�½��ļ���
void FtpClientClass::execute_mkdirFolder(string folder)
{
	char operation[10], name[1024];		//�������ļ���
	char order[1024] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order
	FILE *fd1, *fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));
	
	//startSock();				//����winsock����ʼ��
	//if (callServer() == -1) 
	//{	//������������ʧ��
	//	cout << "������������ʧ��!!!";
	//}

	string str_name = folder;
	strcpy(name,str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "mkdir"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);	
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	//closesocket(sockClient);	//�ر�����
	//WSACleanup();				//�ͷ�Winsock

}
//ɾ�����ļ���
void FtpClientClass::execute_delFolder(string folder)
{
	char operation[10], name[1024];		//�������ļ���
	char order[1024] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order
	FILE *fd1, *fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));
	
	//startSock();				//����winsock����ʼ��
	//if (callServer() == -1) 
	//{	//������������ʧ��
	//	cout << "������������ʧ��!!!";
	//}

	string str_name = folder;
	strcpy(name,str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "del"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);	
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	//closesocket(sockClient);	//�ر�����
	//WSACleanup();				//�ͷ�Winsock

}

//ɾ��ĳ���ļ�
void FtpClientClass::execute_Filedelete(string folder)
{
	char operation[10], name[1024];		//�������ļ���
	char order[1024] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order
	FILE *fd1, *fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));
	
	//startSock();				//����winsock����ʼ��
	//if (callServer() == -1) 
	//{	//������������ʧ��
	//	cout << "������������ʧ��!!!";
	//}

	string str_name = folder;
	strcpy(name,str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "Fdel"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
//	sendTCP(buff);	
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	//closesocket(sockClient);	//�ر�����
//	WSACleanup();				//�ͷ�Winsock

}
//ɾ��ĳ���ļ�
void FtpClientClass::execute_deleteFileList(string folder)
{
	char operation[10], name[1024];		//�������ļ���
	char order[1024] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order
	FILE *fd1, *fd2;					//FileЭ����Ҫ���ڷ��ʱ��ؼ�����е��ļ���fdָ��ָ��Ҫ���ʵ�Ŀ���ļ� 
	int cnt;

	memset(buff, 0, sizeof(buff));
	memset(rbuff, 0, sizeof(rbuff));
	memset(sbuff, 0, sizeof(sbuff));
	
	//startSock();				//����winsock����ʼ��
	//if (callServer() == -1) 
	//{	//������������ʧ��
	//	cout << "������������ʧ��!!!";
	//}

	string str_name = folder;
	strcpy(name,str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "fldel"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	//sendTCP(buff);	
	if (sendTCP(buff) == -1)									//����ָ��
	{
		return;
	}
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
//	closesocket(sockClient);	//�ر�����
//	WSACleanup();				//�ͷ�Winsock

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
	if (sendTCP(sbuff) == -1)									//����ָ��
	{
		return false;
	}
	
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	if (strcmp(rbuff, "rename-ok") == 0) {
		return true;
	}
	return false;
}

bool FtpClientClass::execute_compress(const std::vector<std::string> vecPath, const std::string newZip)
{
	
	memset(sbuff, 0, sizeof(sbuff));

	strcat(sbuff, "compress");
	if (sendTCP(sbuff,sizeof(sbuff)) == -1)									//����ָ��
	{
		return false;
	}

	// ѭ������Ҫѹ����·��
	for (const auto& strPath : vecPath)
	{
		memset(sbuff, 0, sizeof(sbuff));
		sprintf(sbuff, strPath.c_str());
		if (sendTCP(sbuff, sizeof(sbuff)) == -1)
		{
			return false;
		}
	}
	// ����·��������־
	memset(sbuff, 0, sizeof(sbuff));
	strcat(sbuff, "compress-zipname ");
	strcat(sbuff, newZip.c_str());
	if (sendTCP(sbuff) == -1)
	{
		return false;
	}

	memset(rbuff, 0, sizeof(rbuff));
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	if (strncmp(rbuff, "compress-ok",11) == 0) {
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

// ��ѹ�ļ�;
bool FtpClientClass::execute_uncompress(const std::vector<std::string> vecPath)
{
	memset(sbuff, 0, sizeof(sbuff));

	strcat(sbuff, "uncompress");
	if (sendTCP(sbuff, sizeof(sbuff)) == -1)									//����ָ��
	{
		return false;
	}

	// ѭ������Ҫѹ����·��
	for (const auto& strPath : vecPath)
	{
		memset(sbuff, 0, sizeof(sbuff));
		sprintf(sbuff, strPath.c_str());
		if (sendTCP(sbuff, sizeof(sbuff)) == -1)
		{
			return false;
		}
	}
	// ����·��������־
	memset(sbuff, 0, sizeof(sbuff));
	strcat(sbuff, "uncompress-paths-end");
	if (sendTCP(sbuff) == -1)
	{
		return false;
	}

	memset(rbuff, 0, sizeof(rbuff));
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	if (strncmp(rbuff, "uncompress-ok", 13) == 0) {
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

// ��ȡ�ļ�������
/*vector<string>*/ 	vector<vector<string>> FtpClientClass::Gets_FolderName()
{
	return vecDirName;
}
// ��ȡ�ļ�����
vector<vector<string>> FtpClientClass::Gets_FileName()
{
	return vecFileName;
}
