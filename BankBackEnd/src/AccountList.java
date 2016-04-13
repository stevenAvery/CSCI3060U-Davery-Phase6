import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.ArrayList;

/**
 * Class for getting and holding all instantiated accounts
 */
public class AccountList 
{
	public ArrayList<Account> accounts;
	
	public AccountList()
	{
		accounts = new ArrayList<Account>(10);
	}
  
	/**
	 * Uses the old current account file to create each account and add them to the account list
	 * @param oldCurrentAccountFile The file path to the old current account file
	 * @throws Exception
	 */
	public void loadAccounts(String oldCurrentAccountFile) throws Exception
	{
		final int ACCOUNT_NUMBER_START = 0;
		final int ACCOUNT_NUMBER_END = 5;
		final int ACCOUNT_HOLDER_START = 6;
		final int ACCOUNT_HOLDER_END = 26;
		final int ACCOUNT_STATUS_START = 27;
		final int ACCOUNT_STATUS_END = 28;
		final int ACCOUNT_BALANCE_START = 29;
		final int ACCOUNT_BALANCE_END = 37;
		final int ACCOUNT_PLAN_START = 38;
		final int ACCOUNT_PLAN_END = 39;
		
		boolean isEndAccount = false;
		String line;
		
		String accountHolderName;
		String accountNumber;
		float balance;
		boolean isDisabled = false;
		boolean isStudent = false;
		
		String temp;
		
		try
		{
			FileReader fileReader = new FileReader(oldCurrentAccountFile);
			BufferedReader accountFileReader = new BufferedReader(fileReader);
			
			while (!isEndAccount)
			{
				line = accountFileReader.readLine();
				
				if(line == null)
					isEndAccount = true;
				else
				{
					accountHolderName = line.substring(ACCOUNT_HOLDER_START, ACCOUNT_HOLDER_END).trim();
					accountNumber = line.substring(ACCOUNT_NUMBER_START, ACCOUNT_NUMBER_END);
					balance = Float.parseFloat(line.substring(ACCOUNT_BALANCE_START, ACCOUNT_BALANCE_END));
					
					//Get and validate account status
					temp = line.substring(ACCOUNT_STATUS_START, ACCOUNT_STATUS_END);
					
					if(temp.equals("A"))
						isDisabled = false;
					else if (temp.equals("D"))
						isDisabled = true;
					else
						throw new AccountListError("Invalid account status");
					
					//Get and validate account plan
					temp = line.substring(ACCOUNT_PLAN_START, ACCOUNT_PLAN_END);
					
					if(temp.equals("N"))
						isStudent = false;
					else if (temp.equals("S"))
						isStudent = true;
					else
						throw new AccountListError("Invalid account plan");
					
					accounts.add(new Account(accountHolderName, accountNumber, balance, isDisabled, isStudent));
				}
			}
			
			accountFileReader.close();
			
		}
		catch (Exception ex)
		{
			throw ex;
		}
		
		return;
	}
	
	/**
	 * Adds an account to the list, positioned by account number
	 * @param newAccount The account to add
	 * @throws TransactionError When the account number is already taken
	 */
	public void addAccount(Account newAccount) throws TransactionError
	{
		boolean accountAdded = false;
		int accountToCheck = 0;
		
		int accountNum = Integer.parseInt(newAccount.getAccountNumber());
		int checkedAccountNum;
		
		while (accountAdded == false && accountToCheck < accounts.size())
		{
			checkedAccountNum = Integer.parseInt(accounts.get(accountToCheck++).getAccountNumber());
			
			if(checkedAccountNum == accountNum)
				throw new TransactionError("Account Number is already taken");
			else if(checkedAccountNum > accountNum)
			{
				accountAdded = true;
				accounts.add(accountToCheck - 1, newAccount);
			}
		}
		
		if( ! accountAdded)
			accounts.add(accounts.size(), newAccount);
	}
	
	/**
	 * 
	 * @param accountNumber Account number to find in the list
	 * @return The account with the matching account number
	 * @throws AccountListError When the account number does not exist in the list
	 */
	public Account getAccount(String accountNumber) throws AccountListError
	{  
	  for(int i = 0; i < accounts.size(); i++)
	  {
		  if(accounts.get(i).getAccountNumber().equals(accountNumber))
		  {
			  return accounts.get(i);
		  }
	  }
	  
	  throw new AccountListError("Account could not be found");
	}
	
	/**
	 * 
	 * @param accountNumber The account number of the account to delete
	 * @throws AccountListError When the account number does not correspond to an account in the list
	 */
	public void deleteAccount(String accountNumber) throws AccountListError//, TransactionError
	{
		Account accountToDelete;
		
		try
		{
			accountToDelete = getAccount(accountNumber);
			
			//if(accountToDelete.getIsDisabled())
				accounts.remove(accountToDelete);
			//else
				//throw new TransactionError("Tried to delete an account that was not disabled");
		}
		catch(AccountListError ex)
		{
			throw new AccountListError("Tried to delete an account that does not exist");
		}
	}

	/**
	 * Creates the new current and master account files using the accounts in the list
	 * @throws Exception
	 */
	public void writeNewAccountFiles(String newMasterFilePath, String newCurrentAccountsFilePath) throws Exception
	{
		try
		{
			PrintWriter writer = new PrintWriter(newCurrentAccountsFilePath);
			
			for(int i = 0; i < accounts.size(); i++)
			{
				writer.println(accounts.get(i).formatForCurrentAccountFile());
			}
			
			writer.println("99999 END OF FILE          D 00000.00 N");
			writer.close();
			
			writer = new PrintWriter(newMasterFilePath);
			
			for(int i = 0; i < accounts.size(); i++)
			{
				writer.println(accounts.get(i).formatForMasterAccountFile());
			}
			
			writer.close();
		}
		catch (Exception ex)
		{
			throw ex;
		}
	}

}