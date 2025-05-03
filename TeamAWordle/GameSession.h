#pragma once
#include "WordList.h"
#include "GuessValidator.h"
#include <string>
#include <memory>

class GameSession {
public:
    GameSession(const std::string& dictionaryPath, bool allowDoubleLetters = false);

    std::string getTargetWord() const;
    GuessValidationResult validate(const std::string& guess) const;

private:
    std::unique_ptr<WordList> wordList_;
    std::unique_ptr<GuessValidator> validator_;
    std::string targetWord_;
};