#include "stdafx.h"
#include "mysql_helper.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;


int 
MysqlHelper::createTable(const string &sql)
{

	if (mysql_query(con, sql.c_str()))
	{
		cout << "create table already exists\n" << endl;
		return -1;
	}
	return 0;
}


int 
MysqlHelper::insertItem(const string &sql)
{
	if (mysql_query(con, sql.c_str()))
	{
		cout << "insert item error\n" << endl;
		return -1;
	}
	return mysql_insert_id(con);
}


int
MysqlHelper::updateItem(const string &sql)
{
	if (mysql_query(con, sql.c_str()))
	{
		cout << "yodate item error\n" << endl;
		return 0;
	}
	return mysql_affected_rows(con);
}



vector<map<string, string>> 
MysqlHelper::queryItems(const string &sql)
{
	vector<map<string, string>> query_vec;

	MYSQL_RES *result;

	if (mysql_query(con, sql.c_str()))
	{
		cout << "insert item error\n" << endl;
		return query_vec;
	}
	else// query succeeded, process any data returned by it
	{
		result = mysql_store_result(con);
		if (result)  // there are rows
		{

			auto num_fields = mysql_num_fields(result);
			auto num_rows = mysql_num_rows(result);
			// retrieve rows, then call mysql_free_result(result)
			MYSQL_ROW row;
			MYSQL_FIELD *fields;

			num_fields = mysql_num_fields(result);
			fields = mysql_fetch_fields(result);

			while ((row = mysql_fetch_row(result)))
			{
				// do something with data
				map<string, string> row_map;
				for (decltype(num_fields) i = 0; i < num_fields; i++)
				{
					row_map[fields[i].name] = row[i];
				}

				query_vec.push_back(row_map);
			}
		}
		else  // mysql_store_result() returned nothing; should it have?
		{
			if (mysql_field_count(con) == 0)
			{
				// query does not return data
				// (it was not a SELECT)
				auto num_rows = mysql_affected_rows(con);
			}
			else // mysql_store_result() should have returned data
			{
				fprintf(stderr, "Error: %s\n", mysql_error(con));
			}
		}
		mysql_free_result(result);
	}

	return query_vec;
}




