#include "account.h"
Account::Account() {}
Account::Account(string name, string email, string address, string password, string contact, double balance)
{
    this->name = name;
    this->email = email;
    this->address = address;
    this->password = password;
    this->contact = contact;
    this->balance = balance;
}
void Account::createAccount(MYSQL *conn)
{
    MYSQL_RES *res, *result;
    MYSQL_ROW row, accountRow;
    string confirmPassword, insertQuery, fetchQuery, accountNumber;
    bool isValid = true;
    cout << "Enter Full Name : " << endl;
    cin.ignore();
    getline(cin, this->name);
    while (!validate.validateFullName(this->name))
    {
        cout << "Invalid Name , Try again. " << endl;
        getline(cin, this->name);
    }
    cout << "--------------------------------------" << endl;
    cout << "Enter Email : " << endl;
    cin >> this->email;
    while (!validate.validateEmail(this->email))
    {
        cout << "Invalid Email , Try again. " << endl;
        cin >> this->email;
    }
    cout << "--------------------------------------" << endl;
    cout << "Enter Contact Number : " << endl;
    cin >> this->contact;
    while (!validate.validateContact(this->contact))
    {
        cout << "Invalid Contact Number , Try again. " << endl;
        cin >> this->contact;
    }
    cout << "--------------------------------------" << endl;
    cout << "Enter Address : " << endl;
    cin.ignore();
    getline(cin, this->address);
    while (!validate.validateAddress(this->address))
    {
        cout << "Invalid Address , Try again. " << endl;
        getline(cin, this->address);
    }
    cout << "--------------------------------------" << endl;
    while (isValid)
    {
        cout << "Enter Password : " << endl;
        cin >> this->password;
        while (!validate.validatePassword(this->password))
        {
            cout << "Invalid Password , Try again. " << endl;
            cin >> this->password;
        }
        cout << "--------------------------------------" << endl;
        cout << "Confirm Password : " << endl;
        cin >> confirmPassword;
        while (this->password != confirmPassword)
        {
            cout << "Password Mismatch , Try again. " << endl;
            cin >> confirmPassword;
        }
        if (this->password == confirmPassword)
        {
            isValid = false;
        }
    }
    cout << "--------------------------------------" << endl;
    cout << "Enter Initial Balance ( Minimum Rs.500 ) : " << endl;
    cin >> this->balance;
    while (!validate.validateBalance(this->balance))
    {
        cout << "Minimum Rs.500 required." << endl;
        cin >> this->balance;
    }
    insertQuery = "INSERT INTO ACCOUNTS(NAME,EMAIL,CONTACT,ADDRESS,PASSWORD,BALANCE,STATUS) VALUES('" + this->name + "','" + this->email + "','" + this->contact + "','" + this->address + "','" + this->password + "','" + to_string(this->balance) + "','ACTIVE')";
    query.runQuery(conn, insertQuery.c_str());
    cout << "--------------------------------------" << endl;
    cout << "Account Created Successfully." << endl;
    cout << "--------------------------------------" << endl;
    if (mysql_query(conn, "SELECT LAST_INSERT_ID()"))
    {
        cerr << "Failed to retrieve Account Number : " << mysql_error(conn) << endl;
    }
    else
    {
        res = mysql_store_result(conn);
        if (res && (row = mysql_fetch_row(res)))
        {
            accountNumber = row[0];
            mysql_free_result(res);
            fetchQuery = "SELECT ACCOUNT_NUMBER, NAME, EMAIL, CONTACT, ADDRESS, BALANCE FROM ACCOUNTS WHERE ACCOUNT_NUMBER = " + accountNumber;
            if (mysql_query(conn, fetchQuery.c_str()))
            {
                cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
            }
            else
            {
                result = mysql_store_result(conn);
                if (result && (accountRow = mysql_fetch_row(result)))
                {
                    cout << "Account details -" << endl;
                    cout << "Account Number  : " << accountRow[0] << endl;
                    cout << "Name            : " << accountRow[1] << endl;
                    cout << "Email           : " << accountRow[2] << endl;
                    cout << "Contact         : " << accountRow[3] << endl;
                    cout << "Address         : " << accountRow[4] << endl;
                    cout << "Balance         : Rs." << accountRow[5] << endl;
                }
                mysql_free_result(result);
            }
        }
    }
}
bool Account::userLogin(MYSQL *conn, string username1, string password1)
{
    MYSQL_RES *result;
    MYSQL_ROW accountRow;
    string fetchQuery;
    fetchQuery = "SELECT * FROM ACCOUNTS WHERE (ACCOUNT_NUMBER = '" + username1 + "' OR EMAIL = '" + username1 + "') AND PASSWORD = '" + password1 + "'";
    if (mysql_query(conn, fetchQuery.c_str()))
    {
        cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
        cout << "--------------------------------------" << endl;
        return false;
    }
    result = mysql_store_result(conn);
    if (result && mysql_num_rows(result) > 0)
    {
        mysql_free_result(result);
        cout << "Account Found , Login Successful. " << endl;
        cout << "--------------------------------------" << endl;
        return true;
    }
    else
    {
        cout << "Username / Password Incorrect , Login Failed. " << endl;
        cout << "--------------------------------------" << endl;
        if (result)
        {
            mysql_free_result(result);
        }
        return false;
    }
}
void Account::displayAccount(MYSQL *conn, string username1)
{
    MYSQL_RES *result;
    MYSQL_ROW accountRow;
    string fetchQuery;
    fetchQuery = "SELECT ACCOUNT_NUMBER, NAME, EMAIL, CONTACT, ADDRESS, BALANCE FROM ACCOUNTS WHERE (ACCOUNT_NUMBER = '" + username1 + "' OR EMAIL = '" + username1 + "')";
    if (mysql_query(conn, fetchQuery.c_str()))
    {
        cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
    }
    else
    {
        result = mysql_store_result(conn);
        if (result && (accountRow = mysql_fetch_row(result)))
        {
            cout << "Account Number  : " << accountRow[0] << endl;
            cout << "Name            : " << accountRow[1] << endl;
            cout << "Email           : " << accountRow[2] << endl;
            cout << "Contact         : " << accountRow[3] << endl;
            cout << "Address         : " << accountRow[4] << endl;
            cout << "Balance         : Rs." << accountRow[5] << endl;
            cout << "--------------------------------------" << endl;
        }
        mysql_free_result(result);
    }
}
void Account::deposit(MYSQL *conn, string username1, string password2, double amount)
{
    MYSQL_RES *result;
    MYSQL_ROW accountRow;
    string fetchQuery, balance, password, updateQuery, accountNumber, insertQuery;
    double newBalance;
    fetchQuery = "SELECT ACCOUNT_NUMBER,BALANCE,PASSWORD FROM ACCOUNTS WHERE (ACCOUNT_NUMBER = '" + username1 + "' OR EMAIL = '" + username1 + "')";
    if (mysql_query(conn, fetchQuery.c_str()))
    {
        cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
    }
    else
    {
        result = mysql_store_result(conn);
        if (result && (accountRow = mysql_fetch_row(result)))
        {
            accountNumber = accountRow[0];
            balance = accountRow[1];
            password = accountRow[2];
        }
        mysql_free_result(result);
    }
    if (password == password2)
    {
        newBalance = stod(balance) + amount;
        updateQuery = "UPDATE ACCOUNTS SET BALANCE = " + to_string(newBalance) + " WHERE ACCOUNT_NUMBER = '" + accountNumber + "'";
        if (mysql_query(conn, updateQuery.c_str()))
        {
            cerr << "Failed to deposit : " << mysql_error(conn) << endl;
            cout << "--------------------------------------" << endl;
        }
        else
        {
            cout << "Deposit Successful." << endl;
            insertQuery = "INSERT INTO TRANSACTIONS (FROM_ACCOUNT, TYPE, AMOUNT, UPDATED_BALANCE, DESCRIPTION) VALUES('" + accountNumber + "','DEPOSIT','" + to_string(amount) + "','" + to_string(newBalance) + "','Cash Deposit')";
            query.runQuery(conn, insertQuery.c_str());
        }
    }
    else
    {
        cout << "Invalid Password." << endl;
        cout << "--------------------------------------" << endl;
    }
}
bool Account::withdraw(MYSQL *conn, string username1, string password2, double amount)
{
    MYSQL_RES *result;
    MYSQL_ROW accountRow;
    string fetchQuery, balance, password, updateQuery, accountNumber, insertQuery;
    double newBalance;
    fetchQuery = "SELECT ACCOUNT_NUMBER,BALANCE,PASSWORD FROM ACCOUNTS WHERE (ACCOUNT_NUMBER = '" + username1 + "' OR EMAIL = '" + username1 + "')";
    if (mysql_query(conn, fetchQuery.c_str()))
    {
        cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
        cout << "--------------------------------------" << endl;
        return false;
    }
    else
    {
        result = mysql_store_result(conn);
        if (result && (accountRow = mysql_fetch_row(result)))
        {
            accountNumber = accountRow[0];
            balance = accountRow[1];
            password = accountRow[2];
        }
        mysql_free_result(result);
    }
    if (password == password2)
    {
        newBalance = stod(balance) - amount;
        if (newBalance < 0)
        {
            cout << "--------------------------------------" << endl;
            cout << "Insufficient Balance." << endl;
            cout << "--------------------------------------" << endl;
            return false;
        }
        else if (newBalance < 500)
        {
            cout << "--------------------------------------" << endl;
            cout << "Minimum Rs.500 required in account." << endl;
            cout << "--------------------------------------" << endl;
            return false;
        }
        else
        {
            updateQuery = "UPDATE ACCOUNTS SET BALANCE = " + to_string(newBalance) + " WHERE ACCOUNT_NUMBER = '" + accountNumber + "'";
            if (mysql_query(conn, updateQuery.c_str()))
            {
                cout << "--------------------------------------" << endl;
                cerr << "Failed to deposit : " << mysql_error(conn) << endl;
                cout << "--------------------------------------" << endl;
                return false;
            }
            else
            {
                cout << "--------------------------------------" << endl;
                cout << "Withdraw Successful." << endl;
                balanceEnquiry(conn, username1);
                insertQuery = "INSERT INTO TRANSACTIONS (FROM_ACCOUNT, TYPE, AMOUNT, UPDATED_BALANCE, DESCRIPTION) VALUES('" + accountNumber + "','WITHDRAWAL','" + to_string(amount) + "','" + to_string(newBalance) + "','Cash Withdraw')";
                query.runQuery(conn, insertQuery.c_str());
                return true;
            }
        }
    }
    else
    {
        cout << "Invalid Password." << endl;
        cout << "--------------------------------------" << endl;
        return false;
    }
}
void Account::balanceEnquiry(MYSQL *conn, string username1)
{
    MYSQL_RES *result;
    MYSQL_ROW accountRow;
    string fetchQuery;
    fetchQuery = "SELECT BALANCE FROM ACCOUNTS WHERE (ACCOUNT_NUMBER = '" + username1 + "' OR EMAIL = '" + username1 + "')";
    if (mysql_query(conn, fetchQuery.c_str()))
    {
        cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
    }
    else
    {
        result = mysql_store_result(conn);
        if (result && (accountRow = mysql_fetch_row(result)))
        {
            cout << "Current Balance : Rs." << accountRow[0] << endl;
            cout << "--------------------------------------" << endl;
        }
        mysql_free_result(result);
    }
}
void Account::transfer(MYSQL *conn, string username1, string accountNumber, string password2, double amount)
{
    MYSQL_RES *result, *result1;
    MYSQL_ROW accountRow, accountRow1;
    string fetchQuery, password, insertQuery, balance1, fetchQuery1, balance2, insertQuery1;
    double newBalance1, newBalance2;
    if (withdraw(conn, username1, password2, amount) == true)
    {
        fetchQuery1 = "SELECT ACCOUNT_NUMBER,BALANCE FROM ACCOUNTS WHERE (ACCOUNT_NUMBER = '" + username1 + "' OR EMAIL = '" + username1 + "')";
        if (mysql_query(conn, fetchQuery1.c_str()))
        {
            cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
        }
        else
        {
            result1 = mysql_store_result(conn);
            if (result1 && (accountRow1 = mysql_fetch_row(result1)))
            {
                username1 = accountRow1[0];
                balance2 = accountRow1[1];
                newBalance2 = stod(balance2) - amount;
            }
            mysql_free_result(result1);
        }
        fetchQuery = "SELECT ACCOUNT_NUMBER,PASSWORD,BALANCE FROM ACCOUNTS WHERE ACCOUNT_NUMBER = " + accountNumber;
        if (mysql_query(conn, fetchQuery.c_str()))
        {
            cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
        }
        else
        {
            result = mysql_store_result(conn);
            if (result && (accountRow = mysql_fetch_row(result)))
            {
                accountNumber = accountRow[0];
                password = accountRow[1];
                balance1 = accountRow[2];
                newBalance1 = stod(balance1) + amount;
                cout << "Reciever Account Found." << endl;
                deposit(conn, accountNumber, password, amount);
                insertQuery1 = "INSERT INTO TRANSACTIONS (FROM_ACCOUNT, TO_ACCOUNT, TYPE, AMOUNT, UPDATED_BALANCE, DESCRIPTION) VALUES('" + username1 + "','" + accountNumber + "','TRANSFER','" + to_string(amount) + "','" + to_string(newBalance2) + "','Send Transfer')";
                query.runQuery(conn, insertQuery1.c_str());
                insertQuery = "INSERT INTO TRANSACTIONS (FROM_ACCOUNT, TO_ACCOUNT, TYPE, AMOUNT, UPDATED_BALANCE, DESCRIPTION) VALUES('" + username1 + "','" + accountNumber + "','TRANSFER','" + to_string(amount) + "','" + to_string(newBalance1) + "','Recieved Transfer')";
                query.runQuery(conn, insertQuery.c_str());
                cout << "--------------------------------------" << endl;
            }
            else
            {
                cout << "Account not found." << endl;
            }
            mysql_free_result(result);
        }
    }
}
void Account::transactionHistory(MYSQL *conn, string username1)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    int num_fields, rowCount;
    string queryStr;
    string accountDetails[5] = {"TO_ACCOUNT", "TYPE", "AMOUNT", "UPDATED_BALANCE", "TIMESTAMP"};

    queryStr = "SELECT TO_ACCOUNT, TYPE, AMOUNT, UPDATED_BALANCE, TIMESTAMP FROM TRANSACTIONS WHERE FROM_ACCOUNT = '" + username1 + "' ORDER BY TIMESTAMP DESC";

    if (mysql_query(conn, queryStr.c_str()))
    {
        cerr << "Query Failed : " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_store_result(conn);
    if (!res)
    {
        cerr << "Result Fetch Failed : " << mysql_error(conn) << endl;
        return;
    }

    num_fields = mysql_num_fields(res);
    rowCount = 1;

    cout << "Transaction Details -" << endl;
    while ((row = mysql_fetch_row(res)))
    {
        cout << "--------------------------------------" << endl;
        cout << "Transaction " << rowCount << " : " << endl;
        for (int i = 0; i < num_fields; i++)
        {
            cout << accountDetails[i] << " : " << (row[i] ? row[i] : " ") << endl;
        }
        rowCount++;
        cout << endl;
    }

    mysql_free_result(res);
    cout << "--------------------------------------" << endl;
}
void Account::searchAccount(MYSQL *conn)
{
    MYSQL_RES *result;
    MYSQL_ROW accountRow, row;
    int choice1, num_fields, rowCount;
    string accountNumber, name, fetchQuery;
    do
    {
        cout << "Search Account Using\n1. Account Number\n2. Name\n3. Back" << endl;
        cout << "--------------------------------------" << endl;
        cin >> choice1;
        switch (choice1)
        {
        case 1:
            cout << "--------------------------------------" << endl;
            cout << "Enter Account Number : ";
            cin >> accountNumber;
            cout << "--------------------------------------" << endl;
            fetchQuery = "SELECT ACCOUNT_NUMBER, NAME, EMAIL, CONTACT, ADDRESS, BALANCE,STATUS FROM ACCOUNTS WHERE ACCOUNT_NUMBER = " + accountNumber;
            if (mysql_query(conn, fetchQuery.c_str()))
            {
                cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
            }
            else
            {
                result = mysql_store_result(conn);
                if (result && (accountRow = mysql_fetch_row(result)))
                {
                    cout << "Account Found -" << endl;
                    cout << "Account Number  : " << accountRow[0] << endl;
                    cout << "Name            : " << accountRow[1] << endl;
                    cout << "Email           : " << accountRow[2] << endl;
                    cout << "Contact         : " << accountRow[3] << endl;
                    cout << "Address         : " << accountRow[4] << endl;
                    cout << "Balance         : Rs." << accountRow[5] << endl;
                    cout << "Status          : " << accountRow[6] << endl;
                }
                else
                {
                    cout << "Account not found." << endl;
                }
                mysql_free_result(result);
            }
            cout << "--------------------------------------" << endl;
            break;
        case 2:
            cout << "--------------------------------------" << endl;
            cout << "Enter Name : ";
            cin.ignore();
            getline(cin, name);
            fetchQuery = "SELECT ACCOUNT_NUMBER, NAME, EMAIL, CONTACT, ADDRESS, BALANCE,STATUS FROM ACCOUNTS WHERE NAME LIKE '%" + name + "%'";
            if (mysql_query(conn, fetchQuery.c_str()))
            {
                cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
            }
            else
            {
                result = mysql_store_result(conn);
                if (result && mysql_num_rows(result) > 0)
                {
                    num_fields = mysql_num_fields(result);
                    rowCount = 1;
                    while ((row = mysql_fetch_row(result)))
                    {
                        cout << "--------------------------------------" << endl;
                        cout << "Search Results - " << rowCount << endl;
                        rowCount += 1;
                        cout << "Account Number  : " << row[0] << endl;
                        cout << "Name            : " << row[1] << endl;
                        cout << "Email           : " << row[2] << endl;
                        cout << "Contact         : " << row[3] << endl;
                        cout << "Address         : " << row[4] << endl;
                        cout << "Balance         : Rs." << row[5] << endl;
                        cout << "Status          : " << row[6] << endl;
                    }
                }
                else
                {
                    cout << "No accounts found with name matching : " << name << endl;
                }
                mysql_free_result(result);
                cout << "--------------------------------------" << endl;
            }
            break;
        case 3:
            break;
        default:
            cout << "--------------------------------------" << endl;
            cout << "Invalid Choice , Try Again." << endl;
            break;
        }
    } while (choice1 != 3);
    cout << "--------------------------------------" << endl;
}
void Account::showAllAccounts(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    int num_fields, rowCount;
    string queryStr;
    string accountDetails[7] = {"ACCOUNT_NUMBER", "NAME", "EMAIL", "CONTACT", "ADDRESS", "BALANCE", "STATUS"};
    queryStr = "SELECT ACCOUNT_NUMBER, NAME, EMAIL, CONTACT, ADDRESS, BALANCE,STATUS FROM ACCOUNTS";
    if (mysql_query(conn, queryStr.c_str()))
    {
        cerr << "Query Failed : " << mysql_error(conn) << endl;
        return;
    }
    res = mysql_store_result(conn);
    if (!res)
    {
        cerr << "Result Fetch Failed : " << mysql_error(conn) << endl;
        return;
    }
    num_fields = mysql_num_fields(res);
    cout << "Account Details -" << endl;
    rowCount = 1;
    while ((row = mysql_fetch_row(res)))
    {
        cout << "--------------------------------------" << endl;
        cout << "Account " << rowCount << " : " << endl;
        rowCount += 1;
        for (int i = 0; i < num_fields; i++)
        {
            cout << accountDetails[i] << " : " << row[i] << endl;
        }
        cout << endl;
    }
    mysql_free_result(res);
    cout << "--------------------------------------" << endl;
}
bool Account::closeAccount(MYSQL *conn, string username1)
{
    MYSQL_RES *result;
    MYSQL_ROW accountRow;
    string fetchQuery, balance, updateQuery, accountNumber, choice, password, password2, updateQuery1;
    bool closed = false;
    fetchQuery = "SELECT ACCOUNT_NUMBER,BALANCE,PASSWORD FROM ACCOUNTS WHERE (ACCOUNT_NUMBER = '" + username1 + "' OR EMAIL = '" + username1 + "')";
    if (mysql_query(conn, fetchQuery.c_str()))
    {
        cerr << "Failed to fetch account details : " << mysql_error(conn) << endl;
        cout << "--------------------------------------" << endl;
        return false;
    }
    else
    {
        result = mysql_store_result(conn);
        if (result && (accountRow = mysql_fetch_row(result)))
        {
            accountNumber = accountRow[0];
            balance = accountRow[1];
            password = accountRow[2];
            cout << "Balance : Rs." << balance << endl;
            cout << "--------------------------------------" << endl;
        }
        mysql_free_result(result);
    }
    if (balance != "0")
    {
        cout << "Account cannot be closed. Please withdraw Rs." << balance << " first." << endl;
        cout << "--------------------------------------" << endl;
        cout << "Do you want to withdraw ? (Y/N) : ";
        cin >> choice;
        cout << "--------------------------------------" << endl;
        if (choice == "Y" || choice == "y")
        {
            cout << "Enter password : ";
            cin >> password2;
            cout << "--------------------------------------" << endl;
            if (password == password2)
            {
                updateQuery1 = "UPDATE ACCOUNTS SET BALANCE = 0 WHERE ACCOUNT_NUMBER = '" + accountNumber + "'";
                if (mysql_query(conn, updateQuery1.c_str()))
                {
                    cerr << "Failed to withdraw : " << mysql_error(conn) << endl;
                    cout << "--------------------------------------" << endl;
                }
                else
                {
                    cout << "Withdraw Successful." << endl;
                    updateQuery = "UPDATE ACCOUNTS SET STATUS = 'INACTIVE' WHERE ACCOUNT_NUMBER = '" + accountNumber + "'";
                    if (mysql_query(conn, updateQuery.c_str()))
                    {
                        cerr << "Failed to close account : " << mysql_error(conn) << endl;
                        cout << "--------------------------------------" << endl;
                        return false;
                    }
                    else
                    {
                        cout << "Account closed successfully." << endl;
                        closed = true;
                        return true;
                    }
                }
            }
            else
            {
                cout << "Invalid Password." << endl;
                cout << "--------------------------------------" << endl;
                return false;
            }
        }
        else
        {
            cout << "Account cannot be closed. Please withdraw Rs." << balance << " first." << endl;
            cout << "--------------------------------------" << endl;
            return false;
        }
    }
}