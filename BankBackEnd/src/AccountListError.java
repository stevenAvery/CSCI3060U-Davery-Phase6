
public class AccountListError extends Exception
{
	private static final long serialVersionUID = 1L;
	
	private String message;
	
	public AccountListError()
	{
		this.message = "";
	}
	
	public AccountListError(String message)
	{
		this.message = message;
	}
	
	public String getMessage()
	{
		return message;
	}
}