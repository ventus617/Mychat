#pragma once

#include <mysql.h>
#include <string>
#include <iostream>
#pragma comment(lib,"libmysql.lib")
#include <list>
using namespace std;

class CMySql
{
public:
    CMySql(void);
    ~CMySql(void);
public:                    //ip,�û���,���룬���ݿ⣬�˿ں�
    bool  ConnectMySql(const char* host, const char* user, const char* pass, const char* db, short nport = 3306);
    void  DisConnect();
    bool  SelectMySql(char* szSql, int nColumn, list<string>& lstStr);
    //������ݿ��еı�
    bool GetTables(char* szSql, list<string>& lstStr);
    //���£�ɾ�������롢�޸�
    bool  UpdateMySql(char* szSql);

private:
    MYSQL* m_sock;
    MYSQL_RES* m_results;
    MYSQL_ROW m_record;

};

