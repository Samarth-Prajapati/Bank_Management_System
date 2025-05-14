#include "login.h"
void Login::login()
{
    int choice1;
    do
    {
        cout << "1. Admin Login\n2. User Login\n3. Back" << endl;
        cout << "--------------------------------------" << endl;
        cin >> choice1;
        switch (choice1)
        {
        case 1:
            cout << "--------------------------------------" << endl;
            adminLogin();
            break;
        case 2:
            cout << "--------------------------------------" << endl;
            userLogin();
            break;
        case 3:
            return;
        default:
            cout << "--------------------------------------" << endl;
            cout << "Invalid Choice , Try Again." << endl;
            break;
        }
    } while (true);
}
void Login::adminLogin()
{
    string username, password;
    cout << "Enter Username : ";
    cin >> username;
    cout << "Enter Password : ";
    cin >> password;
    cout << "--------------------------------------" << endl;
    if (username == "admin" && password == "admin")
    {
        cout << "Login Successful" << endl;
        cout << "--------------------------------------" << endl;
    }
    else
    {
        cout << "Invalid Username or Password." << endl;
        cout << "--------------------------------------" << endl;
    }
}
void Login::userLogin() {}