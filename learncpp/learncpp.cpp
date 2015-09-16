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


constexpr int a = 10;
constexpr const int *pa = &a;


int main()
{
	MYSQL * con; 
	MYSQL_RES *res;
	MYSQL_ROW row;

	char tmp[400];
	//database configuartion
	char dbuser[30] = "ning";
	char dbpasswd[30] = "2012";
	char dbip[30] = "localhost";
	char dbname[50] = "server";
	char tablename[50] = "test";
	char *query = NULL;

	int x;
	int y;
	int rt;//return value
	unsigned int t;

	int count = 0;

	printf("input x,y\n");
	scanf_s("%d,%d", &x, &y);
	fflush(stdin);
	printf("input over\n");
	con = mysql_init((MYSQL*)0);


	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306/*TCP IP端口*/, NULL/*Unix Socket 连接类型*/, 0/*运行成ODBC数据库标志*/))
	{
		if (!mysql_select_db(con, dbname))
		{
			printf("Select successfully the database!\n");

			con->reconnect = 1;

			query = "set names \'GBK\'";
					//mysql_query(con,"set names \'GBK\'"); 
			rt = mysql_real_query(con, query, strlen(query));
			if (rt)
			{
					printf("Error making query: %s !!!\n", mysql_error(con));
			}
			else
			{
				printf("query %s succeed!\n", query);
			}

		}
	}
	else
	{
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);

	}



	string s1;
	string s2(s1);


	getchar();
	getchar();
    return 0;
}

