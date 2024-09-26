#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

#include "Server.h"

//���̺߳����������Ķ��߳����д˺���
//void server(SOCKET s);
#include <windows.h>
#include <winnetwk.h>

#pragma comment(lib, "Mpr.lib")

void InitResource(const TCHAR* userName, const TCHAR* password, const TCHAR* localDrive, const TCHAR* remotePath) {
	NETRESOURCE net_Resource;

	// ��ʼ��NETRESOURCE�ṹ
	net_Resource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
	net_Resource.dwScope = RESOURCE_CONNECTED;
	net_Resource.dwType = RESOURCETYPE_DISK;
	net_Resource.dwUsage = 0;
	net_Resource.lpComment = NULL;
	net_Resource.lpLocalName = const_cast<TCHAR*>(localDrive); // ӳ�䵽����������
	net_Resource.lpProvider = NULL;
	net_Resource.lpRemoteName = const_cast<TCHAR*>(remotePath); // ������Դ��·��

	DWORD dwFlags = CONNECT_UPDATE_PROFILE;

	// ȡ����������
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);

	// ���������
	DWORD dw = WNetAddConnection2(&net_Resource, password, userName, 0);
	switch (dw) {
	case ERROR_SUCCESS:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_ACCESS_DENIED:
		std::wcout << TEXT("û��Ȩ�޷��ʣ�\n");
		break;
	case ERROR_ALREADY_ASSIGNED:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_INVALID_ADDRESS:
		std::wcout << TEXT("IP��ַ��Ч\n");
		break;
	case ERROR_NO_NETWORK:
		std::wcout << TEXT("���粻�ɴ�!\n");
		break;
	case ERROR_NO_TOKEN:
		std::wcout << TEXT("û����Ч��ƾ�ݣ������û��������롣\n");
		break;
	case ERROR_SESSION_CREDENTIAL_CONFLICT:
		std::wcout << TEXT("ERROR_SESSION_CREDENTIAL_CONFLICT��\n");
		break;
	default:
		std::wcout << TEXT("�������󣬴������: ") << dw << TEXT("\n");
		break;
	}
}
void InitResource(/*const TCHAR* szUserName, const TCHAR* szPasswd*/) {

	TCHAR szPasswd[] = TEXT("Share123");          //������Դ��Ȩ�û�������
	TCHAR szUserName[] = TEXT("share");        //������Դ��Ȩ���û�
	NETRESOURCE net_Resource;

	// ��ʼ��NETRESOURCE�ṹ
	net_Resource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
	net_Resource.dwScope = RESOURCE_CONNECTED;
	net_Resource.dwType = RESOURCETYPE_DISK;
	net_Resource.dwUsage = 0;
	net_Resource.lpComment = NULL; // ������ΪNULL
	TCHAR localName[] = TEXT("Y:");  // ӳ��ɱ��������� Z:
	net_Resource.lpLocalName = localName;
	net_Resource.lpProvider = NULL;
	TCHAR lpRemoteName[] = TEXT("\\\\192.168.0.250\\share");  // ������Դ��·��

	net_Resource.lpRemoteName = lpRemoteName; // ������Դ��·��

	DWORD dwFlags = CONNECT_UPDATE_PROFILE;

	// ȡ����������
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);

	// ���������
	DWORD dw = WNetAddConnection2(&net_Resource, szPasswd, szUserName, 0);
	switch (dw) {
	case ERROR_SUCCESS:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_ACCESS_DENIED:
		printf(TEXT("û��Ȩ�޷��ʣ�\n"));
		break;
	case ERROR_ALREADY_ASSIGNED:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_INVALID_ADDRESS:
		printf(TEXT("IP��ַ��Ч\n"));
		break;
	case ERROR_NO_NETWORK:
		printf(TEXT("���粻�ɴ�!\n"));
		break;
	case ERROR_NO_TOKEN:
		printf(TEXT("û����Ч��ƾ�ݣ������û��������롣\n"));
		break;
	case ERROR_SESSION_CREDENTIAL_CONFLICT:
		printf(TEXT("ERROR_SESSION_CREDENTIAL_CONFLICT��\n"));
		break;
	default:
		printf(TEXT("�������󣬴������: %lu\n"), dw);

		break;
	}
}


void main()
{
	// ʾ�������� InitResource ��������������ӳ��
	TCHAR userName[] = TEXT("share");
	TCHAR password[] = TEXT("Share123");
	TCHAR localDrive[] = TEXT("Y:");  //����������ӳ��
	TCHAR remotePath[] = TEXT("\\\\192.168.1.253\\share");  // ������Դ��·��

	//InitResource(userName, password, localDrive, remotePath);
	//InitResource();
	char chInput[512];

	char fileName_my[120] = "Y:\\FileData";//"D:\\FileData";// "E:\\1008";
	//char fileName_my[120] = "D:\\FileData";//"D:\\FileData";// "E:\\1008";
	SetCurrentDirectory(fileName_my);//���õ�ǰĿ¼ 

	sprintf_s(chInput, "int:%d\n", 500);
	OutputDebugString(chInput);

	//������ص�����
	int iPort = 4312;//������˿�
	WSADATA wsaData;//Winsock ����������
	SOCKET sListen, sAccept;//�׽ӿڹؼ���,�ֱ����ڼ����ͽ�������
	int iLen;
	int iSend;
	char buf[] = "I am a server";
	struct sockaddr_in ser, cli;  // �����ַ
	//������߳�ָ�룬���ڴ����߳�
	std::thread* t;
	//�����̵߳Ĺ������洴���Ķ��߳�ָ�룬�������ʱ�ͷ�ռ�õ��ڴ�
	std::vector<std::thread*> tManage;
	Server* server = NULL;


	std::cout << "----------------------------\n";
	std::cout << "Server waitting\n";
	std::cout << "----------------------------\n";

	//����winSocket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed to load Winsock.\n";
		return;
	}

	//����Socket
	sListen = socket(AF_INET, SOCK_STREAM, 0);
	if (sListen == INVALID_SOCKET) {
		std::cout << "socket() Failed:" << WSAGetLastError() << "\n";
		return;
	}

	//��IP��ַ
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	//bind(sListen, (LPSOCKADDR)&ser, sizeof(ser));
	if (bind(sListen, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR) {
		std::cout << "bind() Failed\n";
		return;
	}

	//����
	if (listen(sListen, 5) == SOCKET_ERROR) {
		std::cout << "bind() Failed: " << WSAGetLastError() << "\n";
		return;
	}

	iLen = sizeof(cli);//��ȡ�ͻ��������ַ�ĳ���

	
	//�������Ӻͷ��ͻ�ӭ��Ϣ
	//��ѭ��ʹ����һֱ����
	while (true) {
		//��������
		sAccept = accept(sListen, (struct sockaddr*)&cli, &iLen);
		if (sAccept == INVALID_SOCKET) {
			std::cout << "accept() Failed\n";
			break;
		}

		//�����µ��̣߳������������У������̺߳�̨����
		
		//server = new Server(sAccept);
		t = new std::thread(&Server::running, new Server(sAccept));
		//tManage.push_back(t);
		t->detach();
	}

	//�ͷ�ָ��ռ�õ��ڴ�
	/*for (int i = 0; i < tManage.size(); i++) {
		delete(tManage[i]);
	}*/

	//�رռ���
	closesocket(sListen);
	//�ر� Winsock
	WSACleanup();
}

//���̺߳����������Ķ��߳����д˺���
//void server(SOCKET s) {
//	SOCKET socket = s;
//	struct sockaddr_in ser, cli;//�����ַ
//	int iSend, iRecv;
//	char buf[1024] = "I am a server";
//
//	//��ʾ�ͻ��˵� IP ��Ϣ
//	char clibuf[20] = { '\0' };
//	inet_ntop(AF_INET, (void*)&cli.sin_addr, clibuf, 16);
//	std::cout << "Accept client IP:" << clibuf << ":" << ntohs(cli.sin_port) << std::endl;
//
//	//������Ϣ���ͻ���
//	iSend = send(socket, buf, sizeof(buf), 0);
//	if (iSend == SOCKET_ERROR) {
//		std::cout << "send() Failed\n";
//	}
//	else if (iSend == 0) {
//		std::cout << "send() Zero\n";
//	}
//	else {
//		std::cout << "Send byte:" << iSend << std::endl;
//		std::cout << "----------------------------------\n";
//	}
//
//	//ʹ��ѭ�����Ͻ��ܿͻ��˷���������Ϣ����ʾ
//	while (true) {
//		iRecv = recv(socket, buf, sizeof(buf), 0);
//		if (iRecv == 0) {
//			//std::cout << "recv() Zero\n";
//		}
//		else if (iRecv == SOCKET_ERROR) {
//			std::cout << "recv() Failed\n";
//		}
//		else {
//			std::cout << "recv() data from server:" << buf << std::endl;
//		}
//	}
//}