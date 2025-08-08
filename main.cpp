#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits> // Required for numeric_limits

using namespace std;

// --- Helper Functions for a Cleaner UI ---

// Clears the console screen in a portable way.
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // ANSI escape code for clearing the screen on Linux/macOS
     cout << "\033[2J\033[1;1H";
#endif
}

// Pauses the program and waits for the user to press Enter.
void pause() {
     cout << "\nPress Enter to continue...";
     cin.ignore( numeric_limits< streamsize>::max(), '\n');
}

// --- Data Structure for a Record ---

struct Record {
     string companyName;
     string address;
    int studentsPlaced = 0;
    long salary = 0; // Use long for potentially large salary figures
};

// --- Main System Class ---

class PlacementSystem {
private:
    const  string INDEX_FILE = "placement_records_index.txt";

    // Helper function to display a single record's details.
    void displayRecord(const Record& record) {
         cout << "\n--- Placement Details ---" <<  endl;
         cout << "Company Name: " << record.companyName <<  endl;
         cout << "Address: " << record.address <<  endl;
         cout << "Students Placed: " << record.studentsPlaced <<  endl;
        if (record.salary > 0) {
             cout << "Salary (LPA): " << record.salary <<  endl;
        }
         cout << "-------------------------" <<  endl;
    }

    // Reads a record from its specific file.
    bool readRecordFromFile(const  string& companyName, Record& record) {
         ifstream file(companyName + ".txt");
        if (!file.is_open()) {
            return false;
        }
        
        // Simple format: each value on a new line
        getline(file, record.companyName);
        getline(file, record.address);
        file >> record.studentsPlaced;
        file >> record.salary;
        
        file.close();
        return true;
    }

    // Writes a record to its specific file.
    void writeRecordToFile(const Record& record) {
         ofstream file(record.companyName + ".txt");
        file << record.companyName <<  endl;
        file << record.address <<  endl;
        file << record.studentsPlaced <<  endl;
        file << record.salary <<  endl;
        file.close();
    }

    // Adds a company name to our main index file.
    void addToIndex(const  string& companyName) {
         ofstream indexFile(INDEX_FILE,  ios::app);
        indexFile << companyName <<  endl;
        indexFile.close();
    }

    // Gets a list of all company names from the index file.
     vector< string> getCompanyList() {
         vector< string> companies;
         ifstream indexFile(INDEX_FILE);
         string companyName;
        while (getline(indexFile, companyName)) {
            companies.push_back(companyName);
        }
        indexFile.close();
        return companies;
    }


public:
    void enterPlacementDetails() {
        Record newRecord;
         cout << "Enter company name: ";
        getline( cin, newRecord.companyName);

         cout << "Enter company address: ";
        getline( cin, newRecord.address);

         cout << "Enter number of students placed: ";
         cin >> newRecord.studentsPlaced;
         cin.ignore( numeric_limits< streamsize>::max(), '\n'); // Consume newline

        writeRecordToFile(newRecord);
        addToIndex(newRecord.companyName);

         cout << "\nPlacement details saved successfully for " << newRecord.companyName <<  endl;
        displayRecord(newRecord);
    }

    void editStudentsPlaced() {
         cout << "Enter the company name to edit: ";
         string companyName;
        getline( cin, companyName);

        Record record;
        if (!readRecordFromFile(companyName, record)) {
             cout << "Error: Record for '" << companyName << "' not found." <<  endl;
            return;
        }

         cout << "Current number of students placed: " << record.studentsPlaced <<  endl;
         cout << "Enter new number of students placed: ";
         cin >> record.studentsPlaced;
         cin.ignore( numeric_limits< streamsize>::max(), '\n');

        writeRecordToFile(record);
         cout << "\nUpdated details saved successfully." <<  endl;
        displayRecord(record);
    }

    void appendSalary() {
         cout << "Enter the company name to append salary: ";
         string companyName;
        getline( cin, companyName);

        Record record;
        if (!readRecordFromFile(companyName, record)) {
             cout << "Error: Record for '" << companyName << "' not found." <<  endl;
            return;
        }

         cout << "Enter salary (LPA, e.g., 15 for 15 Lakhs Per Annum): ";
         cin >> record.salary;
         cin.ignore( numeric_limits< streamsize>::max(), '\n');

        writeRecordToFile(record);
         cout << "\nSalary appended successfully." <<  endl;
        displayRecord(record);
    }

    void displayAllRecords() {
         vector< string> companies = getCompanyList();
        if (companies.empty()) {
             cout << "No placement records found." <<  endl;
            return;
        }

         cout << "--- Displaying All Placement Records ---" <<  endl;
        for (const auto& companyName : companies) {
            Record record;
            if (readRecordFromFile(companyName, record)) {
                displayRecord(record);
            }
        }
    }
};

void showMenu() {
     cout << "\n===== Placement Management System =====\n";
     cout << "1. Enter New Placement Details\n";
     cout << "2. Edit Number of Students Placed\n";
     cout << "3. Add/Update Salary Information\n";
     cout << "4. Display All Placement Records\n";
     cout << "5. Exit\n";
     cout << "=======================================\n";
     cout << "Enter your choice: ";
}

int main() {
    PlacementSystem system;
    int choice;

    do {
        showMenu();
         cin >> choice;
        
        // This is crucial to handle the newline character left by `cin >> choice`
        // before we use `getline` in the functions.
         cin.ignore( numeric_limits< streamsize>::max(), '\n');
        
        clearScreen();

        switch (choice) {
            case 1:
                system.enterPlacementDetails();
                pause();
                break;
            case 2:
                system.editStudentsPlaced();
                pause();
                break;
            case 3:
                system.appendSalary();
                pause();
                break;
            case 4:
                system.displayAllRecords();
                pause();
                break;
            case 5:
                 cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                 cout << "Invalid choice! Please try again.\n";
                pause();
        }
        if (choice != 5) {
            clearScreen();
        }
    } while (choice != 5);

    return 0;
}
