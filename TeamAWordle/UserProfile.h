#pragma once
#include "PlayerStats.h"
#include <string>

/// <summary>
/// Represents a user profile that stores a username and associated player statistics.
/// </summary>
class UserProfile {
public:
    /// <summary>
    /// Constructs a UserProfile with the specified username.
    /// </summary>
    /// <param name="username">The username for this profile.</param>
    UserProfile(const std::string& username);

    /// <summary>
    /// Gets the username associated with this profile.
    /// </summary>
    /// <returns>A constant reference to the username string.</returns>
    const std::string& getUsername() const;

    /// <summary>
    /// Gets a reference to the PlayerStats object associated with this profile.
    /// </summary>
    /// <returns>A reference to the PlayerStats object.</returns>
    PlayerStats& getStats();

    /// <summary>
    /// Saves the user's profile data and statistics to a file in the specified base directory.
    /// </summary>
    /// <param name="basePath">The directory where the profile should be saved.</param>
    /// <returns>True if saving was successful; otherwise, false.</returns>
    bool saveToFile(const std::string& basePath) const;

    /// <summary>
    /// Loads the user's profile data and statistics from a file in the specified base directory.
    /// </summary>
    /// <param name="basePath">The directory from which to load the profile.</param>
    /// <returns>True if loading was successful; otherwise, false.</returns>
    bool loadFromFile(const std::string& basePath);

private:
    /// <summary>The username for the profile.</summary>
    std::string username_;

    /// <summary>The statistics associated with the user.</summary>
    PlayerStats stats_;
};
