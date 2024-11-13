#ifndef COMMON_H
#define COMMON_H
#include <vector>
#include <string>
#include <set>
#include <windows.h>
#include "globel.h"


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
	extern unsigned long	dwLastIn;				//上一秒钟的接收字节数
	extern unsigned long	dwLastOut;				//上一秒钟的发送字节数
	extern QString			strFtpIp;				// ftp的ip
	extern int				iFtpPort;
	extern QString          strDbIp;
	extern QString          strDbUser;
	extern QString          strDbPassword;

	extern int				iUserID;
	extern bool             bAdministrator;			 // 是否是管理员;
	extern int				onePageRows;			 // 每页显示的行数;

	extern int				iLoginNum;				 // 登录顺序; 123456;
	extern int              iSoftStartHostNum;		 // 模块234软件 启动的所在主机标志;
	//extern   std::set<std::string>    setHostIps;    // 每个用户分配的三个主机网卡ip;;         // 每个用户分配的三个主机网卡ip;
	extern   std::vector<table_ip_configure>    setHostData;    // 每个用户分配的三个主机网卡ip;;         // 每个用户分配的三个主机网卡ip;

	//extern   QMap<QString, table_ip_configure>  setHostData;

	extern QString          strCopyPath;			 // 复制的远程路径;
	extern QString          strVipPath;				 //   普通用户不能操作的路径;
	extern table_user       stUser;
	extern int              index;                //一键加载时，点击不同模块


	void findIpWithGpuMinValue(table_ip_configure &stHost);
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

	HWND FindMainWindow(unsigned long process_id);
	
	std::vector<HWND> getWindowHandlesByProcessId(DWORD processID);

	HWND FindWindowByProcessId(DWORD processID);
	HWND StartExeAndFindWindow(QString & strPath);

	HWND getHWND(QString& strClassName, int& number);

	void InitResource(const TCHAR* userName, const TCHAR* password, const TCHAR* localDrive, const TCHAR* remotePath);
	void UnInitResource();
	void StoreCredential(const std::wstring& target, const std::wstring& username, const std::wstring& password);
	void startDspExe(QString& strPath);

	// ---------类型转换-----------
	// string转time_t;
	time_t string_to_datetime(const std::string& str);

	//Qt相关函数----------------------------;
	 // 删除所有行 保留标题;
	void delAllModelRow(QStandardItemModel* model);

	void hideMidelRowsbyColumnValue(QStandardItemModel* model,const int & Column, const QString& strValue);

	void setTableViewBasicConfiguration(QTableView *tableView);

	void clearLayout(QLayout* layout);

	void getScreenCenterPos(int& x, int& y,const int & dialgX, const int& dialgY);

	void addNetworkCredential(const QString& target, const QString& username, const QString& password);
	

}


#endif // COMMON_H
