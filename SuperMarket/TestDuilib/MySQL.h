#pragma once

#include<WinSock2.h>
#include <mysql.h>
#include <string>
using std::string;
#include <vector>
using namespace std;


class MySQL{
public:
	MySQL();
	bool ConnectMySQL(const char* host, const char* user, const char* password, const char* dbNAME);
	~MySQL();

	bool Insert(const string& strSQL);
	bool UpDate(const string& strSQL);
	bool Delete(const string& strSQL);
	vector<vector<string>> Select(const string& strSQL);
	
private:
	MYSQL* _mySQL;
};