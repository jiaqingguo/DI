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
// ���ò�ѯ�ο���
// ============================================================================
// ����ϵͳ��
// https://learn.microsoft.com/zh-cn/windows/win32/cimwin32prov/operating-system-classes
//
// �����ϵͳӲ����
// https://learn.microsoft.com/zh-cn/windows/win32/cimwin32prov/computer-system-hardware-classes

class CWmiClassHelper
{
public:
    explicit CWmiClassHelper(IWbemClassObject* pObj);

    // ��ȡ��ϵͳ����
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

    // ��ȡϵͳ����
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

    // ��ӡ����
    void PrintProperty() const;
    void PrintPropertySystemOnly() const;
    void PrintPropertyNonSystemOnly() const;
    void ConsolePrint(LPCTSTR pFormat, ...) const;
    
private:

    // ��ӡ
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
    // @brief:  ��ѯ
    // @param:  strClass         ����, ��: SELECT * FROM Win32_Bios
    // @ret:    bool   �����Ƿ�ɹ�
    bool ExecQuery(
        const _tstring& strSql, 
        std::function<void(
            uint64_t nIndex,            //�������
            const CWmiClassHelper& obj  //�����
            )> cb
    );
    
    //
    // @brief:  ��ѯָ��������
    // @param:  strClass         ����, ��: Win32_Bios
    // @ret:    bool   �����Ƿ�ɹ�
    bool QueryClass(
        const _tstring& strClass, 
        std::function<void(
            uint64_t nIndex,            //�������
            const CWmiClassHelper& obj  //�����
            )> cb
    );
    
private:
    bool m_bInit;           // ��ʼ�����
    IWbemServices* m_pSvc;  // �ͻ��˺��ṩ����ʹ�õ� WMI ����
    IWbemLocator* m_pLoc;   // ָ���ض������� WMI �� IWbemServices �ӿڵĳ�ʼ�����ռ�ָ��
};
