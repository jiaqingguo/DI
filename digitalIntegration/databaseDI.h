#pragma once

#include "database.h"
#include "globel.h"

#include <map>
#include <list>
#include <string>
#include <unordered_map>
#include <set>

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
		virtual bool open() override;

		// 关闭数据库;
		virtual bool close() override;

		// 业务操作;
	public:
	
		// 用户表
		bool add_user_info(table_user& userInfo);
		bool is_exist_user(const std::string& user);
		bool is_exist_user(const std::string &user, const std::string &password);
		bool get_user_count( int& count);
		bool get_new_regist_user(int &id);//获取最新注册的用户的id
		// 条件查询
		bool get_user_by_condition(table_user& stData, const int& userID,const int& approval = 1);
		bool get_user_list_by_condition(std::list<table_user>& listData, const int& rows, const int& offset);
		bool get_user_list_by_condition(std::list<table_user>& listData, const std::string & fields, const std::string& value );
		bool get_user(table_user& userInfo, const std::string& user);
		bool get_user_list(std::list<table_user>& listData);
		bool get_pop(int& pop, const std::string& user, const std::string& password);
		bool get_pop(int& pop, int &id);
		bool get_approval(int &approval,int &id);
		// 获取用户登录数量;
		bool get_user_login_number(int& loginNumber);

		bool update_user_state(const int& id, int& approval);
		bool update_user_LoginStatus(const int& id, int& status);
		bool del_user(const int& id);

		//指纹表
		bool add_user_finger(unsigned char *tempdata, int &templen, const int &id);
		bool get_user_finger2(unsigned char *temp, int &templen, int &userid);

		bool add_user_finger(const QString &str, int &templen, const int &id);
		bool get_user_finger2(QString &str, int &templen, int &userid);

		//bool get_user_finger(std::string &u_finger, int &templen, int userid);

		// 工具表;
		bool get_tools(std::list<table_tools>& listTools, const int &module);
		bool get_tool(table_tools& stTools, const int& toolId);
		bool get_tools(std::list<table_tools>& listTools);
		bool add_tools( table_tools& stTool);
		bool add_ip_tools(table_ip &stIp);
		

		// ip表;
		bool get_ip_data(std::list<table_ip>& listData);
		//bool get_ip_data(std::list<table_ip>& listData, const int& module);
		bool get_ip_data(std::map<std::string,table_ip>& softMap, const int& module,const int &number);
		
		bool add_ip(table_ip& stData);
		bool del_ip(const int& id);
		bool update_ip_status(const uint32_t& id, int status);
		bool update_ip_all_status();

		//遍历t_ip列表查询ip数量
		bool get_ip_count(const std::string& ip, int& count);
		//在新增工具画面中 显示t_ip中的所有的ip
		bool get_all_ip_data(std::list<table_ip>& listData);
		bool get_one_ip_data(table_ip &stData,const std::string strToolName,const int &number);
		//将t_ip中的username字段设置成用户名，显示已占用
		bool updata_ip_username(const int& status, const std::string& u_name, const uint32_t& id);
		//退出时，t_ip的username字段置0
		bool updata_ipusername(const std::string& u_name);
		bool select_same_name_software(const std::string &software, const int& module);
		bool del_tools(const std::string &software,const int &name);



		// ip配置表;
		//bool get_ip_data_by_number(std::set<std::string> &vecIpData, const int& number);
		bool get_ip_data_by_number(const int& number, std::vector<table_ip_configure>& vecIpData);
		bool get_ip_data_by_number(const int& number, std::map<std::string,table_ip_configure>& vecIpData);
		bool get_all_ip(std::list<table_ip_configure>& listData);
		bool get_host(std::string &hostname,unsigned int &number,std::string &ip);
		bool get_ip_by_software(std::string &ip,std::string software,int &number);



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

		//用户加载表
		bool add_load_software(table_one_load_software &stData);
		bool get_load_software(std::list<table_one_load_software> &listData);
		bool del_load_software(std::string software,int &userid, const int &module);
		bool get_software(std::string software, int &userid,const int &module);

		// 远程账户密码表;
		bool get_account_password(table_account_password& stAccount);
		bool update_account_use_state(const int& id, int& approval);
	};
}
