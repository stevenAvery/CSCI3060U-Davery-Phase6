/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: Transaction.h
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
*/
#include "Transaction.h"
#ifndef ADMIN_TRANSACTION_H
#define ADMIN_TRANSACTION_H

// AdminTransaction:
// This class is the child of Transaction and only contains the transaction operations which
// only the administrator can request for.  For information on transaction operations in general
// see the Transaction class description in Transaction.h.
class AdminTransaction : Transaction
{
	public:
		AdminTransaction(Account *, TransactionType, std::string);
		AdminTransaction(const AdminTransaction &);
		~AdminTransaction(){}
		void operator=(const AdminTransaction &);
		void Create();
		void Delete();
		void Disable();
		void ChangePlan();
};

#endif
