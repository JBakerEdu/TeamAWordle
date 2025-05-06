#pragma once
#include <string>
#include <vector>

/// <summary>
/// Enum representing the available game modes.
/// </summary>
enum class GameMode {
    Original,   ///< Standard Wordle gameplay.
    Hard,       ///< Hard mode with reduced feedback.
    Lightning,  ///< Timed gameplay with guess deadlines.
    Memory      ///< Requires remembering past feedback.
};

/// <summary>
/// Represents the result of evaluating a guess,
/// including per-letter feedback and optional memory-mode summary.
/// </summary>
struct FeedbackResult {
    /// <summary>
    /// A vector of integers representing the color code for each letter in the guess.
    /// Typically: 0 = wrong, 1 = present, 2 = correct.
    /// </summary>
    std::vector<int> perLetterColors;

    /// <summary>
    /// A summary string for memory mode feedback.
    /// </summary>
    std::string memorySummary;
};

/// <summary>
/// Controls logic based on the selected GameMode. Provides guess evaluation tailored to each mode.
/// </summary>
class GameModeController {
public:
    /// <summary>
    /// Constructs a new controller using the specified game mode.
    /// </summary>
    /// <param name="mode">The initial game mode to apply.</param>
    explicit GameModeController(GameMode mode);

    /// <summary>
    /// Evaluates the player's guess against the target word, applying feedback logic based on game mode.
    /// </summary>
    /// <param name="guess">The player's guessed word.</param>
    /// <param name="target">The correct target word.</param>
    /// <returns>A FeedbackResult containing feedback per letter and mode-specific information.</returns>
    FeedbackResult EvaluateGuess(const std::string& guess, const std::string& target);

    /// <summary>
    /// Updates the controller to a new game mode.
    /// </summary>
    /// <param name="mode">The new game mode to set.</param>
    void SetMode(GameMode mode);

    /// <summary>
    /// Retrieves the current game mode.
    /// </summary>
    /// <returns>The currently selected GameMode.</returns>
    GameMode GetMode() const;

private:
    /// <summary>
    /// The currently selected game mode which determines how guesses are evaluated.
    /// </summary>
    GameMode currentMode_;
};
