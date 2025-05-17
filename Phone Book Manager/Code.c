#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Required for qsort
#include <ctype.h>  // Required for isdigit
#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 20 // Buffer size for phone number input
#define MAX_PHONE_DIGITS 10 // Maximum allowed digits for a phone number
#define COUNTRY_COUNT 8 // Defining Country codes

const char *countries[COUNTRY_COUNT] = {
    "India", "United States", "Canada", "UK", "China", "Italy", "France", "Mexico"
};

const char *countryCodes[COUNTRY_COUNT] = {
    "+91", "+1", "+1", "+44", "+86", "+39", "+33", "+52"
};

// Structure to represent a contact
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH]; // Can store up to MAX_PHONE_LENGTH-1 chars + null
} Contact;

// Array to store contacts
Contact contacts[MAX_CONTACTS];
int contactCount = 0;

// Helper function to validate phone number
int isValidPhoneNumber(const char *phoneStr) {
    int len = strlen(phoneStr);
    if (len == 0 || len > MAX_PHONE_DIGITS || len < 10) { // Check if empty or too long
        if (len > MAX_PHONE_DIGITS)
             printf("Error: Phone number cannot exceed %d digits.\n", MAX_PHONE_DIGITS);
        else if(len < 10)
            printf("Invalid Contact.\n");
        else
             printf("Error: Phone number cannot be empty.\n");
        
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit(phoneStr[i])) {
            printf("Error: Phone number must contain only digits.\n");
            return 0;
        }
    }
    return 1;
}

// Function to add a new contact
void addContact() {
    if (contactCount < MAX_CONTACTS) {
        printf("Enter name: ");
        fgets(contacts[contactCount].name, MAX_NAME_LENGTH, stdin);
        contacts[contactCount].name[strcspn(contacts[contactCount].name, "\n")] = 0;

        // --- Country selection ---
        int countryChoice = -1;
        printf("Select a country:\n");
        for (int i = 0; i < COUNTRY_COUNT; i++) 
            printf("%d. %s\n", i + 1, countries[i]);

        while (1) {
            printf("Enter country number (1-%d): ", COUNTRY_COUNT);
            if (scanf("%d", &countryChoice) != 1 || countryChoice < 1 || countryChoice > COUNTRY_COUNT) {
                printf("Invalid choice. Please try again.\n");
                while (getchar() != '\n'); // Clear invalid input
            } else {
                getchar(); // Consume newline after number input
                break;
            }
        }

        // --- Phone number input and validation ---
        char tempPhone[MAX_PHONE_LENGTH];
        while (1) {
            printf("Enter phone number (up to %d digits): ", MAX_PHONE_DIGITS);
            fgets(tempPhone, MAX_PHONE_LENGTH, stdin);
            tempPhone[strcspn(tempPhone, "\n")] = 0; // Remove newline character

            if (isValidPhoneNumber(tempPhone)) {
                snprintf(contacts[contactCount].phone, MAX_PHONE_LENGTH, "%s%s", countryCodes[countryChoice - 1], tempPhone);
                break;
            } else 
                printf("Please try again.\n");   
        }
        contactCount++;
        printf("Contact added successfully!\n");
    } else 
        printf("Phone book is full. Cannot add more contacts.\n");
}

// Function to delete a contact
void deleteContact() {
    if (contactCount == 0) {
        printf("Phone book is empty. Nothing to delete.\n");
        return;
    }
    char name[MAX_NAME_LENGTH];
    printf("Enter name of contact to delete: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    int found = -1;
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        for (int j = found; j < contactCount - 1; j++) {
            contacts[j] = contacts[j + 1];
        }
        contactCount--;
        printf("Contact deleted successfully!\n");
    } else
        printf("Contact not found.\n");
}

// Function to edit a contact
void editContact() {
    if (contactCount == 0) {
        printf("Phone book is empty. Nothing to edit.\n");
        return;
    }
    char name[MAX_NAME_LENGTH];
    printf("Enter name of contact to edit: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    int found = -1;
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        printf("Editing contact: %s\n", contacts[found].name);
        printf("Enter new name (or press Enter to keep '%s'): ", contacts[found].name);
        char newName[MAX_NAME_LENGTH];
        fgets(newName, MAX_NAME_LENGTH, stdin);
        newName[strcspn(newName, "\n")] = 0;
        if (strlen(newName) > 0) 
            strcpy(contacts[found].name, newName);

        char tempPhone[MAX_PHONE_LENGTH];
        while (1) {
            printf("Enter new phone number (up to %d digits, or press Enter to keep '%s'): ", MAX_PHONE_DIGITS, contacts[found].phone);
            fgets(tempPhone, MAX_PHONE_LENGTH, stdin);
            tempPhone[strcspn(tempPhone, "\n")] = 0;
            if (strlen(tempPhone) == 0) // User pressed Enter, keep old number
                break;
            if (isValidPhoneNumber(tempPhone)){
                strcpy(contacts[found].phone, tempPhone);
                break;
            }
            else
                printf("Please try again.\n");
        }
        printf("Contact edited successfully!\n");
    } else
        printf("Contact not found.\n");
}

// Comparison function for qsort (sorts by name)
int compareContacts(const void *a, const void *b) {
    Contact *contactA = (Contact *)a;
    Contact *contactB = (Contact *)b;
    return strcmp(contactA->name, contactB->name);
}

// Function to view all contacts
void viewContacts() {
    if (contactCount == 0)
        printf("No contacts in phone book.\n");
    else {
        // Create a temporary array to sort for viewing, or sort in place
        // Sorting in place:
        qsort(contacts, contactCount, sizeof(Contact), compareContacts);
        printf("\n--- Contacts (Sorted by Name) ---\n");
        for (int i = 0; i < contactCount; i++) {
            // Assuming all country codes are 3 characters (like +91, +44, etc.)
            if (strlen(contacts[i].phone) > 3)
                printf("Name: %s, Phone: %.3s %s\n", contacts[i].name, contacts[i].phone, contacts[i].phone + 3);
            else 
                // Fallback in case phone format is unexpected
                printf("Name: %s, Phone: %s\n", contacts[i].name, contacts[i].phone);
        }
        printf("---------------------------------\n");
    }
}

// Function to search for a contact
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) 
        str[i] = tolower(str[i]);
}

void searchContact() {
    if (contactCount == 0) {
        printf("Phone book is empty. Nothing to search.\n");
        return;
    }
    
    char name[MAX_NAME_LENGTH];
    printf("Enter name of contact to search: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;

    // Convert search query to lowercase
    char lowerName[MAX_NAME_LENGTH];
    strcpy(lowerName, name);
    toLowerCase(lowerName);

    int foundCount = 0;
    // To ensure search works even if viewContacts hasn't been called recently,
    // it's better to search the unsorted list or re-sort before a specific search if needed.
    // For simple name search, sorting isn't strictly necessary here, but if you want to list
    // multiple matches in sorted order, you might sort a temporary list of matches.
    // The current implementation searches the potentially sorted (if viewContacts was called) list.
    printf("\n--- Search Results ---\n");
    for (int i = 0; i < contactCount; i++) {
         // Using strstr for partial match, or strcmp for exact match
        char contactNameLower[MAX_NAME_LENGTH];
        strcpy(contactNameLower, contacts[i].name);
        toLowerCase(contactNameLower);

        if (strstr(contactNameLower, lowerName) != NULL) {
            printf("Name: %s, Phone: %.3s %s\n", contacts[i].name, contacts[i].phone, contacts[i].phone + 3);
            foundCount++;
        } 
    }

    if (foundCount == 0)
        printf("Contact not found.\n");
    printf("----------------------\n");
}

int main() {
    int choice;
    while (1) {
        printf("\nPhone Book Application\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Edit Contact\n");
        printf("4. View Contacts (Sorted)\n");
        printf("5. Search Contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }
        getchar(); // Consume the newline character left by scanf
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                deleteContact();
                break;
            case 3:
                editContact();
                break;
            case 4:
                viewContacts();
                break;
            case 5:
                searchContact();
                break;
            case 6:
                printf("Exiting phone book application.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}