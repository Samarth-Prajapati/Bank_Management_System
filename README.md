Banking System
Overview
This is a C++ console-based banking system application that interacts with a MySQL database to manage bank accounts and transactions. It provides functionalities for account creation, user and admin login, deposits, withdrawals, transfers, balance inquiries, transaction history, and account management.
Features

User Features:

Create a new account with validated inputs (name, email, contact, address, password, initial balance).
Login using account number/email and password.
Deposit and withdraw money (with minimum balance requirement of Rs. 500).
Transfer funds to other accounts.
View account details and transaction history.
Close account (requires zero balance).


Admin Features:

Login with admin credentials (username: admin, password: admin).
View all accounts.
Search accounts by account number or name.
View all transactions.



Prerequisites

Compiler: GCC (MinGW for Windows)
Database: MySQL Server 8.0
Libraries: MySQL C API (libmysql)
Operating System: Windows (based on provided configuration)

Setup Instructions
1. Install Dependencies

MySQL Server:
Download and install MySQL Server 8.0 from MySQL Official Website.
Ensure MySQL Server is running and accessible.


MinGW:
Install MinGW from MinGW Official Website or use a package manager.
Ensure g++ is available in your PATH.


MySQL C API:
Ensure MySQL Server installation includes the C API libraries (typically located at C:/Program Files/MySQL/MySQL Server 8.0/lib).
Include path: C:/Program Files/MySQL/MySQL Server 8.0/include.



2. Database Setup

Create the database and tables by executing the SQL script provided in queries.sql:mysql -u root -p < queries.sql


Update the MySQL connection details in main.cpp if necessary:mysql_real_connect(conn, "localhost", "root", "Apple@2310", "BANKING_SYSTEM", 3306, NULL, 0)


Replace "root" with your MySQL username.
Replace "Apple@2310" with your MySQL password.
Ensure "BANKING_SYSTEM" matches the database name.



3. Project Structure

main.cpp: Entry point with the main menu and logic for user/admin interactions.
account.h / account.cpp: Handles account-related operations (create, login, deposit, etc.).
validation.h / validation.cpp: Input validation using regex for name, email, contact, etc.
query.h / query.cpp: Utility for executing MySQL queries.
queries.sql: SQL script to set up the database and tables.
c_cpp_properties.json: VS Code configuration for IntelliSense.
tasks.json: VS Code task for building the project.

4. Build the Project

Using VS Code:
Open the project folder in VS Code.
Ensure tasks.json is configured as provided.
Run the build-mysql task (Ctrl+Shift+B or Terminal > Run Build Task).


Using Command Line:g++ -std=c++14 -I "C:/Program Files/MySQL/MySQL Server 8.0/include" main.cpp query.cpp validation.cpp account.cpp -L "C:/Program Files/MySQL/MySQL Server 8.0/lib" -lmysql -o main.exe



5. Run the Application

Execute the compiled binary:./main.exe



Usage

Main Menu:

Create Account: Enter validated details to create a new account.
Admin Login: Use admin/admin to access admin features.
User Login: Enter account number/email and password.
Exit: Close the application.


Admin Menu:

View all accounts, search accounts, or view transaction history.


User Menu:

Perform account operations like deposit, withdraw, transfer, or close account.



Validation Rules

Full Name: Must start with a capital letter, followed by lowercase letters, and include at least one space (e.g., "John Doe").
Email: Standard email format (e.g., "user@example.com").
Contact: 10-digit number starting with 6-9 (e.g., "9876543210").
Address: Alphanumeric with spaces, commas, and specific symbols.
Password: At least 6 characters, including uppercase, lowercase, digit, and special character.
Balance: Minimum Rs. 500 for new accounts and after withdrawals.

Notes

The application uses a simple admin login (admin/admin). Consider securing this in a production environment.
Ensure MySQL server is running before executing the application.
Account numbers start from 8985420000 as per the SQL configuration.
Transactions are logged in the TRANSACTIONS table with details like type, amount, and timestamp.

Troubleshooting

MySQL Connection Error:
Verify MySQL server is running and credentials are correct.
Check the include and library paths in the build command.


Validation Errors:
Ensure inputs match the regex patterns defined in validation.cpp.


Build Errors:
Confirm MinGW and MySQL libraries are correctly installed and paths are set.



License
This project is for educational purposes and does not include a specific license.
