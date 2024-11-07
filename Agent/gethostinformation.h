#ifndef GETHOSTINFORMATION_H
#define GETHOSTINFORMATION_H

#include <QWidget>
#include <pdh.h>
#include <pdhmsg.h>
#include <tchar.h>
#include <windows.h>
#include "getGpu.h"
namespace common{

extern unsigned long   dwLastIn;           //上一秒钟的接收字节数
extern unsigned long   dwLastOut;          //上一秒钟的发送字节数
//获取主机的CPU
double getCpuUsage();
//获取主机的内存
void getPhysicsMem(long& allPhysicsMem, long& freePhysicsMem);
//    double getMemUseRate();
//获取主机的磁盘
void getAllDisSpace(double& lFreeAll, double& lToalAll);
//获取主机的网络
void getNetworkInterfaceStatistics();
void PrintAdapterInfo();
unsigned long GetNetworkInterfacesThroughput();
//获取主机的Gpu
double getGpuUsage(const std::wstring& strCounterPath, DWORD dwFormat);
}

#endif // GETHOSTINFORMATION_H
