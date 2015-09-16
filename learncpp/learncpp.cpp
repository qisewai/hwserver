// learncpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Screen.h"
#include "mysql.h" 


using std::cout;
using std::cin;
using std::endl;
using std::string;



class Sales_data {

	friend std::istream &read(std::istream &is, Sales_data &item);

	friend std::ostream &print(std::ostream &os, Sales_data &item);

public:
	// 构造函数！！
	Sales_data() = default;
	explicit Sales_data(const string &s): bookNum(s) {}
	Sales_data(const string &s, unsigned unit, double price) :
		bookNum(s),
		unit_sold(unit),
		revenue{ price * unit } {}
	
	Sales_data(std::istream &is);
	// 拷贝构造函数
	
	Sales_data(const Sales_data &orig) :
		bookNum("test"),
		unit_sold(orig.unit_sold),
		revenue(orig.revenue)
	{
		cout << "copy" << endl;
	}
	
	

	std::string isbn() const { return bookNum; };
	Sales_data &combine(const Sales_data&);

private:
	double avg_price() const;

	std::string bookNum;
	unsigned unit_sold = 0;
	double revenue = 0.0;

};





Sales_data::Sales_data(std::istream &is)
{
	read(is, *this);
}



std::istream &read(std::istream &is, Sales_data &item)
{
	double price;
	is >> item.bookNum >> item.unit_sold >> price;

	item.revenue = item.unit_sold * price;

	return is;
}


std::ostream &print(std::ostream &os, Sales_data &item)
{
	os << item.isbn() << ":" << item.unit_sold << ":" << item.revenue << endl;
	return os;
}



Sales_data &Sales_data::combine(const Sales_data &rhs)
{
	unit_sold += rhs.unit_sold;
	revenue += rhs.revenue;
	return *this;
}

inline double Sales_data::avg_price() const
{
	if (unit_sold)
	{
		return revenue / unit_sold;
	}
	else
	{
		return 0.0;
	}
}




struct Person {

	string getName() const { return name; };
	string getAddress() const { return address; };

	string name;
	string address;



};

class MysqlHelper {

public:
	MysqlHelper(
		const string &dbuser = "ning", 
		const string &dbpasswd = "2012", 
		const string &dbip = "localhost",
		const string &dbname = "server") {
		con = mysql_init((MYSQL*)0);
		if (con != NULL && mysql_real_connect(con, dbip.c_str(), dbuser.c_str(), dbpasswd.c_str(), dbname.c_str(), 3306/*TCP IP端口*/, NULL/*Unix Socket 连接类型*/, 0/*运行成ODBC数据库标志*/))
		{
			std::cout << "connect db ok!" << endl;
		}
		else
		{
			std::cout << "connect database error" << endl;
		}

	}

	~MysqlHelper() {

		mysql_close(con);

		std::cout << "disconnect db ok" << endl;
	}


	int createTable(const string &sql)
	{

		if (mysql_query(con, sql.c_str()))
		{
			cout << "create table already exists\n" << endl;
			return -1;
		}
		return 0;
	}


	int insertItem(const string &sql)
	{
		if (mysql_query(con, sql.c_str()))
		{
			cout << "insert item error\n" << endl;
			return -1;
		}
		return 0;
	}


	MYSQL_FIELD


private:

	MYSQL *con;

};


void test()
{
	MysqlHelper *sqlh = new MysqlHelper();

	sqlh->createTable("CREATE TABLE `USER` (\
						`ID` int(11) NOT NULL auto_increment,\
						`USER_NAME` tinytext,\
						`USER_PWD` tinytext,\
						PRIMARY KEY  (`ID`)\
					)");


	delete sqlh;

}


int main()
{
	MYSQL * con; 
	MYSQL_RES *res;
	MYSQL_ROW row;

	


		test();
	





	string s1;
	string s2(s1);


	getchar();
	getchar();
    return 0;
}

