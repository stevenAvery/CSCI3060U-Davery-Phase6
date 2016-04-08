/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: Transaction.cpp
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
* Compile with: g++ -std=c++11 <source_files> -o <executable_name>
*               g++ -std=c++11 main.cpp Account.cpp AdminTransaction.cpp ConsoleGui.cpp Transaction.cpp -o FrontEnd.o
* Description:
* This part of the program is like Transaction.cpp but has transaction operations
* which only administrators can request
*/
#include "AdminTransaction.h"

#include <iostream>
#include <string>

using namespace std;

AdminTransaction::AdminTransaction(Account *assoc_account, TransactionType transaction_type, string print_file_name) : Transaction(assoc_account, transaction_type, print_file_name)
{
}

AdminTransaction::AdminTransaction(const AdminTransaction &obj) : Transaction(obj)
{
}

void AdminTransaction::operator=(const AdminTransaction &obj)
{
	this->account_obj_ = obj.account_obj_;
	this->transaction_type_ = obj.transaction_type_;
	this->transaction_amount_ = obj.transaction_amount_;
	this->addtional_info_ = obj.addtional_info_;
}

static bool expectingInput(string output, string *input_buffer) {
	cout << output;
	getline(cin, *input_buffer);
	return !cin.eof();
}

void AdminTransaction::Create()
{
	string account_holder_name;
	float initial_balance;
	string input_buffer = "";
	float input_balance = -1; // Set initial value to -1 for initial false condition

	// get account holder's name
	while(expectingInput("Account holder's name: ", &input_buffer))
	{
		if(input_buffer == "")
		{
			cout << "There must be an account holder name given\n";
		}
		else if(input_buffer.length() > kAccountHolderNameLength)
		{
			cout << "Account holder name cannot exceed " << kAccountHolderNameLength << endl;
		}
		else
		{
			account_holder_name = input_buffer;
			break;
		}
	}

	// get the initial balance
	while(expectingInput("Initial balance: ", &input_buffer))
	{
		if(input_buffer == "")
		{
			cout << "There must be an initial balance given\n";
		}
		else if (input_buffer.find_first_not_of(".0123456789") != string::npos)
		{
			cout << "Non numeric characters cannot be in initial balance" << endl;
		}
		else if(stof(input_buffer) < 0.0f)
		{
			cout << "Initial balance of bank account must be >= $0\n";
		}
		else if(stof(input_buffer) > 99999.99f)
		{
			cout << "Initial balance must be <= $99,999.99\n";
		}
		else
		{
			initial_balance = input_balance;
			break;
		}
	}
}

void AdminTransaction::Delete()
{
	string account_holder_name;
	int account_number;
	string input_buffer;

	// get account holder's name
	cout << "Account holder's name: ";

	getline(cin, input_buffer);
	if(input_buffer == "")
	{
		cout << "There must be an accout holder name given\n";
	}
	else if(input_buffer.length() > 20)
	{
		cout << "Account holder name cannot exceed 20\n";
	}
	else
	{
		account_holder_name = input_buffer;

		// get the bank account holder's number
		cout << "Acccount number: ";

		getline(cin, input_buffer);
		if(input_buffer == "")
		{
			cout << "There must be an account number given\n";
		}
		else
		{
			int input_account_number = stoi(input_buffer);
		}
	}
}

void AdminTransaction::Disable()
{
	string account_holder_name;
	int account_number;
	string input_buffer;

	// get account holder's name
	cout << "Account holder's name: ";

	getline(cin, input_buffer);
	if(input_buffer == "")
	{
		cout << "There must be an accout holder name given\n";
	}
	else if(input_buffer.length() > 20)
	{
		cout << "Account holder name cannot exceed 20\n";
	}
	else
	{
		account_holder_name = input_buffer;

		// get the bank account holder's number
		cout << "Acccount number: ";

		getline(cin, input_buffer);
		if(input_buffer == "")
		{
			cout << "There must be an account number given\n";
		}
		else
		{
			int input_account_number = stoi(input_buffer);
		}
	}
}

void AdminTransaction::ChangePlan()
{
	string account_holder_name;
	int account_number;
	string input_buffer;

	// get account holder's name
	cout << "Account holder's name: ";

	getline(cin, input_buffer);
	if(input_buffer == "")
	{
		cout << "There must be an accout holder name given\n";
	}
	else if(input_buffer.length() > 20)
	{
		cout << "Account holder name cannot exceed 20\n";
	}
	else
	{
		account_holder_name = input_buffer;

		// get the bank account holder's number
		cout << "Acccount number: ";

		getline(cin, input_buffer);
		if(input_buffer == "")
		{
			cout << "There must be an account number given\n";
		}
		else
		{
			int input_account_number = stoi(input_buffer);
		}
	}
}
