/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: Account.cpp
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
* Compile with: g++ -std=c++11 <source_files> -o <executable_name>
*               g++ -std=c++11 main.cpp Account.cpp AdminTransaction.cpp ConsoleGui.cpp Transaction.cpp -o FrontEnd.o
* Description:
* This part of the program runs the account operation functions which are part of the Account class stored in Account.h.
* Examples of operations done here are login and logout type operations which effect the user login information status and
* validating account number inputs.
*/

#include "Account.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Account::Account(std::string file_name)
{
	this->account_number_ = 0;
	this->account_holder_name_ = "";
	this->account_active_ = true;
	this->account_balance_ = 0.0;
	this->account_type_ = STANDARD;
	this->is_logged_in_ = false;
	this->account_file_name_ = file_name;
}

Account::Account(const Account& obj)
{
	this->account_number_ = obj.account_number_;
	this->account_holder_name_ = obj.account_holder_name_;
	this->account_active_ = obj.account_active_;
	this->account_balance_ = obj.account_balance_;
	this->account_type_ = obj.account_type_;
	this->is_logged_in_ = obj.is_logged_in_;
	this->account_file_name_ = obj.account_file_name_;
}

void Account::operator=(const Account& obj)
{
	this->account_number_ = obj.account_number_;
	this->account_holder_name_ = obj.account_holder_name_;
	this->account_active_ = obj.account_active_;
	this->account_balance_ = obj.account_balance_;
	this->account_type_ = obj.account_type_;
	this->is_logged_in_ = obj.is_logged_in_;
	this->account_file_name_ = obj.account_file_name_;
}

static bool expectingInput(string output, string *input_buffer) {
	cout << output;
	getline(cin, *input_buffer);
	return !cin.eof();
}

void Account::Login()
{
	string input_buffer;
	while(expectingInput("Session kind: ", &input_buffer)) {
		if(input_buffer == "admin")
		{
			AdminLogin();
			break;
		}
		else if(input_buffer == "standard")
		{
			StdLogin();
			break;
		}
		else
		{
			cout << "The user must enter either 'standard' or 'admin'\n";
		}
	}
}


void Account::AdminLogin()
{
	this->account_type_ = ADMIN;
	this->is_logged_in_ = true;
}

void Account::StdLogin()
{
	string input_buffer;
	string file_buffer;
	string account_holder_name_f;
	ifstream acc_file(GetFileName());
	int account_count = 0;

	while(expectingInput("Account holder's name: ", &input_buffer)) {
		if(input_buffer != "")
		{
			while(getline(acc_file, file_buffer))
			{
				account_holder_name_f = Account::GetNameString(file_buffer);

				if(input_buffer == account_holder_name_f && account_holder_name_f != "END OF FILE")
				{
					this->account_number_ = stoi(file_buffer.substr(kAccountNumberPos, kAccountNumberLength));
					this->account_holder_name_ = input_buffer;
					switch (file_buffer.at(kAccountStatusPos))
					{
						case 'A':
							this->account_active_ = true;
							break;
						case 'D':
							this->account_active_ = false;
							break;
					}
					this->account_balance_ = stod(file_buffer.substr(kAccountBalancePos, kAccountBalanceLength));
					this->account_type_ = STANDARD;
					this->is_logged_in_ = true;
					return;
				}

				account_count++;
			}

			if (account_count == Account::GetAccountCount())
			{
				cout << "Account holder's name not found, please enter a valid account holder\n";
			}
		}
		else
		{
			cout << "The standard user must enter account holder's name\n";
		}

		acc_file.close();

		if(!this->account_active_)
		{
			cout << "The standard user must have a valid account\n";
		}
	}
}

void Account::Logout()
{
	/* nothing to be done here on the front end */
	this->account_number_ = 0;
	this->account_holder_name_ = "";
	this->account_active_ = true;
	this->account_balance_ = 0.0;
	this->account_type_ = STANDARD;
	this->is_logged_in_ = false;
}

string Account::GetNameString(string acc_string)
{
	int position;
	string name = acc_string;

	name = name.substr(kAccountHolderNamePos, kAccountHolderNameLength);

	while(name.find("_") != -1)
	{
		if(position == (name.find("_") - 1)) // compare preivous find
		{
			position = name.find("_");
			name.erase(position, 1);
		}
		else
		{
			position = name.find("_");
			name.replace(position, 1, " ");
			if(position == (name.find("_") - 1)) // compare preivous find
			{
				name.erase(position, 2);
			}
		}

	}

	return name;
}

int Account::GetAccountCount()
{
	int acc_count = 0;
	char temp;
	ifstream acc_file(GetFileName());

	while(acc_file.get(temp))
	{
		if(temp == '\n')
			acc_count++;
	}

	return acc_count;
}

int Account::GetAccountNumber()
{
	return this->account_number_;
}

string Account::GetAccountHolderName()
{
	return this->account_holder_name_;
}

bool Account::IsAccountActive()
{
	return this->account_active_;
}

double Account::GetAccountBalance()
{
	return this->account_balance_;
}

AccountType Account::GetAccountType()
{
	return this->account_type_;
}

bool Account::GetIsLoggedIn()
{
	return this->is_logged_in_;
}

string Account::GetFileName()
{
	return this->account_file_name_;
}

void Account::SetAccountHolderName(string name)
{
	this->account_holder_name_ = name;
}
