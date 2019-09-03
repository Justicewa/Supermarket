#include "MySQL.h"
#include <iostream>
#include <vector>
using namespace std;

MySQL::MySQL(){
	_mySQL = mysql_init(nullptr);
}

bool MySQL::ConnectMySQL(const char* host, const char* user, const char* password, const char* dbNAME){
	if (!mysql_real_connect(_mySQL, host, user, password, dbNAME, 3306, nullptr, 0)){
		cout << "���ݿ�����ʧ��" << endl;
		return false;
	}
	mysql_query(_mySQL, "set names 'gbk'");
	cout << "���ӳɹ�!" << endl;

	return true;
}

vector<vector<string>> MySQL::Select(const string& strSQL){
	
	vector<vector<string>> vvRet;
	if (mysql_query(_mySQL, strSQL.c_str())){
		//SQL������Ӧʧ��
		cout << mysql_error(_mySQL) << endl;
		return vvRet;
	}
	//��ȡ��ѯ�ļ�¼��
	MYSQL_RES* mySQLRes =  mysql_store_result(_mySQL);
	if (nullptr == mySQLRes){
		cout << mysql_error(_mySQL) << endl;
		return vvRet;
	}
	//��ȡ��¼���ж��ٸ��ֶ�
	int itemCount = mysql_num_fields(mySQLRes);
	MYSQL_ROW mysqlRow;

	while (mysqlRow = mysql_fetch_row(mySQLRes)){
		//��ȡ��һ����¼
		vector<string> vItem;
		for (size_t i = 0; i < itemCount; ++i){
			vItem.push_back(mysqlRow[i]);
		}
		vvRet.push_back(vItem);
	}

	mysql_free_result(mySQLRes);
	return vvRet;
}

bool MySQL::Insert(const string& strSQL){
	if (mysql_query(_mySQL, strSQL.c_str())){
		//SQL������Ӧʧ��
		cout << mysql_error(_mySQL) << endl;
		return false;
	}
	return true;
}


MySQL::~MySQL(){
	mysql_close(_mySQL);
}