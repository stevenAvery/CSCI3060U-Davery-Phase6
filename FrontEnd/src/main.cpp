/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: main.cpp
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
* Compile with: g++ -std=c++11 <source_files> -o <executable_name>
*               g++ -std=c++11 main.cpp Account.cpp AdminTransaction.cpp ConsoleGui.cpp Transaction.cpp -o FrontEnd.o
* run with:     ./FrontEnd.o user-accounts-file.dat Bank-Account-Transactions.txt
* Description:
* This program is the front end to a banking system which handles user transactions done on a regular basis.  The front end
* subsystem runs the GUI and login for the users as well as request transaction to be done to their bank account which will
* be processed in the back end subsystem.
*/

#include "Account.h"
#include "AdminTransaction.h"
#include "ConsoleGui.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	if (argc > 2)
	{
		string account_file_name;
		string print_file_name;

		account_file_name = argv[1];
		print_file_name = argv[2];

		account_file_name = account_file_name.substr(0, account_file_name.length());
		print_file_name = print_file_name.substr(0, print_file_name.length());

		Account *the_account = new Account(account_file_name);

		ConsoleGui::RunGui(the_account, print_file_name);
	}
	else
	{
		cout << "You must provide a accounts file and transaction file as arguments" << endl;
	}

	return 0;
}
