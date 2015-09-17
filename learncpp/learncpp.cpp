// learncpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Screen.h"
#include "mysql.h" 
#include "mysql_helper.h"
#include "tcp_server.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;



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




void test()
{
	MysqlHelper *db = new MysqlHelper();

	db->createTable("CREATE TABLE `user` (\
						`id` int(11) NOT NULL auto_increment,\
						`user_name` tinytext,\
						`user_pwd` tinytext,\
						PRIMARY KEY  (`id`)\
					)");

	// insert
	db->insertItem("insert into user (user_name, user_pwd)values('qisewai', '881109')");

	vector<map<string, string>> query_res;
	query_res = db->queryItems("select * from user where user_name = 'qisewai'");

	cout << "the query result size is" << query_res.size() << endl;
	cout << "the user name is " << query_res[0]["user_name"] << endl;

	delete db;

}


void test_net()
{
	TcpServer *server = new TcpServer();


	server->Run();


	delete server;

}


int main()
{


	

//	test();
	test_net();

	string s1;
	string s2(s1);


	getchar();
	getchar();
    return 0;
}

