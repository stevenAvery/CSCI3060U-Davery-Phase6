/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: Account.h
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
*/
#include <string>
#ifndef ACCOUNT_H
#define ACCOUNT_H

// Constraint values
static const int kAccountNumberPos = 0; // Account Number Position
static const int kAccountNumberLength = 5; // Length of Account Number
static const int kAccountHolderNamePos = 6; // Account Holder Name Position
static const int kAccountHolderNameLength = 20; // Length of Account Holder Name
static const int kAccountStatusPos = 27; // Account Status Position
static const int kAccountStatusLength = 1; // Length of Account Status
static const int kAccountBalancePos = 29; // Account Balance Position
static const int kAccountBalanceLength = 8; // Length of Account Balance

// AccountType:
// The enum structure "AccountType" is a method of letting the program know if a logged in user is a standard account
// or the administrator account.
enum AccountType {
	ADMIN = 0,
	STANDARD = 1
};

// Account:
// This class contains the properties and operations for every account currently logged in.  Each account
// has one of two type which is identified by an enum member which tells the program which account type the user
// is.  Other members include the users account number, name (used to login), and boolean switches where one determines
// if the user is logged in and the other determines if the user is active (is only changed by the admin). If the account
// logged in is the administrator then members of the logged in Account object like account number and name are only used
// as temporary variables to store the account information of the account(s) which the administrator is requesting transactions
// to be performed on.
class Account
{
	public:
		Account(std::string);
		Account(const Account&);
		~Account(){}
		void operator=(const Account&);
		void Login();
		void StdLogin();
		void AdminLogin();
		void Logout();
		std::string GetNameString(std::string);
		int GetAccountCount();
		int GetAccountNumber();
		std::string GetAccountHolderName();
		bool IsAccountActive();
		double GetAccountBalance();
		AccountType GetAccountType();
		bool GetIsLoggedIn();
		void SetAccountHolderName(std::string);
		std::string GetFileName();

	private:
		std::string account_file_name_;
		bool is_logged_in_;
		int account_number_;
		std::string account_holder_name_;
		bool account_active_;
		double account_balance_;
		AccountType account_type_;
};

#endif
