#pragma once
#include <array>

/// <summary>
/// Represents the statistical tracking for a single player,
/// including games played, wins, streaks, and guess distribution.
/// </summary>
class PlayerStats
{
public:
    /// <summary>
    /// Constructs a new PlayerStats object and initializes all statistics to zero.
    /// </summary>
    PlayerStats();

    /// <summary>
    /// Records the result of a completed game and updates statistics accordingly.
    /// </summary>
    /// <param name="won">True if the player won the game; false otherwise.</param>
    /// <param name="guessCount">The number of guesses used in the game.</param>
    void recordGame(bool won, int guessCount);

    /// <summary>
    /// Gets the total number of games played.
    /// </summary>
    /// <returns>The total number of games.</returns>
    int getTotalGames() const;

    /// <summary>
    /// Gets the number of games the player has won.
    /// </summary>
    /// <returns>The number of wins.</returns>
    int getWins() const;

    /// <summary>
    /// Gets the current win streak of the player.
    /// </summary>
    /// <returns>The current win streak count.</returns>
    int getCurrentStreak() const;

    /// <summary>
    /// Gets the highest win streak the player has achieved.
    /// </summary>
    /// <returns>The maximum win streak count.</returns>
    int getMaxStreak() const;

    /// <summary>
    /// Gets the number of games won using a specific guess number.
    /// </summary>
    /// <param name="guessNum">The guess number (1-6).</param>
    /// <returns>The number of wins using that many guesses.</returns>
    int getGuessCount(int guessNum) const;

    /// <summary>
    /// Resets all player statistics to their initial state.
    /// </summary>
    void reset();

private:
    /// <summary>Total number of games played.</summary>
    int totalGames;

    /// <summary>Total number of games won.</summary>
    int wins;

    /// <summary>Current streak of consecutive wins.</summary>
    int currentStreak;

    /// <summary>Maximum streak of consecutive wins achieved.</summary>
    int maxStreak;

    /// <summary>Array storing the number of wins per guess number (1 through 6).</summary>
    std::array<int, 6> guessCounts;
};
