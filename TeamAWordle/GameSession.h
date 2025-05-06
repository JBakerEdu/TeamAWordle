#pragma once
#include "WordList.h"
#include "GuessValidator.h"
#include <string>
#include <memory>

/// <summary>
/// Manages the state of a Wordle game session, including the current target word,
/// word validation, and dictionary handling.
/// </summary>
class GameSession {
public:
    /// <summary>
    /// Constructs a new GameSession with the specified dictionary and game settings.
    /// </summary>
    /// <param name="dictionaryPath">Path to the dictionary file used for word validation.</param>
    /// <param name="allowDoubleLetters">Indicates whether words with double letters are allowed.</param>
    GameSession(const std::string& dictionaryPath, bool allowDoubleLetters = false);

    /// <summary>
    /// Gets the current target word for the session.
    /// </summary>
    /// <returns>The target word as a std::string.</returns>
    std::string getTargetWord() const;

    /// <summary>
    /// Validates a player's guess against the game rules and dictionary.
    /// </summary>
    /// <param name="guess">The player's guessed word.</param>
    /// <returns>A GuessValidationResult indicating if the guess is valid, incorrect length, or not in the dictionary.</returns>
    GuessValidationResult validate(const std::string& guess) const;

private:
    /// <summary>Pointer to the WordList containing valid dictionary words.</summary>
    std::unique_ptr<WordList> wordList_;

    /// <summary>Pointer to the GuessValidator used to validate guesses.</summary>
    std::unique_ptr<GuessValidator> validator_;

    /// <summary>The target word for the current session.</summary>
    std::string targetWord_;
};
