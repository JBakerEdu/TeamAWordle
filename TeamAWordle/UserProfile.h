#pragma once
#include "PlayerStats.h"
#include <string>

class UserProfile {
public:
    UserProfile(const std::string& username);

    const std::string& getUsername() const;
    PlayerStats& getStats();
    bool saveToFile(const std::string& basePath) const;
    bool loadFromFile(const std::string& basePath);

private:
    std::string username_;
    PlayerStats stats_;
};