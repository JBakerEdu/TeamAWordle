#include "WordList.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <cctype>

WordList::WordList(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string word;

    while (file >> word) {
        // Normalize to lowercase
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Accept only alphabetic 5-letter words
        if (word.length() == 5 && std::all_of(word.begin(), word.end(), ::isalpha)) {
            fiveLetterWords.push_back(word);
        }
    }
}

std::string WordList::getRandomWord() const {
    if (fiveLetterWords.empty()) return "";

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, static_cast<int>(fiveLetterWords.size() - 1));

    return fiveLetterWords[dist(gen)];
}

bool WordList::isValidWord(const std::string& word) const {
    return std::find(fiveLetterWords.begin(), fiveLetterWords.end(), word) != fiveLetterWords.end();
}