/*
* Names: Michael Valdron (100487615) & Steven Avery (100493227)
* Filename: ConsoleGui.h
* Group: Dev Solutions Inc.
* Course: CSCI 3060U
*/
#include "Account.h"
#include "AdminTransaction.h"

#ifndef CONSOLEGUI_H
#define CONSOLEGUI_H

// ConsoleGui:
// This static class contains the operation for building and running
// the GUI.
class ConsoleGui
{
	public:
		static void RunGui(Account *, std::string);
};

#endif
