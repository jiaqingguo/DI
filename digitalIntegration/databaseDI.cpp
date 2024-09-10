#define _SCL_SECURE_NO_WARNINGS
#include <mysql.h>
#include "databaseDI.h" 
#include <QDebug>
#include <sstream>
#include <iomanip>

namespace db
{
	databaseDI& databaseDI::Instance()
	{
		static databaseDI instance;
		return instance;
	}
	bool databaseDI::open()
	{
		//std::string path = "/../data/config/database.xml";
		//// 加载配置文件;
		//if (!load_config(path.c_str()))
		//{
		//	//PRINT_ERROR("加载配置文件失败!\n");
		//	//return false;
		//}

		// 初始化;
		mysql_ = mysql_init(nullptr);

		if (mysql_ == nullptr)
			return false;

		// 连接mysql;
		if (!mysql_real_connect(mysql_, server_.c_str(), user_.c_str(), pwd_.c_str(), m_diDatabase.c_str(), port_, NULL, 0))
		{
			qDebug("连接失败!\n%s", mysql_error(mysql_));
			return false;
		}

		// 字符集设置;
		//mysql_query(tempDB, "SET NAMES UTF8");
		std::string char_set_name = "UTF8";
		if (mysql_set_character_set(mysql_, char_set_name.c_str()) != 0)
		{
			qDebug("字符集设置失败!\n%s", mysql_error(mysql_));
		}

		return true;
	}

	bool databaseDI::close()
	{
		if (mysql_ != nullptr)
			mysql_close(mysql_);
		return true;
	}

	bool databaseDI::add_user_info(table_user& userInfo)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		uint32_t last_id = 0;
		// 执行SQL语句;
		char sql[1024] = { 0 };

		sprintf_s(sql, "insert into t_user(UserName,Password,name,department,JobTitle,PhoneNumber,Pop,CreateTime,approval,loginStatus) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\',\'%s\',\'%d\',\'%d\')",
			userInfo.UserName.c_str(),
			userInfo.Password.c_str(),
			userInfo.name.c_str(),
			userInfo.department.c_str(),
			userInfo.JobTitle.c_str(),
			userInfo.PhoneNumber.c_str(),
			userInfo.Pop,
			datetime_to_string(userInfo.CreateTime).c_str(),
			userInfo.approval,
			userInfo.loginStatus);

		if (!exec_sql(last_id, sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		userInfo.PKID = last_id;
		return true;
	}

	bool databaseDI::is_exist_user(const std::string& user)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_user where UserName = \'%s\'", user.c_str());

		if (!exec_sql_select(sql_row, sql))
			return false;
		if (!sql_row)
			return false;

		return true;
	}

	bool databaseDI::is_exist_user(const std::string &user, const std::string &password)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_user where UserName = \'%s\' AND Password = \'%s\'", user.c_str(), password.c_str());

		if (!exec_sql_select(sql_row, sql))
			return false;
		if (!sql_row)
			return false;

		return true;
	}

	bool databaseDI::get_user_count(int& count)
	{

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "SELECT COUNT(*) AS total_records FROM t_user");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;


		while (sql_row = mysql_fetch_row(result))
		{
			count = std::atoi(sql_row[0]);
		}
		return true;
	}

	bool databaseDI::get_new_regist_user(int &id)
	{
		//listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_user");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_user userInfo;
		while (sql_row = mysql_fetch_row(result))
		{
			id = std::atoi(sql_row[0]);
		}
		return true;
	}


	bool databaseDI::get_user_by_condition(table_user &stData, const int& userID, const int& approval)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_user where PKID = \'%d\' AND approval=\'%d\'", userID, approval);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;


		while (sql_row = mysql_fetch_row(result))
		{
			stData.PKID = std::atoi(sql_row[0]);
			stData.UserName = sql_row[1];
			stData.Password = sql_row[2];
			stData.name = sql_row[3];
			stData.department = sql_row[4];
			stData.JobTitle = sql_row[5];
			stData.PhoneNumber = sql_row[6];
			stData.Pop = std::atoi(sql_row[7]);
			stData.CreateTime = string_to_datetime(sql_row[8]);
			stData.approval = std::atoi(sql_row[9]);
			stData.loginStatus = std::atoi(sql_row[10]);
			//listData.push_back(userInfo);
		}
		return true;
	}

	bool databaseDI::get_user_list_by_condition(std::list<table_user>& listData, const int& rows, const int& offset)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "SELECT * FROM t_user ORDER BY CreateTime LIMIT %d OFFSET %d", rows, offset);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_user userInfo;
		while (sql_row = mysql_fetch_row(result))
		{
			userInfo.PKID = std::atoi(sql_row[0]);
			userInfo.UserName = sql_row[1];
			userInfo.Password = sql_row[2];
			userInfo.name = sql_row[3];
			userInfo.department = sql_row[4];
			userInfo.JobTitle = sql_row[5];
			userInfo.PhoneNumber = sql_row[6];
			userInfo.Pop = std::atoi(sql_row[7]);
			userInfo.CreateTime = string_to_datetime(sql_row[8]);
			userInfo.approval = std::atoi(sql_row[9]);
			userInfo.loginStatus = std::atoi(sql_row[10]);
			listData.push_back(userInfo);
		}
		return true;

	}

	bool databaseDI::get_user_list_by_condition(std::list<table_user>& listData, const std::string& fields, const std::string& value)
	{
		listData.clear();
		// 结果集声明;
		MYSQL_ROW sql_row;

		int a = std::stoi(value);
		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_user where %s=\'%d\'", fields.c_str(), a);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_user userInfo;
		while (sql_row = mysql_fetch_row(result))
		{
			userInfo.PKID = std::atoi(sql_row[0]);
			userInfo.UserName = sql_row[1];
			userInfo.Password = sql_row[2];
			userInfo.name = sql_row[3];
			userInfo.department = sql_row[4];
			userInfo.JobTitle = sql_row[5];
			userInfo.PhoneNumber = sql_row[6];
			userInfo.Pop = std::atoi(sql_row[7]);
			userInfo.CreateTime = string_to_datetime(sql_row[8]);
			userInfo.approval = std::atoi(sql_row[9]);
			userInfo.loginStatus = std::atoi(sql_row[10]);
			listData.push_back(userInfo);
		}
		return true;
	}

	bool databaseDI::get_user(table_user& userInfo, const std::string& user)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_user where UserName = \'%s\' ORDER BY PKID DESC LIMIT 1", user.c_str());

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		while (sql_row = mysql_fetch_row(result))
		{
			userInfo.PKID = std::atoi(sql_row[0]);
			userInfo.UserName = sql_row[1];
			userInfo.Password = sql_row[2];
			userInfo.name = sql_row[3];
			userInfo.department = sql_row[4];
			userInfo.JobTitle = sql_row[5];
			userInfo.PhoneNumber = sql_row[6];
			userInfo.Pop = std::atoi(sql_row[7]);
			userInfo.CreateTime = string_to_datetime(sql_row[8]);
			userInfo.approval = std::atoi(sql_row[9]);
			userInfo.loginStatus = std::atoi(sql_row[10]);
		}
		return true;
	}

	bool databaseDI::get_user_list(std::list<table_user>& listData)
	{

		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_user");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_user userInfo;
		while (sql_row = mysql_fetch_row(result))
		{
			userInfo.PKID = std::atoi(sql_row[0]);
			userInfo.UserName = sql_row[1];
			userInfo.Password = sql_row[2];
			userInfo.name = sql_row[3];
			userInfo.department = sql_row[4];
			userInfo.JobTitle = sql_row[5];
			userInfo.PhoneNumber = sql_row[6];
			userInfo.Pop = std::atoi(sql_row[7]);
			userInfo.CreateTime = string_to_datetime(sql_row[8]);
			userInfo.approval = std::atoi(sql_row[9]);
			userInfo.loginStatus = std::atoi(sql_row[10]);
			listData.push_back(userInfo);
		}
		return true;
	}

	bool databaseDI::get_pop(int& pop, const std::string& user, const std::string& password)
	{

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select Pop from t_user where UserName = \'%s\' AND Password = \'%s\'", user.c_str(), password.c_str());

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		while (sql_row = mysql_fetch_row(result))
		{
			pop = std::atoi(sql_row[0]);
		}
		return false;
	}

	bool databaseDI::get_approval(int &approval, int &id)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select approval from t_user where PKID = \'%d\'", id);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		while (sql_row = mysql_fetch_row(result))
		{
			approval = std::atoi(sql_row[0]);
		}
		return false;
	}


	bool databaseDI::get_user_login_number(int& loginNumber)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "SELECT COUNT(*) AS count FROM t_user WHERE  loginStatus = 1");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		while (sql_row = mysql_fetch_row(result))
		{
			loginNumber = std::atoi(sql_row[0]);
		}
		return true;
	}

	bool databaseDI::update_user_state(const int& id, int& approval)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "update t_user set approval=\'%d\' where PKID=\'%d\'",
			approval,
			id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;

	}

	bool databaseDI::update_user_LoginStatus(const int& id, int& status)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "update t_user set loginStatus=\'%d\' where PKID=\'%d\'",
			status,
			id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::del_user(const int& id)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "delete from t_user where id = (\'%d\')", id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}
		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::get_tools(std::list<table_tools>& listTools, const int& module)
	{
		listTools.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_tools where module=\'%d\'", module);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_tools stTool;
		while (sql_row = mysql_fetch_row(result))
		{
			stTool.id = std::atoi(sql_row[0]);
			stTool.name = sql_row[1];
			stTool.host = sql_row[2];
			stTool.path = sql_row[3];
			stTool.icoPath = sql_row[4];
			stTool.module = std::atoi(sql_row[5]);


			listTools.push_back(stTool);
		}
		return true;
	}

	bool databaseDI::add_tools(table_tools& stTool)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		uint32_t last_id = 0;
		// 执行SQL语句;
		char sql[1024] = { 0 };


		//sprintf_s(sql, "insert into t_tools(name,host,path,icoPath,module) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%d\')",
		sprintf_s(sql, R"(insert into t_tools(name,host,path,icoPath,module) values('%s', '%s', '%s', '%s', '%d'))",
			stTool.name.c_str(),
			stTool.host.c_str(),
			stTool.path.c_str(),
			stTool.icoPath.c_str(),
			stTool.module);

		if (!exec_sql(last_id, sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		stTool.id = last_id;
		return true;
	}

	bool databaseDI::add_ip_tools(table_ip &stIp)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		uint32_t last_id = 0;
		// 执行SQL语句;
		char sql[1024] = { 0 };

		sprintf_s(sql, R"(insert into t_ip(ip,host,software,module,number) values('%s', '%s', '%s', '%d', '%d'))",
			stIp.ip.c_str(),
			stIp.host.c_str(),
			stIp.software.c_str(),
			stIp.module,
			stIp.number);

		if (!exec_sql(last_id, sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		stIp.id = last_id;
		return true;
	}

	bool databaseDI::del_tools(const int& id)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "delete from t_tools where id = (\'%d\')", id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}
		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::get_ip_data(std::list<table_ip>& listData)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_ip");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_ip stData;
		while (sql_row = mysql_fetch_row(result))
		{
			stData.id = std::atoi(sql_row[0]);
			stData.ip = sql_row[1];
			stData.host = sql_row[2];
			stData.software = sql_row[3];
			stData.module = std::atoi(sql_row[4]);
			stData.used = std::atoi(sql_row[5]);
			stData.number = std::atoi(sql_row[8]);
			listData.push_back(stData);
		}
		return true;
	}

	bool databaseDI::get_ip_data(std::list<table_ip>& listData, const int& module)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_ip where module=\'%d\'", module);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_ip stData;
		while (sql_row = mysql_fetch_row(result))
		{
			stData.id = std::atoi(sql_row[0]);
			stData.ip = sql_row[1];
			stData.host = sql_row[2];
			stData.software = sql_row[3];
			stData.module = std::atoi(sql_row[4]);
			stData.icoPath = sql_row[7];
			stData.number = std::atoi(sql_row[8]);
			listData.push_back(stData);
		}
		return true;
	}

	bool databaseDI::get_ip_data_by_number(std::set<std::string> setIpData, const int& number)
	{
		setIpData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select ip from t_ip_configure where number=\'%d\'", number);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		//table_ip stData;
		while (sql_row = mysql_fetch_row(result))
		{
			std::string strIp = sql_row[0];

			setIpData.insert(strIp);
		}
		return true;
	}

	bool databaseDI::get_all_ip(std::list<table_ip_configure>& listData)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_ip_configure");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_ip_configure stData;
		while (sql_row = mysql_fetch_row(result))
		{
			stData.id = std::atoi(sql_row[0]);
			stData.ip = sql_row[1];
			stData.hostname = sql_row[2];
			stData.number = std::atoi(sql_row[3]);

			listData.push_back(stData);
		}
		return true;
	}


	bool databaseDI::add_ip(table_ip& stData)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		uint32_t last_id = 0;
		// 执行SQL语句;
		char sql[1024] = { 0 };

		sprintf_s(sql, "insert into t_ip(host,ip,module,used,username) values(\'%s\',\'%s\',\'%d\',\'%d\',\'%s\')",
			stData.host.c_str(),
			stData.ip.c_str(),
			stData.module,
			stData.used,
			stData.username.c_str());

		if (!exec_sql(last_id, sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		stData.id = last_id;
		return true;
	}

	bool databaseDI::del_ip(const int& id)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "delete from t_ip where id = (\'%d\')", id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}
		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::update_ip_status(const uint32_t& id, int status)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, sizeof(sql), "update t_ip set used = (\'%d\') where id = (\'%d\')", status, id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::update_ip_all_status()
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		int used = 0;
		sprintf_s(sql, sizeof(sql), "update t_ip set used = (\'%d\')", used);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::get_ip_count(const std::string& m_ip, int& count)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };

		sprintf_s(sql, "SELECT COUNT(*) AS count FROM t_ip WHERE ip= \'%s\'", m_ip.c_str());

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;


		while (sql_row = mysql_fetch_row(result))
		{
			count = std::atoi(sql_row[0]);
		}
		return true;
	}

	bool databaseDI::get_all_ip_data(std::list<table_ip>& listData)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_ip");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_ip stData;
		while (sql_row = mysql_fetch_row(result))
		{
			stData.id = std::atoi(sql_row[0]);
			stData.host = sql_row[1];
			stData.ip = sql_row[2];
			stData.module = std::atoi(sql_row[3]);
			stData.used = std::atoi(sql_row[4]);
			stData.username = sql_row[5];
			listData.push_back(stData);
		}
		return true;
	}

	bool databaseDI::updata_ip_username(const int& status, const std::string& u_name, const uint32_t& id)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, sizeof(sql), "update t_ip set used = \'%d\',username = \'%s\' where id = \'%d\'", status, u_name.c_str(), id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::updata_ipusername(const std::string& u_name)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		int used = 0;
		sprintf_s(sql, sizeof(sql), "update t_ip set username = (\'%s\') where username = (\'%s\')", "", u_name.c_str());

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::add_data_approval_info(table_dataApproval& stData)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		uint32_t last_id = 0;
		// 执行SQL语句;
		char sql[1024] = { 0 };

		sprintf_s(sql, "insert into t_data_approval(proposer,department,applicationTime,host,createTime,tool,fileName,fileType,state) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\')",
			stData.proposer.c_str(),
			stData.department.c_str(),
			datetime_to_string(stData.applicationTime).c_str(),
			stData.host.c_str(),
			datetime_to_string(stData.createTime).c_str(),
			stData.tool.c_str(),
			stData.fileName.c_str(),
			stData.fileType.c_str(),
			stData.state);

		if (!exec_sql(last_id, sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		stData.id = last_id;
		return true;
	}

	bool databaseDI::get_data_approval_list(std::list<table_dataApproval>& listData)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_data_approval");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_dataApproval stData;
		while (sql_row = mysql_fetch_row(result))
		{
			stData.id = std::atoi(sql_row[0]);
			stData.proposer = sql_row[1];
			stData.department = sql_row[2];
			stData.applicationTime = string_to_datetime(sql_row[3]);
			stData.host = sql_row[4];
			stData.createTime = string_to_datetime(sql_row[5]);
			stData.tool = sql_row[6];
			stData.fileName = sql_row[7];
			stData.fileType = sql_row[8];
			stData.state = std::atoi(sql_row[9]);
			listData.push_back(stData);
		}
		return true;
	}

	bool databaseDI::get_data_approval_list_by_condition(std::list<table_dataApproval>& listData, const int& rows, const int& offset)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "SELECT * FROM t_data_approval ORDER BY CreateTime LIMIT %d OFFSET %d", rows, offset);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_dataApproval stData;
		while (sql_row = mysql_fetch_row(result))
		{
			stData.id = std::atoi(sql_row[0]);
			stData.proposer = sql_row[1];
			stData.department = sql_row[2];
			stData.applicationTime = string_to_datetime(sql_row[3]);
			stData.host = sql_row[4];
			stData.createTime = string_to_datetime(sql_row[5]);
			stData.tool = sql_row[6];
			stData.fileName = sql_row[7];
			stData.fileType = sql_row[8];
			stData.state = std::atoi(sql_row[9]);
			listData.push_back(stData);
		}
		return true;
	}

	bool databaseDI::get_data_approval_count(int& count)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "SELECT COUNT(*) AS total_records FROM t_data_approval");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;


		while (sql_row = mysql_fetch_row(result))
		{
			count = std::atoi(sql_row[0]);
		}
		return true;
	}

	bool databaseDI::update_data_approval_state(const int& id, int& approval)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "update t_data_approval set state=\'%d\' where id=\'%d\'",
			approval,
			id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	bool databaseDI::add_download_approval_info(table_DownloadApproval& stData)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		uint32_t last_id = 0;
		// 执行SQL语句;
		char sql[1024] = { 0 };

		sprintf_s(sql, "insert into t_download_approval(userID,applicationTime,filePath,fileType,fileTime,status) values(\'%d\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\')",
			stData.userID,
			datetime_to_string(stData.applicationTime).c_str(),
			stData.filePath.c_str(),
			stData.fileType.c_str(),
			datetime_to_string(stData.fileTime).c_str(),
			stData.status);

		if (!exec_sql(last_id, sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		stData.id = last_id;
		return true;
	}

	bool databaseDI::get_download_approval_list(std::list<table_DownloadApproval>& listData)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_download_approval");

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_DownloadApproval stData;
		while (sql_row = mysql_fetch_row(result))
		{
			stData.id = std::atoi(sql_row[0]);
			stData.userID = std::atoi(sql_row[1]);
			stData.applicationTime = string_to_datetime(sql_row[2]);
			stData.filePath = sql_row[3];
			stData.fileType = sql_row[4];
			stData.fileTime = string_to_datetime(sql_row[5]);
			stData.status = std::atoi(sql_row[6]);
			listData.push_back(stData);
		}
		return true;
	}

	bool databaseDI::get_download_approval_list_by_userID(std::list<table_DownloadApproval>& listData, const int& userID)
	{
		listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select * from t_download_approval where userID=\'%d\'", userID);

		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		table_DownloadApproval stData;
		while (sql_row = mysql_fetch_row(result))
		{
			stData.id = std::atoi(sql_row[0]);
			stData.userID = std::atoi(sql_row[1]);
			stData.applicationTime = string_to_datetime(sql_row[2]);
			stData.filePath = sql_row[3];
			stData.fileType = sql_row[4];
			stData.fileTime = string_to_datetime(sql_row[5]);
			stData.status = std::atoi(sql_row[6]);
			listData.push_back(stData);
		}
		return true;
	}

	bool databaseDI::update_download_approval_status(const int& id, int& approval)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "update t_download_approval set status=\'%d\' where id=\'%d\'",
			approval,
			id);

		if (!exec_sql(sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		return true;
	}

	//指纹表的操作，16进制添加指纹到数据库中
	bool databaseDI::add_user_finger(unsigned char *tempdata, int &templen, const int &id)
	{
		// 启动事务;
		if (!startup_transaction())
			return false;

		uint32_t last_id = 0;

		std::ostringstream oss;
		oss << std::hex << std::setfill('0');
		for (int i = 0; i < templen; ++i) {
			oss << std::setw(2) << static_cast<int>(tempdata[i]);
		}
		std::string hexStr = oss.str();

		// 执行SQL语句;
		char sql[3072] = { 0 };
		sprintf_s(sql, sizeof(sql), "insert into t_fingerprint(fingerData,fingerLen,registUserid) values(\'%s\',\'%d\',\'%d\')", hexStr.c_str(), templen, id);


		if (!exec_sql(last_id, sql))
		{
			// 回滚事务;
			if (!rollback_transaction())
				return false;
			// 修改数据失败;
			return false;
		}

		// 提交事务;
		if (!commit_transaction())
			return false;

		//fingerprint.id = last_id;
		return true;
	}


	//获取注册的指纹的数据
	bool databaseDI::get_user_finger(std::vector<std::pair<unsigned char *, int>>& vec, int &userid)
	{
		//listData.clear();

		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select fingerData,fingerLen from t_fingerprint where registUserid=\'%d\'", userid);
		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		while (sql_row = mysql_fetch_row(result))
		{
			int templen = std::atoi(sql_row[1]);
			const char *tempdata = sql_row[0];

			// 分配内存存储二进制数据
			unsigned char*  binaryData = new unsigned char[templen];

			// 将十六进制字符串转换为二进制数据
			for (int i = 0; i < templen; i += 2) {
				// 每次处理两个字符
				char byteString[3] = { tempdata[i], tempdata[i + 1], '\0' };
				// 将十六进制字符转换为无符号整数
				binaryData[i / 2] = static_cast<unsigned char>(std::stoul(byteString, nullptr, 16));
			}
			//std::string u_finger2(reinterpret_cast<const char*>(binaryData),templen);
			//u_finger = u_finger2;
			// 存储数据和长度到 vector
			vec.push_back(std::make_pair(binaryData, templen));

		}
		return true;
	}

	bool databaseDI::get_user_finger2(unsigned char *temp, int &templen, int &userid)
	{
		// 结果集声明;
		MYSQL_ROW sql_row;

		// 执行SQL语句;
		char sql[256] = { 0 };
		sprintf_s(sql, "select fingerData,fingerLen from t_fingerprint where registUserid=\'%d\'", userid);
		MYSQL_RES* result = exec_sql_select(sql);
		if (result == nullptr)
			return false;

		while (sql_row = mysql_fetch_row(result))
		{
			int templen = std::atoi(sql_row[1]);
			const char *tempdata = sql_row[0];

			// 分配内存存储二进制数据
			temp = new unsigned char[templen];

			// 将十六进制字符串转换为二进制数据
			for (int i = 0; i < templen; i += 2) {
				// 每次处理两个字符
				char byteString[3] = { tempdata[i], tempdata[i + 1], '\0' };
				// 将十六进制字符转换为无符号整数
				temp[i / 2] = static_cast<unsigned char>(std::stoul(byteString, nullptr, 16));
			}
		}
		return true;
	}

	//bool databaseDI::add_user_finger(const std::string& ffingerdata, int fingerlen)
	//{
	//	const char* query = "INSERT INTO t_fingerprint(fingerData, fingerLen) VALUES (?, ?)";
	//	MYSQL_STMT* stmt = mysql_stmt_init(mysql_);

	//	

	//	if (!stmt) {
	//		qDebug("SQL：mysql_stmt_init() failed\n");
	//		
	//		return false;
	//	}

	//	if (mysql_stmt_prepare(stmt, query, strlen(query))) 
	//	{
	//		qDebug("SQL：mysql_stmt_prepare() failed\n");
	//		
	//		mysql_stmt_close(stmt);
	//		return false;
	//	}

	//	MYSQL_BIND bind[2]; // 绑定参数
	//	memset(bind, 0, sizeof(bind));

	//	// 第一个参数
	//	bind[0].buffer_type = MYSQL_TYPE_STRING;
	//	bind[0].buffer = (char*)ffingerdata.data();
	//	bind[0].buffer_length = ffingerdata.size();  // 使用实际长度

	//	// 第二个参数
	//	bind[1].buffer_type = MYSQL_TYPE_LONG;
	//	bind[1].buffer = (char*)&fingerlen;

	//	// 绑定参数
	//	if (mysql_stmt_bind_param(stmt, bind)) {
	//	
	//		qDebug("SQL：mysql_stmt_bind_param() failed\n");
	//		mysql_stmt_close(stmt);
	//		return false;
	//	}

	//	// 执行语句
	//	if (mysql_stmt_execute(stmt)) {
	//	
	//		qDebug("SQL：mysql_stmt_execute() failed\n");
	//	}
	//	else {
	//		
	//		qDebug("SQL：nsert successful() failed\n");
	//	}

	//	mysql_stmt_close(stmt); // 清理资源
	//	return true;
	//}

}


