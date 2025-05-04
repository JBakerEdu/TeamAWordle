#pragma once
#include <string>
#include <vector>
#include <tuple>

enum class GameMode {
    Original,
    Hard,
    Lightning,
    Memory
};

struct FeedbackResult {
    std::vector<int> perLetterColors;
    std::string memorySummary;
};

class GameModeController {
public:
    explicit GameModeController(GameMode mode);
    FeedbackResult EvaluateGuess(const std::string& guess, const std::string& target);

    void SetMode(GameMode mode);
    GameMode GetMode() const;

private:
    GameMode currentMode_;
};
