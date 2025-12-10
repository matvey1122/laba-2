#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H
#include <iostream>

class FileOpenException : public std::runtime_error {
public:
    FileOpenException() : std::runtime_error("Failed to open file") {}
};

class TextProcessor {
private:
    char* text;

public:
    TextProcessor();
    TextProcessor(const char* filename);
    ~TextProcessor();

    void loadFile(const char* filename);
    void findSentencesWithWord(const char* word) const;

private:
    static bool containsWord(const char* sentence, const char* word);
    static void toLower(char* str);
};

#endif