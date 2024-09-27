
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
    unsigned long           dwLastIn = 0;               //��һ���ӵĽ����ֽ���
    unsigned long           dwLastOut = 0;              //��һ���ӵķ����ֽ���
    int                     onePageRows=12;             // ÿҳ��ʾ������;
    QString                 strFtpIp = "127.0.0.1";     // ftp��ip
    int                     iFtpPort = 5555;
    QString                 strDbIp = "127.0.0.1";
    QString                 strDbUser = "root";
    QString                 strDbPassword = "123456";

    int				        iUserID=-1;                 //���ݿ��û�id
    bool                    bAdministrator = false;     // �Ƿ��ǹ���Ա;

    int				        iLoginNum = 1;              // ��¼˳��; 123456;
    int                     iSoftStartHostNum = 1;      // ģ��234��� ����������������־;
    std::set<std::string>   setHostIps;                 // ÿ���û������������������ip;

    QString          strCopyPath;                // ���Ƶ�Զ��·��;

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
        // ��ʼֵΪnonsignaled
        hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        // �ȴ�500ms
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
        // �洢��ǰϵͳ���ڵ��̷�
        static char path[_MAX_PATH];
        int iCurdrive = _getdrive();
        for (int iDrive = 1; iDrive <= iCurdrive; iDrive++)
        {
            if (!_chdrive(iDrive))
            {
                sprintf(path, "%c:\\", iDrive + 'A' - 1);
                ULARGE_INTEGER iTotalBytes;//����������   
                ULARGE_INTEGER iFreeBytesToCaller;//����ʣ������   
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

        //// ��ȡ���軺������С
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
        GetIfTable(NULL, &dwSize, TRUE); // ��ȡ���軺������С

        pIfTable = (MIB_IFTABLE*)malloc(dwSize);
        if (pIfTable == NULL) {
            printf("Error allocating memory\n");
            return;
        }

        if (GetIfTable(pIfTable, &dwSize, TRUE) == NO_ERROR) {
            for (DWORD i = 0; i < pIfTable->dwNumEntries; i++) {
                MIB_IFROW row = pIfTable->table[i];

                // ���ӿ��Ƿ�Ϊ��̫���� WiFi
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

        // ���ȵ��� GetAdaptersInfo ��ȡ����Ļ�������С
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

                // ��� IP ��ַ��Ϣ
                IP_ADDR_STRING* pAddr = &pAdapter->IpAddressList;
                while (pAddr) {
                    printf("IP Address: %s\n", pAddr->IpAddress.String);
                    printf("Subnet Mask: %s\n", pAddr->IpMask.String);
                    pAddr = pAddr->Next;
                }

                // ���Ĭ������
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
            m_pTable = (PMIB_IFTABLE)new BYTE[65535];   //����˿���������65535��
        }

         //DWORD   dwLastIn = 0;           //��һ���ӵĽ����ֽ���
         //DWORD   dwLastOut = 0;          //��һ���ӵķ����ֽ���
         DWORD   dwBandIn = 0;           //�����ٶ�
         DWORD   dwBandOut = 0;          //�ϴ��ٶ�

        
            NetSpeedInfo.clear();
            GetIfTable(m_pTable, &m_dwAdapters, TRUE);
            DWORD   dwInOctets = 0;
            DWORD   dwOutOctets = 0;

            //�����ж˿ڵ���������ͳ��
            for (UINT i = 0; i < m_pTable->dwNumEntries; i++)
            {
               
                MIB_IFROW   Row = m_pTable->table[i];
                dwInOctets += Row.dwInOctets;
                dwOutOctets += Row.dwOutOctets;
            }

            dwBandIn = dwInOctets - dwLastIn;       //�����ٶ�
            dwBandOut = dwOutOctets - dwLastOut;    //�ϴ�����
            if (dwLastIn <= 0)
            {
                dwBandIn = 0;
            }
            else
            {
                dwBandIn = dwBandIn / 1024; //bת����kb
            }

            if (dwLastOut <= 0)
            {
                dwBandOut = 0;
            }
            else
            {
                dwBandOut = dwBandOut / 1024;   //bת����kb
            }

            dwLastIn = dwInOctets;
            dwLastOut = dwOutOctets;

            //        printf("�յ��ֽ�: %u bytes\n", dwLastIn);
            //        printf("�����ֽ�: %u bytes\n", dwLastOut);
            //        printf("�����ٶ�: %u KB\n", dwBandIn);
            //        printf("�����ٶ�: %u KB\n", dwBandOut);
            //        printf("--------------------------\n");
            NetSpeedInfo = QString("�յ��ֽ�: %1 bytes\r\n"
                "�����ֽڣ� %2 bytes\r\n"
                "�����ٶ�: %3 Kb\r\n"
                "�����ٶ�: %4 kb\r\n")
                .arg(dwLastIn)
                .arg(dwLastOut)
                .arg(dwBandIn)
                .arg(dwBandOut);
           // emit netspeedResult(NetSpeedInfo);
            //sleep(1);       //����һ����
        
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
                return FALSE; // �ҵ�Ŀ�괰�ں�ֹͣö��
            }
            return TRUE; // ����ö��
        }, (LPARAM)&hwnd);

        return hwnd;
    }

    QString GetWindowTitle(DWORD processID) {
        HWND hwnd = FindWindowByProcessId(processID);
        if (hwnd) {
            const int length = GetWindowTextLength(hwnd) + 1;
            TCHAR* title = new TCHAR[length];
            GetWindowText(hwnd, title, length); // ��ȡ���ڱ���
            QString windowTitle = QString::fromWCharArray(title);
            delete[] title; // �ͷ��ڴ�
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
                return FALSE; // �ҵ���ֹͣ
            }
            return TRUE; // ����ö��
            }, (LPARAM)&hwnd);

        return hwnd;
    }
    HANDLE getProcessHandle(DWORD processID) {
        // ʹ�� PROCESS_ALL_ACCESS Ȩ�޴򿪽���
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
        if (hProcess == NULL) {
           // qDebug() << "Could not open process. Error:" << GetLastError();
        }
        return hProcess;
    }

    struct EnumWindowData {
        std::vector<HWND> windowHandles; // ���ڴ洢���ھ��
        DWORD processID;                  // Ŀ����� ID
    };
    std::vector<HWND> getWindowHandlesByProcessId(DWORD processID) 
    {
        EnumWindowData data = { {}, processID }; // ��ʼ�����ݽṹ

        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            EnumWindowData* pData = reinterpret_cast<EnumWindowData*>(lParam);
            DWORD windowProcessId;
            GetWindowThreadProcessId(hwnd, &windowProcessId);

            // ������ ID �Ƿ�ƥ��
            if (windowProcessId == pData->processID) {
                pData->windowHandles.push_back(hwnd); // ��Ӵ��ھ��
            }

            return TRUE; // ����ö�ٴ���
            }, reinterpret_cast<LPARAM>(&data)); // �������ݽṹ��ָ��

        return data.windowHandles; // �����ҵ��Ĵ��ھ��
    }



    HWND StartExeAndFindWindow(QString strPath)
    {
        std::wstring wStr = strPath.toStdWString();

        // ��std::wstring��ȡLPCWSTR
        LPCWSTR lpwstr = wStr.c_str();
        // ��������
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        if (CreateProcess(lpwstr, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            std::cout << "Process started!" << std::endl;

            // �ȴ�һ��ʱ�䣬�ô��ڴ���
            Sleep(1000); // �����������������Ҫ����

            // ��ȡ���ھ��
            HWND hwnd = FindWindowByProcessId(pi.dwProcessId);
            if (hwnd) {
                std::cout << "Window handle: " << hwnd << std::endl;
            }
            else {
                std::cout << "No top-level window found for the process." << std::endl;
            }

            // �رս��̾��
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
    //    if (1strcmpi(_T("MainWnd")�� szClassName) == 0) {
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

        //// ��ȡ��ǰ����Ŀ¼
        //if (GetCurrentDirectoryA(bufferSize, currentDirectory)) {
        //    std::cout << "Current Directory: " << currentDirectory << std::endl;

        //   
        //   
        //}
        QByteArray byteArray = strPath.toUtf8(); // ת��Ϊ UTF-8 ����
            // Ӧ�ó���·��
        LPCSTR applicationPath = byteArray.constData();//= "E:\Visual Studio 2017.rdp";// "C:\\Path\\To\\Your\\Application.exe"; // �滻Ϊʵ��·��

            // ���� ShellExecuteA ����Ӧ�ó���
            HINSTANCE result = ShellExecuteA(NULL, "open", applicationPath, NULL, currentDirectory, SW_SHOW);

            // ��鷵��ֵ
            if ((int)result > 32) {
                std::cout << "Application opened successfully." << std::endl;
            }
            else {
                std::cerr << "Failed to open application. Error code: " << (int)result << std::endl;
            }
        
       
    }

    void UnInitResource()
    {
        TCHAR szPasswd[] = TEXT("administrataor");          //������Դ��Ȩ�û�������
        TCHAR szUserName[] = TEXT("Ate123");        //������Դ��Ȩ���û�

        //TCHAR szPasswd[] = TEXT("Share123");          //������Դ��Ȩ�û�������
        //TCHAR szUserName[] = TEXT("share");        //������Դ��Ȩ���û�
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
        TCHAR lpRemoteName[] = TEXT("\\\\192.168.1.247");  // ������Դ��·��

        net_Resource.lpRemoteName = lpRemoteName; // ������Դ��·��

        DWORD dwFlags = CONNECT_UPDATE_PROFILE;

        // ȡ����������
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
            //��ͷ��Ϣ��ʾ���� 
            // ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
            tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            // �����п�ȿ�������
            // tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   // ѡ������
            // �����и�
            tableView->horizontalHeader()->setDefaultSectionSize(28);
            // ���ñ������Ĺ̶��߶ȣ�
            tableView->horizontalHeader()->setFixedHeight(28);
            tableView->verticalHeader()->setVisible(false);
            // ���ñ��ĵ�ԪΪֻ�����ԣ����ܱ༭
            tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            // ���õ�ѡ
            tableView->setSelectionMode(QAbstractItemView::SingleSelection);
            // ���ö�ѡ
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
    //    // ��ȡ��Ҫ�Ķ��ֽ��ַ���������С
    //    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wChar, -1, nullptr, 0, nullptr, nullptr);
    //    // �������ֽ��ַ�������
    //    char* charBuffer = new char[bufferSize];
    //    // �����ַ���ת��
    //    WideCharToMultiByte(CP_UTF8, 0, wChar, -1, charBuffer, bufferSize, nullptr, nullptr);
    //    // �����ֽ��ַ���ת��Ϊstd::string
    //    return std::string(charBuffer);
    //}

    //wchar_t* String2Wchar(const std::string strTag)
    //{
    //    // ��ȡ��Ҫ�Ŀ��ַ���������С
    //    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, strTag.c_str(), -1, nullptr, 0);
    //    // �������ַ�������
    //    wchar_t* tagBuffer = new wchar_t[bufferSize];
    //    // �����ַ���ת��
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

        // ʹ�� std::copy �� QString ת��Ϊ wchar_t
        std::copy(password.utf16(), password.utf16() + password.length() + 1, passwordBlob.data());

        cred.CredentialBlob = reinterpret_cast<LPBYTE>(passwordBlob.data());
      //  cred.CredentialBlob = const_cast<LPWSTR>(reinterpret_cast<const wchar_t*>(password.utf16()));
        cred.Persist = CRED_PERSIST_LOCAL_MACHINE;

        // ����ƾ��
        if (CredWrite(&cred, 0)) {
            std::cout << "ƾ���ѳɹ����档" << std::endl;
        }
        else {
            std::cerr << "����ƾ��ʧ�ܣ�������룺" << GetLastError() << std::endl;
        }
    }
   
}


