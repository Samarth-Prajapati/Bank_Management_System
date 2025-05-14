#include "validation.h"
bool Validation::validateFullName(const string &name)
{
    regex pattern(R"(^[A-Z][a-z]+(\s[A-Z][a-z]+)+$)");
    return regex_match(name, pattern);
}
bool Validation::validateEmail(const string &email)
{
    regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}
bool Validation::validateContact(const string &contact)
{
    regex pattern(R"(^[6-9][0-9]{9}$)");
    return regex_match(contact, pattern);
}
bool Validation::validateAddress(const string &address)
{
    regex pattern(R"(^[A-Za-z0-9\s,./#\-]+$)");
    return regex_match(address, pattern);
}
bool Validation::validatePassword(const string &password)
{
    regex pattern(R"((?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[@#$%^&+=]).{6,})");
    return regex_match(password, pattern);
}
bool Validation::validateBalance(double balance)
{
    return balance >= MIN_BALANCE;
}
