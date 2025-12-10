#define _CRT_SECURE_NO_WARNINGS
#include "TextProcessor.h"
#include <fstream>
#include <cstring>
#include <cctype>

TextProcessor::TextProcessor() : text(nullptr) {
    std::cout << "TextProcessor default constructor called." << std::endl;
}

TextProcessor::TextProcessor(const char* filename) : text(nullptr) {
    std::cout << "TextProcessor parameterized constructor called." << std::endl;
    loadFile(filename);
}

TextProcessor::~TextProcessor() {
    std::cout << "TextProcessor destructor called." << std::endl;
    delete[] text;
}

void TextProcessor::loadFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FileOpenException();
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size <= 0) {
        text = nullptr;
        return;
    }

    text = new char[size + 1];
    if (!file.read(text, size)) {
        delete[] text;
        throw std::runtime_error("Error reading file");
    }
    text[size] = '\0';
}

void TextProcessor::findSentencesWithWord(const char* word) const {
    if (!text || strlen(text) == 0) {
        std::cout << "File is empty." << std::endl;
        return;
    }

    char* copy = new char[strlen(text) + 1];
    strcpy(copy, text);

    char* sentence = strtok(copy, ".!?");
    bool found = false;

    while (sentence != nullptr) {
        while (isspace(*sentence)) sentence++;
        if (*sentence == '\0') {
            sentence = strtok(nullptr, ".!?");
            continue;
        }

        char* end = sentence + strlen(sentence) - 1;
        while (end > sentence && isspace(*end)) end--;
        *(end + 1) = '\0';

        if (containsWord(sentence, word)) {
            std::cout << "> " << sentence << std::endl;
            found = true;
        }
        sentence = strtok(nullptr, ".!?");
    }

    if (!found) {
        std::cout << "No sentences found with the word: " << word << std::endl;
    }

    delete[] copy;
}

bool TextProcessor::containsWord(const char* sentence, const char* word) {
    char* lowerSentence = new char[strlen(sentence) + 1];
    char* lowerWord = new char[strlen(word) + 1];

    strcpy(lowerSentence, sentence);
    strcpy(lowerWord, word);

    toLower(lowerSentence);
    toLower(lowerWord);

    const char* pos = lowerSentence;
    while ((pos = strstr(pos, lowerWord)) != nullptr) {
        bool startOk = (pos == lowerSentence || !isalnum(*(pos - 1)));
        bool endOk = (!isalnum(*(pos + strlen(lowerWord))));

        if (startOk && endOk) {
            delete[] lowerSentence;
            delete[] lowerWord;
            return true;
        }
        pos++;
    }

    delete[] lowerSentence;
    delete[] lowerWord;
    return false;
}

void TextProcessor::toLower(char* str) {
    for (size_t i = 0; i < strlen(str); ++i) {
        str[i] = tolower(str[i]);
    }
}