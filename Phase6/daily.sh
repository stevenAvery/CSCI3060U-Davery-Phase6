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
FRONT_END_DIR="../FrontEnd/src"                    # location of the FrontEnd directory
EXEC="FrontEnd.o"                                  # executable file to run script on
USER_ACCOUNTS_DIR=$FRONT_END_DIR                   # user accounts file dir location
USER_ACCOUNTS_FILE="user-accounts-file.dat"        # user accounts file name
BANK_ACCOUNTS_FILE="Bank-Account-Transactions.txt" # bank accounts file name
DAILY_SESSIONS_DIR="DailySessions"                 # daily sessions dir
BANK_ACCOUNTS_OUT_DIR="BankAccounts"               # the daily bank accounts
MERGED_ACCOUNTS="transactionLogs.txt"              # the final merged accounts file
BACK_END_SRC_DIR="../BankBackEnd/src"              # back end src location
OLD_MASTER_DIR="../BankBackEnd"                    # original location of old master for backend
OLD_MASTER="oldMaster.txt"                         # original name for old master

# get accounts
mkdir -p $BANK_ACCOUNTS_OUT_DIR
cp $USER_ACCOUNTS_DIR/$USER_ACCOUNTS_FILE .

# compile the FrontEnd
v_log "compiling front end"
SOURCE_FILES=$(find $FRONT_END_DIR -mindepth 1 -maxdepth 1 -name *.cpp)
g++ -std=c++11 $SOURCE_FILES -o $EXEC

# runs your Front End over a number of Banking transaction sessions, saving the
# 	output Bank Account Transaction File for each session in a separate file
for sessionFile in $DAILY_SESSIONS_DIR/*.dat
do
	v_log "----------------"
	v_log "running session: $sessionFile"
	touch $BANK_ACCOUNTS_FILE . # make sure the bank accounts file exists
	./$EXEC $USER_ACCOUNTS_FILE $BANK_ACCOUNTS_FILE < $sessionFile
	echo ""

	cp $BANK_ACCOUNTS_FILE $BANK_ACCOUNTS_OUT_DIR/$(basename $sessionFile | cut -d"." -f1)Accounts.dat
	rm -f $BANK_ACCOUNTS_FILE
done

# concatenates the separate Bank Account Transaction Files into a Merged Bank
# 	Accounts Transaction file
rm -f $MERGED_ACCOUNTS
cat $BANK_ACCOUNTS_OUT_DIR/*.dat >> $MERGED_ACCOUNTS

# runs your Back End with the Merged Bank Accounts Transaction File as input
v_log ""
v_log "setting up backend input files"
head -n -1 $USER_ACCOUNTS_FILE > temp.txt # remove END_OF_FILE line from frontend accounts
mv temp.txt $USER_ACCOUNTS_FILE

cat $USER_ACCOUNTS_FILE # TODO remove (debugging)

cp $USER_ACCOUNTS_FILE $OLD_MASTER # rename the front end user accounts to backend oldMaster

v_log "compiling back end"
javac $BACK_END_SRC_DIR/*.java
java -cp $BACK_END_SRC_DIR/ Main # takes transactionLogs.txt and oldMaster.txt

# clean up
v_log "cleaning up temp files"
rm -f $MERGED_ACCOUNTS
rm -f $OLD_MASTER
rm -f $BACK_END_SRC_DIR/*.class
rm -f $EXEC
rm -f $BANK_ACCOUNTS_FILE
rm -f $USER_ACCOUNTS_FILE
