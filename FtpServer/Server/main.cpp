#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#pragma comment(lib,"ws2_32.lib")

#include "Server.h"

//多线程函数，创建的多线程运行此函数
//void server(SOCKET s);
#include <windows.h>
#include <winnetwk.h>

#pragma comment(lib, "Mpr.lib")

void InitResource(const TCHAR* userName, const TCHAR* password, const TCHAR* localDrive, const TCHAR* remotePath) {
	NETRESOURCE net_Resource;

	// 初始化NETRESOURCE结构
	net_Resource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
	net_Resource.dwScope = RESOURCE_CONNECTED;
	net_Resource.dwType = RESOURCETYPE_DISK;
	net_Resource.dwUsage = 0;
	net_Resource.lpComment = NULL;
	net_Resource.lpLocalName = const_cast<TCHAR*>(localDrive); // 映射到本地驱动器
	net_Resource.lpProvider = NULL;
	net_Resource.lpRemoteName = const_cast<TCHAR*>(remotePath); // 共享资源的路径

	DWORD dwFlags = CONNECT_UPDATE_PROFILE;

	// 取消已有连接
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);

	// 添加新连接
	DWORD dw = WNetAddConnection2(&net_Resource, password, userName, 0);
	switch (dw) {
	case ERROR_SUCCESS:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_ACCESS_DENIED:
		std::wcout << TEXT("没有权限访问！\n");
		break;
	case ERROR_ALREADY_ASSIGNED:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_INVALID_ADDRESS:
		std::wcout << TEXT("IP地址无效\n");
		break;
	case ERROR_NO_NETWORK:
		std::wcout << TEXT("网络不可达!\n");
		break;
	case ERROR_NO_TOKEN:
		std::wcout << TEXT("没有有效的凭据！请检查用户名和密码。\n");
		break;
	case ERROR_SESSION_CREDENTIAL_CONFLICT:
		std::wcout << TEXT("ERROR_SESSION_CREDENTIAL_CONFLICT。\n");
		break;
	default:
		std::wcout << TEXT("发生错误，错误代码: ") << dw << TEXT("\n");
		break;
	}
}
void InitResource(/*const TCHAR* szUserName, const TCHAR* szPasswd*/) {

	TCHAR szPasswd[] = TEXT("Share123");          //共享资源授权用户的密码
	TCHAR szUserName[] = TEXT("share");        //共享资源授权的用户
	NETRESOURCE net_Resource;

	// 初始化NETRESOURCE结构
	net_Resource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
	net_Resource.dwScope = RESOURCE_CONNECTED;
	net_Resource.dwType = RESOURCETYPE_DISK;
	net_Resource.dwUsage = 0;
	net_Resource.lpComment = NULL; // 可以设为NULL
	TCHAR localName[] = TEXT("Y:");  // 映射成本地驱动器 Z:
	net_Resource.lpLocalName = localName;
	net_Resource.lpProvider = NULL;
	TCHAR lpRemoteName[] = TEXT("\\\\192.168.0.250\\share");  // 共享资源的路径

	net_Resource.lpRemoteName = lpRemoteName; // 共享资源的路径

	DWORD dwFlags = CONNECT_UPDATE_PROFILE;

	// 取消已有连接
	WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);

	// 添加新连接
	DWORD dw = WNetAddConnection2(&net_Resource, szPasswd, szUserName, 0);
	switch (dw) {
	case ERROR_SUCCESS:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_ACCESS_DENIED:
		printf(TEXT("没有权限访问！\n"));
		break;
	case ERROR_ALREADY_ASSIGNED:
		ShellExecute(NULL, TEXT("open"), net_Resource.lpLocalName, NULL, NULL, SW_SHOWNORMAL);
		break;
	case ERROR_INVALID_ADDRESS:
		printf(TEXT("IP地址无效\n"));
		break;
	case ERROR_NO_NETWORK:
		printf(TEXT("网络不可达!\n"));
		break;
	case ERROR_NO_TOKEN:
		printf(TEXT("没有有效的凭据！请检查用户名和密码。\n"));
		break;
	case ERROR_SESSION_CREDENTIAL_CONFLICT:
		printf(TEXT("ERROR_SESSION_CREDENTIAL_CONFLICT。\n"));
		break;
	default:
		printf(TEXT("发生错误，错误代码: %lu\n"), dw);

		break;
	}
}


void main()
{
	// 示例：调用 InitResource 进行网络驱动器映射
	TCHAR userName[] = TEXT("share");
	TCHAR password[] = TEXT("Share123");
	TCHAR localDrive[] = TEXT("Y:");  //本地驱动器映射
	TCHAR remotePath[] = TEXT("\\\\192.168.1.253\\share");  // 共享资源的路径

	//InitResource(userName, password, localDrive, remotePath);
	//InitResource();
	char chInput[512];

	char fileName_my[120] = "Y:\\FileData";//"D:\\FileData";// "E:\\1008";
	//char fileName_my[120] = "D:\\FileData";//"D:\\FileData";// "E:\\1008";
	SetCurrentDirectory(fileName_my);//设置当前目录 

	sprintf_s(chInput, "int:%d\n", 500);
	OutputDebugString(chInput);

	//定义相关的数据
	int iPort = 4312;//定义其端口
	WSADATA wsaData;//Winsock 的启动参数
	SOCKET sListen, sAccept;//套接口关键字,分别用于监听和接收连接
	int iLen;
	int iSend;
	char buf[] = "I am a server";
	struct sockaddr_in ser, cli;  // 网络地址
	//定义多线程指针，用于创建线程
	std::thread* t;
	//用于线程的管理，保存创建的多线程指针，程序结束时释放占用的内存
	std::vector<std::thread*> tManage;
	Server* server = NULL;


	std::cout << "----------------------------\n";
	std::cout << "Server waitting\n";
	std::cout << "----------------------------\n";

	//启动winSocket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed to load Winsock.\n";
		return;
	}

	//创建Socket
	sListen = socket(AF_INET, SOCK_STREAM, 0);
	if (sListen == INVALID_SOCKET) {
		std::cout << "socket() Failed:" << WSAGetLastError() << "\n";
		return;
	}

	//绑定IP地址
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	//bind(sListen, (LPSOCKADDR)&ser, sizeof(ser));
	if (bind(sListen, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR) {
		std::cout << "bind() Failed\n";
		return;
	}

	//监听
	if (listen(sListen, 5) == SOCKET_ERROR) {
		std::cout << "bind() Failed: " << WSAGetLastError() << "\n";
		return;
	}

	iLen = sizeof(cli);//获取客户端网络地址的长度

	
	//接受连接和发送欢迎信息
	//用循环使程序一直运行
	while (true) {
		//接收连接
		sAccept = accept(sListen, (struct sockaddr*)&cli, &iLen);
		if (sAccept == INVALID_SOCKET) {
			std::cout << "accept() Failed\n";
			break;
		}

		//创建新的线程，并加入容器中，并将线程后台运行
		
		//server = new Server(sAccept);
		t = new std::thread(&Server::running, new Server(sAccept));
		//tManage.push_back(t);
		t->detach();
	}

	//释放指针占用的内存
	/*for (int i = 0; i < tManage.size(); i++) {
		delete(tManage[i]);
	}*/

	//关闭监听
	closesocket(sListen);
	//关闭 Winsock
	WSACleanup();
}

//多线程函数，创建的多线程运行此函数
//void server(SOCKET s) {
//	SOCKET socket = s;
//	struct sockaddr_in ser, cli;//网络地址
//	int iSend, iRecv;
//	char buf[1024] = "I am a server";
//
//	//显示客户端的 IP 信息
//	char clibuf[20] = { '\0' };
//	inet_ntop(AF_INET, (void*)&cli.sin_addr, clibuf, 16);
//	std::cout << "Accept client IP:" << clibuf << ":" << ntohs(cli.sin_port) << std::endl;
//
//	//发送信息给客户端
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
//	//使用循环不断接受客户端发送来的信息并显示
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