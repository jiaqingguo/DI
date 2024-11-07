#pragma once

#include <windows.h>
#include <tchar.h>
#include <string>
#include <pdh.h>
#include <string>
#include <mutex>
#include <thread>
#include <map>

#ifdef _UNICODE
using _tstring = std::wstring;
#else
using _tstring = std::string;
#endif

// CPU 使用率
#define PERFM_PATH_CPU_UTILITY                      "\\Processor Information(_Total)\\% Processor Utility"

// CPU 性能
#define PERFM_PATH_CPU_PERFORMANCE                  "\\Processor Information(_Total)\\% Processor Performance"

// CPU 主频
#define PERFM_PATH_CPU_FREQUENCY                    "\\Processor Information(_Total)\\Processor Frequency"

// 磁盘读写
#define PERFM_PATH_DISK_READ_RATE                   "\\PhysicalDisk(_Total)\\Disk Read Bytes/sec"
#define PERFM_PATH_DISK_WRITE_RATE                  "\\PhysicalDisk(_Total)\\Disk Write Bytes/sec"

// 网络收发
#define PERFM_PATH_NETWORK_RECV_RATE                "\\Network Interface(*)\\Bytes Received/sec"
#define PERFM_PATH_NETWORK_SENT_RATE                "\\Network Interface(*)\\Bytes Sent/sec"

// GPU 使用率
#define PERFM_PATH_GPU_UTILITY                                  "\\GPU Engine(*)\\Utilization Percentage"
#define PERFM_PATH_GPU_3D_UTILITY                               "\\GPU Engine(*_3D)\\Utilization Percentage"
#define PERFM_PATH_GPU_COPY_UTILITY                             "\\GPU Engine(*_Copy)\\Utilization Percentage"
#define PERFM_PATH_GPU_HIGH_PRIORITY_3D_UTILITY                 "\\GPU Engine(*_High Priority 3D)\\Utilization Percentage"
#define PERFM_PATH_GPU_HIGH_PRIORITY_COMPUTE_UTILITY            "\\GPU Engine(*_High Priority Compute)\\Utilization Percentage"
#define PERFM_PATH_GPU_COMPUTE_UTILITY                          "\\GPU Engine(*_Compute *)\\Utilization Percentage"
#define PERFM_PATH_GPU_TIMER_UTILITY                            "\\GPU Engine(*_Timer *)\\Utilization Percentage"
#define PERFM_PATH_GPU_SECURITY_UTILITY                         "\\GPU Engine(*_Security *)\\Utilization Percentage"
#define PERFM_PATH_GPU_VIDEO_DECODE_UTILITY                     "\\GPU Engine(*_Video Decode *)\\Utilization Percentage"
#define PERFM_PATH_GPU_VIDEO_ENCODE_UTILITY                     "\\GPU Engine(*_Video Encode *)\\Utilization Percentage"
#define PERFM_PATH_GPU_VIDEO_CODEC_UTILITY                      "\\GPU Engine(*_Video Codec *)\\Utilization Percentage"

// GPU 专有内存
#define PERFM_PATH_GPU_MEMORY_DEDICATED_USAGE_UTILITY           "\\GPU Adapter Memory(*)\\Dedicated Usage"
// GPU 共享内存
#define PERFM_PATH_GPU_MEMORY_SHARE_USAGE_UTILITY               "\\GPU Adapter Memory(*)\\Shared Usage"
// GPU 总提交内存
#define PERFM_PATH_GPU_MEMORY_TOTAL_COMMITTED_USAGE_UTILITY     "\\GPU Adapter Memory(*)\\Total Committed"

#ifdef UNICODE
using PerfMonInfo = std::map<std::wstring, HCOUNTER> ;
#else
using PerfMonInfo = std::map<std::string, HCOUNTER>;
#endif

class CPerformHelper
{
public:
    CPerformHelper();
    virtual ~CPerformHelper();

    // 初始化
    bool Initialize();
    
    // 反初始化
    void Uninitialize();

    // 添加性能计数器
    bool AddCounter(const _tstring& strCounterPath);

    // 移除性能计数器
    bool RemoveCounter(const _tstring& strCounterPath);

    // 设置性能采集时间间隔
    void SetCollectInterval(DWORD millisecond = 1000);

    // 获取性能计数器数值
    bool GetFormattedCounterValue(const _tstring&  strCounterPath, DWORD dwFormat, PPDH_FMT_COUNTERVALUE pValue);

    // 获取性能计数器数值数组
    bool GetFormattedCounterArray(const _tstring&  strCounterPath, DWORD dwFormat, PPDH_FMT_COUNTERVALUE pValue);

    // 开始采集数据
    bool StartCollect();

private:

    void _Sleep(int millisecond);

private:
    HQUERY m_hQuery;
    bool m_fQuit;
    DWORD m_msCollectInterval;
    std::mutex m_Mutex;
    PerfMonInfo m_hPerfMonInfos;
    std::thread m_task;
};
