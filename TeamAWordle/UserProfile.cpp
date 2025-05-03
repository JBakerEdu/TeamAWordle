#include "UserProfile.h"

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