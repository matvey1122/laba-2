#define _CRT_SECURE_NO_WARNINGS
#include "STUDENT.h"
#include <cstring>
#include <cctype>

STUDENT::STUDENT()
    : fullName(nullptr), groupNumber(0), grades(nullptr), numGrades(0) {
    std::cout << "Default constructor called for STUDENT." << std::endl;
}

STUDENT::STUDENT(const char* name, int group, const int* grades, int numGrades)
    : groupNumber(group), numGrades(numGrades) {
    std::cout << "Parameterized constructor called for STUDENT." << std::endl;

    if (name && strlen(name) > 0) {
        this->fullName = new char[strlen(name) + 1];
        strcpy(this->fullName, name);
    }
    else {
        this->fullName = nullptr;
    }

    if (numGrades > 0 && grades) {
        this->grades = new int[numGrades];
        for (int i = 0; i < numGrades; ++i) {
            this->grades[i] = grades[i];
        }
    }
    else {
        this->grades = nullptr;
    }
}

STUDENT::STUDENT(const STUDENT& other) {
    std::cout << "Copy constructor called for STUDENT." << std::endl;
    groupNumber = other.groupNumber;
    numGrades = other.numGrades;

    if (other.fullName) {
        fullName = new char[strlen(other.fullName) + 1];
        strcpy(fullName, other.fullName);
    }
    else {
        fullName = nullptr;
    }

    if (numGrades > 0 && other.grades) {
        grades = new int[numGrades];
        for (int i = 0; i < numGrades; ++i) {
            grades[i] = other.grades[i];
        }
    }
    else {
        grades = nullptr;
    }
}

STUDENT::~STUDENT() {
    std::cout << "Destructor called for STUDENT: "
        << (fullName ? fullName : "Unnamed") << std::endl;
    delete[] fullName;
    delete[] grades;
}

void STUDENT::setFullName(const char* name) {
    delete[] fullName;
    if (name && strlen(name) > 0) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }
    else {
        fullName = nullptr;
    }
}

const char* STUDENT::getFullName() const {
    return fullName;
}

void STUDENT::setGroupNumber(int group) {
    groupNumber = group;
}

int STUDENT::getGroupNumber() const {
    return groupNumber;
}

void STUDENT::setGrades(const int* grades, int numGrades) {
    delete[] this->grades;
    this->numGrades = numGrades;

    if (numGrades > 0 && grades) {
        this->grades = new int[numGrades];
        for (int i = 0; i < numGrades; ++i) {
            this->grades[i] = grades[i];
        }
    }
    else {
        this->grades = nullptr;
    }
}

const int* STUDENT::getGrades() const {
    return grades;
}

int STUDENT::getNumGrades() const {
    return numGrades;
}

double STUDENT::calculateAverage() const {
    if (numGrades == 0) return 0.0;
    int sum = 0;
    for (int i = 0; i < numGrades; ++i) {
        sum += grades[i];
    }
    return static_cast<double>(sum) / numGrades;
}

bool STUDENT::isExcellent() const {
    for (int i = 0; i < numGrades; ++i) {
        if (grades[i] < 4) return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const STUDENT& student) {
    os << "Name: " << (student.fullName ? student.fullName : "N/A")
        << ", Group: " << student.groupNumber
        << ", Average: " << student.calculateAverage();
    return os;
}

std::istream& operator>>(std::istream& is, STUDENT& student) {
    char name[100];
    int group;
    int numGrades;

    std::cout << "Enter full name: ";
    is.ignore();
    is.getline(name, 100);

    std::cout << "Enter group number: ";
    is >> group;

    std::cout << "Enter number of grades: ";
    is >> numGrades;
    if (numGrades <= 0) numGrades = 0;

    int* grades = nullptr;
    if (numGrades > 0) {
        grades = new int[numGrades];
        std::cout << "Enter grades: ";
        for (int i = 0; i < numGrades; ++i) {
            is >> grades[i];
        }
    }

    student.setFullName(name);
    student.setGroupNumber(group);
    student.setGrades(grades, numGrades);

    delete[] grades;
    return is;
}