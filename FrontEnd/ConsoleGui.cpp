/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: ConsoleGui.cpp
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
* Compile with: g++ -std=c++11 <source_files> -o <executable_name>
*               g++ -std=c++11 main.cpp Account.cpp AdminTransaction.cpp ConsoleGui.cpp Transaction.cpp -o FrontEnd.o
* Description:
* This part of the program runs the GUI operations that users use, which is part of the ConsoleGui class stored in
* ConsoleGui.h.  Examples of operations done here are producing the GUI for the user and uses logic to take the user to
* location or request the transaction they wish to perform.
*/
#include "ConsoleGui.h"
#include <iostream>
#include <string>

using namespace std;

static bool expectInput(string output, string *input_buffer) {
	cout << output;
	getline(cin, *input_buffer);
	return !cin.eof();
}

void ConsoleGui::RunGui(Account *assoc_account, string print_file_name)
{
	Transaction *transaction;
	AdminTransaction *admin;

	string input_buffer;

	while(expectInput("Transaction: ", &input_buffer))
	{
		if(input_buffer == "login" ||
			input_buffer == "logout" ||
			input_buffer == "transfer" ||
			input_buffer == "withdrawal" ||
			input_buffer == "paybill" ||
			input_buffer == "deposit" ||
			input_buffer == "create" ||
			input_buffer == "delete" ||
			input_buffer == "disable" ||
			input_buffer == "changeplan")
		{
			// transactions and errors if not logged in
			if(!assoc_account->GetIsLoggedIn())
			{
				if(input_buffer == "logout" ||
					input_buffer == "transfer" ||
					input_buffer == "withdrawal" ||
					input_buffer == "paybill" ||
					input_buffer == "deposit" ||
					input_buffer == "create" ||
					input_buffer == "delete" ||
					input_buffer == "disable" ||
					input_buffer == "changeplan")
				{
					cout << "Unable to perform transaction without being logged in\n";
				}
				else
				{
					assoc_account->Login();
				}
			}
			else if(input_buffer == "logout")
			{
				transaction = new Transaction(assoc_account, END_OF_SESSION, print_file_name);
				transaction->Logout();
				delete transaction;
			}
			else if(input_buffer == "login")
			{
				cout << "Unable to perform transaction without being logged out\n";
			}
			else if(input_buffer == "withdrawal")
			{
				transaction = new Transaction(assoc_account, WITHDRAWAL, print_file_name);
				transaction->Withdrawal();
				delete transaction;
			}
			else if(input_buffer == "transfer")
			{
				transaction = new Transaction(assoc_account, TRANSFER, print_file_name);
				transaction->Transfer();
				delete transaction;
			}
			else if(input_buffer == "paybill")
			{
				transaction = new Transaction(assoc_account, PAYBILL, print_file_name);
				transaction->Paybill();
				delete transaction;
			}
			else if(input_buffer == "deposit")
			{
				transaction = new Transaction(assoc_account, DEPOSIT, print_file_name);
				transaction->Deposit();
				delete transaction;

			}
			else if (assoc_account->GetAccountType() == STANDARD)
			{
				if(input_buffer == "create" ||
					input_buffer == "delete" ||
					input_buffer == "disable" ||
					input_buffer == "changeplan")
				{
					cout << "Desired transaction requires admin privileges" << endl;
				}
			}
			else if (assoc_account->GetAccountType() == ADMIN)
			{
				if(input_buffer == "create")
				{
					admin = new AdminTransaction(assoc_account, CREATE, print_file_name);
					admin->Create();
					delete admin;
				}
				else if(input_buffer == "delete")
				{
					admin = new AdminTransaction(assoc_account, DELETE, print_file_name);
					admin->Delete();
					delete admin;
				}
				else if(input_buffer == "disable")
				{
					admin = new AdminTransaction(assoc_account, DISABLE, print_file_name);
					admin->Disable();
					delete admin;
				}
				else if(input_buffer == "changplan")
				{
					admin = new AdminTransaction(assoc_account, CHANGE_PLAN, print_file_name);
					admin->ChangePlan();
					delete admin;
				}
			}
		}
		else
		{
			cout << "Unknown transaction" << endl;
		}
	}
}
