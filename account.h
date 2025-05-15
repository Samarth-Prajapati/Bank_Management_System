#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "validation.h"
#include "query.h"
class Account
{
private:
    string name, email, address, password, contact;
    double balance;
    Query query;
    Validation validate;

public:
    Account();
    Account(string name, string email, string address, string password, string contact, double balance);
    void createAccount(MYSQL *conn);
    bool userLogin(MYSQL *conn, string username1, string password1);
    void displayAccount(MYSQL *conn, string username1);
    void deposit();
    void withdraw();
    void balanceEnquiry(MYSQL *conn, string username1);
    void transfer();
    void transactionHistory();
    void searchAccount(MYSQL *conn);
    void showAllAccounts(MYSQL *conn);
    bool closeAccount(MYSQL *conn, string username1);
};
#endif