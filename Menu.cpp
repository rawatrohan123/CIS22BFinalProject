#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Book.h"
#include "Inventory.h"
#include "ReportModule.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "BookPile.h"

#include <iostream>
#include <string>

//CIS 22B
//Rohan Rawat, Brandon Kawula, Noah Gutierrez, Barr Avr
//Team 3


using namespace std;

void cashierMode(char& mode, Inventory&);
void inventoryMode(bool& run, char& mode, Inventory&);
void queryReport(bool& run, char& mode, Inventory* BookStore, int shelfSize, char& screen);
bool user_navigator(char& screen, int& userComand, int numberOfuserOptions);

int main() 
{
	char screen = 'E'; // main menu
	const int shelfSize = 25;
	Inventory BookStore;

	//BookPile inventory[shelfSize];

	//reads files from "books.txt"
	BookStore.readFile();


	// final project start
	bool run;
	bool operating = true;
	while (screen != 'D')
	{
		int input;
		string mode;
		if (screen == 'E')
		{
			std::system("CLS");
			std::cout << "Main Menu:\nEnter Letter to change modes\n"
				<< "[A]: Cashier Mode\n"
				<< "[B]: Inventory Mode\n"
				<< "[C]: Query Report\n"
				<< "[D]: Exit System\n";
			user_navigator(screen, input, 0);
		}
		
		

		if (screen == 'A') {
			//"CASHIER MODE";
			input = 1;
		}
		else if (screen == 'B') {
			//"INVENTORY MODE";
			input = 2;
		}
		else if (screen == 'C') {
			//"QUERY REPORT";
			input = 3;
		}
		else if (screen == 'D') {
			std::cout << "Exiting..." << endl;
			input = 4;
		}
		else {
			std::cout << "ERROR" << endl;
		}



		switch (input) 
		{
		case 1:
			cashierMode(screen, BookStore);
			break;
		case 2:
			inventoryMode(run, screen, BookStore);
			break;
		case 3:
			queryReport(run, screen, &BookStore, shelfSize, screen);
			break;
		case 4:
			{
			BookStore.writeFile();
			operating = false;
			break;
			}
		default:
			std::cout << "Invalid input, please try again." << endl;
			break;
		}
	}
	return 0;
}


void cashierMode(char& mode, Inventory& BookStore)
{
	//BookPile cart[25];
	int cartInfo[25];
	for (int i = 0; i < 25; i++) {
		cartInfo[i] = -1;
	}
	int count = 0;
	Inventory cart;
	//bool run = true;
	while (mode=='A')
	{
		std::system("CLS");
		//displays to user what mode the program currently is in
		modeDisplay(mode);
		//printInventory();
		//printCart();
		//printTotals();

		
		int userComand;

BookStore.printInventory();

std::cout << "Enter number to select action: \n"
<< "[1]: Add book to cart\n"
<< "[2]: Remove book from cart\n"
<< "[3]: Check out\n"
<< "[4]: Return to Main Menu (empty cart)" << endl;
user_navigator(mode, userComand, 4);

switch (userComand) {
case 1:
{
	int isbn = 0;
	int quantity;
	std::cout << "Please enter the ISBN# of the book you would like to add: " << endl;
	std::cin >> isbn;
	std::cout << isbn << endl;
	while (isbn <= 999 || isbn > 9999) {
		std::cout << "please enter a positive four digit number for the isbn#: " << endl;
		std::cin >> isbn;
	}

	std::cout << "Please enter the number of copies of this book you would like to add to your cart: " << endl;
	std::cin >> quantity;
	while (quantity <= 0) {
		std::cout << "Please enter a quantity greater than 0: " << endl;
		std::cin >> quantity;
	}


	if (BookStore.searchBookByISBN(isbn) != -1)
	{
		//add the given amount of the given book to cart
		BookPile temp = BookStore.getBook(BookStore.searchBookByISBN(isbn));
		cartInfo[count] = isbn;
		count++;
		temp.setQuantity(0);
		cart.addBook(temp); //check if copy constructor works correctly
		cart.getBook(BookStore.searchBooks(cart.getBook(cart.searchBookByISBN(isbn)))).setQuantity(0);
		if (quantity <= BookStore.getBook(BookStore.searchBookByISBN(isbn)).getQuantity())
		{
			cart.getBook(BookStore.searchBooks(cart.getBook(cart.searchBookByISBN(isbn)))).setQuantity(quantity);
			
			for (int i = 0; i < quantity; i++)
			{

				BookStore.removeBook(cart.getBook(cart.searchBookByISBN(isbn)));
				cart.addBook(cart.getBook(cart.searchBookByISBN(isbn)));

			}

		}
		else {
			int maxbooks = BookStore.getBook(BookStore.searchBookByISBN(isbn)).getQuantity();
			std::cout << "We didn't have that many of that book left, so " << maxbooks << " were put in the cart" << endl; //ran out of books message
			
			for (int i = 0; i < maxbooks; i++)
			{

				BookStore.removeBook(cart.getBook(cart.searchBookByISBN(isbn)));
				cart.addBook(cart.getBook(cart.searchBookByISBN(isbn)));

			}
			BookStore.getBook(BookStore.searchBooks(cart.getBook(cart.searchBookByISBN(isbn)))).setQuantity(0);
		}

		//cart.printInventory();
		//BookStore.printInventory();
	}
	else
	{
		std::cout << "Sorry, we don't appear to have that book in stock" << endl;
	}
	BookStore.writeFile();
	std::system("pause");
	break;

}
case 2: //pls fix this noah
{
	int isbn = 0;
	int quantity;
	std::cout << "Please enter the ISBN# of the book you would like to remove: " << endl;
	std::cin >> isbn;
	while (isbn <= 999 || isbn > 9999) {
		std::cout << "Please enter a positive four digit number for the ISBN#: " << endl;
		std::cin >> isbn;
	}

	std::cout << "Please enter the number of copies of this book you would like to remove from your cart: " << endl;
	std::cin >> quantity;
	while (quantity <= 0) {
		std::cout << "Please enter a quantity greater than 0: " << endl;
		std::cin >> quantity;
	}

		if (quantity >= cart.getBook(cart.searchBookByISBN(isbn)).getQuantity())
			{
			//ran out of books message
			quantity = cart.getBook(cart.searchBookByISBN(isbn)).getQuantity();
			std::cout << "We didn't have that many of that book left in cart, so " << cart.getBook(cart.searchBookByISBN(isbn)).getQuantity() << " where removed from the cart" << endl;
			}

			//add the given amount of the given book to bookstore
			for (int i = 0; i < quantity; i++)
			{

				cart.removeBook(cart.getBook(cart.searchBookByISBN(isbn)));
				BookStore.addBook(cart.getBook(cart.searchBookByISBN(isbn)));

			}

			cart.removeBook(BookStore.getBook(BookStore.searchBookByISBN(isbn)));
			BookStore.writeFile();
			std::system("pause");
			break;
			
			//delete the given amount of the given book in cart
		}
		case 3:
		{

			//printReciept
			string temp;
			double cost = 0;
			std::cout << "Shopping Cart:" << endl;
			if (cartInfo[0] != -1) {
				cart.printInventory();
			}
			for (int i = 0; i < 25; i++)
			{
				if (cartInfo[i] != -1)
				{
					cost += cart.getBook(cart.searchBookByISBN(cartInfo[i])).getRetailPrice();
				}
			}

			double tax = cost * 0.09;
			std::cout << "\nSubtotal: $" << fixed << setprecision(2) << cost << endl;
			std::cout << "Tax: $" << setprecision(2) << tax << endl;
			std::cout << "Total: $" << setprecision(2) << (cost + tax) << endl;

			std::cout << endl << "Enter anything to go back to menu: ";
			std::system("pause");
			//mode = 'E';
			//run = false;
			BookStore.writeFile();
			break;
		}
		case 4:
		{
			//put everything from cart back into bookstore, and tell user

			for (int i = 0; i < 25; i++) {
				int bookIsbn =cartInfo[i];
				if (bookIsbn != -1)
				{
					for (bool run=true; run != false; )
					{
						//remove books from cart and adding back to store till none left in cart
						cart.removeBook(cart.getBook(cart.searchBookByISBN(bookIsbn)));
						BookStore.addBook(cart.getBook(cart.searchBookByISBN(bookIsbn)));
						if(cart.getBook(cart.searchBookByISBN(bookIsbn)).getQuantity()==0)
						{
							run = false;
						}
						
					}
					//cout << "added book back" << endl;
				}
			}

			for (int i = 0; i < 25; i++) {
				if (cartInfo[i] != -1)
				{
					cart.removeBook(cart.getBook(cart.searchBookByISBN(cartInfo[i])));
					//cout << "removed book from cart" << endl;
				}
			}

			string temp;
			std::cout << "Enter anything to go back to menu: ";
			BookStore.writeFile();
			std::system("pause");
			mode = 'E';
			//run = false;
			break;
		}
		

		}
		std::system("CLS");

	}

}

//we need to check for error cases and need to finish the selection code
void inventoryMode(bool& run, char& mode, Inventory& BookStore)
{
	
	while (mode=='B') {
		std::system("CLS");
		modeDisplay(mode);
		//printInventory();
		//printSelectedBook();

		BookStore.printInventory();
		std::cout << endl;

		int userComand;
		std::cout << "Commands:\n"
			<< "[1]: Select a new book:\n"
			<< "[2]: Add new book:\n"
			<< "[3]: Delete existing book:\n"
			<< "[4]: Edit Existing book:\n"
			<< "[5]: Return to Main Menu: " << endl;
		

		user_navigator(mode, userComand, 5);

		//select mode
		switch (userComand) {
		case 1: 
		{
			int isbn;
			int index;
			std::cout << "Please enter the ISBN# of the book you would like to select: " << endl;
			std::cin >> isbn;
			while (isbn <= 999 || isbn > 9999) {
				std::cout << "Please enter a positive four digit number for the ISBN#: " << endl;
				std::cin >> isbn;
			}
			index = BookStore.searchBookByISBN(isbn);
			if (index == -1) {
				std::cout << "The ISBN# you entered does not match with the ISBN#'s of any of the books in our database." << endl;
			}
			else {
				std::system("CLS");
				BookPile b = BookStore.getBook(index);
				book btemp = static_cast<book>(b);
				std::cout << "The book you have selected is: " << endl << btemp << endl
					<< "Quantity: " << b.getQuantity() << endl
					<< "Author: " << b.getAuthor() << endl
					<< "Publisher: " << b.getPublisher() << endl
					<< "Date Added: " << *b.getDate() << "/" << *(b.getDate() + 1) << "/" << *(b.getDate() + 2) << endl
					<< "Retail Price: $" << b.getRetailPrice() << endl
					<< "Whole Sale Price: $" << b.getWholeSaleCost() << endl;
			}

			std::system("pause");
			break;
		}
		case 2:
		{
			int isbn;
			int month, day, year;
			string title;
			string author;
			string publisher;
			string dateAdded;

			int quantityOnHand;

			double retailPrice;
			double wholeSaleCost;
			//asks user for variables
			std::cout << "Please enter the information when prompted: " << endl;
			std::cout << "ISBN#: " << endl;
			std::cin >> isbn;
			while (isbn < 1000 || isbn > 9999 || BookStore.searchBookByISBN(isbn) != -1) {
				if (BookStore.searchBookByISBN(isbn) != -1) {
					std::cout << "This ISBN# is already in use, please enter a new ISBN#: " << endl;
				}
				else {
					std::cout << "Please enter a positive four digit number for the ISBN#: " << endl;
				}
				std::cin >> isbn;
			}
			std::cin.ignore();
			std::cout << "Title: " << endl;
			std::getline(std::cin, title);
			std::cout << "Author: " << endl;
			std::getline(std::cin, author);
			std::cout << "Publisher: " << endl;
			std::getline(std::cin, publisher);
			std::cout << "Quantity-On-Hand: " << endl;
			std::cin >> quantityOnHand;
			std::cout << "Retail Price: " << endl;
			std::cin >> retailPrice;
			while (retailPrice < 0) {
				std::cout << "Please enter a positive number for the retail price: " << endl;
				std::cin >> retailPrice;
			}
			std::cout << "Wholesale Cost: " << endl;
			std::cin >> wholeSaleCost;
			while (wholeSaleCost < 0) {
				std::cout << "Please enter a positive number for the whole sale cost: " << endl;
				std::cin >> wholeSaleCost;
			}
			std::cout << "Date Added: " << endl;
			std::cout << "Month (number 1 - 12): " << endl;
			std::cin >> month;
			while (month > 12 || month < 1) {
				std::cout << "Enter a number from 1 to 12 for the month: ";
				std::cin >> month;
			}
			std::cout << "Day: " << endl;
			std::cin >> day;
			std::cout << "Year: " << endl;
			std::cin >> year;

			BookPile temp(isbn, title, author, publisher, month, day, year, retailPrice, wholeSaleCost, quantityOnHand);
			BookStore.addBook(temp);
			BookStore.writeFile();
			std::system("pause");
			break;
		}
		case 3:
		{
			int isbn;
			std::cout << "Please enter the ISBN# of the book you would like to delete: " << endl;
			std::cin >> isbn;
			while (isbn <= 999 || isbn > 9999) {
				std::cout << "Please enter a positive four digit number for the ISBN#: " << endl;
				std::cin >> isbn;
			}
			if (BookStore.searchBookByISBN(isbn) == -1) {
				std::cout << "Sorry, book was not found in inventory" << endl;
			}
			else {
				std::cout << isbn << ": " << BookStore.getBook(BookStore.searchBookByISBN(isbn)).getTitle() << " was deleted from the inventory" << endl;
				BookPile empty;
				BookStore.setBook(BookStore.searchBookByISBN(isbn), empty);
			}
			std::system("pause");
			break;
		}
		case 4:
		{
			int isbnTemp;
			int month, day, year;
			std::cout << "Please enter the ISBN# of the book you would like to edit: " << endl;
			std::cin >> isbnTemp;
			while (isbnTemp <= 999 || isbnTemp > 9999 || BookStore.searchBookByISBN(isbnTemp) == -1) {
				if (BookStore.searchBookByISBN(isbnTemp) != -1) {
					std::cout << "Sorry, book was not found in inventory. Please enter a new ISBN#: " << endl;
				}
				else {
					std::cout << "Please enter a positive four digit number for the ISBN#: " << endl;
				}
				std::cin >> isbnTemp;
			}
			

			int isbn;
			string title;
			string author;
			string publisher;
			string dateAdded;

			int quantityOnHand;

			double retailPrice;
			double wholeSaleCost;

			std::cout << "Please enter the information when prompted: " << endl;
			std::cout << "ISBN#: " << endl;
			std::cin >> isbn;
			while (isbn <= 999 || isbn > 9999) {
				std::cout << "Please enter a positive four digit number for the ISBN#: " << endl;
				std::cin >> isbn;
			}
			std::cin.ignore();
			std::cout << "New Title: " << endl;
			std::getline(std::cin, title);
			std::cout << "New Author: " << endl;
			std::getline(std::cin, author);
			std::cout << "New Publisher: " << endl;
			std::getline(std::cin, publisher);
			std::cout << "New Quantity-On-Hand: " << endl;
			std::cin >> quantityOnHand;
			std::cout << "New Retail Price: " << endl;
			std::cin >> retailPrice;
			while (retailPrice < 0) {
				std::cout << "Please enter a positive number for the retail price: " << endl;
				std::cin >> retailPrice;
			}
			std::cout << "New Wholesale Cost: " << endl;
			std::cin >> wholeSaleCost;
			while (wholeSaleCost < 0) {
				std::cout << "Please enter a positive number for the whole sale cost: " << endl;
				std::cin >> wholeSaleCost;
			}
			std::cout << "New Date Added: " << endl;
			std::cout << "New Month (number 1 - 12): " << endl;
			std::cin >> month;
			while (month > 12 || month < 1) {
				std::cout << "Enter a number from 1 to 12 for the month: ";
				std::cin >> month;
			}
			std::cout << "New Day: " << endl;
			std::cin >> day;
			std::cout << "New Year: " << endl;
			std::cin >> year;

			BookStore.setBook(BookStore.searchBookByISBN(isbnTemp), BookPile(isbn, title, author, publisher, month, day, year, retailPrice, wholeSaleCost, quantityOnHand));
			BookStore.writeFile();
			std::system("pause");
			break;
		}
		case 5:
		{
			//run = false;
			mode = 'E';
			break;
		}
		}
		std::system("CLS");
	}
}

//Report mode switch controls sub windows that user enters and leaves.
/*****************************************************************************/
//
// Function: queryReport
//
// Parameters: bool& run, char& mode,Inventory* BookStore, int shelfSize, char& screen
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// displays report screen. calls user_navigator to check for valid input and control navigation useing mode (to move between modes) and usercomand (to move within mode).
// Screen clears and reprints each time user enters a command. Bookstore inventory passed along with other variables linking module to main menu.
//
// submenues:
//   1. print inventory list
//   2. print inventory wholesale value list
//   3. print invetory retail value list
//   4. print list by quantity
//   5. print list by cost
//   6. print list by age
//   7. exits to main menu
//
/*****************************************************************************/
void queryReport(bool& run, char& mode,Inventory* BookStore, int shelfSize, char& screen)
{
	{
		//while on screen 'C' loopps through report commands
		while (screen=='C') {
			int userComand = 0;
			//reportMode(screen, BookStore, shelfSize);
			std::system("CLS");
			modeDisplay(screen);
			reportComandList();
			user_navigator(screen, userComand, 7);

			
			switch (userComand) {
			case 1:
			{
				//print inventory list
				std::system("CLS");
				BookStore->printInventoryReport();
				std::system("pause");
				break;
			}
			case 2:
			{
				//print inventory wholesale value list
				std::system("CLS");
				BookStore->inventoryWholesale();
				std::system("pause");
				break;
			}
			case 3:
			{
				//print invetory retail value list
				std::system("CLS");
				BookStore->inventoryRetail();
				std::system("pause");
				break;
			}
			case 4:
			{
				//print list by quantity
				std::system("CLS");
				BookStore->sortByQuantity();
				std::system("pause");
				break;
			}
			case 5:
			{
				//print list by cost
				std::system("CLS");
				BookStore->sortByWholeSaleCost();
				std::system("pause");
				break;
			}
			case 6:
			{
				//print list by age
				std::system("CLS");
				BookStore->sortByAge();
				std::system("pause");
				break;
			}
			case 7:
			{
				screen = 'E';
				break;
			}
			}
			
		}
	}
}



//User navigation for main menu and report module
/*****************************************************************************/
//
// Function: user_navigator
//
// Parameters: char& screen, int& userComand,int numberOfuserOptions
// (Inputs)    
//
// Outputs:    none
//
// Returns:    bool
//
// Description:
// displays prompt for user comand used to switch between screens and comands within screen.only used in main menu and report screen.
// checks if user input is valid and if so changes screen or user comand value. number of user options value is used to check if valid comand is given
//
/*****************************************************************************/
bool user_navigator(char& screen, int& userComand,int numberOfuserOptions)
{
	char temp = '\0';
	bool validInput = false;
	std::cout << "\t" << "-----------------------------------" << "Input" << "-----------------------------------" << std::endl;
	std::cout << "Reminder: letters move between modes, numbers select options in mode. " << std::endl
		<< "Valid comands: A to D";
		if (numberOfuserOptions != 0)
		{
			std::cout << ", numbers 1 to " << numberOfuserOptions;
		}
		std::cout << std::endl<< "Please enter comand: ";
		std::cin >> temp;
	if (temp == 'A' || temp == 'a')
	{
		screen = 'A';
		validInput = true;
	}
	
	if (temp == 'B' || temp == 'b')
	{
		screen = 'B';
		validInput = true;
	}

	if (temp == 'C' || temp == 'c')
	{
		screen = 'C';
		validInput = true;
	}

	if (temp == 'D' || temp == 'd')
	{
		screen = 'D';
		validInput = true;
	}

	if ((temp - '0') <= numberOfuserOptions&& (temp - '0') >0)
	{
		userComand = temp-'0';
		validInput = true;
	}

	if (validInput == false)
	{
		std::cout << "Error Invalid input: " << std::endl;;
		std::system("pause");
	}
	//for debug
	//cout << "User comand: " << userComand << "  Screen: " << screen <<std::endl;
	
	return validInput;
}