#define _CRT_SECURE_NO_WARNINGS

#include "ReportModule.h"
#include "Inventory.h"
#include "Book.h"
#include "BookPile.h"

//CIS 22B
//Rohan Rawat, Brandon Kawula, Noah Gutierrez, Barr Avr
//Team 3

//protypes
void modeDisplay(char screen);
void reportComandList();

//prints mode on screen
/*****************************************************************************/
//
// Function: modeDisplay
//
// Parameters: char screen
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:This displayes the screen the user is on
//
/*****************************************************************************/
void modeDisplay(char screen)
{
	
	std::cout << "\t" << "-----------------------------------" << "Screen" << "-----------------------------------" << std::endl;
	std::cout << "A: [" << (screen == 'A' || screen == 'a' ? "X" : " ") << "] Cashier Mode" << "\t"
		<< "B: [" << (screen == 'B' || screen == 'b' ? "X" : " ") << "] Inventory Mode" << "\t"
		<< "C: [" << (screen == 'C' || screen == 'c' ? "X" : " ") << "] Query Report" << "\t"<< "D: Exits Program" << std::endl << std::endl;
				
}



//prints all comands user can use on this remort module
/*****************************************************************************/
//
// Function: reportComandList()
//
// Parameters: none
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
//	Report Screen Comand List:
//	Prints out all valid user inputs for screen 3
//	1.	[1]: Inventory List: A list of information on all books in the inventory.
//	2.	[2]: Inventory Wholesale  Value List:
//	3.	[3]: Inventory  Retail  Value
//	4.	[4]: List by Quantity
//	5.	[5]: List by Cost
//	6.	[6]: List  by  Age
//
//
/*****************************************************************************/

void reportComandList()
{
	std::cout << "\t" << "-----------------------------------" << "Comands" << "-----------------------------------" << std::endl;
	std::cout << "[1]: Inventory List: A list of information on all books in the inventory.\n"
		<< "[2]: Inventory Wholesale  Value List:\n"
		<< "[3]: Inventory  Retail  Value:\n"
		<< "[4]: List by Quantity\n"
		<< "[5]: List by Cost\n"
		<< "[6]: List  by  Age\n"
		<< "[7]: Return to Main Menu: " << std::endl;

}

//prints out a list displaying whole sale price (empty books not displayed)
/*****************************************************************************/
//
// Function: inventoryWholesale
//
// Parameters: std::string name
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Prints out whole sale Price, ISBN and Title of all books in inventory ignores any empty entrys form printing. 
// Demonstrates polymorphism by useing bookpile's parent books << operator overload instead of it's own class.
//
// entering ifrent name changes defalt title of print out. ISBN formated to print 4 digits leading 0's and price to print out 2 decimal places
//
// prints total whole sale price
/*****************************************************************************/
void Inventory::inventoryWholesale(std::string name)
{
	//prints list of whole sale showes polymporphism of bookpile to parent of book
	std::cout << "\t" << "-----------------------------------" << name << "-----------------------------------" << std::endl;
	std::cout << std::left << std::setw(12) <<"Price:" << std::setw(8) <<"ISBN:" << "\t" << "Title:" << std::endl << std::resetiosflags(std::ios::showbase);
	double total = 0;
	for (int i = 0; i < numOfBooks; i++)
	{
		//guard to prevent empty entrys from printing
		if (books[i].getISBN() != 0)
		{
			total += books[i].getWholeSaleCost();
			book* temp = &books[i];
			std::cout  << "$" << std::left  << std::fixed << std::setprecision(2)<<std::setw(11) <<temp->getWholeSaleCost() << std::setw(8) << *temp << std::resetiosflags(std::ios::showbase) << std::endl;
		}
	}
	std::cout << std::endl << "Total: $" << std::fixed << std::setprecision(2) << total << std::resetiosflags(std::ios::showbase) << std::endl << std::endl;
}

//prints out a Inventory List for Report Screen (empty books not displayed)
/*****************************************************************************/
//
// Function: inventoryWholesale
//
// Parameters: std::string name
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Prints out ISBN and Title of all books in inventory ignores any empty entrys form printing. 
// Demonstrates polymorphism by useing bookpile's parent books << operator overload instead of it's own class.
//
// ISBN formated to print 4 digits leading 0's and price to print out 2 decimal places
//
/*****************************************************************************/
void Inventory::printInventoryReport()
{
	//prints list of Inventory showes polymporphism of bookpile to parent of book
	std::cout << "\t" << "-----------------------------------" << "Inventory:" << "-----------------------------------" << std::endl;
	std::cout << std::left << "ISBN:" << "\t" << "Title:" << std::endl << std::resetiosflags(std::ios::showbase);

	for (int i = 0; i < numOfBooks; i++)
	{
		//guard to prevent empty entrys from printing
		if (books[i].getISBN() != 0)
		{
			book* temp = &books[i];
			std::cout << std::left  << *temp << std::resetiosflags(std::ios::showbase) << std::endl;
		}
	}
}


//prints out a list displaying retail price (empty books not displayed)
/*****************************************************************************/
//
// Function: inventoryRetail
//
// Parameters: std::string name
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Prints out retail Price, ISBN and Title of all books in inventory ignores any empty entrys form printing. 
// Demonstrates polymorphism by useing bookpile's parent books << operator overload instead of it's own class.
//
// entering difrent name changes defalt title of print out. ISBN formated to print 4 digits leading 0's and price to print out 2 decimal places
//
// prints total retail price
/*****************************************************************************/
void Inventory::inventoryRetail(std::string name)
{
	//prints list of Retail sale showes polymporphism of bookpile to parent of book
	std::cout << "\t" << "-----------------------------------" << name << "-----------------------------------" << std::endl;
	std::cout << std::left << std::setw(12) << "Price:" << std::setw(8) << "ISBN:" << "\t" << "Title:" << std::endl << std::resetiosflags(std::ios::showbase);
	double total = 0;
	for (int i = 0; i < numOfBooks; i++)
	{
		//guard to prevent empty entrys from printing
		if (books[i].getISBN() != 0)
		{
			total += books[i].getRetailPrice();
			book* temp = &books[i];
			std::cout << "$" << std::left << std::fixed << std::setprecision(2) << std::setw(11) << temp->getRetailPrice() << std::setw(8) << *temp << std::resetiosflags(std::ios::showbase) << std::endl;
		}
	}
	std::cout << std::endl << "Total: $" << std::fixed << std::setprecision(2) << total << std::resetiosflags(std::ios::showbase) << std::endl << std::endl;

}

//prints out a list displaying number of books (empty books not displayed)
/*****************************************************************************/
//
// Function: inventoryQuantity
//
// Parameters: std::string name
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Prints out Quantity, ISBN and Title of all books in inventory ignores any empty entrys form printing. 
// Demonstrates polymorphism by useing bookpile's parent books << operator overload instead of it's own class.
//
// entering difrent name changes defalt title of print out. ISBN formated to print 4 digits leading 0's and price to print out 2 decimal places
//
// displays sold out if book quantity is 0
/*****************************************************************************/
void Inventory::inventoryQuantity(std::string name)
{
	//prints list of Retail sale showes polymporphism of bookpile to parent of book
	std::cout << "\t" << "-----------------------------------" << name << "-----------------------------------" << std::endl;
	std::cout << std::left << std::setw(10) << "Quantity:" << std::setw(5) << "ISBN:" << "\t" << "Title:" << std::endl << std::resetiosflags(std::ios::showbase);
	int total = 0;
	for (int i = 0; i < numOfBooks; i++)
	{
		//guard to prevent empty entrys from printing
		if (books[i].getISBN() != 0)
		{
			book* temp = &books[i];
			std::cout << std::left << std::setw(10);
				
				if (books[i].getQuantity() > 0) {
					std::cout << books[i].getQuantity();
				}
				else {
					std::cout << "sold out";
				}

			std::cout << std::setw(8) << *temp << std::resetiosflags(std::ios::showbase) << std::endl;
		}
	}
}


//prints out a list displaying date added (empty books not displayed)
/*****************************************************************************/
//
// Function: inventoryAge
//
// Parameters: std::string name
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Prints out date added, ISBN and Title of all books in inventory ignores any empty entrys form printing. 
// Demonstrates polymorphism by useing bookpile's parent books << operator overload instead of it's own class.
//
// entering difrent name changes defalt title of print out. ISBN formated to print 4 digits leading 0's and price to print out 2 decimal places
//
/*****************************************************************************/
void Inventory::inventoryAge(std::string name)
{
	//prints list of Retail sale showes polymporphism of bookpile to parent of book
	std::cout << "\t" << "-----------------------------------" << name << "-----------------------------------" << std::endl;
	std::cout << std::left << std::setw(10) << "Date Added:" << "\t"<< "ISBN:" << "\t" << "Title:" << std::endl << std::resetiosflags(std::ios::showbase);
	int total = 0;
	for (int i = 0; i < numOfBooks; i++)
	{
		//guard to prevent empty entrys from printing
		if (books[i].getISBN() != 0)
		{
			book temp = books[i];
			std::cout << std::right << std::setfill('0') << std::setw(2)<<books[i].dateAdded[0]<<"/"<< std::setw(2)<< books[i].dateAdded[1] << "/" << std::setw(4) << std::setfill(' ') << books[i].dateAdded[2] << "\t" << temp << std::resetiosflags(std::ios::showbase) << std::endl;
		}
	}
}

//Sorts by wholesale price then prints out a list displaying books and wholesale price(empty books not displayed)
/*****************************************************************************/
//
// Function: Inventory::sortByWholeSaleCost()
//
// Parameters: none
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// function of the inventory class that sort list by wholesale cost useing select sort; highest to lowest.
//  calls inventory class function "inventoryWholesale" to display results
//
/*****************************************************************************/
void  Inventory::sortByWholeSaleCost()
{
	for (int i = 0; i < numOfBooks; i++)
	{
		for (int x = i + 1; x < numOfBooks; x++)
		{
			if ((books + i)->getWholeSaleCost() < (books + x)->getWholeSaleCost())
			{
				BookPile temp = *(books + i);
				*(books + i) = *(books + x);
				*(books + x) = temp;
			}
		}
	}
	this->inventoryWholesale("Sorted By Whole Sale Cost");
}

//Sorts by Quantity then prints out a list displaying books and Quantity(empty books not displayed)
/*****************************************************************************/
//
// Function: Inventory::sortByQuantity()
//
// Parameters: none
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// function of the inventory class that sort list by quantity useing select sort; highest to lowest.
// calls inventory class function "inventoryQuantity()" to display results
//
/*****************************************************************************/
void  Inventory::sortByQuantity()
{
	for (int i = 0; i < numOfBooks; i++)
	{
		for (int x = i + 1; x < numOfBooks; x++)
		{
			if ((books + i)->getQuantity() < (books + x)->getQuantity())
			{
				BookPile temp = *(books + i);
				*(books + i) = *(books + x);
				*(books + x) = temp;

			}

		}

	}
	this->inventoryQuantity("Sorted By Quantity");

}

//Sorts by date added then prints out a list displaying books and date added(empty books not displayed)
/*****************************************************************************/
//
// Function: Inventory::sortByQuantity()
//
// Parameters: none
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// function of the inventory class that sort list by date added useing select sort; oldest to newest.
// calls inventory class function "inventoryAge()" to display results
//
/*****************************************************************************/
void  Inventory::sortByAge()
{
	//sorts by year
	for (int i = 0; i < numOfBooks; i++)
	{
		for (int x = i + 1; x < numOfBooks; x++)
		{
			if ((books + i)->dateAdded[2] > (books + x)->dateAdded[2])
			{
				BookPile temp = *(books + i);
				*(books + i) = *(books + x);
				*(books + x) = temp;

			}

		}

	}
	//sorts by month within same year
	for (int i = 0; i < numOfBooks; i++)
	{
		for (int x = i + 1; x < numOfBooks; x++)
		{
			if (((books + i)->dateAdded[0] > (books + x)->dateAdded[0])&& ((books + i)->dateAdded[2] == (books + x)->dateAdded[2]))
			{
				BookPile temp = *(books + i);
				*(books + i) = *(books + x);
				*(books + x) = temp;

			}

		}

	}

	//sorts by day within same year and month
	for (int i = 0; i < numOfBooks; i++)
	{
		for (int x = i + 1; x < numOfBooks; x++)
		{
			if (((books + i)->dateAdded[1] > (books + x)->dateAdded[1]) && ((books + i)->dateAdded[2] == (books + x)->dateAdded[2]) && ((books + i)->dateAdded[0] == (books + x)->dateAdded[0]))
			{
				BookPile temp = *(books + i);
				*(books + i) = *(books + x);
				*(books + x) = temp;

			}

		}

	}



	this->inventoryAge("Sorted By Date Added");

}