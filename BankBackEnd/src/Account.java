
public class Account {
    private String holderName;
    private String accountNumber;
    private float balance;
    private float amountDeposited;
    private float amountWithdrawn;
    private boolean isDisabled;
    private boolean isStudent;
    private int transactionPerformed;

    public Account(String holderName, String accountNumber, float balance, boolean isDisabled, boolean isStudent)
    {
    	this.holderName = holderName;
    	this.accountNumber = accountNumber;
    	this.balance = balance;
    	this.isDisabled = isDisabled;
    	this.isStudent = isStudent;
    }
    
    /**
     * Gets the account's account number
     * @return The account's number
     */
    public String getAccountNumber()
    {
    	return accountNumber;
    }
    
    /**
     * Checks if the person is holder of this account
     * @param name
     * @return True if the names match, otherwise false
     */
    public boolean isHolder(String name)
    {
    	return (holderName.equals(name));
    }
    
    /**
     * 
     * @return True if the account is disabled, otherwise false
     */
    public boolean getIsDisabled()
    {
    	return isDisabled;
    }

    /**
     * Withdraws the amount from the account, and waives fee if admin transaction
     * @param amount The amount to withdraw
     * @param isAdminTransaction Boolean indicating if the transaction is being performed by an admin
     * @throws TransactionError
     */
    public void withdraw(float amount, boolean isAdminTransaction) throws TransactionError
    {
    	float fee = 0;
    	
    	if(isDisabled)
    		throw new TransactionError("Tried to withdraw from a disabled account");
    	
    	if(!isAdminTransaction)
    	{
    		fee = transactionFeeAmount();
    		
    		if(amountWithdrawn + amount > 500.0f)
    			throw new TransactionError("Has withdrawn more than $500");
    	}
    	
    	if(workingBalance() < amount + fee)
    		throw new TransactionError("Insuficiant funds, cannot withdraw from account");
    	else if((amount - (int)amount) != 0 || ((int)amount) % 5 != 0)
    		throw new TransactionError("Amount to withdrawal needs to be base 5");
    	else
    	{
    		balance -= (amount + fee);
    		amountWithdrawn += amount;
    	}
    	
    	transactionPerformed++;
    	
    	return;
    }

    /**
     * Deposits the amount into the account, and waives fee if admin transaction
     * @param amount The amount to deposit
     * @param isAdminTransaction Boolean indicating if the transaction is being performed by an admin
     * @throws TransactionError
     */
    public void deposit(float amount, boolean isAdminTransaction) throws TransactionError
    {
    	float fee = 0;
    	
    	if(isDisabled)
    		throw new TransactionError("Tried to deposit to a disabled account");
    	
    	if(!isAdminTransaction)
    	{
    		fee = transactionFeeAmount();
    		
    		if(balance + amount - fee < 0.0f)
    			throw new TransactionError("Deposit made balance negative");
    	}
    	
    	balance += amount - fee;
    	amountDeposited += amount;
    	
    	transactionPerformed++;
    }

    /**
     * Deposits money from a transfer transaction
     * @param amount The amount to transfer into the account
     * @throws TransactionError 
     */
    public void transferIn(float amount) throws TransactionError
    {
    	if(isDisabled)
    		throw new TransactionError("Tried to transfer funds to a disabled account");
    	
    	balance += amount;
    	
    	transactionPerformed++;
    }

    /**
     * Withdraws money for a transfer transaction
     * @param amount The amount to transfer out
     * @param isAdminTransaction Boolean indicating if the transaction is being performed by an admin
     * @throws TransactionError
     */
    public void transferOut(float amount, boolean isAdminTransaction) throws TransactionError
    {
    	float fee = 0;
    	
    	if(isDisabled)
    		throw new TransactionError("Tried to transfer funds from a disabled account");
    	
    	if(!isAdminTransaction)
    		fee = transactionFeeAmount();
    	
    	if(workingBalance() >= amount + fee)
    		balance -= (amount + fee);
    	else
    		throw new TransactionError("Account does not have the funds to transfer");
    	
    	transactionPerformed++;
    	
    	return;
    }

    /**
     * Withdraws the amount needed to pay the bill, and waives fee if admin transaction
     * @param amount The amount to pay
     * @param isAdminTransaction Boolean indicating if the transaction is being performed by an admin
     * @throws TransactionError
     */
    public void paybill(float amount, boolean isAdminTransaction) throws TransactionError
    {
    	float fee = 0;
    	
    	if(isDisabled)
    		throw new TransactionError("Tried to pay a bill from a disabled account");
    	
    	if(!isAdminTransaction)
    		fee = transactionFeeAmount();
    	
    	if(workingBalance() >= amount + fee)
    		balance -= (amount + fee);
    	else
    		throw new TransactionError("Cannot pay bill due to insuficient funds");
    	
    	transactionPerformed++;
    }
    
    /**
     * Determines the transaction fee amount for the account
     * @return The transaction fee amount
     */
    public float transactionFeeAmount()
    {
    	if(isStudent)
    		return 0.05f;
    	else
    		return 0.10f;
    }

    /**
     * Determines the working balance of the account
     * @return The account balance minus the amount deposited so far
     */
    public float workingBalance()
    {
    	return (balance - amountDeposited);
    }

    /**
     * Enables the account
     * @throws TransactionError If already enabled
     */
    public void enable() throws TransactionError
    {
    	if (isDisabled)
    		isDisabled = false;
    	else
    		throw new TransactionError("Account was already enabled");
    	
    	transactionPerformed++;
    	
    	return;
    }

    /**
     * Disables the account
     * @throws TransactionError If already disabled
     */
    public void disable() throws TransactionError
    {
    	if (!isDisabled)
    		isDisabled = true;
    	else
    		throw new TransactionError("Account was already disabled");
    	
    	transactionPerformed++;
    	
    	return;
    }

    /**
     * Switches the plan from student to standard and vice versa
     * @throws TransactionError 
     */
    public void changePlan() throws TransactionError
    {
    	if(isDisabled)
    		throw new TransactionError("Tried to change the plan of a disabled account");
    	
    	isStudent = !isStudent;
    }

    /**
     * Formats the accounts information for writing to the current accounts file
     * @return The accounts information formated as a string
     */
    public String formatForCurrentAccountFile()
    {
    	return String.format("%1$5s %2$-20s %3$1s %4$08.2f %5$1s", accountNumber, holderName, isDisabled ? "D" : "S", balance, isStudent ? "S" : "N").replace(' ', '_');
    }

    /**
     * Formats the accounts information for writing to the master accounts file
     * @return The accounts information formated as a string
     */
    public String formatForMasterAccountFile()
    {
    	String recordLine = formatForCurrentAccountFile();
    	
    	recordLine += String.format("_%1$04d", transactionPerformed);
    	
    	return recordLine;
    }

    /**
     *  Resets amount deposited and amount withdrawn for this account
     */
    public void resetLimits()
    {
    	amountDeposited = 0;
    	amountWithdrawn = 0;
    	
    	return;
    }
}