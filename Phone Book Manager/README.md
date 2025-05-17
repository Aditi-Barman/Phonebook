
---

# 📱 Phone Book Manager in C

**Group 11**

A command-line based Phone Book Manager written in C. This application enables users to manage contacts by adding, editing, deleting, searching, and viewing them in a sorted list. It uses in-memory data storage with simple input validation.

---

## 👥 Team Members

| Name               | Roll Number  |
| ------------------ | ------------ |
| Aditi Barman       | 241001001182 |
| Sanjana Mahata     | 241001001274 |
| Krish Ranjan       | 241001001212 |
| Vaibhav Jha        | 241001001234 |
| Pushpesh Kant Ojha | 241001001233 |

---

## 📦 How to Clone the Project

To get a local copy of the project, run the following command in your terminal:

```bash
git clone https://github.com/Aditi-Barman/Phonebook.git
cd Phone-Book-Manager
```

---

## 📂 Project Structure

* `phonebook.c` – Main C source file
* `README.md` – Project documentation

---
## 🚀 Features

- ➕ Add contacts with country-specific phone code
- 🗑️ Delete contacts by name
- ✏️ Edit existing contacts (name and/or phone number)
- 🔍 Search contacts (supports partial, case-insensitive matches)
- 📋 View all contacts sorted by name (alphabetically)
- 🌍 Country code support (India, US, Canada, UK, etc.)
- 🔢 Validates phone number length and digits

---

## 📦 Technologies Used

- Language: **C**
- Interface: **Command-Line Interface (CLI)**
- No external libraries used beyond standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`)

---

## 🔧 Data Structures Used

```c
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Contact;
```

* Uses a global array of `Contact` structures
* Contact name: up to 49 characters
* Phone number: up to 10 digits

---

## 🧪 Sample Interaction

```text
Phone Book Application
1. Add Contact
2. Delete Contact
3. Edit Contact
4. View Contacts (Sorted)
5. Search Contact
6. Exit
Enter your choice: 1
Enter name: Aditi
Enter phone number (up to 10 digits): 9876543210
Contact added successfully!
```

---

## 🛠️ Compilation & Execution

### Compile:

```bash
gcc phonebook.c -o phonebook
```

### Run:

```bash
./phonebook
```

---

## 🔐 Input Validation

* Phone numbers must:

  * Contain only digits (`0-9`)
  * Be no longer than 10 digits
* Names can contain any characters but are case-sensitive during search/edit/delete

---

## 🚀 Possible Enhancements

* File-based data persistence
* Case-insensitive search
* Contact grouping or categorization
* GUI version using libraries like GTK

---

## 📄 License

This project is provided for educational purposes.

---