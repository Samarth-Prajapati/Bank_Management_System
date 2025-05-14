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
void Account::createAccount()
{
    string confirmPassword;
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
    cout << "--------------------------------------" << endl;
    cout << "Account Created Successfully." << endl;
    cout << "--------------------------------------" << endl;
    cout << "Account Details : " << endl;
    cout << "Name : " << this->name << endl;
    cout << "Email : " << this->email << endl;
    cout << "Contact : " << this->contact << endl;
    cout << "Address : " << this->address << endl;
    cout << "Balance : " << this->balance << endl;
}
void Account::balanceEnquiry() {}
void Account::displayAccount() {}
void Account::searchAccount() {}
void Account::showAllAccounts() {}
void Account::closeAccount() {}