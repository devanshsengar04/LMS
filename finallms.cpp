#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    int edition;
    bool isAvailable;
    string issuedTo;
};

vector<Book> bookArray;
list<Book> bookList;
stack<int> issueStack;
queue<int> returnQueue;

void loadData() {
    ifstream file("library.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string val;
            Book book;
            getline(ss, val, ',');
            book.id = stoi(val);
            getline(ss, val, ',');
            book.title = val;
            getline(ss, val, ',');
            book.author = val;
            getline(ss, val, ',');
            book.edition = stoi(val);
            getline(ss, val, ',');
            book.isAvailable = (val == "1");
            if (!book.isAvailable) {
                getline(ss, val, ',');
                book.issuedTo = val;
            }
            bookArray.push_back(book);
            bookList.push_back(book);
        }
        file.close();
    }
}

void saveData() {
    ofstream file("library.txt");
    if (file.is_open()) {
        for (const auto& book : bookArray) {
            file << book.id << "," << book.title << "," << book.author << "," << book.edition << ",";
            file << (book.isAvailable ? "1" : "0") << ",";
            if (!book.isAvailable) {
                file << book.issuedTo;
            }
            file << "\n";
        }
        file.close();
    }
}

void addBook() {
    Book newBook;
    cout << "Enter book ID: ";
    cin >> newBook.id;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    cout << "Enter book edition: ";
    cin >> newBook.edition;
    newBook.isAvailable = true;
    bookArray.push_back(newBook);
    bookList.push_back(newBook);
    cout << "Book added successfully!" << endl;
    saveData();
}

void searchBook() {
    string searchQuery;
    cout << "Enter book title or ID to search: ";
    cin.ignore();
    getline(cin, searchQuery);

    bool found = false;
    for (Book book : bookArray) {
        if (book.title == searchQuery || to_string(book.id) == searchQuery) {
            cout << "Book found!" << endl;
            cout << "ID: " << book.id << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Edition: " << book.edition << endl;
            cout << "Status: " << (book.isAvailable ? "Available" : "Issued") << endl;
            if (!book.isAvailable) {
                cout << "Issued to: " << book.issuedTo << endl;
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Book not found!" << endl;
    }
}

void issueBook() {
    int bookID;
    cout << "Enter book ID to issue: ";
    cin >> bookID;

    for (Book &book : bookArray) {
        if (book.id == bookID && book.isAvailable) {
            cout << "Book details:" << endl;
            cout << "ID: " << book.id << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Edition: " << book.edition << endl;
            cout << "Enter student name to issue the book to: ";
            cin.ignore();
            getline(cin, book.issuedTo);
            book.isAvailable = false;
            cout << "Book issued successfully!" << endl;
            saveData();
            return;
        }
    }
    cout << "Book not found or already issued!" << endl;
}

void returnBook() {
    int bookID;
    cout << "Enter book ID to return: ";
    cin >> bookID;

    for (Book &book : bookArray) {
        if (book.id == bookID && !book.isAvailable) {
            book.isAvailable = true;
            book.issuedTo = "";
            cout << "Book returned successfully!" << endl;
            saveData();
            return;
        }
    }
    cout << "Book not found or not issued!" << endl;
}
void listBooks() {
    if (bookArray.empty()) {
        cout << "No books in the library!" << endl;
        return;
    }

    cout << setw(15) << left << "ID" << setw(1) << setfill(' ') << " " << setw(30) << left << "TITLE" << setw(1) << setfill(' ') << " " << setw(20) << left << "AUTHOR" << setw(1) << setfill(' ') << " " << setw(20) << left << "EDITION" << setw(1) << setfill(' ') << " " << setw(20) << left << "STATUS" << setw(1) << setfill(' ') << " " << setw(10) << left << "ISSUED_TO" << endl;

    for (const Book &book : bookArray) {
        cout << setw(15) << left << book.id << setw(1) << setfill(' ') << " " << setw(30) << left << book.title << setw(1) << setfill(' ') << " " << setw(20) << left << book.author << setw(1) << setfill(' ') << " " << setw(20) << left << book.edition << setw(1) << setfill(' ') << " " << setw(20) << left << (book.isAvailable ? "Available" : "Issued") << setw(1) << setfill(' ') << " " << setw(10) << left << book.issuedTo << endl;
    }
}

void deleteBook() {
    int bookID;
    cout << "Enter book ID to delete: ";
    cin >> bookID;

    for (auto it = bookArray.begin(); it != bookArray.end(); ++it) {
        if (it->id == bookID) {
            bookArray.erase(it);
            cout << "Book deleted successfully!" << endl;
            saveData();
            return;
        }
    }
    cout << "Book not found!" << endl;
}

int main() {
    cout << "*******************************************" << endl;
    cout << "*                                         *" << endl;
    cout << "*      WELCOME TO THE LIBRARY SYSTEM      *" << endl;
    cout << "*                                         *" << endl;
    cout << "*******************************************" << endl;

    loadData();

    int choice;
    while (true) {
        cout << endl << endl << endl << endl;

        cout << "MENU" << endl << endl;
        cout << "1. Add a new book" << endl;
        cout << "2. Search for a book" << endl;
        cout << "3. Issue a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. List all books" << endl;
        cout << "6. Delete a book" << endl;
        cout << "7. Exit" << endl;
        cout << " \n \n Enter your choice: ";
        cin >> choice;
        cout << " \n \n ";
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                issueBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                listBooks();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                cout << "THANKS FOR USING THE LIBRARY MANAGEMENT SYSTEM" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
