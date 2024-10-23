
#include "database.h"

#include <iomanip>
#include <istream>
#include <sstream>

#include <QDebug>

namespace db
{
	void database::setDbLoginData(const std::string& server, const std::string& user, const std::string& password)
	{
		server_ = server;
		user_ = user;
		pwd_ = password;
	}
	MYSQL* database::get_sql_query()
	{
		if (mysql_ == nullptr)
			return nullptr;
		return mysql_;
	}

	bool database::exec_sql_select(char**& sql_row, const std::string& sql)
	{
		MYSQL_RES *result = nullptr;

		if (mysql_ == nullptr)
			return false;

		if (mysql_real_query(mysql_, sql.c_str(), (unsigned long)sql.size()) != 0)
		{
			std::string error = mysql_error(mysql_);
			
			qDebug()<<QString::fromStdString( sql)<<  QString::fromStdString(error);
			return false;
		}
		else
		{
			result = mysql_store_result(mysql_);
			if (result == nullptr)
				return false;

			sql_row = mysql_fetch_row(result);
		}

		if (result != NULL)
			mysql_free_result(result);

		return true;
	}

	MYSQL_RES* database::exec_sql_select(const std::string& sql)
	{
		MYSQL_RES* result = nullptr;

		if (mysql_ == nullptr)
			return nullptr;
		if (mysql_real_query(mysql_, sql.c_str(), (unsigned long)sql.size()) != 0)
		{
			std::string error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return nullptr;
		}
		else
		{
			result = mysql_store_result(mysql_);
		}

		return result;
	}

	bool database::exec_sql(uint32_t& lastId, const std::string& sql)
	{
		if (mysql_ == nullptr)
			return false;
		if (mysql_real_query(mysql_, sql.c_str(), (unsigned long)sql.size()) != 0)
		{
			int erriD=mysql_errno(mysql_);
			std::string error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		// 获取被更新行数id;
		lastId = (unsigned int)mysql_insert_id(mysql_);

		return true;
	}

	bool database::exec_sql(const std::string& sql)
	{
		if (mysql_ == nullptr)
			return false;
		if (mysql_real_query(mysql_, sql.c_str(), (unsigned long)sql.size()) != 0)
		{
			std::string error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}
		return true;
	}

	bool database::exec_sql_write_binary(const std::string& sql, const uint8_t* buffer, const uint32_t& length)
	{		
		MYSQL_STMT* stmt = mysql_stmt_init(mysql_);
		std::string error;
		if (mysql_stmt_prepare(stmt, sql.c_str(), (unsigned long)strlen(sql.c_str())))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		MYSQL_BIND param = { 0 };
		param.buffer_type = MYSQL_TYPE_MEDIUM_BLOB;
		param.buffer = NULL;
		param.is_null = 0;
		param.length = NULL;
		if (mysql_stmt_bind_param(stmt, &param))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		if (mysql_stmt_send_long_data(stmt, 0, (const char*)buffer, length))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		if (mysql_stmt_execute(stmt))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		if (mysql_stmt_close(stmt))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}
		return true;
	}

	bool database::exec_sql_write_binary(uint32_t& lastId, const std::string& sql, const uint8_t* buffer, const uint32_t& length)
	{
		MYSQL_STMT* stmt = mysql_stmt_init(mysql_);
		std::string error;
		if (mysql_stmt_prepare(stmt, sql.c_str(), (unsigned long)strlen(sql.c_str())))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		MYSQL_BIND param = { 0 };
		param.buffer_type = MYSQL_TYPE_MEDIUM_BLOB;
		param.buffer = NULL;
		param.is_null = 0;
		param.length = NULL;
		if (mysql_stmt_bind_param(stmt, &param))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		if (mysql_stmt_send_long_data(stmt, 0, (const char*)buffer, length))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		if (mysql_stmt_execute(stmt))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		if (mysql_stmt_close(stmt))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}
		// 获取被更新行数id;
		lastId = (unsigned int)mysql_insert_id(mysql_);
		return true;
	}

	bool database::exec_sql_read_binary(const std::string& sql, uint8_t*& buffer, uint32_t& length)
	{
		MYSQL_STMT* stmt = mysql_stmt_init(mysql_);
		std::string error;
		if (mysql_stmt_prepare(stmt, sql.c_str(), (unsigned long)strlen(sql.c_str())))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		MYSQL_BIND result = { 0 };
		result.buffer_type = MYSQL_TYPE_MEDIUM_BLOB;
		result.buffer = 0;
		result.buffer_length = 0;
		unsigned long total_length = 0;
		result.length = &total_length;
		if (mysql_stmt_bind_result(stmt, &result))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		if (mysql_stmt_execute(stmt))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		if (mysql_stmt_store_result(stmt))
		{
			error = mysql_error(mysql_);
			qDebug("SQL：%s\nError：%s", sql.c_str(), error.c_str());
			return false;
		}

		while (1)
		{
			int ret = mysql_stmt_fetch(stmt);
			if(ret != 0 && ret != MYSQL_DATA_TRUNCATED)
				break;

			if (total_length > 0)
			{
				result.buffer = malloc(total_length);
				memset(result.buffer, 0, total_length);
				result.buffer_length = total_length;
				mysql_stmt_fetch_column(stmt, &result, 0, 0);
			}
			
			length = total_length;
			buffer = new uint8_t[length]{0};
			memcpy_s(buffer, length, (uint8_t*)result.buffer, total_length);
		}
		mysql_stmt_close(stmt);
		return true;
	}

	bool database::startup_transaction()
	{
		if (mysql_ == nullptr)
			return false;

		// 启动事务;
		if (mysql_real_query(mysql_, "START TRANSACTION", (unsigned long)strlen("START TRANSACTION")))
		{
			std::string error = mysql_error(mysql_);
			qDebug("启动事务失败!\nError: %s", error.c_str());
			return false;
		}

		return true;
	}

	bool database::commit_transaction()
	{
		if (mysql_ == nullptr)
			return false;

		// 提交事务;
		if (mysql_real_query(mysql_, "COMMIT", (unsigned long)strlen("COMMIT")))
		{
			std::string error = mysql_error(mysql_);
			qDebug("提交事务失败!\nError: %s", error.c_str());
			return false;
		}

		return true;
	}

	bool database::rollback_transaction()
	{
		if (mysql_ == nullptr)
			return false;

		// 回滚事务;
		if (mysql_real_query(mysql_, "ROLLBACK", (unsigned long)strlen("ROLLBACK")))
		{
			std::string error = mysql_error(mysql_);
			qDebug("回滚事务失败!\nError: %s", error.c_str());
			return false;
		}

		return true;
	}

	bool database::create_config(const char* filepath)
	{
	
		return false;
	}

	

	time_t database::string_to_datetime(const std::string& str)
	{
		tm tm_;
		int year = 0;
		int month = 0;
		int day = 0;
		int hour = 0;
		int minute = 0;
		int second = 0;
		sscanf(str.data(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		tm_.tm_year = year - 1900;
		tm_.tm_mon = month - 1;
		tm_.tm_mday = day;
		tm_.tm_hour = hour;
		tm_.tm_min = minute;
		tm_.tm_sec = second;
		tm_.tm_isdst = 0;
		time_t t_ = mktime(&tm_);
		return t_;

	/*	std::tm tm = {};
		std::istringstream ss(str);
		ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
		if (ss.fail()) {
			throw std::runtime_error("Failed to parse time string.");
		}
		return mktime(&tm);*/
	}

	std::string database::datetime_to_string(const time_t& timeValue)
	{
		/*std::stringstream ss;
		ss << std::put_time(std::localtime(&timeValue), "%Y-%m-%d %H:%M:%S");
		return ss.str();*/
		// 使用 std::localtime 转换 time_t 到 tm
		std::tm* localTime = std::localtime(&timeValue);
		if (!localTime) {
			// 处理 localtime 失败的情况
			return "Invalid time";
		}

		std::stringstream ss;
		ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
		return ss.str();
		// 第二种
	/*	char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timeValue));
		return std::string(buffer);*/
	}

	uint64_t database::datetime_to_uint64(const time_t&tm)
	{
		std::chrono::system_clock::time_point  time_stamp = std::chrono::system_clock::from_time_t(tm);
	     return std::chrono::time_point_cast<std::chrono::milliseconds>(time_stamp).time_since_epoch().count();
	}

}
