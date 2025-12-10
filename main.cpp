#include <iostream>
#include "STUDENT.h"
#include "TextProcessor.h"

void manageStudents();
void processText();
void sortStudents(STUDENT* students, int size);
void printExcellentStudents(STUDENT* students, int size);

int main() {
    std::cout << "Program started at: Wednesday, December 10, 2025\n";

    int choice;
    while (true) {
        std::cout << "\n===== MAIN MENU =====\n";
        std::cout << "1. Student Management\n";
        std::cout << "2. Text Processing\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        try {
            switch (choice) {
            case 1: manageStudents(); break;
            case 2: processText(); break;
            case 3: return 0;
            default: std::cout << "Invalid choice!\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "ERROR: " << e.what() << "\n";
        }
    }
}

void manageStudents() {
    STUDENT* students = nullptr;
    int size = 0;

    while (true) {
        std::cout << "\n--- STUDENT MENU ---\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Remove student\n";
        std::cout << "3. Edit student\n";
        std::cout << "4. Sort by average grade\n";
        std::cout << "5. Show excellent students (4/5)\n";
        std::cout << "6. Print all students\n";
        std::cout << "7. Back to main menu\n";
        int choice;
        std::cin >> choice;

        if (choice == 7) {
            delete[] students;
            return;
        }

        try {
            switch (choice) {
            case 1: {
                int pos;
                std::cout << "Position (0-" << size << "): ";
                std::cin >> pos;
                if (pos < 0 || pos > size) throw IndexOutOfBoundsException();

                STUDENT* newStudents = new STUDENT[size + 1];
                for (int i = 0; i < pos; ++i) newStudents[i] = students[i];
                std::cout << "Enter new student data:\n";
                std::cin >> newStudents[pos];
                for (int i = pos; i < size; ++i) newStudents[i + 1] = students[i];

                delete[] students;
                students = newStudents;
                size++;
                break;
            }
            case 2: {
                int pos;
                std::cout << "Position to remove (0-" << size - 1 << "): ";
                std::cin >> pos;
                if (pos < 0 || pos >= size) throw IndexOutOfBoundsException();

                STUDENT* newStudents = new STUDENT[size - 1];
                for (int i = 0; i < pos; ++i) newStudents[i] = students[i];
                for (int i = pos; i < size - 1; ++i) newStudents[i] = students[i + 1];

                delete[] students;
                students = newStudents;
                size--;
                break;
            }
            case 3: {
                int pos;
                std::cout << "Position to edit (0-" << size - 1 << "): ";
                std::cin >> pos;
                if (pos < 0 || pos >= size) throw IndexOutOfBoundsException();
                std::cout << "Enter new data:\n";
                std::cin >> students[pos];
                break;
            }
            case 4: sortStudents(students, size); break;
            case 5: printExcellentStudents(students, size); break;
            case 6:
                for (int i = 0; i < size; ++i) {
                    std::cout << "Student " << i << ": " << students[i] << "\n";
                }
                break;
            default: std::cout << "Invalid choice!\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "ERROR: " << e.what() << "\n";
        }
    }
}

void sortStudents(STUDENT* students, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (students[j].calculateAverage() > students[j + 1].calculateAverage()) {
                STUDENT temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    std::cout << "Students sorted by average grade.\n";
}

void printExcellentStudents(STUDENT* students, int size) {
    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (students[i].isExcellent()) {
            std::cout << students[i].getFullName()
                << " (Group " << students[i].getGroupNumber() << ")\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No excellent students found.\n";
    }
}

void processText() {
    try {
        char filename[256], word[50];
        std::cout << "Enter filename: ";
        std::cin >> filename;
        std::cout << "Enter search word: ";
        std::cin >> word;

        TextProcessor processor;
        processor.loadFile(filename);
        processor.findSentencesWithWord(word);
    }
    catch (const std::exception& e) {
        std::cerr << "TEXT PROCESSING ERROR: " << e.what() << "\n";
    }
}