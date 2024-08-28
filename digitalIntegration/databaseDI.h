#pragma once

#include "database.h"
#include "globel.h"

#include <map>
#include <list>
#include <string>
#include <unordered_map>

namespace db
{
	// 数据库接口;
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
	
		// 用户表
		bool add_user_info(table_user& userInfo);
		bool is_exist_user(const std::string& user);
		bool is_exist_user(const std::string &user, const std::string &password);
		bool get_user_count( int& count);
		// 条件查询
		bool get_user_by_condition(table_user& stData, const int& userID,const int& approval = 1);
		bool get_user_list_by_condition(std::list<table_user>& listData, const int& rows, const int& offset);
		bool get_user_list_by_condition(std::list<table_user>& listData, const std::string & fields, const std::string& value );
		bool get_user(table_user& userInfo, const std::string& user);
		bool get_user_list(std::list<table_user>& listData);
		bool get_pop(int& pop, const std::string& user, const std::string& password);
		bool update_user_state(const int& id, int& approval);
		bool update_user_LoginStatus(const int& id, int& status);
		bool del_user(const int& id);

		//指纹表
		//bool add_user_finger(table_fingerprint &fingerprint);
		bool add_user_finger(unsigned char *tempdata, int templen);
		bool get_user_finger(std::list<table_fingerprint>& listData);

		// 工具表;

		bool get_tools(std::list<table_tools>& listTools, const int &module);
		bool add_tools( table_tools& stTool);
		bool del_tools(const int& id);

		// ip表;

		bool get_ip_data(std::list<table_ip>& listData, const int& module);
		bool add_ip(table_ip& stData);
		bool del_ip(const int& id);
		bool update_ip_status(const uint32_t& id, int status);
		bool update_ip_all_status();

		//遍历ip列表，看看有没有此ip
		bool get_ip_count(const std::string& ip, int& count);
		//在新增工具画面中 显示数据库中的所有的ip
		bool get_all_ip_data(std::list<table_ip>& listData);
		//将t_ip中的username字段设置成用户名
		bool updata_ip_username(const int& status, const std::string& u_name, const uint32_t& id);
		//客户端退出的时候，该用户所用的ip的username字段置nullptr
		bool updata_ipusername(const std::string& u_name);

		// 数据审批表;
		bool add_data_approval_info(table_dataApproval& stData);
		bool get_data_approval_list(std::list<table_dataApproval>& listData);
		bool get_data_approval_list_by_condition(std::list<table_dataApproval>& listData, const int& rows, const int& offset);
		bool get_data_approval_count(int& count);
		bool update_data_approval_state(const int& id, int& approval);


		// 下载审批表
		bool add_download_approval_info(table_DownloadApproval& stData);
		bool get_download_approval_list(std::list<table_DownloadApproval>& listData);
		bool get_download_approval_list_by_userID(std::list<table_DownloadApproval>& listData,const int &userID);
		bool update_download_approval_status(const int& id, int& approval);
	};
}
