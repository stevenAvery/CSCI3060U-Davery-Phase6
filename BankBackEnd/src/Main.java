import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Main 
{	
	public static void main(String[] args) 
	{
		if(args.length == 4)
		{
			String oldMasterFilePath = args[0];
			String transactionLogFilePath = args[1];
			String newMasterFilePath = args[2];
			String newCurrentAccountsFilePath = args[3];
	
			AccountList accounts = new AccountList();
			
			try
			{
				accounts.loadAccounts(oldMasterFilePath);
				
				updateAccounts(accounts, transactionLogFilePath);
				
				accounts.writeNewAccountFiles(newMasterFilePath, newCurrentAccountsFilePath);
			}
			catch (Exception ex)
			{
				System.out.println("Error: " + ex.getMessage());
			}
		}
		else
		{
			System.out.println("Error: Missing file path arguments");
		}
		
	}
 
	/**
	 * Applies the transactions from the transaction log file onto the accounts
	 * @param accounts The list of accounts to apply transactions on
	 * @param transactionLogFile The file path to the transaction log file
	 * @throws TransactionError
	 * @throws IOException
	 * @throws AccountListError
	 */
	public static void updateAccounts(AccountList accounts, String transactionLogFile) throws TransactionError, IOException, AccountListError
	{	
		final int TRANSACTION_CODE_START = 0;
		final int TRANSACTION_CODE_END = 2;
		final int ACCOUNT_HOLDER_START = 3;
		final int ACCOUNT_HOLDER_END = 23;
		final int ACCOUNT_NUMBER_START = 24;
		final int ACCOUNT_NUMBER_END = 29;
		final int AMOUNT_START = 30;
		final int AMOUNT_END = 38;
		final int MISC_START = 39;
		final int MISC_END = 41;
		
		Session session = null;
		boolean isFinished = false;
		
		String line = null;
		
		String transactionCode = null;
		String accountHolderName = null;
		String accountNumber = null;
		Float amount = -1.0f;
		String miscField = null;
		
		Account workingAccount;
		ArrayList<Account> workingAccountList = new ArrayList<Account>(10);
		
		boolean isExpectingTransferTo = false;
		
		try
		{
			FileReader fileReader = new FileReader(transactionLogFile);
			BufferedReader transactionReader = new BufferedReader(fileReader);
			
			while (!isFinished)
			{
				line = transactionReader.readLine();
				
				transactionCode = line.substring(TRANSACTION_CODE_START, TRANSACTION_CODE_END);
				accountHolderName = line.substring(ACCOUNT_HOLDER_START, ACCOUNT_HOLDER_END).replace('_', ' ').trim();
				accountNumber = line.substring(ACCOUNT_NUMBER_START, ACCOUNT_NUMBER_END);
				miscField = line.substring(MISC_START, MISC_END).replace('_', ' ');
				
				if(isExpectingTransferTo && (! transactionCode.equals("02")))
				{
					throw new TransactionError("Was expecting a transfer to");
				}
				else if (transactionCode.equals("00")) //Logout
				{
					if(session != null)
					{
						session = null;
						
						while(workingAccountList.size() > 0)
						{
							workingAccountList.get(0).resetLimits();
							workingAccountList.remove(0);
						}
					}
					else
						isFinished = true;
				}
				else if (transactionCode.equals("10")) //Login
				{
					if(session == null)
						session = new Session(accountHolderName, miscField.equals("A "));
					else
						throw new TransactionError("Encountered login while a session was still active");
				}
				else if(transactionCode.equals("05")) //Create
				{
					if(session.getIsAdmin())
					{
						amount = Float.valueOf(line.substring(AMOUNT_START, AMOUNT_END));
						workingAccount = new Account(accountHolderName, accountNumber, amount, false, false);
						
						accounts.addAccount(workingAccount);
					}
					else
						throw new TransactionError("Tried to create an account while not an admin");
				}
				else
				{
					amount = Float.valueOf(line.substring(AMOUNT_START, AMOUNT_END));
					
					workingAccount = accounts.getAccount(accountNumber);
					
					if( ! workingAccount.isHolder(accountHolderName))
						throw new TransactionError("Holder name and account number mismatch in transaction log");
					
					if( ! (session.getIsAdmin() || isExpectingTransferTo || workingAccount.isHolder(session.getName())))
						throw new TransactionError("Session user does not have access to the account");
					
					switch (transactionCode)
					{		
						case("01"): //Withdrawal
							
							workingAccount.withdraw(amount, session.getIsAdmin());
							
							if(!session.getIsAdmin())
								workingAccountList.add(workingAccount);
						
							break;
						
						case("02"): //Transfer
							
							if(isExpectingTransferTo)
							{
								workingAccount.transferIn(amount);
								isExpectingTransferTo = false;
							}
							else
							{
								workingAccount.transferOut(amount, session.getIsAdmin());
								isExpectingTransferTo = true;
								
								if(!session.getIsAdmin())
								{
									workingAccountList.add(workingAccount);
									session.transferAmount(amount);
									
									if(session.getAmountTransfered() > 1000)
										throw new TransactionError("Transfered over $1000 in one session");
								}
							}
							break;
						
						case("03"): //Paybill
							
							session.payCompany(amount, miscField);
							workingAccount.paybill(amount, session.getIsAdmin());
						
							if((! session.getIsAdmin()) && session.getAmountPayed(miscField) > 2000)
								throw new TransactionError("Payed to much on a bill in a session");

							break;
						
						case("04"): //Deposit
							
							workingAccount.deposit(amount, session.getIsAdmin());
							
							if(!session.getIsAdmin())
								workingAccountList.add(workingAccount);
						
							break;
							
						case("06"): //Delete
							
							if(session.getIsAdmin())
								accounts.deleteAccount(accountNumber);
							else
								throw new TransactionError("Tried to delete an account while not an admin");
							
							break;
						
						case("07"): //Disable
							
							if(session.getIsAdmin())
								workingAccount.disable();
							else
								throw new TransactionError("Tried to disable an account while not an admin");
						
							break;
						
						case("08"): //Changeplan
							
							if(session.getIsAdmin())
								workingAccount.changePlan();
							else
								throw new TransactionError("Tried to change an account's plan while not an admin");
						
							break;
						
						case("09"): //Enable
							
							if(session.getIsAdmin())
								workingAccount.enable();
							else
								throw new TransactionError("Tried to enable an account while not an admin");
						
							break;
						
						default: //Invalid transaction code
							throw new TransactionError("Invalid transaction code");
					}
				}
			}
			
			transactionReader.close();
		}
		catch (FileNotFoundException fnfex)
		{
			throw new TransactionError("Transaction log file could not be found");
		}
		catch(IOException ioex)
		{
			throw new TransactionError("Encountered an IO exception while handling the transaction log");
		}
	
		return;
	}
}
