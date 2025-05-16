#include "query.h"
#include "account.h"
int main()
{
    MYSQL *conn;
    MYSQL_RES *result, *result1;
    MYSQL_ROW accountRow, accountRow1;
    Account account;
    string username, password, username1, password1, fetchQuery1, status, password2;
    int choice1, choice2, choice3;
    double amount;
    cout << "--------------------------------------" << endl;
    cout << "Running..." << endl;
    conn = mysql_init(NULL);
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
        cout << "1. Create Account\n2. Admin Login\n3. User Login\n4. Exit" << endl;
        cout << "--------------------------------------" << endl;
        cin >> choice1;
        cout << "--------------------------------------" << endl;
        switch (choice1)
        {
        case 1:
            account.createAccount(conn);
            break;
        case 2:
            cout << "Enter Username : ";
            cin >> username;
            cout << "Enter Password : ";
            cin >> password;
            if (username == "admin" && password == "admin")
            {
                cout << "Admin Login Successful." << endl;
                cout << "--------------------------------------" << endl;
                do
                {
                    cout << "--Admin--\n1. Show all accounts\n2. Search Account\n3. Back" << endl;
                    cout << "--------------------------------------" << endl;
                    cin >> choice2;
                    switch (choice2)
                    {
                    case 1:
                        cout << "--------------------------------------" << endl;
                        account.showAllAccounts(conn);
                        break;
                    case 2:
                        cout << "--------------------------------------" << endl;
                        account.searchAccount(conn);
                        break;
                    case 3:
                        break;
                    default:
                        cout << "--------------------------------------" << endl;
                        cout << "Invalid Choice , Try Again." << endl;
                        break;
                    }
                } while (choice2 != 3);
            }
            else
            {
                cout << "Invalid Username or Password." << endl;
            }
            break;
        case 3:
            cout << "Enter Account Number / Email : ";
            cin >> username1;
            cout << "Enter Password : ";
            cin >> password1;
            cout << "--------------------------------------" << endl;
            fetchQuery1 = "SELECT STATUS FROM ACCOUNTS WHERE (ACCOUNT_NUMBER = '" + username1 + "' OR EMAIL = '" + username1 + "')";
            if (mysql_query(conn, fetchQuery1.c_str()))
            {
                cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
            }
            else
            {
                result1 = mysql_store_result(conn);
                if (result1 && (accountRow1 = mysql_fetch_row(result1)))
                {
                    status = accountRow1[0];
                }
                mysql_free_result(result1);
            }
            if (status == "INACTIVE")
            {
                cout << "Account is closed. Please contact the bank." << endl;
                break;
            }
            if (account.userLogin(conn, username1, password1) == true)
            {
                do
                {
                    cout << "1. Show Account Details\n2. Deposit\n3. Withdraw\n4. Balance Enquiry\n5. Transfer\n6. Transaction History\n7. Close Account\n8. Back" << endl;
                    cout << "--------------------------------------" << endl;
                    cin >> choice3;
                    switch (choice3)
                    {
                    case 1:
                        cout << "--------------------------------------" << endl;
                        account.displayAccount(conn, username1);
                        break;
                    case 2:
                        cout << "--------------------------------------" << endl;
                        cout << "Enter Amount : ";
                        cin >> amount;
                        cout << "Enter Password : ";
                        cin >> password2;
                        cout << "--------------------------------------" << endl;
                        account.deposit(conn, username1, password2, amount);
                        break;
                    case 3:
                        cout << "--------------------------------------" << endl;
                        cout << "Enter Amount : ";
                        cin >> amount;
                        cout << "Enter Password : ";
                        cin >> password2;
                        account.withdraw(conn, username1, password2, amount);
                        break;
                    case 4:
                        cout << "--------------------------------------" << endl;
                        account.balanceEnquiry(conn, username1);
                        break;
                    case 5:
                        cout << "--------------------------------------" << endl;
                        account.transfer();
                        break;
                    case 6:
                        cout << "--------------------------------------" << endl;
                        account.transactionHistory();
                        break;
                    case 7:
                        cout << "--------------------------------------" << endl;
                        if (account.closeAccount(conn, username1) == true)
                        {
                            choice3 = 8;
                        }
                        break;
                    case 8:
                        break;
                    default:
                        cout << "--------------------------------------" << endl;
                        cout << "Invalid Choice , Try Again." << endl;
                        cout << "--------------------------------------" << endl;
                        break;
                    }
                } while (choice3 != 8);
            }
            break;
        case 4:
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