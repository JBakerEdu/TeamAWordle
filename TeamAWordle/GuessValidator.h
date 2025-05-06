#pragma once
#include <string>
#include "WordList.h"

/// <summary>
/// Enum representing the result of a guess validation attempt.
/// </summary>
enum class GuessValidationResult {
    /// <summary>The guess is valid and meets all requirements.</summary>
    Valid,

    /// <summary>The guess does not contain exactly five letters.</summary>
    NotFiveLetters,

    /// <summary>The guess is not found in the dictionary.</summary>
    NotInDictionary
};

/// <summary>
/// Validates player guesses based on length and dictionary presence.
/// </summary>
class GuessValidator {
public:
    /// <summary>
    /// Constructs a GuessValidator using a reference to a WordList.
    /// </summary>
    /// <param name="wordList">The WordList used to validate dictionary entries.</param>
    explicit GuessValidator(const WordList& wordList);

    /// <summary>
    /// Validates a given guess to ensure it is the correct length and present in the dictionary.
    /// </summary>
    /// <param name="guess">The guess string entered by the player.</param>
    /// <returns>A GuessValidationResult indicating if the guess is valid.</returns>
    GuessValidationResult validateGuess(const std::string& guess) const;

private:
    /// <summary>Reference to the WordList used for dictionary validation.</summary>
    const WordList& wordList;
};
