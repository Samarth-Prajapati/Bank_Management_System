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
void Account::balanceEnquiry() {}
void Account::displayAccount() {}
void Account::deposit() {}
void Account::withdraw() {}
void Account::transfer() {}
void Account::transactionHistory() {}
void Account::searchAccount() {}
void Account::showAllAccounts() {}
void Account::closeAccount() {}