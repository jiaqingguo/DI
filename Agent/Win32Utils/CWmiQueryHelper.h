#pragma once
#include <Wbemidl.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <functional>
#include <stdint.h>

#ifdef _UNICODE
using _tstring = std::wstring;
#else
using _tstring = std::string;
#endif

// ============================================================================
// 常用查询参考类
// ============================================================================
// 操作系统类
// https://learn.microsoft.com/zh-cn/windows/win32/cimwin32prov/operating-system-classes
//
// 计算机系统硬件类
// https://learn.microsoft.com/zh-cn/windows/win32/cimwin32prov/computer-system-hardware-classes

class CWmiClassHelper
{
public:
    explicit CWmiClassHelper(IWbemClassObject* pObj);

    // 获取非系统属性
    VARTYPE GetType(const _tstring& strName) const;
    BOOL GetBool(const _tstring& strName) const;
    INT8 GetInt8(const _tstring& strName) const;
    UINT8 GetUInt8(const _tstring& strName) const;
    SHORT GetInt16(const _tstring& strName) const;
    USHORT GetUInt16(const _tstring& strName) const;
    LONG GetInt32(const _tstring& strName) const;
    ULONG GetUInt32(const _tstring& strName) const;
    INT64 GetInt64(const _tstring& strName) const;
    UINT64 GetUInt64(const _tstring& strName) const;
    DOUBLE GetFloat(const _tstring& strName) const;
    _tstring GetString(const _tstring& strName) const;

    INT64 GetIntEx(const _tstring& strName) const;
    UINT64 GetUIntEx(const _tstring& strName) const;

    std::vector<_tstring> GetStringArray(const _tstring& strName) const;
    std::vector<short> GetShortArray(const _tstring& strName) const;

    // 获取系统属性
    _tstring GetClass() const;
    _tstring GetSuperClass() const;
    _tstring GetNameSpace() const;
    _tstring GetPath() const;
    _tstring GetServer() const;
    _tstring GetRelPath() const;
    int GetPropertyCount() const;
    int GetGenus() const;
    _tstring GetDynasty() const;
    _tstring GetDerivation() const;

    // 打印属性
    void PrintProperty() const;
    void PrintPropertySystemOnly() const;
    void PrintPropertyNonSystemOnly() const;
    void ConsolePrint(LPCTSTR pFormat, ...) const;
    
private:

    // 打印
    void _PrintProperty(long lFlags) const;
    void _Print(const VARIANT& val) const;
    void _PrintArray(const VARIANT& val) const;
    void _Print(const _tstring& strName) const;

private:
    IWbemClassObject* m_pObj;
};

class CWmiQueryHelper
{
public:

    CWmiQueryHelper();
    ~CWmiQueryHelper();

    bool Initialize();
    void Uninitialize();

    //
    // @brief:  查询
    // @param:  strClass         类名, 如: SELECT * FROM Win32_Bios
    // @ret:    bool   操作是否成功
    bool ExecQuery(
        const _tstring& strSql, 
        std::function<void(
            uint64_t nIndex,            //结果索引
            const CWmiClassHelper& obj  //结果类
            )> cb
    );
    
    //
    // @brief:  查询指定类属性
    // @param:  strClass         类名, 如: Win32_Bios
    // @ret:    bool   操作是否成功
    bool QueryClass(
        const _tstring& strClass, 
        std::function<void(
            uint64_t nIndex,            //结果索引
            const CWmiClassHelper& obj  //结果类
            )> cb
    );
    
private:
    bool m_bInit;           // 初始化结果
    IWbemServices* m_pSvc;  // 客户端和提供程序使用的 WMI 服务
    IWbemLocator* m_pLoc;   // 指向特定主机上 WMI 的 IWbemServices 接口的初始命名空间指针
};
