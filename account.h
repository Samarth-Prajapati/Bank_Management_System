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
    void balanceEnquiry();
    void displayAccount();
    void searchAccount();
    void showAllAccounts();
    void closeAccount();
    friend class Bank;
};
#endif