package assg9_griffiniz18;

public class Customer extends KeyedItem<String> {

	public String name, phonenum;
	
	/**
	 * default constructor
	 * @param uname	The given customer Name 
	 * @param num	The given customer Phone-Number
	 */
	public Customer(String key, String uname, String num) {
		super(key);
		name = uname;
		phonenum = num;
		// TODO Auto-generated constructor stub
	}
	/**
	 * Retrieve the Student ID 
	 * @return The Student ID 
	 */
	public String getId() {
		return this.getKey();
	}
	/**
	 * Retrieve the Student Standing 
	 * @return The Student  Standing
	 */
	public String getPhonenum() {
		return phonenum;
	}
	/**
	 * Retrieve the Student Name
	 * @return The Student Name 
	 */
	public String getName() {
		return name;
	}
	/**
	 * Modify the Customer name
	 */
	public void setName(String nam) {
		name=nam;
	}
	/**
	 * Modify the Customer Phone-Number
	 */
	public void setPhonenum(String phonenum1) {
		phonenum=phonenum1;
	}
	/**
	 * @Override
	 * Return a string with the Customer id, name, and phone-number
	 * @return The string of the Customer id, name, and phone-number
	 */
	public String toString() 
	{
		return getId() + "	" + getName() + "	" + getPhonenum();
	}
}
