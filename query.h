#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <mysql.h>
using namespace std;
class Query
{
public:
    void runQuery(MYSQL *conn, const char *query);
};
#endif