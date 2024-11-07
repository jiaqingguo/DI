#include "CWmiQueryHelper.h"
#include <Wbemidl.h>
#include <comdef.h>

#pragma comment(lib, "wbemuuid.lib")

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

static _tstring WStrToTStr(const std::wstring& str)
{
#ifdef _UNICODE
    return str;
#else
    return _WStrToMultiStr(CP_ACP, str);
#endif
}

void CWmiClassHelper::ConsolePrint(LPCTSTR pFormat, ...) const
{
    size_t nCchCount = MAX_PATH;
    _tstring strResult(nCchCount, 0);
    va_list args;

    va_start(args, pFormat);

    do
    {
        //格式化输出字符串
        int nSize = _vsntprintf_s(&strResult[0], nCchCount, _TRUNCATE, pFormat, args);
        if (-1 != nSize)
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            ::WriteConsole(console, strResult.c_str(), nSize, NULL, NULL);
            break;
        }

        //缓冲大小超限终止
        if (nCchCount >= INT32_MAX)
        {
            break;
        }

        //重新分配缓冲
        nCchCount *= 2;
        strResult.resize(nCchCount);

    } while (true);

    va_end(args);
}

CWmiClassHelper::CWmiClassHelper(IWbemClassObject* pObj)
{
    m_pObj = pObj;
}

_tstring CWmiClassHelper::GetString(const _tstring& strName) const
{
    _tstring strValue;
    HRESULT hr = S_OK;

    VARIANT vtProp;
    CIMTYPE cType = 0;
    long lFlavor = 0;

    ::VariantInit(&vtProp);

    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, &cType, &lFlavor);
    if (SUCCEEDED(hr) && VT_BSTR == vtProp.vt)
    {
        strValue = WStrToTStr(vtProp.bstrVal);
    }

    ::VariantClear(&vtProp);

    return strValue;
}

VARTYPE CWmiClassHelper::GetType(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    VARTYPE vType = VARENUM::VT_NULL;

    VARIANT vtProp;
    ::VariantInit(&vtProp);

    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr))
    {
        vType = vtProp.vt;
    }

    ::VariantClear(&vtProp);
    return vType;
}

BOOL CWmiClassHelper::GetBool(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    BOOL bValue = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_BOOL == vtProp.vt)
    {
        bValue = vtProp.boolVal;
    }

    ::VariantClear(&vtProp);

    return bValue;
}

INT8 CWmiClassHelper::GetInt8(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    INT8 cVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_I1 == vtProp.vt)
    {
        cVal = vtProp.cVal;
    }

    ::VariantClear(&vtProp);

    return cVal;
}

UINT8 CWmiClassHelper::GetUInt8(const _tstring& strName) const
{

    HRESULT hr = S_OK;
    UINT8 bVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_UI1 == vtProp.vt)
    {
        bVal = vtProp.bVal;
    }

    ::VariantClear(&vtProp);

    return bVal;
}

SHORT CWmiClassHelper::GetInt16(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    SHORT iVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_I2 == vtProp.vt)
    {
        iVal = vtProp.iVal;
    }
    ::VariantClear(&vtProp);

    return iVal;
}

USHORT CWmiClassHelper::GetUInt16(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    USHORT uiVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_I2 == vtProp.vt)
    {
        uiVal = vtProp.uiVal;
    }
    ::VariantClear(&vtProp);

    return uiVal;
}

INT64 CWmiClassHelper::GetIntEx(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    INT64 val = 0;

    VARIANT vtProp;
    CIMTYPE cType = 0;
    long lFlavor = 0;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, &cType, &lFlavor);

    if (SUCCEEDED(hr))
    {
        switch (cType)
        {
        case CIM_SINT8:
        case CIM_SINT16:
        case CIM_SINT32:
        case CIM_SINT64:
        {
            if ( VT_BSTR == vtProp.vt)
            {
                val = _tcstoll(WStrToTStr(vtProp.bstrVal).c_str(), NULL, 10);
            }
            else
            {
                val = vtProp.llVal;
            }

            break;
        }
        }
    }

    ::VariantClear(&vtProp);
    return val;
}


UINT64 CWmiClassHelper::GetUIntEx(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    UINT64 val = 0;

    VARIANT vtProp;
    CIMTYPE cType = 0;
    long lFlavor = 0;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, &cType, &lFlavor);

    if (SUCCEEDED(hr))
    {
        switch (cType)
        {
        case CIM_UINT8:
        case CIM_UINT16:
        case CIM_UINT32:
        case CIM_UINT64:
        {
            if ( VT_BSTR == vtProp.vt)
            {
                val = _tcstoull(WStrToTStr(vtProp.bstrVal).c_str(), NULL, 10);
            }
            else
            {
                val = vtProp.ullVal;
            }

            break;
        }
        }
    }

    ::VariantClear(&vtProp);
    return val;
}

LONG CWmiClassHelper::GetInt32(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    LONG lVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_I4 == vtProp.vt)
    {
        lVal = vtProp.lVal;
    }
    ::VariantClear(&vtProp);
    return lVal;
}

ULONG CWmiClassHelper::GetUInt32(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    ULONG ulVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_UI4 == vtProp.vt)
    {
        ulVal = vtProp.ulVal;
    }
    ::VariantClear(&vtProp);
    return ulVal;
}

INT64 CWmiClassHelper::GetInt64(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    INT64 llVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_I8 == vtProp.vt)
    {
        llVal = vtProp.llVal;
    }
    ::VariantClear(&vtProp);
    return llVal;
}

UINT64 CWmiClassHelper::GetUInt64(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    UINT64 ullVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_UI8 == vtProp.vt)
    {
        ullVal = vtProp.ullVal;
    }
    ::VariantClear(&vtProp);
    return ullVal;
}

DOUBLE CWmiClassHelper::GetFloat(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    DOUBLE dblVal = 0;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && VT_R4 == vtProp.vt)
    {
        dblVal = vtProp.fltVal;
    }

    if (SUCCEEDED(hr) && VT_R8 == vtProp.vt)
    {
        dblVal = vtProp.dblVal;
    }

    ::VariantClear(&vtProp);
    return dblVal;
}

std::vector<short> CWmiClassHelper::GetShortArray(const _tstring& strName) const
{
    std::vector<short> shortList;
    HRESULT hr = S_OK;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && (VT_ARRAY | VT_I2) == vtProp.vt)
    {
        SAFEARRAY* pArray = vtProp.parray;
        SHORT HUGEP* pShort;

        //获取数组维数
        UINT uDim = SafeArrayGetDim(pArray);

        LONG lLBound = 0;
        LONG lUBound = 0;

        ::SafeArrayGetLBound(pArray, uDim, &lLBound);//取得指定维度的下限
        ::SafeArrayGetUBound(pArray, uDim, &lUBound);//取得指定维度的上限
        LONG lCount = lUBound - lLBound;

        SafeArrayAccessData(pArray, (void HUGEP**) & pShort);
        for (int i = 0; i <= lCount; i++)
        {
            shortList.push_back(*pShort);
            pShort++;
        }

        SafeArrayUnaccessData(pArray);
    }
    ::VariantClear(&vtProp);

    return shortList;
}

std::vector<_tstring> CWmiClassHelper::GetStringArray(const _tstring& strName) const
{
    HRESULT hr = S_OK;
    std::vector<_tstring> strList;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);
    if (SUCCEEDED(hr) && (VT_ARRAY | VT_BSTR) == vtProp.vt)
    {
        SAFEARRAY* pArray = vtProp.parray;

        //获取数组维数
        UINT uDim = SafeArrayGetDim(pArray);

        LONG lLBound = 0;
        LONG lUBound = 0;

        ::SafeArrayGetLBound(pArray, uDim, &lLBound);//取得指定维度的下限
        ::SafeArrayGetUBound(pArray, uDim, &lUBound);//取得指定维度的上限
        LONG lCount = lUBound - lLBound;

        BSTR HUGEP* pString;
        SafeArrayAccessData(pArray, (void HUGEP**) & pString);
        for (int i = 0; i <= lCount; i++)
        {
            strList.push_back(WStrToTStr(*pString));
            pString++;
        }
        SafeArrayUnaccessData(pArray);

    }
    ::VariantClear(&vtProp);

    return strList;
}

void CWmiClassHelper::_Print(const VARIANT& val) const
{
    HRESULT hr = S_OK;

    if (SUCCEEDED(hr) && VT_NULL == val.vt)
    {
        ConsolePrint(_T("NULL"));
    }

    if (SUCCEEDED(hr) && VT_BSTR == val.vt)
    {
        ConsolePrint(_T(R"("%s")"), WStrToTStr(val.bstrVal).c_str());
    }

    if (SUCCEEDED(hr) && VT_BOOL == val.vt)
    {
        ConsolePrint(_T("%s"), val.boolVal ? _T("TRUE") : _T("FALSE"));
    }

    //signed char
    if (SUCCEEDED(hr) && VT_I1 == val.vt)
    {
        ConsolePrint(_T("%d"), val.bVal);
    }

    //unsigned char
    if (SUCCEEDED(hr) && VT_UI1 == val.vt)
    {
        ConsolePrint(_T("%d"), val.bVal);
    }

    //signed short
    if (SUCCEEDED(hr) && VT_I2 == val.vt)
    {
        ConsolePrint(_T("%d"), val.iVal);
    }

    //unsigned short
    if (SUCCEEDED(hr) && VT_UI2 == val.vt)
    {
        ConsolePrint(_T("%d"), val.iVal);
    }

    //LONG
    if (SUCCEEDED(hr) && VT_I4 == val.vt)
    {
        ConsolePrint(_T("%d"), val.lVal);
    }

    //ULONG
    if (SUCCEEDED(hr) && VT_UI4 == val.vt)
    {
        ConsolePrint(_T("%u"), val.lVal);
    }

    //signed 64-bit int
    if (SUCCEEDED(hr) && VT_I8 == val.vt)
    {
        ConsolePrint(_T("%lld"), val.llVal);
    }

    //unsigned signed 64-bit int
    if (SUCCEEDED(hr) && VT_UI8 == val.vt)
    {
        ConsolePrint(_T("%llu"), val.llVal);
    }

    if (SUCCEEDED(hr) && VT_ARRAY & val.vt)
    {
        ConsolePrint(_T("{"));
        _PrintArray(val);
        ConsolePrint(_T("}"));
    }
}

void CWmiClassHelper::_PrintArray(const VARIANT& val) const
{
    HRESULT hr = S_OK;

    if (VT_ARRAY & val.vt)
    {
        VARTYPE vt = val.vt & ~VT_ARRAY;
        SAFEARRAY* pArray = val.parray;

        //获取数组维数
        UINT uDim = SafeArrayGetDim(pArray);

        //暂且只处理一维数组
        if (uDim > 1)
        {
            return;
        }

        LONG lLBound = 0;
        LONG lUBound = 0;

        ::SafeArrayGetLBound(pArray, uDim, &lLBound);//取得指定维度的下限
        ::SafeArrayGetUBound(pArray, uDim, &lUBound);//取得指定维度的上限
        LONG lCount = lUBound - lLBound;

        if (VT_BSTR == vt)
        {
            BSTR HUGEP* pString;
            hr = ::SafeArrayAccessData(pArray, (void HUGEP**) & pString);
            if (SUCCEEDED(hr))
            {
                for (int i = 0; i <= lCount; i++)
                {
                    _tstring strValue = WStrToTStr(*pString);
                    ConsolePrint(_T(R"("%s")"), strValue.c_str());
                    pString++;
                    if (i < lCount)
                    {
                        ConsolePrint(_T(", "));
                    }
                }
            }
        }

        if (VT_I2 == vt)
        {
            short HUGEP* pShort;
            hr = ::SafeArrayAccessData(pArray, (void HUGEP**) & pShort);
            if (SUCCEEDED(hr))
            {
                for (int i = 0; i <= lCount; i++)
                {
                    ConsolePrint(_T("%d"), *pShort);
                    pShort++;
                    if (i < lCount)
                    {
                        ConsolePrint(_T(", "));
                    }
                }
            }
        }

        if (VT_I4 == vt)
        {
            long HUGEP* pLong;
            hr = ::SafeArrayAccessData(pArray, (void HUGEP**) & pLong);
            if (SUCCEEDED(hr))
            {
                for (int i = 0; i <= lCount; i++)
                {
                    ConsolePrint(_T("%d"), *pLong);
                    pLong++;
                    if (i < lCount)
                    {
                        ConsolePrint(_T(", "));
                    }
                }
            }
        }

        if (VT_I8 == vt)
        {
            long long HUGEP* pLongLong;
            hr = ::SafeArrayAccessData(pArray, (void HUGEP**) & pLongLong);
            if (SUCCEEDED(hr))
            {
                for (int i = 0; i <= lCount; i++)
                {
                    ConsolePrint(_T("%lld"), *pLongLong);
                    pLongLong++;
                    if (i < lCount)
                    {
                        ConsolePrint(_T(", "));
                    }
                }
            }
        }

        SafeArrayUnaccessData(pArray);
    }
}

void CWmiClassHelper::_Print(const _tstring& strName) const
{
    HRESULT hr = S_OK;

    VARIANT vtProp;
    ::VariantInit(&vtProp);
    hr = m_pObj->Get(TStrToWStr(strName).c_str(), 0, &vtProp, 0, 0);

    ConsolePrint(_T("%s = "), strName.c_str());
    _Print(vtProp);
}

_tstring CWmiClassHelper::GetClass() const
{
    return GetString(_T("__CLASS"));
}

_tstring CWmiClassHelper::GetSuperClass() const
{
    return GetString(_T("__NAMESPACE"));
}

_tstring CWmiClassHelper::GetNameSpace() const
{
    return GetString(_T("__NAMESPACE"));
}

_tstring CWmiClassHelper::GetPath() const
{
    return GetString(_T("__PATH"));
}

_tstring CWmiClassHelper::GetServer() const
{
    return GetString(_T("__SERVER"));
}

_tstring CWmiClassHelper::GetRelPath() const
{
    return GetString(_T("__RELPATH"));
}

int CWmiClassHelper::GetPropertyCount() const
{
    return GetInt32(_T("__PROPERTY_COUNT"));
}

int CWmiClassHelper::GetGenus() const
{
    return GetInt32(_T("__GENUS"));
}

_tstring CWmiClassHelper::GetDynasty() const
{
    return GetString(_T("__DYNASTY"));
}

_tstring CWmiClassHelper::GetDerivation() const
{
    return GetString(_T("__DERIVATION"));
}

void CWmiClassHelper::PrintPropertySystemOnly() const
{
    _PrintProperty(WBEM_FLAG_ALWAYS | WBEM_FLAG_SYSTEM_ONLY);
}

void CWmiClassHelper::PrintPropertyNonSystemOnly() const
{
    _PrintProperty(WBEM_FLAG_ALWAYS | WBEM_FLAG_NONSYSTEM_ONLY);
}

void CWmiClassHelper::PrintProperty() const
{
    _PrintProperty(WBEM_FLAG_ALWAYS);
}

void CWmiClassHelper::_PrintProperty(long lFlags) const
{
    HRESULT hr = S_OK;
    SAFEARRAY* arrayNames;

    hr = m_pObj->GetNames(NULL, lFlags, NULL, &arrayNames);
    if (FAILED(hr))
    {
        return;
    }

    //获取数组维数
    UINT uDim = SafeArrayGetDim(arrayNames);

    LONG lLBound = 0;
    LONG lUBound = 0;

    //取得nDim维度的上界
    SafeArrayGetLBound(arrayNames, uDim, &lLBound);

    //取得nDim维度的下界
    SafeArrayGetUBound(arrayNames, uDim, &lUBound);

    BSTR HUGEP* pvData;
    SafeArrayAccessData(arrayNames, (void HUGEP**) & pvData);
    for (int i = 0; i <= lUBound - lLBound; i++)
    {
        _tstring strName = WStrToTStr(*pvData).c_str();
        _Print(strName);
        ConsolePrint(_T("\r\n"));
        pvData++;
    }
    SafeArrayUnaccessData(arrayNames);
}

CWmiQueryHelper::CWmiQueryHelper():
    m_pSvc(NULL),
    m_pLoc(NULL),
    m_bInit(false)
{

}

CWmiQueryHelper::~CWmiQueryHelper()
{
    Uninitialize();
}

bool CWmiQueryHelper::Initialize()
{
    HRESULT hr = S_OK;

    if (m_bInit)
    {
        return true;
    }

    hr = ::CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        return false;
    }

    do
    {
        //hr = CoInitializeSecurity(
        //    NULL,
        //    -1,                          // COM authentication
        //    NULL,                        // Authentication services
        //    NULL,                        // Reserved
        //    RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        //    RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
        //    NULL,                        // Authentication info
        //    EOAC_NONE,                   // Additional capabilities 
        //    NULL                         // Reserved
        //);

        hr = ::CoCreateInstance(
            CLSID_WbemLocator,
            0,
            CLSCTX_INPROC_SERVER,
            IID_IWbemLocator, (LPVOID*)&m_pLoc);

        if (FAILED(hr))
        {
            break;
        }

        hr = m_pLoc->ConnectServer(
            _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
            NULL,                    // User name. NULL = current user
            NULL,                    // User password. NULL = current
            0,                       // Locale. NULL indicates current
            NULL,                    // Security flags.
            0,                       // Authority (for example, Kerberos)
            0,                       // Context object 
            &m_pSvc                    // pointer to IWbemServices proxy
        );

        if (FAILED(hr))
        {
            break;
        }

        hr = ::CoSetProxyBlanket(
            m_pSvc,                        // Indicates the proxy to set
            RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
            RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
            NULL,                        // Server principal name 
            RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
            RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
            NULL,                        // client identity
            EOAC_NONE                    // proxy capabilities 
        );

        if (FAILED(hr))
        {
            break;
        }

        m_bInit = true;

    } while (false);

    if (!m_bInit)
    {
        if (m_pSvc)
        {
            m_pSvc->Release();
            m_pSvc = NULL;
        }

        if (m_pLoc)
        {
            m_pLoc->Release();
            m_pLoc = NULL;
        }

        ::CoUninitialize();
    }

    return m_bInit;
}

void CWmiQueryHelper::Uninitialize()
{
    if (m_bInit)
    {
        if (m_pSvc)
        {
            m_pSvc->Release();
            m_pSvc = NULL;
        }

        if (m_pLoc)
        {
            m_pLoc->Release();
            m_pLoc = NULL;
        }

        ::CoUninitialize();

        m_bInit = false;
    }
}

bool CWmiQueryHelper::ExecQuery(
    const _tstring& strSql, std::function<void(uint64_t nIndex, const CWmiClassHelper& obj)> cb
)
{
    HRESULT hr = S_OK;
    IEnumWbemClassObject* pEnumerator = NULL;

    if (!m_bInit)
    {
        return false;
    }

    hr = m_pSvc->ExecQuery(
        bstr_t(_T("WQL")),
        bstr_t(strSql.c_str()),
        WBEM_FLAG_RETURN_IMMEDIATELY  | WBEM_FLAG_FORWARD_ONLY,
        NULL,
        &pEnumerator);

    if (FAILED(hr))
    {
        return false;
    }

    IWbemClassObject* pObj = NULL;
    ULONG uReturn = 0;
    uint64_t nIndex = 0;

    while (true)
    {
        if (FAILED(pEnumerator->Next(WBEM_INFINITE, 1, &pObj, &uReturn)))
        {
            break;
        }

        if (0 == uReturn)
        {
            break;
        }

        CWmiClassHelper classObj(pObj);
        if (cb)
        {
            cb(nIndex, classObj);
        }

        pObj->Release();
        nIndex++;
    }

    pEnumerator->Release();
    pEnumerator = NULL;

    return true;
}

bool CWmiQueryHelper::QueryClass(
    const _tstring& strClass, 
    std::function<void(uint64_t nIndex, const CWmiClassHelper& obj)> cb
)
{
    _tstring strSql = _T("SELECT * FROM ") + strClass;
    return ExecQuery(strSql, cb);
}
