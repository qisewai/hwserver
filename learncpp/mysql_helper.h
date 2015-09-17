#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Screen.h"
#include "mysql.h" 

class MysqlHelper {

public:
	MysqlHelper(
		const std::string &dbuser = "ning",
		const std::string &dbpasswd = "2012",
		const std::string &dbip = "localhost",
		const std::string &dbname = "server") {
		con = mysql_init((MYSQL*)0);
		if (con != NULL && mysql_real_connect(con, dbip.c_str(), dbuser.c_str(), dbpasswd.c_str(), dbname.c_str(), 3306/*TCP IP端口*/, NULL/*Unix Socket 连接类型*/, 0/*运行成ODBC数据库标志*/))
		{
			std::cout << "connect db ok!" << std::endl;
		}
		else
		{
			std::cout << "connect database error" << std::endl;
		}

	}

	~MysqlHelper() {

		mysql_close(con);

		std::cout << "disconnect db ok" << std::endl;
	}


	int createTable(const std::string &sql);

	// 返回insert后的id
	int insertItem(const std::string &sql);

	int updateItem(const std::string &sql);

	std::vector<std::map<std::string, std::string>> queryItems(const std::string &sql);




private:

	MYSQL *con;

};

