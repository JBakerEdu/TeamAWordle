#pragma once

#include <vector>
#include <string>

/// <summary>
/// Handles loading and filtering of five-letter words from a file.
/// Provides methods to retrieve random words and check for valid entries.
/// </summary>
class WordList {
public:
    /// <summary>
    /// Constructs a WordList from a file path, optionally filtering words with double letters.
    /// </summary>
    /// <param name="filePath">Path to the word list file.</param>
    /// <param name="allowDoubleLetters">Whether to include words with double letters.</param>
    explicit WordList(const std::string& filePath, bool allowDoubleLetters = true);

    /// <summary>
    /// Returns a random valid word from the loaded list.
    /// </summary>
    std::string getRandomWord() const;

    /// <summary>
    /// Checks if the provided word is in the word list.
    /// </summary>
    /// <param name="word">The word to validate.</param>
    /// <returns>True if the word is valid; otherwise, false.</returns>
    bool isValidWord(const std::string& word) const;

private:
    /// <summary>
    /// List of five-letter words loaded from the file.
    /// </summary>
    std::vector<std::string> fiveLetterWords;

    /// <summary>
    /// Indicates whether words with double letters are allowed.
    /// </summary>
    bool allowDoubleLetters;

    /// <summary>
    /// Checks if a word contains double letters.
    /// </summary>
    /// <param name="word">The word to inspect.</param>
    /// <returns>True if the word contains double letters; otherwise, false.</returns>
    bool hasDoubleLetters(const std::string& word) const;
};
