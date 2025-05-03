#pragma once

#include <vector>
#include <string>

class WordList {
public:
    explicit WordList(const std::string& filePath, bool allowDoubleLetters = true);
    std::string getRandomWord() const;
    bool isValidWord(const std::string& word) const;

private:
    std::vector<std::string> fiveLetterWords;
    bool allowDoubleLetters;

    bool hasDoubleLetters(const std::string& word) const;
};
