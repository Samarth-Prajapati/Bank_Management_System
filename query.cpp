#include "query.h"
void Query::runQuery(MYSQL *conn, const char *query)
{
    if (mysql_query(conn, query))
    {
        cerr << "Query Failed : " << mysql_error(conn) << endl;
    }
}