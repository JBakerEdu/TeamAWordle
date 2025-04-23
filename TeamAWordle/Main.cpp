#include <iostream>
#include "WordList.h"

int main() {
    std::cout << "Main started." << std::endl;
    WordList wordList("dictionary.txt");

    std::string selectedWord = wordList.getRandomWord();
    if (selectedWord.empty()) {
        std::cerr << "Failed to select a word. Is the dictionary loaded properly?" << std::endl;
        return 1;
    }

    std::cout << "Selected Word: " << selectedWord << std::endl;

    std::cin.get();
    return 0;
}