CREATE DATABASE BANKING_SYSTEM;

USE BANKING_SYSTEM;

CREATE TABLE ACCOUNTS (
    ACCOUNT_NUMBER BIGINT AUTO_INCREMENT PRIMARY KEY,
    NAME VARCHAR(100) NOT NULL,
    EMAIL VARCHAR(100) NOT NULL UNIQUE,
    ADDRESS VARCHAR(100) NOT NULL,
    PASSWORD VARCHAR(100) NOT NULL UNIQUE,
    CONTACT VARCHAR(100) NOT NULL UNIQUE,
    BALANCE DOUBLE NOT NULL,
    STATUS VARCHAR(50)
) AUTO_INCREMENT = 8985420000;

CREATE TABLE TRANSACTIONS (
    TRANSACTION_ID INT AUTO_INCREMENT PRIMARY KEY,
    FROM_ACCOUNT BIGINT NOT NULL,
    TO_ACCOUNT BIGINT,
    TYPE VARCHAR(20) CHECK (
        TYPE IN (
            'DEPOSIT',
            'WITHDRAWAL',
            'TRANSFER'
        )
    ),
    AMOUNT DOUBLE NOT NULL,
    TIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP,
    UPDATED_BALANCE DOUBLE,
    DESCRIPTION VARCHAR(255),
    FOREIGN KEY (FROM_ACCOUNT) REFERENCES ACCOUNTS (ACCOUNT_NUMBER),
    FOREIGN KEY (TO_ACCOUNT) REFERENCES ACCOUNTS (ACCOUNT_NUMBER)
);