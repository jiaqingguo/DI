#pragma once

#include <wtypesbase.h>
#include <string>
#include <vector>
#include <tchar.h>

#ifdef _UNICODE
using _tstring = std::wstring;
#else
using _tstring = std::string;
#endif

// ���ݵ�λ
enum eUnitType
{
    eUT_Auto,   // �Զ�
    eUT_b,      // (2 ^ 000) Bit
    eUT_Kb,     // (2 ^ 010) Bit
    eUT_Mb,     // (2 ^ 020) Bit
    eUT_Gb,     // (2 ^ 030) Bit
    eUT_Tb,     // (2 ^ 040) Bit
    eUT_Pb,     // (2 ^ 050) Bit
    eUT_Eb,     // (2 ^ 060) Bit
    eUT_Zb,     // (2 ^ 070) Bit
    eUT_Yb,     // (2 ^ 080) Bit
    eUT_Bb,     // (2 ^ 090) Bit
    eUT_Nb,     // (2 ^ 100) Bit
    eUT_Db,     // (2 ^ 110) Bit
    eUT_Cb,     // (2 ^ 120) Bit
    eUT_Xb,     // (2 ^ 130) Bit

    eUT_B,      // Byte          2 ^ 000 Byte
    eUT_KB,     // Kilobyte      2 ^ 010 Byte 
    eUT_MB,     // Megabyte      2 ^ 020 Byte 
    eUT_GB,     // Gigabyte      2 ^ 030 Byte 
    eUT_TB,     // Terabyte      2 ^ 040 Byte 
    eUT_PB,     // Petabyte      2 ^ 050 Byte 
    eUT_EB,     // Exabyte       2 ^ 060 Byte 
    eUT_ZB,     // Zettabyte     2 ^ 070 Byte 
    eUT_YB,     // Yottabyte     2 ^ 080 Byte 
    eUT_BB,     // Brontobyte    2 ^ 090 Byte 
    eUT_NB,     // NonaByte      2 ^ 100 Byte 
    eUT_DB,     // DoggaByte     2 ^ 110 Byte 
    eUT_CB,     // corydonbyte   2 ^ 120 Byte 
    eUT_XB,     // Xerobyte      2 ^ 130 Byte
    eUT_Max
};

typedef struct _DATA_UNIT_INFO
{
    double value;           // ��ֵ
    eUnitType eUnit;        // ��λ
    _tstring strUnitStr;    // ��λ�ַ���
    _tstring strOutput;     // ����(��ֵ + ��λ�ַ���)
}DATA_UNIT_INFO;

// �ַ���ת��ʵ����
class CStrUtils
{
public:

    // ���ļ������ַ���
    static std::string FromFileA(const std::string& strFile);
    static std::wstring FromFileW(const std::wstring& strFile);
    static _tstring FromFile(const _tstring& strFile);

    // �ַ������浽�ļ�
    static bool ToFileA(const std::string& strFile, const std::string& str);
    static bool ToFileW(const std::wstring& strFile, const std::wstring& str);
    static bool ToFile(const _tstring& strFile, const _tstring& str);

    // ת����д
    static std::string ToUpperStrA(const std::string& str);
    static std::wstring ToUpperStrW(const std::wstring& str);
    static _tstring ToUpperStr(const _tstring& str);

    // ת��Сд
    static std::string ToLowerStrA(const std::string& str);
    static std::wstring ToLowerStrW(const std::wstring& str);
    static _tstring ToLowerStr(const _tstring& str);

    // �ָ��ַ���
    static std::vector<std::string> SplitStrA(const std::string& str, const std::string& delim);
    static std::vector<std::wstring> SplitStrW(const std::wstring& str, const std::wstring& delim);
    static std::vector<_tstring> SplitStr(const _tstring& str, const _tstring& delim);

    // �滻�ַ���
    static std::string& ReplaceA(std::string& strSrc, const std::string& strFind, const std::string& strReplace, bool bCase = false);
    static std::wstring& ReplaceW(std::wstring& strSrc, const std::wstring& strFind, const std::wstring& strReplace, bool bCase = false);
    static _tstring& Replace(_tstring& strSrc, const _tstring& strFind, const _tstring& strReplace, bool bCase = false);

    // �Ƚ��ַ���
    static int CompareA(const std::string& strSrc, const std::string& strDest, bool bCase = true);
    static int CompareW(const std::wstring& strSrc, const std::wstring& strDest, bool bCase = true);
    static int Compare(const _tstring& strSrc, const _tstring& strDest, bool bCase = true);

    // ��ʽ���ַ���
    static std::string FormatA(LPCSTR pFormat, ...);
    static std::wstring FormatW(LPCWSTR pFormat, ...);
    static _tstring Format(LPCTSTR pFormat, ...);

    // ��������ַ���
    static void OutputDebugA(LPCSTR pFormat, ...);
    static void OutputDebugW(LPCWSTR pFormat, ...);
    static void OutputDebug(LPCTSTR pFormat, ...);

    // �����ַ���λ��
    static size_t FindNoCaseA(const std::string& str1, const std::string& str2);
    static size_t FindNoCaseW(const std::wstring& str1, const std::wstring& str2);
    static size_t FindNoCase(const _tstring& str1, const _tstring& str2);

    // ���ַ���ת��
    static std::string WStrToU8Str(const std::wstring& str);
    static std::string WStrToAStr(const std::wstring& str);
    static _tstring WStrToTStr(const std::wstring& str);

    // ANSI�ַ�ת��
    static std::wstring AStrToWStr(const std::string& str);
    static std::string AStrToU8Str(const std::string& str);
    static _tstring AStrToTStr(const std::string& str);

    // UTF-8�ַ���ת��
    static std::wstring U8StrToWStr(const std::string& str);
    static std::string U8StrToAStr(const std::string& str);
    static _tstring U8StrToTStr(const std::string& str);

    // �����ַ���ת��
    static std::string TStrToAStr(const _tstring& str);
    static std::wstring TStrToWStr(const _tstring& str);
    static std::string TStrToU8Str(const _tstring& str);

    // ��ȡUTF8�ַ�����
    static int GetUtf8CharacterCount(const std::string& strContent);

    // ��ȡGetLastError()�Ĵ�����Ϣ�ı�
    static std::string GetErrorMessageA(DWORD dwMessageId, DWORD dwLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT));
    static std::wstring GetErrorMessageW(DWORD dwMessageId, DWORD dwLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT));
    static _tstring GetErrorMessage(DWORD dwMessageId, DWORD dwLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT));

    static DATA_UNIT_INFO FormatByteSize(
        double nBytesSize,                                      // ����ֵ
        eUnitType eSrcUnit = eUnitType::eUT_Auto,               // ԭʼ��λ
        eUnitType eDestUnit = eUnitType::eUT_Auto,              // Ŀ�굥λ
        bool fHasUnits = true,                                  // ����ַ�����ֵ��ӵ�λ
        bool fSpace = true,                                     // ����ַ�����ֵ�뵥λ֮����ӿո�
        int nInteger = 1,                                       // �������ֳ���
        int nPrecision = 3                                      // С�����ֳ���
    );

    // ����̨���
    static void ConsoleOutput(LPCTSTR pFormat, ...);

private:

    // �ַ�������
    template<typename T>
    static size_t _FindNoCase(const T& str1, const T& str2);

    // ���ַ�ת����
    static std::string _WStrToMultiStr(UINT CodePage, const std::wstring& str);

    // ����ת���ַ�
    static std::wstring _MultiStrToWStr(UINT CodePage, const std::string& str);
};
