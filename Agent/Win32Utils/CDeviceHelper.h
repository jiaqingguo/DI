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

// �豸������Ϣ
using DEVICE_BASEBOARD_INFO = struct
{
    _tstring BaseBoardManufacturer;     //����������
    _tstring BaseBoardProduct;          //�����Ʒ
    _tstring BaseBoardVersion;          //����汾
};

// �豸BIOS��Ϣ
using DEVICE_BIOS_INFO = struct
{
    _tstring Manufacturer;              //������
    _tstring BIOSVersion;               //�汾
    _tstring SerialNumber;              //���к�
    struct {
        uint16_t nYear;
        uint16_t nMonth;
        uint16_t nDay;
        uint16_t nHour;
        uint16_t nMinute;
        uint16_t nSecond;
    }BIOSReleaseDate;                   //��������
    int BiosMajorRelease;               //���汾��
    int BiosMinorRelease;               //�Ӱ汾��
    int ECFirmwareMajorRelease;         //EC���汾��
    int ECFirmwareMinorRelease;         //EC�Ӱ汾��
};

// �豸ϵͳ��Ϣ
using DEVICE_SYSTEM_INFO = struct
{
    _tstring    SystemFamily;           // ����
    _tstring    SystemManufacturer;     // ������
    _tstring    SystemProductName;      // ��Ʒ��
    _tstring    SystemSKU;              // SKU
    _tstring    SystemVersion;          // ϵͳ�汾
};

// CPU��Ϣ
using DEVICE_CPU_INFO = struct
{
    _tstring Name;                      // CPU��
    uint32_t MaxClockSpeed;             // ��Ƶ�ٶ�
    uint32_t NumberOfCores;             // �����������
    uint32_t ThreadCount;               // �߳�����
};

// �����ڴ�
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

// �����ڴ�
using DEVICE_PHYSICAL_MEMORY_INFO = struct
{
    std::vector<DEVICE_PHYSICAL_MEMORY_ITEM> Items;        // �ڴ�
    uint64_t Capacity;                                     // �ڴ�����
};

// ��Ƶ������
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

// ��Ƶ������
using DEVICE_VIDEO_CONTROLLER_INFO = struct
{
    std::vector<DEVICE_VIDEO_CONTROLLER_ITEM> Items;        // �ڴ�
};

// �豸��Ϣ
using DEVICE_INFO = struct
{
    DEVICE_BASEBOARD_INFO Baseboard;                        // ����
    DEVICE_BIOS_INFO Bios;                                  // BIOS
    DEVICE_SYSTEM_INFO System;                              // ϵͳ
    DEVICE_CPU_INFO Cpu;                                    // CPU
    DEVICE_PHYSICAL_MEMORY_INFO Memory;                     // �ڴ�
    DEVICE_VIDEO_CONTROLLER_INFO VideoController;           // ��Ƶ������
};

// ��Ƶ��������Ϣ
using VIDEO_OUTPUT_DESC_INFO = struct
{
    DXGI_OUTPUT_DESC                OutputDesc;            // ����������
    std::vector<DXGI_MODE_DESC>     DisplayModeList;       // ��ʾģʽ�б�
};

// ��Ƶ��������Ϣ
using VIDEO_ADAPTER_DESC_INFO = struct
{
    DXGI_ADAPTER_DESC                       AdapterDesc;            // ����������
    std::vector<VIDEO_OUTPUT_DESC_INFO>     OutputDesc;             // �������
};

class CDeviceHelper
{
public:

    CDeviceHelper();
    virtual ~CDeviceHelper();

    // ��ʼ��
    bool Initialize();

    // ����ʼ��
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

