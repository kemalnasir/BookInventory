//MINI PROJECT BITP 1113 SEM 1: PROGRAMMING TECHNIQUE
//GROUP NAME: DE RYZEN FORCE
//GROUP TITLE: RYZEN BOOK INVENTORY MANAGEMENT SYSTEM
//GROUP MEMBER 1: MUHAMMAD AKMAL BIN MOHD NASIR (B032220038)
//GROUP MEMBER 2: MUHAMMAD SYAKIR AIMAN BIN NORISHAMUDDIN (B032220057)
//GROUP MEMBER 3: MUHAMMAD MUAZ BIN NORDIN (B032220042)

// Preprocessor Directive
#include <iostream>
#include <iomanip>
#include <fstream>  // Added for file handling
#include <string>

using namespace std;

// Struct to represent a book
struct Book {
    string title;
    string author;
    int quantity;
    double price;
};

// Function to read books from an input file
void readBooksFromFile(Book*& books, int& bookCount, const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile) {
        cout << "Error opening input file: " << filename << endl;
        return;
    }

    while (inputFile >> books[bookCount].title >> books[bookCount].author >>
        books[bookCount].quantity >> books[bookCount].price) {
        bookCount++;
    }

    inputFile.close();
}

// Function to write books to an output file
void writeBooksToFile(const Book* books, int bookCount, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile) {
        cout << "Error opening output file: " << filename << endl;
        return;
    }

    for (int i = 0; i < bookCount; ++i) {
        outputFile << books[i].title << " " << books[i].author << " "
            << books[i].quantity << " " << books[i].price << endl;
    }

    outputFile.close();
}

// Function prototypes
// Declare Function displayMenu
void displayMenu() {
    cout << "" << endl;
    cout << "\nPlease Enter Your Selection:\n";
    cout << "1. Add a Book\n";
    cout << "2. Search for a Book\n";
    cout << "3. Update Book Quantity\n";
    cout << "4. Delete a Book\n";
    cout << "5. Generate Report Total Inventory\n";
    cout << "6. Exit\n";
    cout << "\n===================================================\n";
}

// Declare Function addBook
void addBook(Book*& books, int& bookCount);

//  Declare Function searchBook
void searchBook(const Book* books, int bookCount)
{
    string searchTitle;
    cout << "Enter the title of the book to search: ";
    cin.ignore();  // Clear the buffer
    getline(cin, searchTitle);

    bool found = false;

    for (int i = 0; i < bookCount; ++i) {
        if (books[i].title == searchTitle) {
            cout << "\n *Book Found*:\n";
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Quantity: " << books[i].quantity << endl;
            cout << "Price per Unit: Rm " << fixed << setprecision(2) << books[i].price << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Sorry, Book not found from your search. Please input valid title books ! \n";
    }
}

//  Declare Function updateBookQuantity
void updateBookQuantity(Book* books, int bookCount)
{
    string updateTitle;
    cout << "Enter the title of the book to update quantity: ";
    cin.ignore();  // Clear the buffer
    getline(cin, updateTitle);

    for (int i = 0; i < bookCount; ++i) {
        if (books[i].title == updateTitle) {
            cout << "Enter the new quantity for book " << books[i].title << ": ";
            cin >> books[i].quantity;
            cout << "Quantity updated successfully!\n";
            return;
        }
    }

    cout << "Book not found. Quantity not updated.\n";
}

//  Declare Function deleteBook
void deleteBook(Book*& books, int& bookCount)
{
    string deleteTitle;
    cout << "Enter the title of the book to delete: ";
    cin.ignore();  // Clear the buffer
    getline(cin, deleteTitle);

    for (int i = 0; i < bookCount; ++i) {
        if (books[i].title == deleteTitle) {
            // Shift the remaining books to fill the gap
            for (int j = i; j < bookCount - 1; ++j) {
                books[j] = books[j + 1];
            }
            bookCount--;
            cout << "Book deleted successfully!\n";
            return;
        }
    }
    cout << "Book not found. Deletion failed.\n";
}

//  Declare Function inventoryreport
void inventoryreport(const Book* books, int bookCount)
{
    double total = 0.0;

    cout << "\nTotal Inventory Stock\n";
    cout << "\n============================================================================================================\n";
    cout << setw(20) << "Title" << setw(10) << "\t\t ""Author" << setw(10) << "\t\tQuantity" << setw(10) << "\tprice" << setw(15) << "\tTotal\n";
    cout << "\n*************************************************************************************************************\n";
    for (int i = 0; i < bookCount; ++i) {
        double bookTotal = books[i].quantity * books[i].price;
        total += bookTotal;

        cout << setw(20) << books[i].title << setw(20) << books[i].author << setw(10) << books[i].quantity << setw(10) << " " << "  Rm " << fixed << setprecision(2) << books[i].price << setw(15) << "Rm " << bookTotal << endl;
    }

    cout << "\nTotal Amount Inventory: Rm" << fixed << setprecision(2) << total << endl;
}

// Main Function
int main() {
    char userName[20];
    cout << "Please enter your name: ";
    cin.getline(userName, sizeof(userName));  // Using cin.getline to avoid buffer overflow

    cout << "Hello, welcome back " << userName << " ! We're glad you're here." << endl;

    const int MAX_BOOKS = 100;
    Book* books = new Book[MAX_BOOKS];
    int bookCount = 0;

    int choice;
    char continueChoice;
    const string inputFile = "books_input.txt";
    const string outputFile = "books_output.txt";


    cout << "\n***************************************************\n";
    cout << "\tRyzen Book Inventory Management System\n";
    cout << "***************************************************\n";

    // Read initial books from input file
    readBooksFromFile(books, bookCount, inputFile);

    do {
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addBook(books, bookCount);
                break;
            case 2:
                searchBook(books, bookCount);
                break;
            case 3:
                updateBookQuantity(books, bookCount);
                break;
            case 4:
                deleteBook(books, bookCount);
                break;
            case 5:
                inventoryreport(books, bookCount);
                break;
            case 6:
                break; // Do nothing for choice 6
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);

        // Write final books to output file before exiting
        writeBooksToFile(books, bookCount, outputFile);

        cout << "Do you want to continue using the system? (Y/N): ";
        cin >> continueChoice;

    } while (continueChoice == 'Y' || continueChoice == 'y');

    // Free the allocated memory
    delete[] books;

    cout << "Exiting the program. Thank you for using the system!\n";

    return 0;
}

// Function to add a book to the inventory
void addBook(Book*& books, int& bookCount) {
    if (bookCount < 100) {
        cout << "Enter book title: ";
        cin.ignore();  // Clear the buffer
        getline(cin, books[bookCount].title);

        cout << "Enter author name: ";
        getline(cin, books[bookCount].author);

        cout << "Enter quantity: ";
        cin >> books[bookCount].quantity;

        cout << "Enter price per Unit: Rm ";
        cin >> books[bookCount].price;

        bookCount++;
        cout << "Book added successfully!\n";
    }
    else {
        cout << "Maximum book limit reached!\n";
    }
}

// Call Function to search for a book by title
void searchBook(const Book* books, int bookCount);

// Call Function to update book quantity
void updateBookQuantity(Book* books, int bookCount);

// Function to delete a book
void deleteBook(Book*& books, int& bookCount);

// Function to generate total report
void inventoryreport(const Book* books, int bookCount);
