#include "GuessValidator.h"
#include <algorithm>
#include <cctype>

GuessValidator::GuessValidator(const WordList& wordList)
    : wordList(wordList) {
}

GuessValidationResult GuessValidator::validateGuess(const std::string& guess) const {
    std::string lowerGuess = guess;
    std::transform(lowerGuess.begin(), lowerGuess.end(), lowerGuess.begin(), ::tolower);

    if (lowerGuess.length() != 5) {
        return GuessValidationResult::NotFiveLetters;
    }

    if (!std::all_of(lowerGuess.begin(), lowerGuess.end(), ::isalpha)) {
        return GuessValidationResult::NotFiveLetters;
    }

    if (!wordList.isValidWord(lowerGuess)) {
        return GuessValidationResult::NotInDictionary;
    }

    return GuessValidationResult::Valid;
}