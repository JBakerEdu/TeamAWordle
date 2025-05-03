#include "GameSession.h"

#include <stdexcept>
#include <random>

GameSession::GameSession(const std::string& dictionaryPath, bool allowDoubleLetters)
{
    wordList_ = std::make_unique<WordList>(dictionaryPath, allowDoubleLetters);
    if (wordList_->getRandomWord().empty()) {
        throw std::runtime_error("Dictionary failed to load or was empty.");
    }

    validator_ = std::make_unique<GuessValidator>(*wordList_);
    targetWord_ = wordList_->getRandomWord();
}

std::string GameSession::getTargetWord() const {
    return targetWord_;
}

GuessValidationResult GameSession::validate(const std::string& guess) const {
    return validator_->validateGuess(guess);
}