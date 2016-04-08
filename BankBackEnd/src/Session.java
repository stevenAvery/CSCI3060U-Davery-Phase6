/**
 * Class for recording session related variables
 */
public class Session {
  private boolean isAdmin;
  private String name;
  private float amountTransferred;
  private float [] amountPayed;

  /**
   * 
   * @param name User name that started session
   * @param isAdmin Flag if user is an admin or not
   */
  public Session(String name, boolean isAdmin)
  {
	  this.name = name;
	  this.isAdmin = isAdmin;
	  this.amountTransferred = 0.0f;
	  this.amountPayed = new float[]{0.0f, 0.0f, 0.0f};
  }
  
  /**
   * Gets a boolean indicating if the user that started the session was an admin
   * @return True if admin session, otherwise returns false
   */
  public boolean getIsAdmin()
  {
	  return isAdmin;
  }

  /**
   * Gets the user name that started the session
   * @return The sessions user name
   */
  public String getName()
  {
	  return name;
  }

  /**
   * Get the amount payed to a company during the session
   * @param companyName Company to check amount payed
   * @return The amount payed to the given company
   */
  public float getAmountPayed(String companyName)
  {
	  float amount = 0.0f;
	  
	  switch(companyName)
	  {
	  	case("EC"):
		  amount = amountPayed[0];
	  		break;
	  	case("CQ"):
			  amount = amountPayed[1];
		  		break;
	  	case("TV"):
			  amount = amountPayed[2];
		  		break;
	  }
	  
	  return amount;
  }

  /**
   * Add to the amount payed to a company during a session
   * @param amount Amount to pay
   * @param companyName Company to pay to
   */
  public void payCompany(float amount, String companyName)
  {
	  switch(companyName)
	  {
	  	case("EC"):
		  amountPayed[0] += amount;
	  		break;
	  	case("CQ"):
			  amountPayed[1] += amount;
		  		break;
	  	case("TV"):
			  amountPayed[2] += amount;
		  		break;
	  }
	  return;
  }

  /**
   * Gets the amount transfered during the session
   * @return Amount transfered during the session
   */
  public float getAmountTransfered()
  {
	  return amountTransferred;
  }

  /**
   * Add to the amount transfered during the session
   * 
   * @param amount Amount being transfered
   */
  public void transferAmount(float amount)
  {
	  amountTransferred += amount;
	  return;
  }
}
