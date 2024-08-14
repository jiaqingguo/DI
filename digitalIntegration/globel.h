#ifndef GLOBEL_H
#define GLOBEL_H

#include <QString>

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

// 工具表;
struct table_tools
{
	uint32_t		id = 0;			       // ID(主键自增unsigned int);
	std::string		name;						
	std::string		host;		
	std::string		path;
	std::string		icoPath;
	uint32_t		module=0;
};

// ip表;
struct table_ip
{
	uint32_t		id = 0;			       // ID(主键自增unsigned int);
	std::string		host;			     
	std::string		ip;						
	uint32_t		module = 0;
	uint32_t        used = 0;
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

#endif // GLOBEL_H
