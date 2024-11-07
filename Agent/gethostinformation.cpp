#include "gethostinformation.h"

#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <tlHelp32.h>
#include <direct.h>
#include <winternl.h>
#include <Psapi.h>
#include <cmath>
#include <string.h>
#include <assert.h>
#include <wininet.h>
//#include <iphlpapi.h>
#include <IPHlpApi.h>
#include "getGpu.h"
//class CPerformHelper;
#include "Win32Utils/CDeviceHelper.h"
#include "Win32Utils/CWmiQueryHelper.h"
#include "Win32Utils/CDeviceHelper.h"
#include "Win32Utils/CStrUtils.h"


//#pragma comment(lib, "IPHLPAPI.lib")
//#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "pdh.lib")


namespace common {


	unsigned long   dwLastIn = 0;           //上一秒钟的接收字节数
	unsigned long   dwLastOut = 0;          //上一秒钟的发送字节数

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
		//bool bRes;
		static FILETIME preIdleTime;
		static FILETIME preKernelTime;
		static FILETIME preUserTime;
		FILETIME idleTime;
		FILETIME kernelTime;
		FILETIME userTime;
		GetSystemTimes(&idleTime, &kernelTime, &userTime);
		preIdleTime = idleTime;
		preKernelTime = kernelTime;
		preUserTime = userTime;
		// 初始值为nonsignaled
		hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		// 等待500ms
		WaitForSingleObject(hEvent, 500);

		GetSystemTimes(&idleTime, &kernelTime, &userTime);
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
	//double getMemUseRate()
	//{
	//    MEMORYSTATUSEX statex;
	//    statex.dwLength = sizeof(statex);
	//    GlobalMemoryStatusEx(&statex);
	//    long allPhysicsMem = statex.ullTotalPhys * 1.0 / 1024.0 / 1024.0;
	//    long freePhysicsMem = statex.ullAvailPhys * 1.0 / 1024.0 / 1024.0;
	//    return (allPhysicsMem - freePhysicsMem) * 100.0 / allPhysicsMem;
	//}

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
					//                printf("Interface Name: %ws\n", row.wszName);
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
				printf("Index: %lu\n", pAdapter->Index);
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

	double getGpuUsage(const std::wstring& strCounterPath, DWORD dwFormat)
	{
		setlocale(LC_ALL, "");

		std::vector<VIDEO_ADAPTER_DESC_INFO> vResult = CDeviceHelper::GetAllVideoAdapterDesc();

		CDeviceHelper obj;

		clock_t tmBegin = ::clock();
		DEVICE_INFO info = obj.GetDeviceInfo();
		clock_t tmEnd = ::clock();

		//Console::Printf(_T("cost time: %d\r\n"), tmEnd - tmBegin);

		CPerformHelper perfmon;

		//int nTimeInterval = 1000;

		perfmon.Initialize();
		perfmon.AddCounter(_T(PERFM_PATH_GPU_UTILITY));
		perfmon.StartCollect();

		PDH_FMT_COUNTERVALUE value = { 0 };

		/*SIZE_T DedicatedVideoMemory = vResult[0].AdapterDesc.DedicatedVideoMemory;
		SIZE_T DedicatedSystemMemory = vResult[0].AdapterDesc.DedicatedSystemMemory;
		SIZE_T SharedSystemMemory = vResult[0].AdapterDesc.SharedSystemMemory;*/

		MEMORYSTATUSEX memStatus = { 0 };
		memStatus.dwLength = sizeof(MEMORYSTATUSEX);

		//double lfFrequency = 0.0f;
		//::GlobalMemoryStatusEx(&memStatus);

		//Console::Clear();
		//获取GPU占用率
		if (perfmon.GetFormattedCounterArray(_T(PERFM_PATH_GPU_UTILITY), PDH_FMT_DOUBLE, &value))
		{
			//Console::Printf(_T("GPU 利用率: %.1lf%%"), value.doubleValue);
			//Console::Printf(_T("\r\n"));
		}
		return value.doubleValue;
	}


}
