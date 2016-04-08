#!/bin/bash

# CSCI3060U - Davery
# Phase6 - daily script
# to run: ./daily.sh
#         give "-v" option for verbose mode

# log function for verbose
function v_log() {
	if [ $VERBOSE == 1 ]
	then
		echo "$@"
	fi
}

# check for options
VERBOSE=0
while getopts "v" op
do
	case $op in
		v)
			VERBOSE=1
			v_log "entering verbose mode"
			;;
	esac
done

# initialization
FRONT_END_DIR="../FrontEnd/src"             # location of the FrontEnd directory
EXEC="FrontEnd.o"                           # executable file to run script on
USER_ACCOUNTS_DIR=$FRONT_END_DIR            # user accounts file dir location
USER_ACCOUNTS_FILE="user-accounts-file.dat" # user accounts file name
BANK_ACCOUNTS_FILE="Bank-Account-Transactions.txt" # bank accounts file name

# set up files
cp $USER_ACCOUNTS_DIR/$USER_ACCOUNTS_FILE .
touch $BANK_ACCOUNTS_FILE .

# compile the FrontEnd
v_log "compiling front end"
SOURCE_FILES=$(find $FRONT_END_DIR -mindepth 1 -maxdepth 1 -name *.cpp)
g++ -std=c++11 $SOURCE_FILES -o $EXEC

# runs your Front End over a number of Banking transaction sessions, saving the
# 	output Bank Account Transaction File for each session in a separate file
./$EXEC $USER_ACCOUNTS_FILE $BANK_ACCOUNTS_FILE < "DailySessions/session1.dat"


# concatenates the separate Bank Account Transaction Files into a Merged Bank
# 	Accounts Transaction file

# runs your Back End with the Merged Bank Accounts Transaction File as input

# clean up
v_log "cleaning up code"
rm -f $EXEC
rm -f $BANK_ACCOUNTS_FILE
rm -f $USER_ACCOUNTS_FILE
