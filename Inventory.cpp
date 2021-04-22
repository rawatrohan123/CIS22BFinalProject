#define _CRT_SECURE_NO_WARNINGS
#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <string>

//CIS 22B
//Rohan Rawat, Brandon Kawula, Noah Gutierrez, Barr Avr
//Team 3


/*UML Diagram:
Inventory:

Class Variables:
- numOfBooks : const int
- books[25] : BookPile

Class Methods:
+ Inventory()
+ printInventory() : void
+ readFile() : void
+ getBook(int) :
+ setBook(int,BookPile) : void
+ addBook(BookPile) : void
+ writeFile() : void 
+ sortBooks() : void
+ searchBooks(BookPile) : int
+ searchBookByISBN(int) : int
+ removeBook(BookPile) : void



*/


Inventory::Inventory() {
	
}

//prints out the Inventory
/*****************************************************************************/
//
// Function: printInventory
//
// Parameters: none
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Prints out ISBN, title, and quantity of all books in inventory  
//
//
//
/*****************************************************************************/

/*Pseudocode:
for(loop through books array){
	if(Title is not empty)
		Print the book
	else
		Print empty book shelf
}

*/
void Inventory::printInventory() {
	for (int i = 0; i < numOfBooks; i++) {
		if(books[i].getTitle() != "Empty"){
			std::cout << books[i] << std::endl;
		}else{
			std::cout << "Empty book slot" << std::endl;
		}
	}
}

//Reads the file of books and stores it in an array.
/*****************************************************************************/
//
// Function: readFile
//
// Parameters: none 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Reads the txt file "books.txt" and stores the information in the inventory array.
//
// 
//
/*****************************************************************************/
/*Pseudocode:
file.open(filename here){
	while(file has more lines){
		Store ISBN, author, publisher, and all other values into Bookpile object
		Add BookPile object into books array
	}
}

getBook(int)

*/
void Inventory::readFile()
{
	int i = 0;
	double d;
	int n;
	std::ifstream file;
	std::string line;
	file.open("books.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> n;
			books[i].setISBN(n);
			//std::cout << n << std::endl;
			file.ignore(111, ' ');
			std::getline(file, line, ',');
			books[i].setTitle(line);
			//std::cout << line << std::endl;
			file.ignore(111, ' ');
			std::getline(file, line, ',');
			books[i].setAuthor(line);
			//std::cout << line << std::endl;
			file.ignore(111, ' ');
			std::getline(file, line, ',');
			books[i].setPublisher(line);
			//std::cout << line << std::endl;
			file.ignore(111, ' ');
			//gets month
			file >> n;
			*(books[i].getDate())=n;
			//std::cout << n << ".";
			file.ignore(111, '.');
			//gets day
			file >> n;
			*(books[i].getDate()+1) = n;
			//std::cout << n <<".";
			file.ignore(111, '.');
			//gets year
			file >> n;
			*(books[i].getDate() + 2) = n;
			file.ignore(111, ',');
			//std::cout << n << std::endl;
			//std::cout << line << std::endl;
			file >> d;
			books[i].setWholeSaleCost(d);
			file >> d;
			books[i].setRetailPrice(d);
			file >> n;
			books[i].setQuantity(n);
			i++;
		}
	}
	else
	{
		std::cout << "File Not found!" <<std::endl;
	}
	file.close();
}


//Returns the BookPile object stored in the index the user enters.
/*****************************************************************************/
//
// Function: getBook
//
// Parameters: int bookNumber 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    BookPile 
//
// Description:
// Returns the BookPile object that is stored in the index the user enters.
//
// 
//
/*****************************************************************************/

/*Pseudocode:
return books[index];

*/
BookPile Inventory::getBook(int bookNumber)
{
	return books[bookNumber];
}

//Setter for books array
/*****************************************************************************/
//
// Function: setBook
//
// Parameters: int booknumber, BookPile book 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Lets the user enter an index of the array and a BookPile objects and stores
// the BookPile object in that index of the array.
//
// 
//
/*****************************************************************************/

/*Pseudocode:
books[bookNumber]=book;
*/
void Inventory::setBook(int bookNumber,BookPile book)
{
	 books[bookNumber]=book;
}


//Adds a book the user enters to the inventory.
/*****************************************************************************/
//
// Function: addBook
//
// Parameters: BookPile b 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Checks to see if the book is available in the inventory. If it is, then adds one
// to the quantity of that book. If not, it will add the book to inventory. If the
// inventory is full, it will print a message saying there is no more space in 
// the inventory.
//
// 
//
/*****************************************************************************/

/*Pseudocode:
for(loop through array){
	if(isbn of b is equal to isbn of a book in array){
		Then add one to the quantity of that BookPile object
	}
}
if(b is not in books array){
	if(check when books has an empty slot){
		Stores the BookPile object in empty slot
	}
}
if(no space in inventory){
	Print message no space
}

*/
void Inventory::addBook(BookPile b) {
	bool inInventory = false;
	bool noSpace = true;
	for (int i = 0; i < numOfBooks; i++) {
		if (books[i].getISBN() == b.getISBN()) {
			books[i].setQuantity(books[i].getQuantity() + 1);
			inInventory = true;
			noSpace = false;
		}
	}
	if (!inInventory) {
		for (int i = 0; i < numOfBooks; i++) {
			if (books[i].getISBN() == 0) {
				books[i] = b;
				noSpace = false;
				break;
			}
		}
	}
	if (noSpace) {
		std::cout << "No more space in Inventory!" << std::endl;
	}
}

//Stores the books in the Inventory object in a txt file.
/*****************************************************************************/
//
// Function: writeFile
//
// Parameters: none 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Stores the books in the Inventory object in the "output.txt" file. 
//
// 
//
/*****************************************************************************/

/*Pseudocode:

for(Loop through book array){
	if(isbn is not 0){
		Store each of the individual values such as isbn, author, title in the file
	}
}

*/
void Inventory::writeFile() {
	bool firstBook = true;
	std::ofstream file;
	file.open("books.txt");
	for (int i = 0; i < numOfBooks; i++) {
		if (books[i].getISBN() != 0) {
			if (!firstBook) {
				file << std::endl;
			}
			file << books[i].getISBN() << " " << books[i].getTitle() << ", " << books[i].getAuthor() << ", " << books[i].getPublisher()
				<< ", " << *(books[i].getDate()) << "." << *(books[i].getDate()+1)<< "." << *(books[i].getDate()+2) <<", " << books[i].getWholeSaleCost() << " " << books[i].getRetailPrice()
				<< " " << books[i].getQuantity();
			firstBook = false;
		}
	}
	file.close();

}

//Sorts the books in the array.
/*****************************************************************************/
//
// Function: sortBooks()
//
// Parameters: none 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Uses a for loop to loop through the books array and sorts the books array
// in alphabetical order.
//
// 
//
/*****************************************************************************/

/*Pseudocode:
for(loop through array){
	for(){
		Check to see which book is greater in terms of alphabetical order and swap
	}

}

*/
void Inventory::sortBooks() {
	BookPile temp;
	for (int j = 0; j < numOfBooks; j++) {
		for (int i = 1; i < numOfBooks; i++) {
			if (books[i].getTitle() > books[i - 1].getTitle()) {
				temp = books[i];
				books[i] = books[i - 1];
				books[i - 1] = temp;
			}
		}
	}
	
}

//Searches the books array
/*****************************************************************************/
//
// Function: searchBooks
//
// Parameters: BookPile b 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    int
//
// Description:
// Searches the books array. If an isbn number matches the users BookPile objects 
// isbn number then it returns the index of where that BookPile object is located 
// in the array. If there is no match in the array it will return -1.
// 
//
/*****************************************************************************/

/*Pseudocode:
for(loop through book array){
	if(ISBN matches){
		return index of book
	}
}

*/
int Inventory::searchBooks(BookPile b) {
	for (int i = 0; i < numOfBooks; i++) {
		if (books[i].getISBN() == b.getISBN()) {
			return i;		//book found
		}
	}
	return -1;		//no book found
}

//Searches the books array
/*****************************************************************************/
//
// Function: searchBookByISBN
//
// Parameters: int isbn 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    int
//
// Description:
// Searches the books array while taking the isbn as a parameter. If the isbn 
// number matches one of the BookPile objects isbn numbers in the book array,
// it will return the index of that BookPile object. If no match is found, 
// this function will return -1.
// 
//
/*****************************************************************************/

/*Pseudocode:
for(loop through array){
	if(ISBN matches){
		Return index ofbooks array
	}
}

*/
int Inventory::searchBookByISBN(int isbn) {
	for (int i = 0; i < numOfBooks; i++) {
		if (books[i].getISBN() == isbn) {
			return i;		//book found
		}
	}
	return -1;		//no book found
}

//Removes a BookPile object in the book array
/*****************************************************************************/
//
// Function: removeBook
//
// Parameters: BookPile b 
// (Inputs)    
//
// Outputs:    none
//
// Returns:    void
//
// Description:
// Removes the BookPile object b that the user enters in the function paramter.
// If the quantity of a book is 0, an empty BookPile object will be stored in
// place of the book.
// 
//
/*****************************************************************************/

/*Pseudocode:
for(loop through books array){
	if(quantity of books is not 0){
		quantity--
	}
	else{
		Store empty book in that part of array
	}
}


*/
void Inventory::removeBook(BookPile b) {
	for (int i = 0; i < numOfBooks; i++) {
		if (books[i].getISBN() == b.getISBN()) {
			if (books[i].getQuantity() != 0) {
				books[i].setQuantity(books[i].getQuantity() - 1);
			}
			else {
				BookPile c;
				books[i] = c;
			}
		}
	}
}

