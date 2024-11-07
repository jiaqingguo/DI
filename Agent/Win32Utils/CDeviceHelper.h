#pragma once
#include <windows.h>
#include <string>
#include "CWmiQueryHelper.h"
#include <stdint.h>
#include <DXGI.h>

#ifdef _UNICODE
using _tstring = std::wstring;
#else
using _tstring = std::string;
#endif

// 设备主板信息
using DEVICE_BASEBOARD_INFO = struct
{
    _tstring BaseBoardManufacturer;     //主板制造商
    _tstring BaseBoardProduct;          //主板产品
    _tstring BaseBoardVersion;          //主板版本
};

// 设备BIOS信息
using DEVICE_BIOS_INFO = struct
{
    _tstring Manufacturer;              //制造商
    _tstring BIOSVersion;               //版本
    _tstring SerialNumber;              //序列号
    struct {
        uint16_t nYear;
        uint16_t nMonth;
        uint16_t nDay;
        uint16_t nHour;
        uint16_t nMinute;
        uint16_t nSecond;
    }BIOSReleaseDate;                   //发布日期
    int BiosMajorRelease;               //主版本号
    int BiosMinorRelease;               //子版本号
    int ECFirmwareMajorRelease;         //EC主版本号
    int ECFirmwareMinorRelease;         //EC子版本号
};

// 设备系统信息
using DEVICE_SYSTEM_INFO = struct
{
    _tstring    SystemFamily;           // 家族
    _tstring    SystemManufacturer;     // 制造商
    _tstring    SystemProductName;      // 产品名
    _tstring    SystemSKU;              // SKU
    _tstring    SystemVersion;          // 系统版本
};

// CPU信息
using DEVICE_CPU_INFO = struct
{
    _tstring Name;                      // CPU名
    uint32_t MaxClockSpeed;             // 主频速度
    uint32_t NumberOfCores;             // 物理核心数量
    uint32_t ThreadCount;               // 线程数量
};

// 物理内存
using DEVICE_PHYSICAL_MEMORY_ITEM = struct
{
    _tstring BankLabel;
    _tstring Caption;
    _tstring CreationClassName;
    _tstring Description;
    _tstring DeviceLocator;
    _tstring Manufacturer;
    _tstring Tag;
    _tstring Name;
    _tstring PartNumber;
    _tstring SerialNumber;
    uint64_t Capacity;
    uint32_t Attributes;
    uint32_t ConfiguredClockSpeed;
    uint32_t ConfiguredVoltage;
    uint32_t DataWidth;
    uint32_t FormFactor;
    uint32_t MaxVoltage;
    uint32_t MemoryType;
    uint32_t MinVoltage;
    uint32_t SMBIOSMemoryType;
    uint32_t Speed;
    uint32_t TotalWidth;
    uint32_t TypeDetail;
    _tstring Status;
    _tstring Version;
    _tstring SKU;
    _tstring Model;
    _tstring OtherIdentifyingInfo;
};

// 物理内存
using DEVICE_PHYSICAL_MEMORY_INFO = struct
{
    std::vector<DEVICE_PHYSICAL_MEMORY_ITEM> Items;        // 内存
    uint64_t Capacity;                                     // 内存容量
};

// 视频控制器
using DEVICE_VIDEO_CONTROLLER_ITEM = struct
{
    _tstring Description;
    _tstring AdapterCompatibility;
    _tstring AdapterDACType;
    _tstring DeviceID;
    _tstring DriverVersion;
    _tstring InstalledDisplayDrivers;
    _tstring Name;
    _tstring PNPDeviceID;
    _tstring VideoModeDescription;
    _tstring VideoProcessor;
    uint64_t AdapterRAM;
    uint64_t CurrentNumberOfColors;
    uint32_t CurrentBitsPerPixel;
    uint32_t CurrentHorizontalResolution;
    uint32_t CurrentNumberOfColumns;
    uint32_t CurrentNumberOfRows;
    uint32_t CurrentRefreshRate;
    uint32_t CurrentScanMode;
    uint32_t CurrentVerticalResolution;
    uint32_t MaxRefreshRate;
    uint32_t MinRefreshRate;
    uint16_t VideoArchitecture;
    uint16_t VideoMemoryType;
    uint16_t Availability;
};

// 视频控制器
using DEVICE_VIDEO_CONTROLLER_INFO = struct
{
    std::vector<DEVICE_VIDEO_CONTROLLER_ITEM> Items;        // 内存
};

// 设备信息
using DEVICE_INFO = struct
{
    DEVICE_BASEBOARD_INFO Baseboard;                        // 主板
    DEVICE_BIOS_INFO Bios;                                  // BIOS
    DEVICE_SYSTEM_INFO System;                              // 系统
    DEVICE_CPU_INFO Cpu;                                    // CPU
    DEVICE_PHYSICAL_MEMORY_INFO Memory;                     // 内存
    DEVICE_VIDEO_CONTROLLER_INFO VideoController;           // 视频控制器
};

// 视频适配器信息
using VIDEO_OUTPUT_DESC_INFO = struct
{
    DXGI_OUTPUT_DESC                OutputDesc;            // 适配器描述
    std::vector<DXGI_MODE_DESC>     DisplayModeList;       // 显示模式列表
};

// 视频适配器信息
using VIDEO_ADAPTER_DESC_INFO = struct
{
    DXGI_ADAPTER_DESC                       AdapterDesc;            // 适配器描述
    std::vector<VIDEO_OUTPUT_DESC_INFO>     OutputDesc;             // 输出描述
};

class CDeviceHelper
{
public:

    CDeviceHelper();
    virtual ~CDeviceHelper();

    // 初始化
    bool Initialize();

    // 反初始化
    void Uninitialize();

    static std::vector<VIDEO_ADAPTER_DESC_INFO> GetAllVideoAdapterDesc();

    DEVICE_INFO GetDeviceInfo();
    DEVICE_BASEBOARD_INFO GetBaseBoardInfo();
    DEVICE_BIOS_INFO GetBiosInfo();
    DEVICE_CPU_INFO GetCpuInfo();
    DEVICE_SYSTEM_INFO GetSystemInfo();
    DEVICE_PHYSICAL_MEMORY_INFO GetPhysicalMemoryInfos();
    DEVICE_VIDEO_CONTROLLER_INFO GetVideoControllerInfos();

private:
    CWmiQueryHelper m_Query;
};

