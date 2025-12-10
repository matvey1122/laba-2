#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <stdexcept>

class IndexOutOfBoundsException : public std::out_of_range {
public:
    IndexOutOfBoundsException() : std::out_of_range("Index out of bounds") {}
};

class STUDENT {
private:
    char* fullName;
    int groupNumber;
    int* grades;
    int numGrades;

public:
    STUDENT();
    STUDENT(const char* name, int group, const int* grades, int numGrades);
    STUDENT(const STUDENT& other);
    ~STUDENT();

    void setFullName(const char* name);
    const char* getFullName() const;
    void setGroupNumber(int group);
    int getGroupNumber() const;
    void setGrades(const int* grades, int numGrades);
    const int* getGrades() const;
    int getNumGrades() const;

    double calculateAverage() const;
    bool isExcellent() const;

    friend std::ostream& operator<<(std::ostream& os, const STUDENT& student);
    friend std::istream& operator>>(std::istream& is, STUDENT& student);
};

#endif