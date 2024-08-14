
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
// Qt
#include <QStandardItemModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QLayout>

#include "common.h"
namespace common
{
    int             tableViewRowHeight = 28; 
    int             tableViewHeight = 344;
    int             tableViewPageRows = 12;
    unsigned long   dwLastIn = 0;           //上一秒钟的接收字节数
    unsigned long   dwLastOut = 0;          //上一秒钟的发送字节数
    int             onePageRows=12;                   // 每页显示的行数;
    QString         strFtpIp = "127.0.0.1";    // ftp的ip
    int             iFtpport = 5555;
    int				iUserID=-1;
    extern bool     bAdministrator = false; // 是否是管理员;

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

   

   
}


