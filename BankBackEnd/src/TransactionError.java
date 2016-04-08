
public class TransactionError extends Exception
{
	private static final long serialVersionUID = 1L;
	
	private String message;
	
	public TransactionError()
	{
		this.message = "";
	}
	
	public TransactionError(String message)
	{
		this.message = message;
	}
	
	public String getMessage()
	{
		return message;
	}
}
