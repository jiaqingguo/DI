#ifndef GLOBEL_H
#define GLOBEL_H

#include <QString>
#include <QDataStream>


#define GBK_STRING(str) QString::fromLocal8Bit(str)


// 用户表;
struct table_user
{
	uint32_t		PKID = 0;			       // ID(主键自增unsigned int);
	std::string		UserName;							// 用户(varchar(255));
	std::string		Password ;			// 密码(unsigned int);
	std::string		name;
	std::string		department;    // 部门
	std::string		JobTitle;      // 职位
	std::string		PhoneNumber;
	
	uint32_t		Pop =0;	
	time_t          CreateTime;
	uint32_t		approval=0;

	uint32_t		loginStatus = 0;
};

//指纹表
//struct table_fingerprint
//{
//	uint32_t	    id = 0;			       // ID(主键自增unsigned int);
//	std::string     fingerdata;
//	uint32_t	    fingerlen = 0;
//};

// 工具表;
struct table_tools
{
	uint32_t		id = 0;			       // ID(主键自增unsigned int);
	std::string		name;						
	std::string		host;		
	std::string		path;
	std::string		icoPath;
	uint32_t		module = 0;
	std::string     ip;
	uint32_t		number = 0;
	std::string     username;
};

// ip表;
struct table_ip
{
	uint32_t		id = 0;			       // ID(主键自增unsigned int); 
	std::string		ip;		
	std::string		host;
	std::string     software;
	uint32_t		module = 0;
	uint32_t        used = 0;
	std::string		username;
	std::string		icoPath;
	uint32_t        number = 0;
	std::string     toolPath;
	std::vector<char> imageData;  // 用于存储图片数据;
	
};

struct table_ip_configure
{
	uint32_t		id = 0;
	std::string		ip;
	std::string		hostname;
	uint32_t        number = 0;

	double         dGpuUsage = 0; // 不在数据库表的字段，
	double         dCpuUsage = 0; // 不在数据库表的字段，
	bool operator<(const table_ip_configure& other) const
	{
		return id <other.id; // 定义相等比较
	}
};

// 用户审批表
struct table_dataApproval
{
	uint32_t		id = 0;			       // ID(主键自增unsigned int);
	std::string		proposer;
	std::string		department;
	time_t			applicationTime;
	std::string		host;
	time_t			createTime;
	std::string		tool;
	std::string		fileName;
	std::string		fileType;
	uint32_t        state = 0;
};

// 下载审批表
struct table_DownloadApproval
{
	uint32_t		id = 0;			       // ID(主键自增unsigned int);
	uint32_t		userID = 0;
	time_t			applicationTime;    //申请时间
	
	std::string		filePath;
	std::string		fileType;
	std::string			fileTime;
	uint32_t        status = 0;

	std::string		ftpName;
	std::string		ftpIp;

	// 关联的表外数据
	std::string    userName;
	std::string    department;
};

//用户加载表
struct table_one_load_software
{
	uint32_t		id = 0;			       // ID(主键自增unsigned int);
	std::string     projectPath;
	uint32_t		userID = 0;
	uint32_t		module = 0;
};
struct table_account_password
{
	uint32_t		id = 0;			       // ID(主键自增unsigned int);
	std::string     account;
	std::string     password;
	uint32_t		used = 0;   // 是否已使用;0:未使用,1已使用;
};
struct st_account_data
{
	
	QString     account="";

	QString     ip="";
	QString     software = "";
};


struct table_configuration
{
	std::string     ftpServerIp;
	std::string     ftpServerAccount;
	std::string     ftpServerPwd;
	std::string     ftpPwd;
};

enum EUserTable : uint32_t
{
	EUT_NAME,
	EUT_DEPARTMENT,
	EUT_CREATE_TIME,
	EUT_USER_NAME,
	EUT_PASSWORD,
	EUT_JOB_TITLE,
	EUT_PHONE_NUMBER,
	EUT_POP,
	EUT_APPROVAL,
};

inline const char* userTable_to_string(const EUserTable& value)
{
	switch (value)
	{
	case EUserTable::EUT_NAME:
		return "name";
	case EUserTable::EUT_DEPARTMENT:
		return "department";
	case EUserTable::EUT_CREATE_TIME:
		return "致命错误";
	case EUserTable::EUT_USER_NAME:
		return "警告";
	case EUserTable::EUT_PASSWORD:
		return "Password";
	case EUserTable::EUT_JOB_TITLE:
		return "JobTitle";
	case EUserTable::EUT_PHONE_NUMBER:
		return "PhoneNumber";
	case EUserTable::EUT_POP:
		return "Pop";
	case EUserTable::EUT_APPROVAL:
		return "approval";

	default:
		break;
	}
	return u8"信息";
}

const QString strQssBlue = R"(
        QPushButton {
            background-color: lightblue;
            border: 2px solid gray;
            border-radius: 5px;
            padding: 5px;
        }
    )";

const QString strQssGray = R"(
        QPushButton {
            background-color: lightgray;
            border: 2px solid gray;
            border-radius: 5px;
            padding: 5px;
        }
    )";

struct st_udp
{
	QString str1;//Lcompress\Wcompress\Luncompress\Wuncompress
	QString str2;//要压缩的文件的路径\解压时的压缩包的路径
	QString str3;//压缩包的路径
};



#define IDM_ABOUTBOX                    0x0010
#define IDD_ABOUTBOX                    100
#define IDS_ABOUTBOX                    101
#define IDD_LIBZKFPDEMO_DIALOG          102
#define IDR_MAINFRAME                   128
#define IDC_BTN_CONN                    1000
#define IDC_BTN_DISCONN                 1001
#define IDC_BTN_REG                     1002
#define IDC_BTN_DBCNT                   1003
#define IDC_BTN_DBCLEAR                 1003
#define IDC_BTN_VERIFY                  1004
#define IDC_BTN_IDENTIFY                1005
#define IDC_STC_FPIMG                   1006
#define IDC_EDIT_RESULT                 1007
#define IDC_BTN_REG_BY_IMG              1008
#define IDC_BTN_IDENTIFY2               1009
#define IDC_BTN_IDENTIFY_BY_IMG         1009

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        129
#define _APS_NEXT_COMMAND_VALUE         32771
#define _APS_NEXT_CONTROL_VALUE         1008
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
#endif // GLOBEL_H
