#include "PlayerStats.h"

PlayerStats::PlayerStats()
	: totalGames(0), wins(0), currentStreak(0), maxStreak(0), guessCounts{0}
{
}

void PlayerStats::recordGame(bool won, int guessCount)
{
	++totalGames;

	if (won)
	{
		++wins;
		++currentStreak;
		if (currentStreak > maxStreak)
			maxStreak = currentStreak;

		if (guessCount >= 1 && guessCount <= 6)
		{
			++guessCounts[guessCount - 1];
		}
	} else {
		currentStreak = 0;
	}
}

int PlayerStats::getTotalGames() const { return totalGames; }
int PlayerStats::getWins() const { return wins; }
int PlayerStats::getCurrentStreak() const { return currentStreak; }
int PlayerStats::getMaxStreak() const { return maxStreak; }

int PlayerStats::getGuessCount(int guessNum) const
{
	if (guessNum >= 1 && guessNum <= 6)
		return guessCounts[guessNum - 1];
	return 0;
}

void PlayerStats::reset()
{
	totalGames = wins = currentStreak = maxStreak = 0;
	guessCounts.fill(0);
}

