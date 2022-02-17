package assg9_griffiniz18;

import java.util.Scanner;

public class CustomerMIS {
	public static void main(String[] args) {
		
		
		// option is the user input of the application
		// count to make sure to save the file if a change is made
		int option, count;
		count = 0;
		Scanner scannerObject = new Scanner(System.in);
		Scanner scannerObject1 = new Scanner(System.in);
		Scanner scannerObject2 = new Scanner(System.in);
		Scanner scannerObject3 = new Scanner(System.in);
		Scanner scannerObject4 = new Scanner(System.in);
		Scanner scannerObject5 = new Scanner(System.in);
		Scanner scannerObject6 = new Scanner(System.in);
		Scanner scannerObject7 = new Scanner(System.in);
		Scanner scannerObject8 = new Scanner(System.in);
		Scanner scannerObject9 = new Scanner(System.in);
		// creates a new roster
		CustomerRoster roster = new CustomerRoster();
		roster.loadData("assg9_CustomerRoster.txt");
		do
		{
		System.out.print("\nEnter the option number you would like to do (Press Enter to Continue):\n"
				+ "1: Display the roster\r\n"
				+ "2. Search for a Customer by id\r\n"
				+ "3. Add a new Customer\r\n"
				+ "4. Remove a Customer\r\n"
				+ "5. Update Customer's Info.\r\n"
				+ "6. Save to file\r\n"
				+ "7. Exit\n ");
		
		// option is the option of the application(user input)
		option = scannerObject.nextInt();
		
		//Switch Case if user puts in option 1-6, will exit if 7
		switch (option)
		{
		// case 1 displays roster
		case 1: 
			System.out.println("");
			roster.displayRoster();
			break;
		// case 2 will search for student by id
		case 2:
			System.out.print("\nEnter the Id of the Student you'd like to find (Press Enter to Continue): ");
			//student's id number
			String stu = scannerObject1.nextLine();
			if (roster.searchForCustomer(stu) == null)
				System.out.println("Customer not found");
			else
				System.out.println(roster.searchForCustomer(stu).name + "	" + roster.searchForCustomer(stu).phonenum);
			break;
		// case 3 will add student
		case 3:
			System.out.print("\nEnter the Customer Id(XXXXX): ");
			String id = scannerObject2.nextLine();
			// if id is not in the roster ( will get the rest of the info from the user) then adds them to the roster
			if (roster.searchForCustomer(id) == null) {
				System.out.print("\nEnter the rest of the Information of the Customer (Press Enter to Continue after each item): \n");
				System.out.print("Name(First name Last name): "); 
				String nam = scannerObject3.nextLine();
				System.out.print("Phone-number(XXX-XXX-XXXX): ");
				String num = scannerObject4.nextLine();
				roster.addCustomer(id,nam,num);
				//adds to count because something was done to the roster
				count++;
			}
			else
				roster.addCustomer(id, " ", " ");
			break;
		// case 4 will remove student from roster
		case 4:
			System.out.print("\nEnter the Customer Id: ");
			String rid = scannerObject5.nextLine();
			// if student is in the roster will remove them
			if (roster.removeCustomer(rid) == true) {
				roster.removeCustomer(rid);
				//adds to count because something was done to the roster
				count++;
			}
			else
				System.out.println("The Customer is not in this Roster");
			break;
		// case 5 will find the customer to edit their information
		case 5:
			System.out.print("\nEnter the Customer Id: ");
			String stu1 = scannerObject6.nextLine();
			if (roster.searchForCustomer(stu1) == null)
				System.out.println("Customer not found");
			else {
				System.out.println("What would you like to edit, Phone-number(P) or Name(N)");
				char stu2 = scannerObject7.next().charAt(0);
				if (stu2 == 'P' || stu2 == 'p') {
					System.out.print("Re-enter Phone-number(XXX-XXX-XXXX): ");
					String stu3 = scannerObject8.next();
					roster.searchForCustomer(stu1).setPhonenum(stu3);
				}
				if (stu2 == 'N' || stu2 == 'n')
				{
					System.out.print("Re-enter Name(First name Last name): ");
					String stu3 = scannerObject9.nextLine();
					roster.searchForCustomer(stu1).setName(stu3);
				}
			}
			break;
		// case 6 saves the roster back to the file
		case 6:
			roster.Save();
			System.out.print("\nThe roster has been saved to the file\n");
			// resets count back to 0 since all the changes have been saved
			count = 0;
			break;
		// case 7 saves the roster back to the file and save changes if they were made and not previously saved
		case 7:
			//if count is 0 
			if (count > 0)
			{
				System.out.print("\nThe changes to the roster have been saved to the file");
				roster.Save();	
			}
			break;
		// default input if the option is not 1-7
		default:
			System.out.println("\nIncorrect input try another option");
			break;
		}
		
		}while (option != 7);
		
		// If user leaves the roster application
		System.out.println("\nThank you, Good-bye!");
		
		// closes all user input objects
		count=0;
		scannerObject.close();
		scannerObject1.close();
		scannerObject2.close();
		scannerObject3.close();
		scannerObject4.close();
		scannerObject5.close();
		scannerObject6.close();
		scannerObject7.close();
		scannerObject8.close();
		scannerObject9.close();
}
}
