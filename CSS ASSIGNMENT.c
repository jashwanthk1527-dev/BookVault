#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define FILE_NAME "library_data.dat"

// Book Structure
typedef struct {
    int id;
    char title[100];
    char author[50];
    int isIssued; // 0 means available, 1 means issued
} Book;

// Global Variables
Book library[MAX_BOOKS];
int bookCount = 0;

// Function Prototypes
void loadBooks();
void saveBooks();
void addBook();
void displayBooks();
void searchBook();
void issueBook();
void returnBook();
void clearBuffer();

int main() {
    int choice;
    
    // Load existing data from file when program starts
    loadBooks();

    do {
        printf("\n========================================\n");
        printf("       LIBRARY MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Add a New Book\n");
        printf("2. Display All Books\n");
        printf("3. Search for a Book (by ID)\n");
        printf("4. Issue a Book\n");
        printf("5. Return a Book\n");
        printf("6. Save & Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer(); // Clear newline character left by scanf

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: 
                saveBooks();
                printf("Data saved successfully. Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please select between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}

// Helper function to clear input buffer to prevent scanf/fgets skipping
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to load books from file
void loadBooks() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file != NULL) {
        fread(&bookCount, sizeof(int), 1, file);
        fread(library, sizeof(Book), bookCount, file);
        fclose(file);
    }
}

// Function to save books to file
void saveBooks() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file != NULL) {
        fwrite(&bookCount, sizeof(int), 1, file);
        fwrite(library, sizeof(Book), bookCount, file);
        fclose(file);
    } else {
        printf("Error: Could not save data to file!\n");
    }
}

// Function to add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("\nLibrary is full! Cannot add more books.\n");
        return;
    }

    Book newBook;
    printf("\nEnter Book ID: ");
    scanf("%d", &newBook.id);
    clearBuffer();

    // Check if ID already exists
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == newBook.id) {
            printf("Error: Book with ID %d already exists!\n", newBook.id);
            return;
        }
    }

    printf("Enter Book Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Remove trailing newline

    printf("Enter Author Name: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;

    newBook.isIssued = 0; // Default to available

    library[bookCount] = newBook;
    bookCount++;

    printf("\nBook '%s' added successfully!\n", newBook.title);
}

// Function to display all books
void displayBooks() {
    if (bookCount == 0) {
        printf("\nThe library is currently empty.\n");
        return;
    }

    printf("\n%-10s %-40s %-25s %-15s\n", "Book ID", "Title", "Author", "Status");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%-10d %-40s %-25s %-15s\n", 
            library[i].id, 
            library[i].title, 
            library[i].author, 
            library[i].isIssued ? "Issued" : "Available");
    }
}

// Function to search for a book by ID
void searchBook() {
    int searchId;
    int found = 0;
    
    printf("\nEnter Book ID to search: ");
    scanf("%d", &searchId);
    clearBuffer();

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == searchId) {
            printf("\n--- Book Found ---\n");
            printf("ID: %d\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Status: %s\n", library[i].isIssued ? "Issued" : "Available");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nBook with ID %d not found.\n", searchId);
    }
}

// Function to issue a book
void issueBook() {
    int issueId;
    int found = 0;

    printf("\nEnter Book ID to issue: ");
    scanf("%d", &issueId);
    clearBuffer();

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == issueId) {
            found = 1;
            if (library[i].isIssued == 1) {
                printf("\nSorry, '%s' is already issued to someone else.\n", library[i].title);
            } else {
                library[i].isIssued = 1;
                printf("\nSuccess! '%s' has been issued.\n", library[i].title);
            }
            break;
        }
    }

    if (!found) {
        printf("\nBook with ID %d not found.\n", issueId);
    }
}

// Function to return a book
void returnBook() {
    int returnId;
    int found = 0;

    printf("\nEnter Book ID to return: ");
    scanf("%d", &returnId);
    clearBuffer();

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == returnId) {
            found = 1;
            if (library[i].isIssued == 0) {
                printf("\nError: '%s' was not issued.\n", library[i].title);
            } else {
                library[i].isIssued = 0;
                printf("\nSuccess! '%s' has been returned to the library.\n", library[i].title);
            }
            break;
        }
    }

    if (!found) {
        printf("\nBook with ID %d not found.\n", returnId);
    }
}