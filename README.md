# C++ Synonym Dictionary

A console-based synonym dictionary developed as a mini-project for the **Advanced Programming** course at **Kharazmi University**.

The project implements a dictionary using a manually managed **singly linked list** in C++. It supports adding, removing, searching, editing, and persisting dictionary entries using text files.

## Features

* Add a word with a synonym
* Add multiple synonyms to an existing word
* Prevent duplicate words and duplicate synonyms
* Remove a word and all of its synonyms
* Remove a specific synonym
* Search for a word
* Display all dictionary entries
* Change an existing word while preserving alphabetical order
* Save dictionary data to a text file
* Load dictionary data from a text file
* Alphabetically ordered linked-list storage
* Manual dynamic memory management
* Basic input validation

## Concepts Demonstrated

This project focuses on fundamental C++ programming and data structure concepts:

* Structs
* Pointers
* Singly linked lists
* Dynamic memory allocation
* `new` and `delete`
* References
* Function decomposition
* String manipulation
* File I/O
* Searching
* Ordered insertion
* Memory management
* Console-based menu systems

## Project Structure

```text
cpp-synonym-dictionary/
├── main.cpp
├── README.md
├── .gitignore
└── LICENSE
```

## Data Structure

Each dictionary entry is represented by a node in a singly linked list:

```cpp
struct WordNode {
    string word;
    string synonym;
    WordNode* next;

    WordNode(const string& w, const string& s)
        : word(w), synonym(s), next(nullptr) {}
};
```

The linked list is maintained in **alphabetical order** based on the stored word.

Each node contains:

* `word` — the dictionary word
* `synonym` — one or more synonyms stored as a string
* `next` — pointer to the next dictionary entry

## Available Operations

The application provides the following menu:

```text
===== Dictionary Menu =====
1. Add a word with its synonym
2. Remove a word and its synonyms
3. Remove a synonym from a word
4. Search for a word
5. Display all words and synonyms
6. Change a word
7. Save dictionary to file
8. Load dictionary from file
9. Exit
===========================
```

### Add Word

Adds a new word and synonym to the dictionary.

If the word already exists, the new synonym is added to the existing entry instead of creating a duplicate node.

### Remove Word

Removes the selected word and all of its associated synonyms from the linked list.

### Remove Synonym

Removes a specific synonym from a word.

If the word contains only one synonym, removing that synonym also removes the word from the dictionary.

### Search

Searches the linked list for an exact word and displays its synonyms.

### Change Word

Changes an existing word while preserving its synonyms.

The updated word is reinserted into the linked list so that the dictionary remains alphabetically ordered.

### Save and Load

The dictionary can be saved to and loaded from a text file.

Each entry is stored using two lines:

```text
word
synonym
```

For example:

```text
happy
joyful, cheerful
```

## Build and Run

### Requirements

* C++ compiler with C++17 support
* `g++`, `clang++`, or another compatible compiler

### Compile

Using `g++`:

```bash
g++ -std=c++17 main.cpp -o dictionary
```

### Run

On macOS/Linux:

```bash
./dictionary
```

On Windows:

```bash
dictionary.exe
```

## Example

```text
===== Dictionary Menu =====
1. Add a word with its synonym
2. Remove a word and its synonyms
3. Remove a synonym from a word
4. Search for a word
5. Display all words and synonyms
6. Change a word
7. Save dictionary to file
8. Load dictionary from file
9. Exit
===========================
Enter your choice: 1

Enter word: happy
Enter its synonym: joyful

Word added successfully!
```

Adding another synonym:

```text
Enter your choice: 1

Enter word: happy
Enter its synonym: cheerful

Synonym added successfully.
```

Searching:

```text
Enter your choice: 4

Enter word to search: happy

Word: happy
Synonyms: joyful, cheerful
```

## Memory Management

The project intentionally uses manual memory management to demonstrate dynamic allocation and linked-list manipulation.

Nodes are created using:

```cpp
new WordNode(...)
```

and properly released using:

```cpp
delete current;
```

The entire dictionary is released before the program exits through the `deleteDictionary()` function.

## Limitations

This project is designed as an educational mini-project and intentionally uses a simple data model.

Current limitations include:

* Synonyms are stored as a single string rather than a separate data structure.
* Input is primarily designed for single-word entries.
* The application is console-based.
* Dictionary data is stored in a simple text format.
* Search is based on exact word matching.
* The project does not currently include automated tests.

## Possible Improvements

Future versions could include:

* Storing synonyms using `std::vector` or a dedicated linked list
* Case-insensitive search
* Support for multi-word entries
* More robust input validation
* Modern C++ smart pointers
* A more structured file format such as JSON
* Unit testing
* Object-oriented design using classes
* Graphical user interface
* More efficient search using a balanced tree or hash table

## Academic Context

This project was developed as a mini-project for the **Advanced Programming** course at **Kharazmi University**.

The main purpose of the project was to practice:

* C++ programming
* Pointers and dynamic memory
* Linked list implementation
* File handling
* Algorithmic problem solving
* Modular function design

## Author

**Ali Mosayebi**

Computer Engineering Student
Kharazmi University
