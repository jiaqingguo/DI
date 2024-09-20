#pragma once

#include <string>
#include <time.h>
#include <mysql.h>
//namespace tinyxml2
//{
//	class XMLElement;
//	class XMLDocument;
//}
////
//struct st_mysql;
//struct st_mysql_res;

namespace db
{
	// 数据库接口;
	class database
	{
	public:
		database() = default;
		virtual ~database() = default;
	public:
		virtual bool open() = 0;
		virtual bool close() = 0;
		void setDbLoginData(const std::string & server, const std::string& user, const std::string& password);
	protected:
		// 获取SQL句柄;
		MYSQL* get_sql_query();
		// 执行SQL语句;
		bool exec_sql_select(char**& sql_row, const std::string& sql);
		MYSQL_RES* exec_sql_select(const std::string& sql);
		bool exec_sql(uint32_t& lastId, const std::string& sql);
		bool exec_sql(const std::string& sql);
		bool exec_sql_write_binary(uint32_t& lastId, const std::string& sql, const uint8_t* buffer, const uint32_t& length);
		bool exec_sql_write_binary(const std::string& sql, const uint8_t* buffer, const uint32_t& length);
		bool exec_sql_read_binary(const std::string& sql, uint8_t*& buffer, uint32_t& length);
		// 数据库启动事务;
		bool startup_transaction();
		// 数据库提交事务;
		bool commit_transaction();
		// 数据库回滚事务;
		bool rollback_transaction();
		// 创建配置文件;
		bool create_config(const char* filepath);

		// string转time_t;
		time_t string_to_datetime(const std::string& str);
		// time_t转string;
		std::string datetime_to_string(const time_t& tm);

		uint64_t datetime_to_uint64(const time_t&tm);
	protected:
		MYSQL*					mysql_						= nullptr;					// mysql句柄;
		
		std::string				server_						= "192.168.0.119";		// 服务地址;
		std::string				user_						= "root";					// 用户名;
		std::string				pwd_						= "123456";					// 密码;
		uint16_t				port_						= 3306;						// 端口号;
	
        std::string				m_diDatabase				= "db_di";				// ;
	};
}
