#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct WordNode {
    string word;
    string synonym;
    WordNode* next;

    WordNode(const string& w, const string& s)
        : word(w), synonym(s), next(nullptr) {}
};

// Finds a word in the dictionary
WordNode* findWord(WordNode* head, const string& word) {
    while (head && head->word != word) {
        head = head->next;
    }

    return head;
}

const WordNode* findWord(const WordNode* head, const string& word) {
    while (head && head->word != word) {
        head = head->next;
    }

    return head;
}

// Adds a word while keeping the dictionary alphabetically sorted
void addWord(WordNode*& head, const string& word, const string& synonym) {
    if (word.empty() || synonym.empty()) {
        cout << "Word and synonym cannot be empty." << endl;
        return;
    }

    // Check if the word already exists
    WordNode* existing = findWord(head, word);

    if (existing) {
        if (existing->synonym == synonym) {
            cout << "This synonym already exists for the word." << endl;
            return;
        }

        existing->synonym += ", " + synonym;
        cout << "Synonym added successfully." << endl;
        return;
    }

    WordNode* newNode = new WordNode(word, synonym);

    // Insert at the beginning
    if (!head || word < head->word) {
        newNode->next = head;
        head = newNode;

        cout << "Word added successfully!" << endl;
        return;
    }

    // Find the correct position
    WordNode* current = head;

    while (current->next && current->next->word < word) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    cout << "Word added successfully!" << endl;
}

// Removes a word and all its synonyms
void removeWord(WordNode*& head, const string& word) {
    WordNode* current = head;
    WordNode* previous = nullptr;

    while (current && current->word != word) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        cout << "Word not found in the dictionary." << endl;
        return;
    }

    if (previous) {
        previous->next = current->next;
    } else {
        head = current->next;
    }

    delete current;

    cout << "Word and its synonyms removed successfully." << endl;
}

// Removes a specific synonym from a word
void removeSynonym(
    WordNode*& head,
    const string& word,
    const string& synonym
) {
    WordNode* current = findWord(head, word);

    if (!current) {
        cout << "Word not found in the dictionary." << endl;
        return;
    }

    string& synonyms = current->synonym;

    // Find the exact synonym
    size_t position = synonyms.find(synonym);

    if (position == string::npos) {
        cout << "Synonym not found for the word." << endl;
        return;
    }

    // Make sure we found a complete synonym rather than a substring
    bool validStart =
        position == 0 || synonyms[position - 1] == ' ';

    size_t endPosition = position + synonym.length();

    bool validEnd =
        endPosition == synonyms.length() ||
        synonyms[endPosition] == ',' ||
        synonyms[endPosition] == ' ';

    if (!validStart || !validEnd) {
        cout << "Synonym not found for the word." << endl;
        return;
    }

    // Case: only synonym exists
    if (synonyms == synonym) {
        removeWord(head, word);
        return;
    }

    // Case: synonym is at the beginning
    if (position == 0) {
        synonyms.erase(0, synonym.length());

        if (!synonyms.empty() && synonyms[0] == ' ') {
            synonyms.erase(0, 1);
        }

        if (!synonyms.empty() && synonyms[0] == ',') {
            synonyms.erase(0, 1);
        }

        if (!synonyms.empty() && synonyms[0] == ' ') {
            synonyms.erase(0, 1);
        }
    }
    // Case: synonym is in the middle or at the end
    else {
        size_t start = position - 2;

        if (start < synonyms.length() &&
            synonyms[start] == ',' &&
            start + 1 < synonyms.length() &&
            synonyms[start + 1] == ' ') {
            synonyms.erase(start, synonym.length() + 2);
        } else {
            synonyms.erase(position, synonym.length());
        }
    }

    cout << "Synonym removed successfully." << endl;
}

// Changes a word while preserving alphabetical order
void changeWord(
    WordNode*& head,
    const string& oldWord,
    const string& newWord
) {
    if (oldWord == newWord) {
        cout << "The new word is the same as the old word." << endl;
        return;
    }

    WordNode* current = findWord(head, oldWord);

    if (!current) {
        cout << "Word not found in the dictionary." << endl;
        return;
    }

    if (findWord(head, newWord)) {
        cout << "The new word already exists in the dictionary." << endl;
        return;
    }

    string synonyms = current->synonym;

    // Remove old word
    removeWord(head, oldWord);

    // Add new word with the same synonyms
    addWord(head, newWord, synonyms);

    cout << "Word changed successfully." << endl;
}

// Searches for a word
void searchWord(const WordNode* head, const string& word) {
    const WordNode* current = findWord(head, word);

    if (!current) {
        cout << "Word not found in the dictionary." << endl;
        return;
    }

    cout << "\nWord: " << current->word << endl;
    cout << "Synonyms: " << current->synonym << endl;
}

// Displays all dictionary entries
void displayDictionary(const WordNode* head) {
    if (!head) {
        cout << "Dictionary is empty." << endl;
        return;
    }

    cout << "\n===== Dictionary =====" << endl;

    const WordNode* current = head;

    while (current) {
        cout << "Word: " << current->word
             << ", Synonyms: " << current->synonym << endl;

        current = current->next;
    }

    cout << "======================" << endl;
}

// Saves dictionary to a file
void saveDictionary(const WordNode* head, const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    const WordNode* current = head;

    while (current) {
        outFile << current->word << endl;
        outFile << current->synonym << endl;

        current = current->next;
    }

    outFile.close();

    cout << "Dictionary saved to file: " << filename << endl;
}

// Loads dictionary from a file
WordNode* loadDictionary(const string& filename) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error: Unable to open file for reading." << endl;
        return nullptr;
    }

    WordNode* head = nullptr;

    string word;
    string synonym;

    while (getline(inFile, word) && getline(inFile, synonym)) {
        addWord(head, word, synonym);
    }

    inFile.close();

    cout << "Dictionary loaded from file: " << filename << endl;

    return head;
}

// Deletes the entire linked list
void deleteDictionary(WordNode*& head) {
    while (head) {
        WordNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Safely gets an integer choice
bool getChoice(int& choice) {
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Invalid input. Please enter a number." << endl;
        return false;
    }

    return true;
}

// Displays the main menu
void displayMenu(WordNode*& head) {
    int choice;

    string word;
    string synonym;
    string newWord;
    string filename;

    while (true) {
        cout << "\n===== Dictionary Menu =====" << endl;
        cout << "1. Add a word with its synonym" << endl;
        cout << "2. Remove a word and its synonyms" << endl;
        cout << "3. Remove a synonym from a word" << endl;
        cout << "4. Search for a word" << endl;
        cout << "5. Display all words and synonyms" << endl;
        cout << "6. Change a word" << endl;
        cout << "7. Save dictionary to file" << endl;
        cout << "8. Load dictionary from file" << endl;
        cout << "9. Exit" << endl;
        cout << "===========================" << endl;
        cout << "Enter your choice: ";

        if (!getChoice(choice)) {
            continue;
        }

        switch (choice) {

            case 1:
                cout << "Enter word: ";
                cin >> word;

                cout << "Enter its synonym: ";
                cin >> synonym;

                addWord(head, word, synonym);
                break;

            case 2:
                cout << "Enter word to remove: ";
                cin >> word;

                removeWord(head, word);
                break;

            case 3:
                cout << "Enter word: ";
                cin >> word;

                cout << "Enter synonym to remove: ";
                cin >> synonym;

                removeSynonym(head, word, synonym);
                break;

            case 4:
                cout << "Enter word to search: ";
                cin >> word;

                searchWord(head, word);
                break;

            case 5:
                displayDictionary(head);
                break;

            case 6:
                cout << "Enter the word to change: ";
                cin >> word;

                cout << "Enter the new word: ";
                cin >> newWord;

                changeWord(head, word, newWord);
                break;

            case 7:
                cout << "Enter filename to save dictionary: ";
                cin >> filename;

                saveDictionary(head, filename);
                break;

            case 8:
                cout << "Enter filename to load dictionary: ";
                cin >> filename;

                deleteDictionary(head);
                head = loadDictionary(filename);
                break;

            case 9:
                cout << "Exiting program. Goodbye!" << endl;

                deleteDictionary(head);
                return;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    WordNode* head = nullptr;

    displayMenu(head);

    return 0;
}