#include "CDeviceHelper.h"
#include <intrin.h>
#include <powerbase.h>
#include <time.h>

#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "PowrProf.lib")

std::vector<VIDEO_ADAPTER_DESC_INFO> CDeviceHelper::GetAllVideoAdapterDesc()
{
    std::vector<VIDEO_ADAPTER_DESC_INFO> infoResult;
    IDXGIFactory* pFactory = NULL;
    UINT nAdapter = 0;
    HRESULT hr = S_OK;

    do
    {
        hr = ::CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));
        if (FAILED(hr))
        {
            break;
        }

        VIDEO_ADAPTER_DESC_INFO AdapterDescInfo;
        DXGI_ADAPTER_DESC lastAdapterDesc = { 0 };
        IDXGIAdapter* pAdapter = NULL;
        while (DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters(nAdapter++, &pAdapter))
        {
            pAdapter->GetDesc(&AdapterDescInfo.AdapterDesc);

            UINT nOutput = 0;
            IDXGIOutput* pOutput = NULL;
            std::vector<VIDEO_OUTPUT_DESC_INFO> OutputDesc;

            // 获取输出描述信息
            while(DXGI_ERROR_NOT_FOUND != pAdapter->EnumOutputs(nOutput++, &pOutput))
            {
                VIDEO_OUTPUT_DESC_INFO outputDescInfo;
                UINT uModeNum       = 0;
                DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
                UINT flags         = DXGI_ENUM_MODES_INTERLACED;

                // 获取输出描述信息
                pOutput->GetDesc(&outputDescInfo.OutputDesc);

                // 获取显示模式列表
                pOutput->GetDisplayModeList(format, flags, &uModeNum, NULL);
                outputDescInfo.DisplayModeList.resize(uModeNum);
                pOutput->GetDisplayModeList(format, flags, &uModeNum, &outputDescInfo.DisplayModeList[0]);

                OutputDesc.push_back(outputDescInfo);
                pOutput->Release();
            }

            pAdapter->Release();
            AdapterDescInfo.OutputDesc = OutputDesc;
            infoResult.push_back(AdapterDescInfo);

            lastAdapterDesc = AdapterDescInfo.AdapterDesc;
        }

    } while (false);

    if (NULL != pFactory)
    {
        pFactory->Release();
    }

    return infoResult;
}

static std::string _WStrToMultiStr(UINT CodePage, const std::wstring& str)
{
    int cbMultiByte = ::WideCharToMultiByte(CodePage, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
    std::string strResult(cbMultiByte, 0);
    size_t nConverted = ::WideCharToMultiByte(CodePage, 0, str.c_str(), (int)str.size(), &strResult[0], (int)strResult.size(), NULL, NULL);
    strResult.resize(nConverted);
    return strResult;
}

static std::wstring _MultiStrToWStr(UINT CodePage, const std::string& str)
{
    int cchWideChar = ::MultiByteToWideChar(CodePage, 0, str.c_str(), -1, NULL, 0);
    std::wstring strResult(cchWideChar, 0);
    size_t nConverted = ::MultiByteToWideChar(CodePage, 0, str.c_str(), (int)str.size(), &strResult[0], (int)strResult.size());
    strResult.resize(nConverted);
    return strResult;
}

static std::wstring TStrToWStr(const _tstring& str)
{
#ifdef _UNICODE
    return str;
#else
    return _MultiStrToWStr(CP_ACP, str);
#endif
}

static std::string TStrToAStr(const _tstring& str)
{
#ifdef _UNICODE
    return _WStrToMultiStr(CP_ACP, str);
#else
    return str;
#endif
}

static _tstring WStrToTStr(const std::wstring& str)
{
#ifdef _UNICODE
    return str;
#else
    return _WStrToMultiStr(CP_ACP, str);
#endif
}

static _tstring AStrToTStr(const std::string& str)
{
#ifdef _UNICODE
    return _MultiStrToWStr(CP_ACP, str);
#else
    return str;
#endif
}

CDeviceHelper::CDeviceHelper()
{

}

CDeviceHelper::~CDeviceHelper()
{
    Uninitialize();
}

bool CDeviceHelper::Initialize()
{
    if (!m_Query.Initialize())
    {
        return false;
    }

    return true;
}

void CDeviceHelper::Uninitialize()
{
    m_Query.Uninitialize();
}

_tstring GetCpuName()
{
    std::string cpuName;
    int cpuInfo[4] = { 0 };
    __cpuid(cpuInfo, 0x80000000);
    unsigned int extMaxCpuID = cpuInfo[0];
    if (extMaxCpuID >= 0x80000004)
    {
        char cpuBrand[0x40] = { 0 };
        for (unsigned int i = 0x80000002; i <= 0x80000004; ++i)
        {
            __cpuid(cpuInfo, i);
            memcpy(cpuBrand + (i - 0x80000002) * 16, cpuInfo, sizeof(cpuInfo));
        }

        // 去除末尾空格
        for (int i = _countof(cpuBrand) - 1; i >=0; i--)
        {
            if (!(' ' == cpuBrand[i] || '\0' == cpuBrand[i]))
            {
                break;
            }

            cpuBrand[i] = '\0';
        }

        cpuName = cpuBrand;
    }

    return AStrToTStr(cpuName);
}

DEVICE_BASEBOARD_INFO CDeviceHelper::GetBaseBoardInfo()
{
    DEVICE_BASEBOARD_INFO infoResult;

    m_Query.ExecQuery(_T("SELECT * FROM Win32_BaseBoard"),
        [&infoResult](uint64_t nIndex,
            const CWmiClassHelper& obj) ->void {

                infoResult.BaseBoardManufacturer = obj.GetString(_T("Manufacturer"));
                infoResult.BaseBoardProduct = obj.GetString(_T("Product"));
                infoResult.BaseBoardVersion = obj.GetString(_T("Version"));

        });

    return infoResult;
}

DEVICE_BIOS_INFO CDeviceHelper::GetBiosInfo()
{
    DEVICE_BIOS_INFO infoResult;
    infoResult.ECFirmwareMajorRelease = 0;
    infoResult.ECFirmwareMinorRelease = 0;
    infoResult.BIOSReleaseDate.nYear = 0;
    infoResult.BIOSReleaseDate.nMonth = 0;
    infoResult.BIOSReleaseDate.nDay = 0;
    infoResult.BIOSReleaseDate.nHour = 0;
    infoResult.BIOSReleaseDate.nMinute = 0;
    infoResult.BIOSReleaseDate.nSecond = 0;
    infoResult.BiosMajorRelease = 0;
    infoResult.BiosMinorRelease = 0;

    m_Query.ExecQuery(_T("SELECT * FROM Win32_BIOS"),
        [&infoResult](uint64_t nIndex,
            const CWmiClassHelper& obj) ->void {

                _tstring strReleaseDate = obj.GetString(_T("ReleaseDate"));
                _stscanf_s(strReleaseDate.c_str(), _T("%4hd%2hd%2hd%2hd%2hd%2hd"), 
                    &infoResult.BIOSReleaseDate.nYear, 
                    &infoResult.BIOSReleaseDate.nMonth, 
                    &infoResult.BIOSReleaseDate.nDay, 
                    &infoResult.BIOSReleaseDate.nHour,
                    &infoResult.BIOSReleaseDate.nMinute, 
                    &infoResult.BIOSReleaseDate.nSecond
                );

                infoResult.Manufacturer = obj.GetString(_T("Manufacturer"));
                infoResult.SerialNumber = obj.GetString(_T("SerialNumber"));
                infoResult.BIOSVersion = obj.GetString(_T("SMBIOSBIOSVersion"));
                infoResult.BiosMajorRelease = obj.GetUInt8(_T("SystemBiosMajorVersion"));
                infoResult.BiosMinorRelease = obj.GetUInt8(_T("SystemBiosMinorVersion"));
                infoResult.ECFirmwareMajorRelease = obj.GetUInt8(_T("EmbeddedControllerMajorVersion"));
                infoResult.ECFirmwareMinorRelease = obj.GetUInt8(_T("EmbeddedControllerMinorVersion"));
        });

    return infoResult;
}

DEVICE_SYSTEM_INFO CDeviceHelper::GetSystemInfo()
{
    DEVICE_SYSTEM_INFO infoResult;

    m_Query.ExecQuery(_T("SELECT SystemFamily,Manufacturer,SystemSKUNumber FROM Win32_ComputerSystem"),
        [&infoResult](uint64_t nIndex,
            const CWmiClassHelper& obj) ->void {

                infoResult.SystemFamily = obj.GetString(_T("SystemFamily"));
                infoResult.SystemManufacturer = obj.GetString(_T("Manufacturer"));
                infoResult.SystemSKU = obj.GetString(_T("SystemSKUNumber"));
        });

    m_Query.ExecQuery(_T("SELECT Name,Version FROM Win32_ComputerSystemProduct"),
        [&infoResult](uint64_t nIndex,
            const CWmiClassHelper& obj) ->void {

                infoResult.SystemProductName = obj.GetString(_T("Name"));
                infoResult.SystemVersion = obj.GetString(_T("Version"));
        });

    return infoResult;
}

DEVICE_CPU_INFO CDeviceHelper::GetCpuInfo()
{
    DEVICE_CPU_INFO infoResult;
    infoResult.NumberOfCores = 0;
    infoResult.ThreadCount = 0;
    infoResult.MaxClockSpeed = 0;

    m_Query.ExecQuery(_T("SELECT Name,MaxClockSpeed,NumberOfCores,ThreadCount FROM Win32_Processor"),
        [&infoResult](uint64_t nIndex,
            const CWmiClassHelper& obj) ->void {

                infoResult.Name = obj.GetString(_T("Name"));
                infoResult.MaxClockSpeed = obj.GetUIntEx(_T("MaxClockSpeed"));
                infoResult.NumberOfCores = obj.GetUIntEx(_T("NumberOfCores"));
                infoResult.ThreadCount   = obj.GetUIntEx(_T("ThreadCount"));

        });

    size_t nSize = infoResult.Name.size();
    for (auto it = infoResult.Name.rbegin(); it != infoResult.Name.rend(); it++)
    {
        if (*it != _T(' '))
        {
            break;
        }
        nSize--;
    }

    infoResult.Name.resize(nSize);

    return infoResult;
}

DEVICE_PHYSICAL_MEMORY_INFO CDeviceHelper::GetPhysicalMemoryInfos()
{
    DEVICE_PHYSICAL_MEMORY_INFO infoResult;
    infoResult.Capacity = 0;

    m_Query.ExecQuery(_T("SELECT * FROM Win32_PhysicalMemory"),
        [&infoResult](uint64_t nIndex,
            const CWmiClassHelper& obj) ->void {

                DEVICE_PHYSICAL_MEMORY_ITEM info;

                info.Attributes             = obj.GetUIntEx(_T("Attributes"));
                info.BankLabel              = obj.GetString(_T("BankLabel"));
                info.Capacity               = obj.GetUIntEx(_T("Capacity"));
                info.Caption                = obj.GetString(_T("Caption"));
                info.ConfiguredClockSpeed   = obj.GetUIntEx(_T("ConfiguredClockSpeed"));
                info.ConfiguredVoltage      = obj.GetUIntEx(_T("ConfiguredVoltage"));
                info.CreationClassName      = obj.GetString(_T("CreationClassName"));
                info.DataWidth              = obj.GetUIntEx(_T("DataWidth"));
                info.Description            = obj.GetString(_T("Description"));
                info.DeviceLocator          = obj.GetString(_T("DeviceLocator"));
                info.FormFactor             = obj.GetUIntEx(_T("FormFactor"));
                info.Manufacturer           = obj.GetString(_T("Manufacturer"));
                info.MaxVoltage             = obj.GetUIntEx(_T("MaxVoltage"));
                info.MemoryType             = obj.GetUIntEx(_T("MemoryType"));
                info.MinVoltage             = obj.GetUIntEx(_T("MinVoltage"));
                info.Name                   = obj.GetString(_T("Name"));
                info.PartNumber             = obj.GetString(_T("PartNumber"));
                info.SerialNumber           = obj.GetString(_T("SerialNumber"));
                info.SMBIOSMemoryType       = obj.GetUIntEx(_T("SMBIOSMemoryType"));
                info.Speed                  = obj.GetUIntEx(_T("Speed"));
                info.Tag                    = obj.GetString(_T("Tag"));
                info.TotalWidth             = obj.GetUIntEx(_T("TotalWidth"));
                info.TypeDetail             = obj.GetUIntEx(_T("TypeDetail"));
                info.Version                = obj.GetString(_T("Version"));
                info.Status                 = obj.GetString(_T("Status"));
                info.SKU                    = obj.GetString(_T("SKU"));
                info.Model                  = obj.GetString(_T("Model"));
                info.OtherIdentifyingInfo   = obj.GetString(_T("OtherIdentifyingInfo"));

                infoResult.Items.push_back(info);

                infoResult.Capacity += info.Capacity;
        });

    return infoResult;
}

DEVICE_VIDEO_CONTROLLER_INFO CDeviceHelper::GetVideoControllerInfos()
{
    DEVICE_VIDEO_CONTROLLER_INFO infoResult;

    m_Query.ExecQuery(_T("SELECT * FROM Win32_VideoController"),
        [&infoResult](uint64_t nIndex,
            const CWmiClassHelper& obj) ->void {

                DEVICE_VIDEO_CONTROLLER_ITEM info;

                info.Description                    =   obj.GetString(_T("Description"));
                info.AdapterCompatibility           =   obj.GetString(_T("AdapterCompatibility"));
                info.AdapterDACType                 =   obj.GetString(_T("AdapterDACType"));
                info.DeviceID                       =   obj.GetString(_T("DeviceID"));
                info.DriverVersion                  =   obj.GetString(_T("DriverVersion"));
                info.InstalledDisplayDrivers        =   obj.GetString(_T("InstalledDisplayDrivers"));
                info.Name                           =   obj.GetString(_T("Name"));
                info.PNPDeviceID                    =   obj.GetString(_T("PNPDeviceID"));
                info.VideoModeDescription           =   obj.GetString(_T("VideoModeDescription"));
                info.VideoProcessor                 =   obj.GetString(_T("VideoProcessor"));
                info.AdapterRAM                     =   obj.GetUIntEx(_T("AdapterRAM"));
                info.CurrentNumberOfColors          =   obj.GetUIntEx(_T("CurrentNumberOfColors"));
                info.CurrentBitsPerPixel            =   obj.GetUIntEx(_T("CurrentBitsPerPixel"));
                info.CurrentHorizontalResolution    =   obj.GetUIntEx(_T("CurrentHorizontalResolution"));
                info.CurrentNumberOfColumns         =   obj.GetUIntEx(_T("CurrentNumberOfColumns"));
                info.CurrentNumberOfRows            =   obj.GetUIntEx(_T("CurrentNumberOfRows"));
                info.CurrentRefreshRate             =   obj.GetUIntEx(_T("CurrentRefreshRate"));
                info.CurrentScanMode                =   obj.GetUIntEx(_T("CurrentScanMode"));
                info.CurrentVerticalResolution      =   obj.GetUIntEx(_T("CurrentVerticalResolution"));
                info.MaxRefreshRate                 =   obj.GetUIntEx(_T("MaxRefreshRate"));
                info.MinRefreshRate                 =   obj.GetUIntEx(_T("MinRefreshRate"));
                info.VideoArchitecture              =   obj.GetUIntEx(_T("VideoArchitecture"));
                info.VideoMemoryType                =   obj.GetUIntEx(_T("VideoMemoryType"));
                info.Availability                   =   obj.GetUIntEx(_T("Availability"));

                infoResult.Items.push_back(info);
        });

    return infoResult;
}

DEVICE_INFO CDeviceHelper::GetDeviceInfo()
{
    DEVICE_INFO infoResult;

    clock_t tmTotalBegin = ::clock();

    clock_t tmBegin = ::clock();
    clock_t tmEnd = ::clock();

    infoResult.Baseboard = GetBaseBoardInfo();
    tmEnd = ::clock();
    _tprintf(_T("GetBaseBoardInfo time: %d\r\n"), tmEnd - tmBegin);
    tmBegin = ::clock();

    infoResult.Bios = GetBiosInfo();
    tmEnd = ::clock();
    _tprintf(_T("GetBiosInfo time: %d\r\n"), tmEnd - tmBegin);
    tmBegin = ::clock();

    infoResult.System = GetSystemInfo();
    tmEnd = ::clock();
    _tprintf(_T("GetSystemInfo time: %d\r\n"), tmEnd - tmBegin);
    tmBegin = ::clock();

    infoResult.Cpu = GetCpuInfo();
    tmEnd = ::clock();
    _tprintf(_T("GetCpuInfo time: %d\r\n"), tmEnd - tmBegin);
    tmBegin = ::clock();

    infoResult.Memory = GetPhysicalMemoryInfos();
    tmEnd = ::clock();
    _tprintf(_T("GetPhysicalMemoryInfos time: %d\r\n"), tmEnd - tmBegin);
    tmBegin = ::clock();

    infoResult.VideoController = GetVideoControllerInfos();
    tmEnd = ::clock();
    _tprintf(_T("GetVideoControllerInfos time: %d\r\n"), tmEnd - tmBegin);
    tmBegin = ::clock();

    tmEnd = ::clock();
    _tprintf(_T("GetDeviceInfo time: %d\r\n"), tmEnd - tmTotalBegin);

    return infoResult;
}
