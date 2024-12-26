#include "widget.h"

#include <QApplication>
#include <windows.h>
#include <winnetwk.h>
#include "ZipFunction.h"
#pragma comment(lib, "Mpr.lib")

void InitResource(const TCHAR* userName, const TCHAR* password, const TCHAR* localDrive, const TCHAR* remotePath)
{
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

int main(int argc, char *argv[])
{
	// 示例：调用 InitResource 进行网络驱动器映射
	TCHAR userName[] = TEXT("administrator");
	TCHAR password[] = TEXT("Ate123");
	TCHAR localDrive[] = TEXT("Y:");  //本地驱动器映射
	TCHAR remotePath[] = TEXT("\\\\192.168.1.253\\share");  // 共享资源的路径
	InitResource(userName, password, localDrive, remotePath);

    QApplication a(argc, argv);
    Widget w;
    w.show();
    //窗口的隐藏
    //w.hide();
    //窗口的最小化
    //w.showMinimized();
    return a.exec();
}
