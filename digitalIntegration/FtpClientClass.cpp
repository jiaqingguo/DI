//#include "stdafx.h"
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
FtpClientClass::FtpClientClass()
{
	checkFlag = false;
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
	strcpy(inputIP, "127.0.0.1");
//	strcpy(inputIP, "192.168.1.23"); /*�����鸳�ַ���*/ 
	//���õ�ַ�ṹ
	serverAddr.sin_family = AF_INET;					//�����ײ���ʹ�õ�����ͨ��Э�����ݽ����ݵģ�AF_INET��ʾʹ�� TCP/IPv4 ��ַ�����ͨ��
	serverAddr.sin_addr.s_addr = inet_addr(inputIP);	//ָ��������IP��ʮ����ת���ɶ�����IPV4��ַ
	serverAddr.sin_port = htons(RECV_PORT);				//���ö˿ںţ�htons���ڽ������ֽ����Ϊ�����ֽ���
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
		cout << "����ʧ��" << endl;
		memset(inputIP, 0, sizeof(inputIP));
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
void FtpClientClass::list(SOCKET sockfd)
{
	vecFileName.clear();
	vecName.clear();
	
	vector<string> eachFile;
	//�г�Զ����ǰĿ¼
	int nRead;
	memset(sbuff, '\0', sizeof(sbuff));
	char recvBuf[1024];
	char time[300];
	while (1) 
	{
		memset(rbuff, 0, sizeof(rbuff));
		memset(recvBuf, 0, sizeof(recvBuf));
		nRead = recv(sockClient, recvBuf, sizeof(m_FileInformation), 0);
		cout << "sizeof(rbuff):" << sizeof(rbuff) << endl;
		memcpy(&m_FileInformation, recvBuf, sizeof(m_FileInformation));

		//recvͨ��sockClient�׽ӿڽ������ݴ���rbuff�����������ؽ��յ����ֽ���
		if (nRead == SOCKET_ERROR) {
			cout << "��ȡʱ��������" << endl;
			exit(1);
		}


		if (nRead == 0) 
		{ //���ݶ�ȡ����
			break;
		}
		//��ʾ����
		rbuff[nRead] = '\0';
		cout << "list=====m_FileInformation.fileName: " << m_FileInformation.fileName << endl;
		string name(m_FileInformation.fileName);
		string fileDir(m_FileInformation.fileDir);
		sprintf(time, "%04d-%02d-%02d %02d:%02d",m_FileInformation.fileYear,m_FileInformation.fileMonth,m_FileInformation.fileDay,
			m_FileInformation.fileHour,m_FileInformation.fileMinute);
		string str_time(time);
		if(name == "." || name == "..")
		{
			cout << "��Ҫ.��.."<< endl;
		}else
		{
			if(fileDir == "<DIR>")
			{
				vecName.push_back(name);
			}else
			{
				eachFile.clear();
				eachFile.push_back(name);
				eachFile.push_back(str_time);
				vecFileName.push_back(eachFile);
			}
			

		}
	
		//cout << "rbuff " << recvBuf << "----------------"<< endl;
	}

}
//����Ҫִ�е������������
DWORD FtpClientClass::sendTCP(char data[])
{
	//����Ҫִ�е������������
	int length = send(sockClient, data, strlen(data), 0);
	if (length <= 0) {
		cout << "���������������ʧ��" << endl;
		closesocket(sockClient);//����ʹ��socket()�������׽���ʱ��Ӧ�õ���closesocket()���������رգ�����ͬ����fclose()�����ر�һ���ļ������������׽�����Դ���ͷš�
		WSACleanup();
		return -1;
	}
	return 1;
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
	sendTCP(buff);									//����ָ��
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
	sendTCP(buff);									//����ָ��
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
	while (1) { //���ļ���ѭ����ȡ���ݲ�����
		int len = fread(sbuff, 1, sizeof(sbuff), file); //fread��file�ļ���ȡsizeof(sbuff)���ȵ����ݵ�sbuff�����سɹ���ȡ�����ݸ���
		if (send(datatcps, sbuff, len, 0) == SOCKET_ERROR) {
			cout << "��ͻ��˵������ж�" << endl;
			closesocket(datatcps);
			return 0;
		}
		if (len < sizeof(sbuff)) {
			break;
		}
	}
	closesocket(datatcps);
	cout << "�������" << endl;
	return true;
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
//��ȡ��ǰ�ļ�����
void FtpClientClass::execute_ls()
{
	
	char operation[10], name[20];		//�������ļ���
	char order[30] = "\0";				//���������
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

	strcat(order, "ls");
	sprintf(buff, order);
	sendTCP(buff);									//����ָ��
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	list(sockClient);


	//for (int i = 0; i < vecName.size(); i++)
	//{
	//	cout << "vecName[i]: " << vecName[i] << endl;//��ӡ����������
	//	ret_vec.push_back(vecName[i]);
	//}
	//vecName.push_back();
	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock


}

//��ȡ��ǰ·��
string FtpClientClass::Gets_CurrentPath()
{
	memset(rbuff, 0, sizeof(rbuff));
	string str_path;

	char operation[10], name[20];		//�������ļ���
	char order[30] = "\0";				//���������
	char buff[80];						//�����洢�����ַ�����ʽ����order

	//startSock();				//����winsock����ʼ��
	//if (callServer() == -1) 
	//{	//������������ʧ��
	//	cout << "������������ʧ��!!!";
	//}

	memset(order, 0, sizeof(order));
	memset(buff, 0, sizeof(buff));
	strcat(order, "pwd");
	sprintf(buff, order);
	sendTCP(buff);									//����ָ��
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
	str_path = rbuff;

	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock

	return str_path;

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
	sendTCP(buff);									//����ָ��
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
			// cout<<"������"<<rbuff<<endl<<"����"<<cnt<<endl;
			fwrite(rbuff, sizeof(char), cnt, fd1);    //C �⺯�� size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) �� ptr ��ָ��������е�����д�뵽������ stream �С�
		}
		//string msg = " ---�յ��ļ���---";
		//TimeSave("E:\\jh\\Time_Client.txt", msg);

		//closesocket(sockClient);
		fclose(fd1);


	}//get


	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock
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
	sendTCP(buff);									//����ָ��
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;							//pwd�����������Ѿ�ʵ��
	if (strncmp(rbuff, "put", 3) == 0) 
	{ ///�ϴ�����
		strcpy(fileName, rbuff + 4);
		fd2 = fopen(fileName, "rb");				//��һ���������ļ����ļ�������ڣ�ֻ������
		if (fd2) { //�ɹ���
			if (!sendFile(sockClient, fd2)) {
				cout << "����ʧ��" << endl;
				
			}
			else
			{

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

	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock

}
//ִ�� �����ļ�������
void FtpClientClass::execute_cdFloder(string floderName)
{
	char operation[1024], name[1024];		//�������ļ���
	char order[1024] = "\0";				//���������
	char buff[1024];						//�����洢�����ַ�����ʽ����order
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

	string str_name = floderName;
	strcpy(name,str_name.c_str());


	//memset(order1, 0, sizeof(order));
	//memset(buff, 0, sizeof(buff));
	strcat(order, "cd"), strcat(order, " "), strcat(order, name);
	sprintf(buff, order);
	sendTCP(buff);	
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock
}
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
	sendTCP(buff);	
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock
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
	sendTCP(buff);	
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock

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
	sendTCP(buff);	
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock

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
	sendTCP(buff);	
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock

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
	sendTCP(buff);	
	recv(sockClient, rbuff, sizeof(rbuff), 0);		//������Ϣ 
	cout << rbuff << endl;	//pwd��
	closesocket(sockClient);	//�ر�����
	WSACleanup();				//�ͷ�Winsock

}
//��ȡ�ļ�������
vector<string> FtpClientClass::Gets_FolderName()
{
	return vecName;
}
//��ȡ�ļ�����
vector<vector<string>> FtpClientClass::Gets_FileName()
{
	return vecFileName;
}