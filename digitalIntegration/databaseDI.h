#pragma once

#include "database.h"
#include "globel.h"

#include <map>
#include <list>
#include <string>
#include <unordered_map>

namespace db
{
	// 历史记录数据库接口;
    class  databaseDI : public db::database
	{
	public:

		static databaseDI& Instance();
        // 数据库操作;
	public:
		// 打开数据库;
		virtual bool open()override;

		// 关闭数据库;
		virtual bool close()override;

		// 业务操作;
	public:
		////记录表;
		//bool add_record_info(db_history::record& record_data);
		//bool update_record(const db_history::record& record_data);
		//bool get_record_by_scheme_id(const uint32_t& scheme_id, std::list<db_history::record>& record_list);
		//bool get_record_by_id(const uint32_t& id, db_history::record& record);
		//bool get_all_records(std::list<db_history::record>& record_list);
		//bool delete_record_by_id(const uint32_t& record_id);


			//开火事件表;
		/*bool add_fire_info(db_history::fire& fire);
		bool get_fire_by_record_id(const uint32_t& record_id, std::list<db_history::fire>& fire_list);
		bool delete_fire_by_id(const uint32_t& fire_id);
		bool is_exist_fire_by_id(const uint32_t& id);*/


		// 用户表
		bool add_user_info(table_user& userInfo);
		bool is_exist_user(const std::string& user);
		bool is_exist_user(const std::string &user, const std::string &password);
		bool get_user_count( int& count);
		// 条件查询
		bool get_user_list_by_condition(std::list<table_user>& listData, const int& rows, const int& offset);
		bool get_user_list_by_condition(std::list<table_user>& listData, const std::string & fields, const std::string& value );
		bool get_user(table_user& userInfo, const std::string& user);
		bool get_user_list(std::list<table_user>& listData);
		bool get_pop(int& pop, const std::string& user, const std::string& password);
		bool update_user_state(const int& id, int& approval);
		bool del_user(const int& id);

		// 工具表;
		bool get_tools(std::list<table_tools>& listTools, const int &module);
		bool add_tools( table_tools& stTool);
		bool del_tools(const int& id);

		// ip表;

		bool get_ip_data(std::list<table_ip>& listData, const int& module);
		bool add_ip(table_ip& stData);
		bool del_ip(const int& id);

		// 数据审批表;
		bool add_data_approval_info(table_dataApproval& stData);
		bool get_data_approval_list(std::list<table_dataApproval>& listData);
		bool get_data_approval_list_by_condition(std::list<table_dataApproval>& listData, const int& rows, const int& offset);
		bool get_data_approval_count(int& count);
		bool update_data_approval_state(const int& id, int& approval);
	};
}
