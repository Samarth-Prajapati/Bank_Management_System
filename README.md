# Banking System

## Overview
This is a C++ console-based banking system application that interacts with a MySQL database to manage bank accounts and transactions. The system supports user and admin functionalities, including account creation, deposits, withdrawals, transfers, and transaction history tracking. It includes input validation to ensure data integrity and secure password handling.

## Features
### User Features
- **Create Account**: Register a new account with validated details (name, email, contact, address, password, and initial balance).
- **Login**: Authenticate using account number/email and password.
- **Deposit**: Add funds to the account (password required).
- **Withdraw**: Remove funds if sufficient balance exists (minimum Rs.500 required).
- **Balance Enquiry**: View current account balance.
- **Transfer**: Transfer funds to another account (password and recipient account number required).
- **Transaction History**: View all transactions for the account.
- **Close Account**: Deactivate the account after withdrawing all funds.

### Admin Features
- **Show All Accounts**: Display details of all accounts in the system.
- **Search Account**: Search accounts by account number or name.
- **Transaction History**: View all transactions across the system.

## Prerequisites
- **C++ Compiler**: Microsoft Visual Studio 2019 or later (Community Edition is free).
- **MySQL Server**: MySQL 5.7 or later (via MySQL Installer for Windows).
- **MySQL C Connector**: MySQL Connector/C++ for database connectivity.
- **Operating System**: Windows 10 or later.

## Setup Instructions
1. **Install MySQL Server**:
   - Download and install MySQL Installer from [MySQL's official website](https://dev.mysql.com/downloads/installer/).
   - Choose "MySQL Server" and "MySQL Connector/C++" during installation.
   - Set up a root password during the configuration process (e.g., `Apple@2310`).
   - Ensure the MySQL service is running: Open Services (Win+R, type `services.msc`), find "MySQL", and start it if necessary.

2. **Install MySQL C Connector**:
   - If not installed via MySQL Installer, download the MySQL Connector/C++ from [MySQL's website](https://dev.mysql.com/downloads/connector/cpp/).
   - Install it to a known location (e.g., `C:\Program Files\MySQL\Connector C++ 8.0`).
   - Note the include and library paths for compilation (e.g., `C:\Program Files\MySQL\Connector C++ 8.0\include` and `lib`).

3. **Set Up the Database**:
   - Open MySQL Workbench or Command Line Client from the MySQL Installer.
   - Log in using `root` and your password: `mysql -u root -p`.
   - Run the SQL script (`queries.sql`) to create the database and tables:
     ```sql
     source C:\path\to\queries.sql;
     ```
   - Replace `C:\path\to\queries.sql` with the actual file path (use backslashes for Windows).
   - Verify that the `BANKING_SYSTEM` database is created with `ACCOUNTS` and `TRANSACTIONS` tables.

4. **Compile the Code**:
   - Install Visual Studio with the "Desktop development with C++" workload.
   - Open Visual Studio and create a new "Empty Project" under C++.
   - Add the project files: `main.cpp`, `account.cpp`, `query.cpp`, `validation.cpp`, `account.h`, `validation.h`, `query.h`.
   - Configure the project properties:
     - **Include Directories**: Add the MySQL Connector include path (e.g., `C:\Program Files\MySQL\Connector C++ 8.0\include`).
     - **Library Directories**: Add the MySQL Connector library path (e.g., `C:\Program Files\MySQL\Connector C++ 8.0\lib64\vs14`).
     - **Additional Dependencies**: Add `mysqlcppconn.lib` under Linker > Input.
   - Build the solution (F7) to generate the executable (e.g., `banking_system.exe`).

5. **Configure MySQL Credentials**:
   - Update the MySQL connection details in `main.cpp`:
     ```cpp
     mysql_real_connect(conn, "localhost", "root", "Apple@2310", "BANKING_SYSTEM", 3306, NULL, 0)
     ```
   - Replace `"root"` and `"Apple@2310"` with your MySQL username and password set during MySQL installation.

## Usage
1. **Run the Program**:
   - Run the compiled executable: Double-click `banking_system.exe` in the project’s Debug or Release folder, or run it from Visual Studio (F5).
   - The console will display a menu with options for creating an account, admin login, user login, or exiting.

2. **Admin Login**:
   - Use username: `admin` and password: `admin` to access admin features.
   - Options include viewing all accounts, searching accounts, or viewing transaction history.

3. **User Operations**:
   - Create an account by entering validated details (full name, email, contact, address, password, and initial balance ≥ Rs.500).
   - Log in using account number or email and password.
   - Perform operations like deposit, withdrawal, transfer, or view transaction history.

## File Structure
- **account.h / account.cpp**: Defines the `Account` class with methods for account management and transactions.
- **validation.h / validation.cpp**: Implements input validation for name, email, contact, address, password, and balance.
- **query.h / query.cpp**: Handles MySQL query execution.
- **main.cpp**: Main program loop with user and admin menus.
- **queries.sql**: SQL script to set up the database and tables.

## Database Schema
- **ACCOUNTS Table**:
  - `ACCOUNT_NUMBER`: Auto-incremented primary key (starts at 8985420000).
  - `NAME`, `EMAIL`, `ADDRESS`, `PASSWORD`, `CONTACT`, `BALANCE`, `STATUS`.
- **TRANSACTIONS Table**:
  - `TRANSACTION_ID`: Auto-incremented primary key.
  - `FROM_ACCOUNT`, `TO_ACCOUNT`, `TYPE` (DEPOSIT, WITHDRAWAL, TRANSFER), `AMOUNT`, `TIMESTAMP`, `UPDATED_BALANCE`, `DESCRIPTION`.

## Notes
- **Security**: Passwords are stored in plain text for simplicity. In a production environment, use hashing (e.g., bcrypt).
- **Validation**: The system enforces strict input validation (e.g., email format, minimum balance of Rs.500).
- **Error Handling**: MySQL errors are logged to `cerr`, and user-friendly messages are displayed.
- **Admin Access**: Hardcoded admin credentials (`admin/admin`) should be replaced with a secure authentication mechanism in production.

## Limitations
- No support for concurrent users (single-threaded console application).
- Plain text password storage is insecure.
- Limited error recovery for database connection failures.

## Future Improvements
- Implement password hashing for secure storage.
- Add session management for concurrent users.
- Introduce a graphical user interface (GUI).
- Enhance admin features (e.g., account deletion, user role management).

## License
This project is for educational purposes and is not licensed for commercial use.