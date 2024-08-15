#ifndef COMMON_H
#define COMMON_H
#include <vector>
#include <string>

struct _FILETIME;
struct NetworkInterface;

class QStandardItemModel;
class QString;
class QTableView;
class QLayout;

struct NetworkInterface
{
	std::string name;
	unsigned long long receivedBytes;
	unsigned long long transmittedBytes;

	unsigned long long getTotalThroughput() const {
		return receivedBytes + transmittedBytes;
	}
};
namespace common
{

	extern int				tableViewRowHeight;
	extern int				tableViewHeight;
	extern int				tableViewPageRows;
	extern unsigned long	dwLastIn;           //��һ���ӵĽ����ֽ���
	extern unsigned long	dwLastOut;          //��һ���ӵķ����ֽ���
	extern QString			strFtpIp;    // ftp��ip
	extern int				iFtpport;
	extern int				iUserID;
	extern bool             bAdministrator; // �Ƿ��ǹ���Ա;

	extern int onePageRows;     // ÿҳ��ʾ������;
	// Windows C++
	//__int64 Filetime2Int64(const FILETIME& ftime);


	//__int64 CompareFileTimeEx(const FILETIME& preTime, const FILETIME& nowTime);
	double getCpuUsage();

	void getPhysicsMem(long& allPhysicsMem, long& freePhysicsMem);

	double getMemUseRate();

	void getAllDisSpace(double& lFreeAll, double& lToalAll);

	void getNetData();

	void getNetSpeed();
	void getNetworkInterfaceStatistics();
	void PrintAdapterInfo();

	unsigned long GetNetworkInterfacesThroughput();

	// ---------����ת��-----------
	// stringתtime_t;
	time_t string_to_datetime(const std::string& str);

	//Qt��غ���----------------------------;
	 // ɾ�������� ��������;
	void delAllModelRow(QStandardItemModel* model);

	void hideMidelRowsbyColumnValue(QStandardItemModel* model,const int & Column, const QString& strValue);

	void setTableViewBasicConfiguration(QTableView *tableView);

	void clearLayout(QLayout* layout);


	/*wchar_t* QString2wchar_t(QString str) {
		std::wstring wstr = str.toStdWString();
		wchar_t* lpcwstr = wstr.c_str();
		return lpcwstr;
	}*/

	// C++
	//LPCWSTR stringToLPCWSTR(std::string orig)
	//{
	//	size_t origsize = orig.length() + 1;
	//	const size_t newsize = 100;
	//	size_t convertedChars = 0;
	//	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	//	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	//	return wcstring;
	//}
	/*std::string Wchar2string(WCHAR wChar[]);

	wchar_t* String2Wchar(const std::string strTag);*/

}


#endif // COMMON_H
