/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: Transaction.h
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
*/
#include "Account.h"
#ifndef TRANSACTION_H
#define TRANSACTION_H

// Constraint values
static const int kTransactionAmountLength = 8; // Transaction Amount Length
static const int kAddtionalInfoLength = 2; // Additional Information Length

// TransactionType:
// The enum structure "TransactionType" is a method of letting the program know which transaction is it which
// needs the be processed.  In the "PrintTransaction" procedure, it passes the type as a number so that the back
// end subsystem knows which transaction it is that needs to be processed.
enum TransactionType {
	END_OF_SESSION = 0,
	WITHDRAWAL = 1,
	TRANSFER = 2,
	PAYBILL = 3,
	DEPOSIT = 4,
	CREATE = 5,
	DELETE = 6,
	DISABLE = 7,
	CHANGE_PLAN = 8
};

// Transaction:
// This class contains the properties and operations for every transaction.  Each transaction
// is identified by an enum member which tells the program which transaction type it needs to perform.
// Other members include the users account information class (Account) to show which user is performing
// the transaction when it is sent to be processed, the amount of money involved (if any), and additional
// information about the transaction that needs to be sent.
class Transaction
{
	public:
		Transaction(Account *, TransactionType, std::string);
		Transaction(const Transaction &);
		~Transaction(){}
		void operator=(const Transaction &);
		void PrintTransaction();
		void Withdrawal();
		void Transfer();
		void Paybill();
		void Deposit();
		void Logout();
		int GetAccountNumber();
		std::string GetAccountHolderName();
		std::string GetAccountType();
		std::string GetTransactionType();
		double GetTransactionAmount();
		std::string GetAddtionalInfo();
		std::string GetFileName();
	protected:
		std::string print_file_name_;
		Account *account_obj_;
		TransactionType transaction_type_;
		double transaction_amount_;
		std::string addtional_info_;
};

#endif
