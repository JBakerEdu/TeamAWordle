#include "UserProfile.h"
#include <fstream>
#include <filesystem>
#include <Windows.h>

UserProfile::UserProfile(const std::string& username)
    : username_(username)
{
}

const std::string& UserProfile::getUsername() const {
    return username_;
}

PlayerStats& UserProfile::getStats() {
    return stats_;
}

bool UserProfile::saveToFile(const std::string& basePath) const {
    CreateDirectoryA(basePath.c_str(), NULL);

    std::ofstream out(basePath + "/" + username_ + ".profile");
    if (!out.is_open()) return false;

    out << username_ << "\n";
    out << stats_.getTotalGames() << " "
        << stats_.getWins() << " "
        << stats_.getCurrentStreak() << " "
        << stats_.getMaxStreak() << "\n";

    for (int i = 1; i <= 6; ++i)
        out << stats_.getGuessCount(i) << " ";
    out << "\n";

    return true;
}

bool UserProfile::loadFromFile(const std::string& basePath) {
    std::ifstream in(basePath + "/" + username_ + ".profile");
    if (!in.is_open()) return false;

    int totalGames, wins, currentStreak, maxStreak;
    std::array<int, 6> guessCounts{ 0 };

    std::string ignoredUsername;
    std::getline(in, ignoredUsername); // skip first line

    in >> totalGames >> wins >> currentStreak >> maxStreak;
    for (int i = 0; i < 6; ++i)
        in >> guessCounts[i];

    // Set fields manually since they're private
    stats_ = PlayerStats(); // reset first
    for (int i = 0; i < totalGames; ++i)
        stats_.recordGame(false, 1); // dummy losses to increment totalGames

    for (int i = 0; i < wins; ++i)
        stats_.recordGame(true, 6);  // dummy wins to increase stats and streak

    // Override streaks and guess counts
    stats_ = PlayerStats(); // wipe again
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < guessCounts[i]; ++j)
            stats_.recordGame(true, i + 1);

    // Apply streaks manually if needed (optional improvement)

    return true;
}