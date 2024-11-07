#include "CPerformHelper.h"
#include <pdh.h>
#include <pdhmsg.h>

#pragma comment(lib, "pdh.lib")

CPerformHelper::CPerformHelper()
    :
    m_fQuit(false),
    m_hQuery(NULL),
    m_msCollectInterval(1000)
{

}

CPerformHelper::~CPerformHelper()
{
    Uninitialize();
}

void CPerformHelper::_Sleep(int millisecond)
{
    do
    {
        const int span = 1;
        if (millisecond < span)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
            return;
        }

        clock_t tmBegin = clock();
        while (true)
        {
            if (::clock() - tmBegin > millisecond)
            {
                break;
            }

            if (m_fQuit)
            {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(span));
        }
    } while (false);
}

bool CPerformHelper::Initialize()
{
    PDH_STATUS status = ERROR_SUCCESS;
    if (NULL == m_hQuery)
    {
        status = ::PdhOpenQuery(NULL, 0, &m_hQuery);
    }

    if (ERROR_SUCCESS != status)
    {
        return false;
    }

    return true;
}

void CPerformHelper::Uninitialize()
{
    m_fQuit = true;
    if (m_task.joinable())
    {
        m_task.join();
    }
    m_fQuit = false;

    {
        m_Mutex.lock();
        for (auto& item : m_hPerfMonInfos)
        {
            if (NULL != item.second)
            {
                ::PdhRemoveCounter(item.second);
            }
        }

        m_hPerfMonInfos.clear();
        m_Mutex.unlock();
    }

    if (m_hQuery)
    {
        ::PdhCloseQuery(m_hQuery);
        m_hQuery = NULL;
    }
}

bool CPerformHelper::AddCounter(const _tstring& strCounterPath)
{
    HCOUNTER hCounter = NULL;
    PDH_STATUS status = ERROR_SUCCESS;

    status = ::PdhAddCounter(m_hQuery, strCounterPath.c_str(), 0, &hCounter);

    if (ERROR_SUCCESS != status)
    {
        return false;
    }

    m_Mutex.lock();
    m_hPerfMonInfos.insert(std::make_pair(strCounterPath, hCounter));
    m_Mutex.unlock();

    return true;
}

bool CPerformHelper::RemoveCounter(const _tstring& szCounterPath)
{
    bool fResult = false;

    m_Mutex.lock();
    auto itFind = m_hPerfMonInfos.find(szCounterPath);

    if (itFind != m_hPerfMonInfos.end())
    {
        ::PdhRemoveCounter(itFind->second);
        m_hPerfMonInfos.erase(itFind);
        fResult = true;
    }

    m_Mutex.unlock();

    return fResult;
}

void CPerformHelper::SetCollectInterval(DWORD millisecond)
{
    if (millisecond < 100)
    {
        m_msCollectInterval = 100;
    }

    m_msCollectInterval = millisecond;
}

bool CPerformHelper::StartCollect()
{
    PDH_STATUS status = ERROR_SUCCESS;
    status = ::PdhCollectQueryData(m_hQuery);

    if (ERROR_SUCCESS != status)
    {
        return false;
    }

    m_task = std::move(std::thread([&]() {

        PDH_STATUS status = ERROR_SUCCESS;
        while ((ERROR_SUCCESS == status) && !m_fQuit)
        {
            status = ::PdhCollectQueryData(m_hQuery);
            if (ERROR_SUCCESS != status)
            {
                break;
            }

            _Sleep(m_msCollectInterval);
        }

        }));

    return ERROR_SUCCESS == status;
}

bool CPerformHelper::GetFormattedCounterValue(const _tstring& strCounterPath, DWORD dwFormat, PPDH_FMT_COUNTERVALUE pValue)
{
    PDH_STATUS status = ERROR_SUCCESS;

    auto itFind = m_hPerfMonInfos.find(strCounterPath);
    if (m_hPerfMonInfos.end() == itFind)
    {
        return false;
    }

    status = ::PdhGetFormattedCounterValue(
        itFind->second,
        dwFormat,
        (LPDWORD)NULL,
        pValue);

    return ERROR_SUCCESS == status;
}

bool CPerformHelper::GetFormattedCounterArray(const _tstring& strCounterPath, DWORD dwFormat, PPDH_FMT_COUNTERVALUE pValue)
{
    PPDH_FMT_COUNTERVALUE_ITEM pAryValue = NULL;
    PDH_STATUS status = ERROR_SUCCESS;
    DWORD dwBufferSize = 0;
    DWORD dwItemCount = 0;

    auto itFind = m_hPerfMonInfos.find(strCounterPath);
    if (m_hPerfMonInfos.end() == itFind)
    {
        return false;
    }

    do
    {
        status = ::PdhGetFormattedCounterArray(
            itFind->second,
            dwFormat,
            &dwBufferSize,
            &dwItemCount,
            NULL
        );

        if (PDH_MORE_DATA != status)
        {
            break;
        }

        pAryValue = (PPDH_FMT_COUNTERVALUE_ITEM)::HeapAlloc(::GetProcessHeap(), 0, dwBufferSize);
        if (NULL == pAryValue)
        {
            break;
        }

        status = ::PdhGetFormattedCounterArray(
            itFind->second,
            dwFormat,
            &dwBufferSize,
            &dwItemCount,
            pAryValue
        );

        PDH_FMT_COUNTERVALUE value = { 0 };
        for (DWORD i = 0; i < dwItemCount; i++)
        {
            if (PDH_FMT_DOUBLE == dwFormat)
            {
                value.doubleValue += pAryValue[i].FmtValue.doubleValue;
            }
            if (PDH_FMT_LARGE == dwFormat)
            {
                value.largeValue += pAryValue[i].FmtValue.largeValue;
            }
            if (PDH_FMT_LONG == dwFormat)
            {
                value.longValue += pAryValue[i].FmtValue.longValue;
            }
        }

        if (pValue)
        {
            *pValue = value;
        }

    } while (false);

    if (pAryValue)
    {
        ::HeapFree(::GetProcessHeap(), 0, pAryValue);
    }

    return ERROR_SUCCESS == status;
}