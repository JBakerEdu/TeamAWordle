#pragma once
#include <array>
#include <string>

class PlayerStats
{
public:
	PlayerStats();

	void recordGame(bool won, int guessCount);

	int getTotalGames() const;
	int getWins() const;
	int getCurrentStreak() const;
	int getMaxStreak() const;
	int getGuessCount(int guessNum) const;

	void reset();

private:
	int totalGames;
	int wins;
	int currentStreak;
	int maxStreak;
	std::array<int, 6> guessCounts;
};

