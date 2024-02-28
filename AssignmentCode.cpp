
#include <iostream>
#include <fstream>

using namespace std;

// Define a struct to represent a student
struct Student {
    string name;
    string SID;
    int grades[6]; // Fixed-size array to store grades for each course
};

const int MAX_STUDENTS = 10;

// Function to clear the screen
void clearScreen() {
    system("CLS");  // Clear screen using system command (Windows-specific)
}

// Function to read student records from file
void readStudentRecords(const string& filename, Student students[]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(EXIT_FAILURE); // Exit program if file cannot be opened
    }

    string line;
    getline(file, line); // Read header line (not used here)

    for (int i = 0; i < MAX_STUDENTS; ++i) {
        getline(file, line); // Read each line containing student record
        size_t pos = line.find(','); // Find position of first comma (separator)
        students[i].name = line.substr(0, pos); // Extract student name
        size_t next_pos = line.find(',', pos + 1); // Find position of next comma
        students[i].SID = line.substr(pos + 1, next_pos - pos - 1); // Extract student ID

        // Read grades
        pos = next_pos; // Update position to start from next comma
        for (int j = 0; j < 6; ++j) {
            next_pos = line.find(',', pos + 1); // Find position of next comma
            if (next_pos == string::npos) // If no more commas found
                next_pos = line.length(); // Set position to end of line
            students[i].grades[j] = stoi(line.substr(pos + 1, next_pos - pos - 1)); // Extract and convert grade to integer
            pos = next_pos; // Update position for next iteration
        }
    }

    file.close();
}

// Function to print result slip for a student
void printResultSlip(const Student students[]) {
    clearScreen(); // Clear screen before printing result slip
    cout << "Enter Student ID: ";
    string SID;
    cin >> SID;

    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (students[i].SID == SID) { // If student found
            clearScreen(); // Clear screen before printing result slip
            cout << "----------------------------------------\n";
            cout << "Name: " << students[i].name << endl; // Print student name
            cout << "Student ID: " << students[i].SID << endl; // Print student ID
            cout << "----------------------------------------\n";
            cout << "Course" << "    " << "Grade" << endl;
            cout << "----------------------------------------\n";
            // Print grades for each course
            cout << "CS 110" << "     " << students[i].grades[0] << endl;
            cout << "MA 110" << "     " << students[i].grades[1] << endl;
            cout << "CS 131" << "     " << students[i].grades[2] << endl;
            cout << "CH 110" << "     " << students[i].grades[3] << endl;
            cout << "LA 111" << "     " << students[i].grades[4] << endl;
            cout << "PH 110" << "     " << students[i].grades[5] << endl;
            cout << "----------------------------------------\n";
            return; // Exit loop after printing result slip
        }
    }
    cout << "Student not found!" << endl; // If student not found
}

int main() {
    Student students[MAX_STUDENTS]; // Array to store student records

    readStudentRecords("grades.txt", students); // Read student records from file

    int choice;
    do {
        clearScreen(); // Clear screen before displaying menu
        cout << "1. Print Result Slip" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                printResultSlip(students); // Call function to print result slip
                break;
            case 2:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        cout << "\nPress Enter to continue..."; // Pause before displaying menu again
        cin.ignore(); // Ignore any remaining characters in input buffer
        cin.get(); // Wait for user to press Enter key
    } while (choice != 2); // Continue loop until user selects exit option

    return 0; // Exit program
}

