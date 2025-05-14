#include "query.h"
#include "account.h"
int main()
{
    Account account;
    int choice1;
    cout << "--------------------------------------" << endl;
    cout << "Running..." << endl;
    MYSQL *conn = mysql_init(NULL);
    if (!conn)
    {
        cerr << "mysql_init() failed." << endl;
        return 1;
    }
    if (!mysql_real_connect(conn, "localhost", "root", "Apple@2310", "BANKING_SYSTEM", 3306, NULL, 0))
    {
        cerr << "Connection Failed : " << mysql_error(conn) << endl;
        mysql_close(conn);
        return 1;
    }
    cout << "Connected to MySQL Successfully." << endl;
    cout << "--------------------------------------" << endl;
    cout << "------------BANKING SYSTEM------------" << endl;
    do
    {
        cout << "--------------------------------------" << endl;
        cout << "1. Create Account\n2. Login\n3. Exit" << endl;
        cout << "--------------------------------------" << endl;
        cin >> choice1;
        cout << "--------------------------------------" << endl;
        switch (choice1)
        {
        case 1:
            account.createAccount(conn);
            break;
        case 2:
            break;
        case 3:
            cout << "Thank You for using our services." << endl;
            cout << "--------------------------------------" << endl;
            return 0;
        default:
            cout << "Invalid Choice, Try Again." << endl;
            break;
        }
    } while (true);
    mysql_close(conn);
}