
#include <iostream>

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Psapi.lib")

#include <windows.h>
//#include <winsock2.h>
#include <stdio.h>
//#include <string.h>
#include <locale.h>
#include <tlHelp32.h>
#include <direct.h>
#include <winternl.h>
#include <Psapi.h>
//#include <atlconv.h>
#include <cmath>
#include <string.h>
//#include <wstring>
#include <assert.h>

#include <wininet.h>
//#include <iphlpapi.h>
#include <stdio.h>
#include <IPHlpApi.h>
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "Ws2_32.lib")

#pragma comment(lib, "Advapi32.lib")

#include <wincred.h>
#include <tlhelp32.h>

#include <winnetwk.h>

#pragma comment(lib, "Mpr.lib")

// Qt
#include <QCoreApplication>

#include <QStandardItemModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QLayout>
#include <QByteArray>

#include <set>

#include "common.h"
namespace common
{
    int                     tableViewRowHeight = 28; 
    int                     tableViewHeight = 344;
    int                     tableViewPageRows = 12;
    unsigned long           dwLastIn = 0;               //上一秒钟的接收字节数
    unsigned long           dwLastOut = 0;              //上一秒钟的发送字节数
    int                     onePageRows=12;             // 每页显示的行数;
    QString                 strFtpIp = "127.0.0.1";     // ftp的ip
    int                     iFtpPort = 5555;
    QString                 strDbIp = "127.0.0.1";
    QString                 strDbUser = "root";
    QString                 strDbPassword = "123456";

    int				        iUserID=-1;                 //数据库用户id
    bool                    bAdministrator = false;     // 是否是管理员;

    int				        iLoginNum = 1;              // 登录顺序; 123456;
    int                     iSoftStartHostNum = 1;      // 模块234软件 启动的所在主机标志;
    std::set<std::string>   setHostIps;                 // 每个用户分配的三个主机网卡ip;

    QString          strCopyPath;                // 复制的远程路径;

    __int64 Filetime2Int64(const FILETIME& ftime)
    {
        LARGE_INTEGER li;
        li.LowPart = ftime.dwLowDateTime;
        li.HighPart = ftime.dwHighDateTime;
        return li.QuadPart;
    }
    __int64 CompareFileTimeEx(const FILETIME& preTime, const FILETIME& nowTime)
    {
        return Filetime2Int64(nowTime) - Filetime2Int64(preTime);
    }
    double getCpuUsage()
    {
        double nCpuRate = -1;

        HANDLE hEvent;
        bool bRes = true;
        static FILETIME preIdleTime;
        static FILETIME preKernelTime;
        static FILETIME preUserTime;
        FILETIME idleTime;
        FILETIME kernelTime;
        FILETIME userTime;
        bRes = GetSystemTimes(&idleTime, &kernelTime, &userTime);
        preIdleTime = idleTime;
        preKernelTime = kernelTime;
        preUserTime = userTime;
        // 初始值为nonsignaled
        hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        // 等待500ms
        WaitForSingleObject(hEvent, 500);

        bRes = GetSystemTimes(&idleTime, &kernelTime, &userTime);
        __int64 idle = CompareFileTimeEx(preIdleTime, idleTime);
        __int64 kernel = CompareFileTimeEx(preKernelTime, kernelTime);
        __int64 user = CompareFileTimeEx(preUserTime, userTime);

        nCpuRate = ceil(100.0 * (kernel + user - idle) / (kernel + user));
        //qDebug() << "windows: CPU user rate: " << nCpurate << "%";

        return nCpuRate;
    }

    void getPhysicsMem(long& allPhysicsMem, long& freePhysicsMem)
    {
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);
        allPhysicsMem = statex.ullTotalPhys * 1.0 / 1024.0 / 1024.0;
        freePhysicsMem = statex.ullAvailPhys * 1.0 / 1024.0 / 1024.0;
        
    }
    double getMemUseRate()
    {
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);
        long allPhysicsMem = statex.ullTotalPhys * 1.0 / 1024.0 / 1024.0;
        long freePhysicsMem = statex.ullAvailPhys * 1.0 / 1024.0 / 1024.0;
        return (allPhysicsMem - freePhysicsMem) * 100.0 / allPhysicsMem;
    }
    void getAllDisSpace(double& lFreeAll, double& lToalAll)
    {
        // 存储当前系统存在的盘符
        static char path[_MAX_PATH];
        int iCurdrive = _getdrive();
        for (int iDrive = 1; iDrive <= iCurdrive; iDrive++)
        {
            if (!_chdrive(iDrive))
            {
                sprintf(path, "%c:\\", iDrive + 'A' - 1);
                ULARGE_INTEGER iTotalBytes;//磁盘总容量   
                ULARGE_INTEGER iFreeBytesToCaller;//磁盘剩余容量   
                ULARGE_INTEGER iFreeBytes;
                WCHAR wszClassName[_MAX_PATH];
                memset(wszClassName, 0, sizeof(wszClassName));
                MultiByteToWideChar(CP_ACP, 0, path, strlen(path) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
                if (GetDiskFreeSpaceEx(wszClassName, &iFreeBytesToCaller, &iTotalBytes, &iFreeBytes) == 0)
                {
                    return;
                }

                double dTepFree = iFreeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
                double dTepToal = iTotalBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
              
                lFreeAll += dTepFree;
                lToalAll += dTepToal;
            }
        }
    }

    void getNetData()
    {
        ULONG outBufLen = sizeof(IP_ADAPTER_INFO);
        PIP_ADAPTER_INFO pAdapterInfo = (PIP_ADAPTER_INFO)malloc(outBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return ;
        }

        DWORD dwRetVal = GetAdaptersInfo(pAdapterInfo, &outBufLen);
        while (dwRetVal == ERROR_BUFFER_OVERFLOW) 
        {
            free(pAdapterInfo);
            pAdapterInfo = (PIP_ADAPTER_INFO)malloc(outBufLen);
            if (pAdapterInfo == NULL) 
            {
                printf("Error allocating memory needed to call GetAdaptersinfo\n");
                return ;
            }
            dwRetVal = GetAdaptersInfo(pAdapterInfo, &outBufLen);
        }

        if (dwRetVal == ERROR_SUCCESS)
        {
            PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
            do 
            {
                printf("\nAdapter Name: %s\n", pAdapter->AdapterName);
                printf("Adapter Desc: %s\n", pAdapter->Description);
                printf("Adapter Address: %02X-%02X-%02X-%02X-%02X-%02X\n",
                    pAdapter->Address[0], pAdapter->Address[1], pAdapter->Address[2],
                    pAdapter->Address[3], pAdapter->Address[4], pAdapter->Address[5]);
                printf("IP Address: %s\n", pAdapter->IpAddressList.IpAddress.String);
                printf("Subnet Mask: %s\n", pAdapter->IpAddressList.IpMask.String);
                printf("Gateway: %s\n", pAdapter->GatewayList.IpAddress.String);
                printf("MAC Address: %02X-%02X-%02X-%02X-%02X-%02X\n",
                    pAdapter->Address[0], pAdapter->Address[1], pAdapter->Address[2],
                    pAdapter->Address[3], pAdapter->Address[4], pAdapter->Address[5]);
                printf("Type: %u\n", pAdapter->Type);

                pAdapter = pAdapter->Next;
            } while (pAdapter);
        }
        else {
            printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
        }

        free(pAdapterInfo);
        return ;
    }

    void getNetSpeed()
    {
        //MIB_IFTABLE* pIfTable = nullptr;
        //DWORD dwSize = 0;

        //// 获取所需缓冲区大小
        //if (GetIfTable(nullptr, &dwSize, TRUE) == ERROR_INSUFFICIENT_BUFFER) 
        //{
        //    pIfTable = (MIB_IFTABLE*)malloc(dwSize);
        //    if (GetIfTable(pIfTable, &dwSize, TRUE) == NO_ERROR) {
        //        for (ULONG i = 0; i < pIfTable->dwNumEntries; ++i) {
        //            MIB_IFROW& row = pIfTable->table[i];
        //            if (row.dwType == MIB_IF_TYPE_ETHERNET || row.dwType == MIB_IF_TYPE_IEEE80211) {
        //                std::cout << "Interface: " << row.wszName << std::endl;
        //                std::cout << "Speed: " << row.dwSpeed << " bps" << std::endl;
        //                std::cout << "Bytes Received: " << row.dwInOctets << std::endl;
        //                std::cout << "Bytes Sent: " << row.dwOutOctets << std::endl;
        //            }
        //        }
        //    }
        //    free(pIfTable);
        //}
    }

    void getNetworkInterfaceStatistics() {
        PMIB_IFTABLE pIfTable;
        DWORD dwSize = 0;
        GetIfTable(NULL, &dwSize, TRUE); // 获取所需缓冲区大小

        pIfTable = (MIB_IFTABLE*)malloc(dwSize);
        if (pIfTable == NULL) {
            printf("Error allocating memory\n");
            return;
        }

        if (GetIfTable(pIfTable, &dwSize, TRUE) == NO_ERROR) {
            for (DWORD i = 0; i < pIfTable->dwNumEntries; i++) {
                MIB_IFROW row = pIfTable->table[i];

                // 检查接口是否为以太网或 WiFi
                if (row.dwType == IF_TYPE_ETHERNET_CSMACD || row.dwType == IF_TYPE_IEEE80211) {
                    printf("Interface Name: %ws\n", row.wszName);
                    printf("Interface Index: %lu\n", row.dwIndex);
                    printf("Speed: %lu bps\n", row.dwSpeed);
                    printf("In Octets: %lu\n", row.dwInOctets);
                    printf("Out Octets: %lu\n", row.dwOutOctets);
                    printf("In Ucast Packets: %lu\n", row.dwInUcastPkts);
                    printf("Out Ucast Packets: %lu\n", row.dwOutUcastPkts);
                    printf("In Non Ucast Packets: %lu\n", row.dwInNUcastPkts);
                    printf("Out Non Ucast Packets: %lu\n", row.dwOutNUcastPkts);
                    printf("In Discards: %lu\n", row.dwInDiscards);
                    printf("Out Discards: %lu\n", row.dwOutDiscards);
                    printf("In Errors: %lu\n", row.dwInErrors);
                    printf("Out Errors: %lu\n", row.dwOutErrors);
                    printf("In Unknown Protocols: %lu\n", row.dwInUnknownProtos);
                    printf("Out Octets: %lu\n", row.dwOutOctets);
                    printf("\n");
                }
            }
        }
        else {
            printf("Error getting interface table\n");
        }

        free(pIfTable);
    }
    void PrintAdapterInfo() {
        PIP_ADAPTER_INFO pAdapterInfo = NULL;
        ULONG ulOutBufLen = 0;

        // 首先调用 GetAdaptersInfo 获取所需的缓冲区大小
        if (GetAdaptersInfo(NULL, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
            pAdapterInfo = (PIP_ADAPTER_INFO)malloc(ulOutBufLen);
        }

        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersInfo\n");
            return;
        }

        if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
            PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
            do {
                printf("\nAdapter Name: %s\n", pAdapter->AdapterName);
                printf("Adapter Desc: %s\n", pAdapter->Description);
                printf("Adapter Address: %02X-%02X-%02X-%02X-%02X-%02X\n",
                    pAdapter->Address[0], pAdapter->Address[1], pAdapter->Address[2],
                    pAdapter->Address[3], pAdapter->Address[4], pAdapter->Address[5]);
                printf("Index: %u\n", pAdapter->Index);
                printf("Type: %u\n", pAdapter->Type);

                // 输出 IP 地址信息
                IP_ADDR_STRING* pAddr = &pAdapter->IpAddressList;
                while (pAddr) {
                    printf("IP Address: %s\n", pAddr->IpAddress.String);
                    printf("Subnet Mask: %s\n", pAddr->IpMask.String);
                    pAddr = pAddr->Next;
                }

                // 输出默认网关
                if (pAdapter->GatewayList.IpAddress.String[0]) {
                    printf("Default Gateway: %s\n", pAdapter->GatewayList.IpAddress.String);
                }

                pAdapter = pAdapter->Next;
            } while (pAdapter);
        }

        if (pAdapterInfo) free(pAdapterInfo);
    }


    unsigned long GetNetworkInterfacesThroughput()
    {
        QString NetSpeedInfo;
        PMIB_IFTABLE    m_pTable = NULL;
        DWORD    m_dwAdapters = 0;
        ULONG    uRetCode = GetIfTable(m_pTable, &m_dwAdapters, TRUE);
        if (uRetCode == ERROR_NOT_SUPPORTED)
        {
            //return (-1);
            return 0;
        }

        if (uRetCode == ERROR_INSUFFICIENT_BUFFER)
        {
            m_pTable = (PMIB_IFTABLE)new BYTE[65535];   //假设端口数不超过65535个
        }

         //DWORD   dwLastIn = 0;           //上一秒钟的接收字节数
         //DWORD   dwLastOut = 0;          //上一秒钟的发送字节数
         DWORD   dwBandIn = 0;           //下载速度
         DWORD   dwBandOut = 0;          //上传速度

        
            NetSpeedInfo.clear();
            GetIfTable(m_pTable, &m_dwAdapters, TRUE);
            DWORD   dwInOctets = 0;
            DWORD   dwOutOctets = 0;

            //将所有端口的流量进行统计
            for (UINT i = 0; i < m_pTable->dwNumEntries; i++)
            {
               
                MIB_IFROW   Row = m_pTable->table[i];
                dwInOctets += Row.dwInOctets;
                dwOutOctets += Row.dwOutOctets;
            }

            dwBandIn = dwInOctets - dwLastIn;       //下载速度
            dwBandOut = dwOutOctets - dwLastOut;    //上床速速
            if (dwLastIn <= 0)
            {
                dwBandIn = 0;
            }
            else
            {
                dwBandIn = dwBandIn / 1024; //b转换成kb
            }

            if (dwLastOut <= 0)
            {
                dwBandOut = 0;
            }
            else
            {
                dwBandOut = dwBandOut / 1024;   //b转换成kb
            }

            dwLastIn = dwInOctets;
            dwLastOut = dwOutOctets;

            //        printf("收到字节: %u bytes\n", dwLastIn);
            //        printf("发送字节: %u bytes\n", dwLastOut);
            //        printf("下行速度: %u KB\n", dwBandIn);
            //        printf("上行速度: %u KB\n", dwBandOut);
            //        printf("--------------------------\n");
            NetSpeedInfo = QString("收到字节: %1 bytes\r\n"
                "发送字节： %2 bytes\r\n"
                "下行速度: %3 Kb\r\n"
                "上行速度: %4 kb\r\n")
                .arg(dwLastIn)
                .arg(dwLastOut)
                .arg(dwBandIn)
                .arg(dwBandOut);
           // emit netspeedResult(NetSpeedInfo);
            //sleep(1);       //休眠一秒钟
        
        delete[] m_pTable;
        unsigned long throughput = dwBandIn + dwBandOut;
        return throughput;
       
    }

    void clearLayout(QLayout* layout)
    {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
    }
    HWND FindWindowByProcessId(DWORD processID) {
        HWND hwnd = NULL;
        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL 
        {
            DWORD wndProcessId;
            GetWindowThreadProcessId(hwnd, &wndProcessId);

            if (wndProcessId == lParam && IsWindowVisible(hwnd)) {
                *(HWND*)lParam = hwnd;
                return FALSE; // 找到目标窗口后停止枚举
            }
            return TRUE; // 继续枚举
        }, (LPARAM)&hwnd);

        return hwnd;
    }

    QString GetWindowTitle(DWORD processID) {
        HWND hwnd = FindWindowByProcessId(processID);
        if (hwnd) {
            const int length = GetWindowTextLength(hwnd) + 1;
            TCHAR* title = new TCHAR[length];
            GetWindowText(hwnd, title, length); // 获取窗口标题
            QString windowTitle = QString::fromWCharArray(title);
            delete[] title; // 释放内存
            return windowTitle;
        }
        return QString();
    }
    HWND findWindowByProcessId(DWORD processID) {
        HWND hwnd = NULL;
        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            DWORD windowProcessId;
            GetWindowThreadProcessId(hwnd, &windowProcessId);
            if (windowProcessId == (DWORD)lParam) {
                *(HWND*)lParam = hwnd;
                return FALSE; // 找到后停止
            }
            return TRUE; // 继续枚举
            }, (LPARAM)&hwnd);

        return hwnd;
    }
    HANDLE getProcessHandle(DWORD processID) {
        // 使用 PROCESS_ALL_ACCESS 权限打开进程
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
        if (hProcess == NULL) {
           // qDebug() << "Could not open process. Error:" << GetLastError();
        }
        return hProcess;
    }

    struct EnumWindowData {
        std::vector<HWND> windowHandles; // 用于存储窗口句柄
        DWORD processID;                  // 目标进程 ID
    };
    std::vector<HWND> getWindowHandlesByProcessId(DWORD processID) 
    {
        EnumWindowData data = { {}, processID }; // 初始化数据结构

        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            EnumWindowData* pData = reinterpret_cast<EnumWindowData*>(lParam);
            DWORD windowProcessId;
            GetWindowThreadProcessId(hwnd, &windowProcessId);

            // 检查进程 ID 是否匹配
            if (windowProcessId == pData->processID) {
                pData->windowHandles.push_back(hwnd); // 添加窗口句柄
            }

            return TRUE; // 继续枚举窗口
            }, reinterpret_cast<LPARAM>(&data)); // 传递数据结构的指针

        return data.windowHandles; // 返回找到的窗口句柄
    }



    HWND StartExeAndFindWindow(QString strPath)
    {
        std::wstring wStr = strPath.toStdWString();

        // 从std::wstring获取LPCWSTR
        LPCWSTR lpwstr = wStr.c_str();
        // 启动进程
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        if (CreateProcess(lpwstr, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            std::cout << "Process started!" << std::endl;

            // 等待一段时间，让窗口创建
            Sleep(1000); // 视情况而定，可能需要调整

            // 获取窗口句柄
            HWND hwnd = FindWindowByProcessId(pi.dwProcessId);
            if (hwnd) {
                std::cout << "Window handle: " << hwnd << std::endl;
            }
            else {
                std::cout << "No top-level window found for the process." << std::endl;
            }

            // 关闭进程句柄
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            return hwnd;
        }
        else {
            std::cout << "Failed to start process. Error: " << GetLastError() << std::endl;
            return HWND();
        }
       
    }

   

    //BOOL CALLBACK SEnumProc(HWND hWnd, LPARAM Param) 
    //{
    //    BOOL bRet = TRUE;
    //    TCHAR szClassName[256] = { 0 };
    //    GetC1assName(hWnd, szC1assName, 255);
    //    if (1strcmpi(_T("MainWnd")， szClassName) == 0) {
    //        DWORD dwProcessId = 0;
    //        GetWindowThreadProcessId(hWnd, &dwProcessId);
    //        if (dwProcessId == GetProcessIdByName(_T("BDWa11Paper_d. exe"))) {
    //            g_hWnd = hWnd; bRet = FALSE;
    //        }
    //        return bRet;
    //    }
        

    struct handle_data {
        unsigned long process_id;
        HWND best_handle;
    };

    BOOL IsMainWindow(HWND handle)
    {
        return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
    }

    BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
    {
        handle_data& data = *(handle_data*)lParam;
        unsigned long process_id = 0;
        GetWindowThreadProcessId(handle, &process_id);
        if (data.process_id != process_id || !IsMainWindow(handle)) {
            return TRUE;
        }
        data.best_handle = handle;
        return FALSE;
    }
    HWND FindMainWindow(unsigned long process_id)
    {
        handle_data data;
        data.process_id = process_id;
        data.best_handle = 0;
        EnumWindows(EnumWindowsCallback, (LPARAM)&data);
        return data.best_handle;
    }

   



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
    void StoreCredential(const std::wstring& target, const std::wstring& username, const std::wstring& password) {
        CREDENTIALW cred = { 0 };
      //  cred.Type = CRED_TYPE_GENERIC;
      ////  cred.Target = const_cast<LPWSTR>(target.c_str());
      //  cred.UserName = const_cast<LPWSTR>(username.c_str());
      //  cred.CredentialBlob = const_cast<LPWSTR>(password.c_str());
      //  cred.CredentialBlobSize = static_cast<DWORD>((password.size() + 1) * sizeof(wchar_t));
      //  cred.Persist = CRED_PERSIST_SESSION;

      //  if (CredWriteW(&cred, 0)) {
      //      std::wcout << L"Credentials saved successfully." << std::endl;
      //  }
      //  else {
      //      std::wcerr << L"Failed to save credentials. Error: " << GetLastError() << std::endl;
      //  }
    }

    void startDspExe(QString& strPath)
    {

       
        DWORD bufferSize = MAX_PATH;
        char currentDirectory[MAX_PATH];

        //// 获取当前工作目录
        //if (GetCurrentDirectoryA(bufferSize, currentDirectory)) {
        //    std::cout << "Current Directory: " << currentDirectory << std::endl;

        //   
        //   
        //}
        QByteArray byteArray = strPath.toUtf8(); // 转换为 UTF-8 编码
            // 应用程序路径
        LPCSTR applicationPath = byteArray.constData();//= "E:\Visual Studio 2017.rdp";// "C:\\Path\\To\\Your\\Application.exe"; // 替换为实际路径

            // 调用 ShellExecuteA 来打开应用程序
            HINSTANCE result = ShellExecuteA(NULL, "open", applicationPath, NULL, currentDirectory, SW_SHOW);

            // 检查返回值
            if ((int)result > 32) {
                std::cout << "Application opened successfully." << std::endl;
            }
            else {
                std::cerr << "Failed to open application. Error code: " << (int)result << std::endl;
            }
        
       
    }

    void UnInitResource()
    {
        TCHAR szPasswd[] = TEXT("administrataor");          //共享资源授权用户的密码
        TCHAR szUserName[] = TEXT("Ate123");        //共享资源授权的用户

        //TCHAR szPasswd[] = TEXT("Share123");          //共享资源授权用户的密码
        //TCHAR szUserName[] = TEXT("share");        //共享资源授权的用户
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
        TCHAR lpRemoteName[] = TEXT("\\\\192.168.1.247");  // 共享资源的路径

        net_Resource.lpRemoteName = lpRemoteName; // 共享资源的路径

        DWORD dwFlags = CONNECT_UPDATE_PROFILE;

        // 取消已有连接
        WNetCancelConnection2(net_Resource.lpLocalName, CONNECT_UPDATE_PROFILE, TRUE);

      
    }
    void delAllModelRow(QStandardItemModel* model)
    {
        int rowCount = model->rowCount();
        for (int row = rowCount - 1; row >= 0; --row)
        {
            model->removeRow(row);
        }
    }
    void hideMidelRowsbyColumnValue(QStandardItemModel* model, const int& Column, const QString& strValue)
    {
      
    }

    time_t string_to_datetime(const std::string& str)
    {
        tm tm_;
        int year = 0;
        int month = 0;
        int day = 0;
        int hour = 0;
        int minute = 0;
        int second = 0;
        sscanf(str.data(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
        tm_.tm_year = year - 1900;
        tm_.tm_mon = month - 1;
        tm_.tm_mday = day;
        tm_.tm_hour = hour;
        tm_.tm_min = minute;
        tm_.tm_sec = second;
        tm_.tm_isdst = 0;
        time_t t_ = mktime(&tm_);
        return t_;
    }
   
    void setTableViewBasicConfiguration(QTableView* tableView)
    {
        if (tableView)
        {
            //表头信息显示居左 
            // ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
            tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            // 设置列宽度可以拉伸
            // tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // 选择整行
            // 设置行高
            tableView->horizontalHeader()->setDefaultSectionSize(28);
            // 设置标题栏的固定高度，
            tableView->horizontalHeader()->setFixedHeight(28);
            tableView->verticalHeader()->setVisible(false);
            // 设置表格的单元为只读属性，不能编辑
            tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            // 设置单选
            tableView->setSelectionMode(QAbstractItemView::SingleSelection);
            // 设置多选
            // ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
            tableView->horizontalHeader()->setSectionsMovable(true);
        }
    }
 /*   wchar_t* QString2wchar_t(QString str)
    {
        std::wstring wstr = str.toStdWString();
         wchar_t* lpcwstr = wstr.c_str();
        return lpcwstr;
    }*/
    //std::string Wchar2string(WCHAR wChar[])
    //{
    //    // 获取需要的多字节字符缓冲区大小
    //    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wChar, -1, nullptr, 0, nullptr, nullptr);
    //    // 创建多字节字符缓冲区
    //    char* charBuffer = new char[bufferSize];
    //    // 进行字符串转换
    //    WideCharToMultiByte(CP_UTF8, 0, wChar, -1, charBuffer, bufferSize, nullptr, nullptr);
    //    // 将多字节字符串转换为std::string
    //    return std::string(charBuffer);
    //}

    //wchar_t* String2Wchar(const std::string strTag)
    //{
    //    // 获取需要的宽字符缓冲区大小
    //    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, strTag.c_str(), -1, nullptr, 0);
    //    // 创建宽字符缓冲区
    //    wchar_t* tagBuffer = new wchar_t[bufferSize];
    //    // 进行字符串转换
    //    MultiByteToWideChar(CP_UTF8, 0, strTag.c_str(), -1, tagBuffer, bufferSize);
    //    return tagBuffer;
    //}


    void addNetworkCredential(const QString& target, const QString& username, const QString& password) {
        CREDENTIALW  cred;
        memset(&cred, 0, sizeof(CREDENTIAL));

        cred.Type = CRED_TYPE_GENERIC;
        cred.TargetName = const_cast<LPWSTR>(reinterpret_cast<const wchar_t*>(target.utf16()));
        cred.UserName = const_cast<LPWSTR>(reinterpret_cast<const wchar_t*>(username.utf16()));
        cred.CredentialBlobSize = password.length() * sizeof(wchar_t);
       // cred.
        // Create a vector to hold the password
        std::vector<wchar_t> passwordBlob(password.length() + 1);

        // 使用 std::copy 将 QString 转换为 wchar_t
        std::copy(password.utf16(), password.utf16() + password.length() + 1, passwordBlob.data());

        cred.CredentialBlob = reinterpret_cast<LPBYTE>(passwordBlob.data());
      //  cred.CredentialBlob = const_cast<LPWSTR>(reinterpret_cast<const wchar_t*>(password.utf16()));
        cred.Persist = CRED_PERSIST_LOCAL_MACHINE;

        // 保存凭据
        if (CredWrite(&cred, 0)) {
            std::cout << "凭据已成功保存。" << std::endl;
        }
        else {
            std::cerr << "保存凭据失败，错误代码：" << GetLastError() << std::endl;
        }
    }
   
}


