package assg9_griffiniz18;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class CustomerRoster {
	// The customer roster
	BinarySearchTree<Customer, String> custroster = new BinarySearchTree<Customer, String>();
	
	/** 
	 *  Will open the file and put all the student s from the file in a roster Arraylist of students
	 *  @catch FileNotFoundException exception if file is invalid
	 */
	public void loadData(String Filename){
		String line;
		Scanner inputStream = null;
		try {
			inputStream = new Scanner(new File(Filename));
		}
		// If file cannot open will print out error
		catch (FileNotFoundException e) {
			System.out.println("Error openning the file " + Filename);
			System.exit(1);
		}
		while (inputStream.hasNextLine()) {
			line = inputStream.nextLine();
			String[] parts = line.split("	");
			custroster.insert(new Customer(parts[0],parts[1],parts[2]));
		}
		inputStream.close();
	}
	
	/**  
	 * Will display all the Customers in the roster (in order)
	 */
	public void displayRoster() {
		TreeIterator<Customer> iter;
		iter = new TreeIterator<Customer>(custroster);
	
		iter.setInorder();
	
		while (iter.hasNext()) {
			Customer i = iter.next();
			System.out.println(i.toString());
		}
	}
	
	/**  
	 * if the customer is in the roster it will add them to the roster
	 * if not prints statement
	 */
	public void addCustomer(String key, String uname, String num) {
		if (searchForCustomer(key)==null){
			custroster.insert(new Customer(key,uname,num));
		}
		else {
		System.out.println("The customer is already in roster");
		}
	}
	/**  
	 * Return true if the Customer is the roster and will remove them from the roster if not returns false
	 * @return true if the Customer is in the roster
	 * @return false if the Customer is not in the roster
	 */
	public boolean removeCustomer(String key) {
		if (searchForCustomer(key)!=null){
			custroster.delete(searchForCustomer(key));
			return true;
		}
		return false;
	}
	/**  
	 * Will return Customer if the ID of the student is equal to the chosen ID
	 * @return Customer(i) if the Customer is in the roster
	 * @return null if the Customer is not in the roster
	 */
	public Customer searchForCustomer(String id) {
		TreeIterator<Customer> iter;
		iter = new TreeIterator<Customer>(custroster);
		
		iter.setInorder();
		
		while (iter.hasNext()) {
			Customer i = iter.next();
			if (i.getKey().equals(id))
    	  		return i;
		}
		return null;
	}
	/**
	 * Saves the roster to the file input 
	 * @catch FileNotFoundException exception if file is invalid 
	 */
	public void Save()
	{
			// creates the output
			PrintWriter outputStream = null;
		
			// try to open the input file and catches exception if file is not found
			try {  
				outputStream = new PrintWriter("assg9_CustomerRoster.txt");
			}        
			catch(FileNotFoundException e) {            
				System.out.println("Error opening the file assg9_CustomerRoster.txt");
				System.exit(0);
			}
			// if file opens will rewrite the current customer roster to the file
			TreeIterator<Customer> iter;
			iter = new TreeIterator<Customer>(custroster);
			
			iter.setInorder();
			
			while (iter.hasNext()) {
				Customer i = iter.next();
				outputStream.write(i.toString()+ "\n");
			}
			outputStream.close();
	}
}
