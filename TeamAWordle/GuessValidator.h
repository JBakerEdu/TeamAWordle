#pragma once
#include <string>
#include "WordList.h"

enum class GuessValidationResult {
    Valid,
    NotFiveLetters,
    NotInDictionary
};

class GuessValidator {
public:
    explicit GuessValidator(const WordList& wordList);
    GuessValidationResult validateGuess(const std::string& guess) const;

private:
    const WordList& wordList;
};