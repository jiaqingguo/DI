#define _SCL_SECURE_NO_WARNINGS
#include <mysql.h>


#include "databaseDI.h" 

#include <QDebug>

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

		sprintf_s(sql, "insert into t_user(UserName,Password,name,department,JobTitle,PhoneNumber,Pop,CreateTime,approval) values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\',\'%s\',\'%d\')",
			userInfo.UserName.c_str(),
			userInfo.Password.c_str(),
			userInfo.name.c_str(),
			userInfo.department.c_str(),
			userInfo.JobTitle.c_str(),
			userInfo.PhoneNumber.c_str(),
			userInfo.Pop,
			datetime_to_string(userInfo.CreateTime).c_str(),
			userInfo.approval);

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

	bool databaseDI::get_user_count( int& count)
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

			listData.push_back(userInfo);
		}
		return true;
	}

	bool databaseDI::get_user(table_user& userInfo,  const std::string& user)
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

	bool databaseDI::add_tools( table_tools& stTool)
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
			stData.host = sql_row[1];
			stData.ip = sql_row[2];
			stData.module = std::atoi(sql_row[3]);
			stData.used = std::atoi(sql_row[4]);
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

		sprintf_s(sql, "insert into t_ip(host,ip,module,used) values(\'%s\',\'%s\',\'%d\',\'%d\')",
			stData.host.c_str(),
			stData.ip.c_str(),
			stData.module,
			stData.used);

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


	//bool history::add_fire_info(db_history::fire& fire)
	//{
	//	// 启动事务;
	//	if (!startup_transaction())
	//		return false;

	//	// 执行SQL语句;
	//	char sql[128] = { 0 };
	//	sprintf_s(sql, "insert into fire(record_id,entity_id,target_id,type,pos,launch_count) values(\'%d\',\'%d\',\'%d\',\'%d\',\'%d\',\'%d\')",
	//		fire.record_id,
	//		fire.entity_id,
	//		fire.target_id,
	//		fire.type,
	//		fire.pos,
	//		fire.launch_count);

	//	if (!exec_sql(fire.id, sql))
	//	{
	//		// 回滚事务;
	//		if (!rollback_transaction())
	//			return false;
	//		// 修改数据失败;
	//		return false;
	//	}

	//	// 提交事务;
	//	if (!commit_transaction())
	//		return false;

	//	return true;
	//}

	//bool history::get_fire_by_record_id(const uint32_t& record_id, std::list<db_history::fire>& fire_list)
	//{
	//	fire_list.clear();

	//	// 结果集声明;
	//	MYSQL_ROW sql_row;

	//	// 执行SQL语句;
	//	char sql[256] = { 0 };
	//	sprintf_s(sql, "select * from fire where record_id=\'%d\'", record_id);

	//	MYSQL_RES* result = exec_sql_select(sql);
	//	if (result == nullptr)
	//		return false;

	//	db_history::fire fire;
	//	while (sql_row = mysql_fetch_row(result))
	//	{
	//		fire.id = std::atoi(sql_row[0]);
	//		fire.record_id = record_id;
	//		fire.entity_id = std::atoi(sql_row[2]);
	//		fire.target_id = std::atoi(sql_row[3]);
	//		fire.type = std::atoi(sql_row[4]);
	//		fire.pos = std::atoi(sql_row[5]);
	//		fire.launch_count = std::atoi(sql_row[6]);

	//		fire_list.push_back(fire);
	//	}
	//	return false;
	//}

	//bool history::delete_fire_by_id(const uint32_t& fire_id)
	//{
	//	// 启动事务;
	//	if (!startup_transaction())
	//		return false;

	//	// 执行SQL语句;
	//	char sql[256] = { 0 };
	//	sprintf_s(sql, "delete from fire where id = (\'%d\')", fire_id);

	//	if (!exec_sql(sql))
	//	{
	//		// 回滚事务;
	//		if (!rollback_transaction())
	//			return false;
	//		// 修改数据失败;
	//		return false;
	//	}
	//	// 提交事务;
	//	if (!commit_transaction())
	//		return false;

	//	return true;
	//}

	//bool history::is_exist_fire_by_id(const uint32_t& id)
	//{
	//	// 结果集声明;
	//	MYSQL_ROW sql_row;

	//	// 执行SQL语句;
	//	char sql[256] = { 0 };
	//	sprintf_s(sql, "select * from fire where id = \'%d\'", id);

	//	if (!exec_sql_select(sql_row, sql))
	//		return false;
	//	if (!sql_row)
	//		return false;

	//	return true;
	//}
}
