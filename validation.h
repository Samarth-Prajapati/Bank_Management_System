#ifndef VALIDATION_H
#define VALIDATION_H
#include <iostream>
#include <regex>
#define MIN_BALANCE 500
using namespace std;
class Validation
{
public:
    static bool validateFullName(const string &name);
    static bool validateEmail(const string &email);
    static bool validateContact(const string &contact);
    static bool validateAddress(const string &address);
    static bool validatePassword(const string &password);
    static bool validateBalance(double balance);
};
#endif