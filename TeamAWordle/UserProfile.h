#pragma once
#include "PlayerStats.h"
#include <string>

class UserProfile {
public:
    UserProfile(const std::string& username);

    const std::string& getUsername() const;
    PlayerStats& getStats();

private:
    std::string username_;
    PlayerStats stats_;
};