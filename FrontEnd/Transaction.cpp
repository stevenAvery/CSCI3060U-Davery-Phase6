/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: Transaction.cpp
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
* Compile with: g++ -std=c++11 <source_files> -o <executable_name>
*               g++ -std=c++11 main.cpp Account.cpp AdminTransaction.cpp ConsoleGui.cpp Transaction.cpp -o FrontEnd.o
* Description:
* This part of the program runs the transaction operation functions which are part of the Transaction class stored in
* Transaction.h.  Examples of operations done here are basic transaction type operations like deposit which any user
* can request which they what to perform.
*/
#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

static bool expectInput(string output, string *input_buffer) {
	cout << output;
	getline(cin, *input_buffer);
	return !cin.eof();
}

Transaction::Transaction(Account *assoc_account, TransactionType transaction_type, string print_file_name)
{
	this->account_obj_ = assoc_account;
	this->transaction_type_ = transaction_type;
	this->transaction_amount_ = 0;
	this->addtional_info_ = "";
	this->print_file_name_ = print_file_name;
}

Transaction::Transaction(const Transaction &obj)
{
	this->account_obj_ = obj.account_obj_;
	this->transaction_type_ = obj.transaction_type_;
	this->transaction_amount_ = obj.transaction_amount_;
	this->addtional_info_ = obj.addtional_info_;
	this->print_file_name_ = obj.print_file_name_;
}

void Transaction::operator=(const Transaction &obj)
{
	this->account_obj_ = obj.account_obj_;
	this->transaction_type_ = obj.transaction_type_;
	this->transaction_amount_ = obj.transaction_amount_;
	this->addtional_info_ = obj.addtional_info_;
	this->print_file_name_ = obj.print_file_name_;
}

void Transaction::PrintTransaction()
{
	stringstream buffer;
	ofstream print_file;
	string transaction_type;
	string account_holder_name;
	string account_number;
	string transaction_amount;
	string addtional_info;

	print_file.open(GetFileName(), ofstream::app);

	transaction_type = this->GetTransactionType();

	account_holder_name = this->GetAccountHolderName();
	if (this->account_obj_->GetAccountType() == STANDARD) // only run if account type standard (fixes std::out_of_range bug)
	{
		account_holder_name.replace(account_holder_name.find(" "), 1, "_");
	}
	buffer << setw(kAccountHolderNameLength) << setfill('_') << left << account_holder_name;
	account_holder_name.assign(buffer.str());

	buffer.str(string());

	buffer << setw(kAccountNumberLength) << setfill('0') << right << this->GetAccountNumber();
	account_number = buffer.str();

	buffer.str(string());

	buffer << setw(kTransactionAmountLength) << setfill('0') << right << fixed << setprecision(2) << this->GetTransactionAmount();
	transaction_amount = buffer.str();

	buffer.str(string());

	buffer << setw(kAddtionalInfoLength) << setfill('_') << left << this->GetAddtionalInfo();
	addtional_info = buffer.str();

	buffer.str(string());

	print_file << transaction_type << "_";
	print_file << account_holder_name << "_";
	print_file << account_number << "_";
	print_file << transaction_amount << "_";
	print_file << addtional_info << endl;

	print_file.close();

}

void Transaction::Withdrawal()
{
	string input_buffer;
	string account_holder_name;
	int account_number;
	double withdrawal_amount;

	if (this->account_obj_->GetAccountType() == ADMIN)
	{
		while(expectInput("Account holder's name: ", &input_buffer))
		{
			if (input_buffer != "")
			{
				account_holder_name = input_buffer;
				account_obj_->SetAccountHolderName(account_holder_name);
				break;
			}
			else
			{
				cout << "Please enter a valid account name" << endl;
			}
		}
	}

	while(expectInput("Account number: ", &input_buffer))
	{
		if (input_buffer != "")
		{
			account_number = stoi(input_buffer);

			if (account_number == GetAccountNumber())
			{
				while(expectInput("Withdrawal amount: ", &input_buffer))
				{
					if (input_buffer != "")
					{
						withdrawal_amount = stod(input_buffer);

						if (withdrawal_amount > 500)
						{
							cout << "Please only enter $500.00 or less" << endl;
						}
						else if ((account_obj_->GetAccountBalance() - withdrawal_amount) < 0)
						{
							cout << "Withdrawal amount is too large for the account's balance, check account balance and try again" << endl;
						}
						else
						{
							transaction_amount_ = withdrawal_amount;
							cout << "Withdrawal successful!" << endl;

							this->PrintTransaction();
							return;
						}
					}
					else
					{
						cout << "Please enter an amount to withdrawal" << endl;
					}
				}
			}
			else
			{
				cout << "Account number mismatches login" << endl;
			}
		}
		else
		{
			cout << "Please enter an account number" << endl;
		}
	}
}

void Transaction::Transfer()
{
	string input_buffer;
	string account_holder_name;
	int account_number_from;
	int account_number_to;
	double transfer_amount;

	// get account holder's name if account is admin
	if (this->account_obj_->GetAccountType() == ADMIN)
	{
		while(expectInput("Account holder's name: ", &input_buffer))
		{
			if (input_buffer == "")
			{
				cout << "Please enter a valid account name" << endl;
			}
			else if (input_buffer.find_first_of("0123456789") != string::npos)
			{
				cout << "Numeric characters cannot be in the account holder's name" << endl;
			}
			else
			{
				account_holder_name = input_buffer;
				account_obj_->SetAccountHolderName(account_holder_name);
				break;
			}
		}
	}

	// get account number of sender
	while(expectInput("Account number: ", &input_buffer))
	{
		if (input_buffer == "")
		{
			cout << "Please enter an account number" << endl;
		}
		else if (input_buffer.find_first_not_of("0123456789") != string::npos)
		{
			cout << "Non numeric characters cannot be in the sender's account number" << endl;
		}
		else
		{
			account_number_from = stoi(input_buffer);
			break;
		}
	}

	// get account number of recipient
	while(expectInput("Recipient account number: ", &input_buffer))
	{
		if (input_buffer == "")
		{
			cout << "Please enter an account number" << endl;
		}
		else if (input_buffer.find_first_not_of("0123456789") != string::npos)
		{
			cout << "Non numeric characters cannot be in the recipients's account number" << endl;
		}
		else if (stoi(input_buffer) == account_number_from)
		{
			cout << "Cannot transfer to the same account" << endl;
		}
		else
		{
			account_number_to = stoi(input_buffer);
			break;
		}
	}

	// get transfer amount
	while(expectInput("Transfer amount: ", &input_buffer))
	{
		if (input_buffer == "")
		{
			cout << "Please enter a transfer amount" << endl;
		}
		else if (stof(input_buffer) <= 0.0)
		{
			cout << "Transfer amount is too small, transfer amount must exceed $0.00" << endl;
		}
		else if (stof(input_buffer) > 1000.0)
		{
			cout << "Transfer amount is too large, transfer limit is $1000.00 or less" << endl;
		}
		if (input_buffer.find_first_not_of(".0123456789") != string::npos)
		{
			cout << "Non numeric characters cannot be in transfer amount" << endl;
		}
		else
		{
			transfer_amount = stof(input_buffer);

			this->PrintTransaction();
			break;
		}
	}
}

void Transaction::Paybill()
{
	string input_buffer;
	string account_holder_name;
	int account_number;
	string company_pay_to;
	double amount_to_pay;

	// get account holder's name if account is admin
	if (this->account_obj_->GetAccountType() == ADMIN)
	{
		while(expectInput("Account holder's name: ", &input_buffer))
		{
			if (input_buffer == "")
			{
				cout << "Please enter a valid account name" << endl;
			}
			else if (input_buffer.find_first_of("0123456789") != string::npos)
			{
				cout << "Numeric characters cannot be in the account holder's name" << endl;
			}
			else
			{
				account_holder_name = input_buffer;
				account_obj_->SetAccountHolderName(account_holder_name);
				break;
			}
		}
	}

	// get account number
	while(expectInput("Account number: ", &input_buffer))
	{
		if (input_buffer == "")
		{
			cout << "Please enter an account number" << endl;
		}
		else if (input_buffer.find_first_not_of("0123456789") != string::npos)
		{
			cout << "Non numeric characters cannot be in account number" << endl;
		}
		else
		{
			account_number = stoi(input_buffer);
			break;
		}
	}

	// get company code to transfer to
	while(expectInput("Company code: ", &input_buffer))
	{
		if (input_buffer == "")
		{
			cout << "Please enter a Company code" << endl;
		}
		else if (input_buffer.find_first_of("0123456789") != string::npos)
		{
			cout << "Company code must be non numeric characters" << endl;
		}
		else if (input_buffer != "EC" && input_buffer != "CQ" && input_buffer != "TV")
		{
			cout << "Unknown company code" << endl;
		}
		else
		{
			company_pay_to = input_buffer;
			break;
		}
	}

	// get amount to pay
	while(expectInput("Amount to pay: ", &input_buffer))
	{
		if (input_buffer == "")
		{
			cout << "Please enter a transfer amount" << endl;
		}
		else if (input_buffer.find_first_not_of(".0123456789") != string::npos)
		{
			cout << "Non numeric characters cannot be in amount to pay" << endl;
		}
		else if (stof(input_buffer) <= 0.0)
		{
			cout << "Amount to pay is too small, amount must exceed $0.00" << endl;
		}
		else if (stof(input_buffer) > 1000.0)
		{
			cout << "Amount to pay is too large, amount limit is $1000.00 or less" << endl;
		}
		else
		{
			amount_to_pay = stof(input_buffer);

			this->PrintTransaction();
			break;
		}
	}
}

void Transaction::Deposit()
{
	string input_buffer;
	string account_holder_name;
	int account_number;
	double deposit_amount;

	if (this->account_obj_->GetAccountType() == ADMIN)
	{
		while(expectInput("Account holder's name: ", &input_buffer))
		{
			if (input_buffer != "")
			{
				account_holder_name = input_buffer;
				account_obj_->SetAccountHolderName(account_holder_name);
				break;
			}
			else
			{
				cout << "Please enter a valid account name" << endl;
			}
		}
	}

	while(expectInput("Account number: ", &input_buffer))
	{
		if (input_buffer != "")
		{
			account_number = stoi(input_buffer);

			if (account_number == GetAccountNumber())
			{
				while(expectInput("Deposit amount: ", &input_buffer))
				{
					if (input_buffer != "")
					{
						deposit_amount = stod(input_buffer);

						transaction_amount_ = deposit_amount;
						cout << "Deposit successful!" << endl;

						this->PrintTransaction();
						return;
					}
					else
					{
						cout << "Please enter an amount to deposit" << endl;
					}
				}
			}
			else
			{
				cout << "Account number mismatches login" << endl;
			}
		}
		else
		{
			cout << "Please enter an account number" << endl;
		}
	}
}

void Transaction::Logout()
{
	this->PrintTransaction();
	this->account_obj_->Logout();
}

int Transaction::GetAccountNumber()
{
	return this->account_obj_->GetAccountNumber();
}

string Transaction::GetAccountHolderName()
{
	return this->account_obj_->GetAccountHolderName();
}

string Transaction::GetAccountType()
{
	string account_type;

	switch (this->account_obj_->GetAccountType())
	{
		case ADMIN:
			account_type = "00";
			break;
		case STANDARD:
			account_type = "01";
			break;
	}

	return account_type;
}

string Transaction::GetTransactionType()
{
	string transaction_type;

	switch (this->transaction_type_)
	{
		case END_OF_SESSION:
			transaction_type = "00";
			break;
		case WITHDRAWAL:
			transaction_type = "01";
			break;
		case TRANSFER:
			transaction_type = "02";
			break;
		case PAYBILL:
			transaction_type = "03";
			break;
		case DEPOSIT:
			transaction_type = "04";
			break;
		case CREATE:
			transaction_type = "05";
			break;
		case DELETE:
			transaction_type = "06";
			break;
		case DISABLE:
			transaction_type = "07";
			break;
		case CHANGE_PLAN:
			transaction_type = "08";
			break;
	}

	return transaction_type;
}

double Transaction::GetTransactionAmount()
{
	return this->transaction_amount_;
}

string Transaction::GetAddtionalInfo()
{
	return this->addtional_info_;
}

string Transaction::GetFileName()
{
	return this->print_file_name_;
}
