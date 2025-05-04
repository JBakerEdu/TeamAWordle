#include "GameModeController.h"
#include <unordered_map>

GameModeController::GameModeController(GameMode mode) : currentMode_(mode) {}

void GameModeController::SetMode(GameMode mode) {
    currentMode_ = mode;
}

GameMode GameModeController::GetMode() const {
    return currentMode_;
}

FeedbackResult GameModeController::EvaluateGuess(const std::string& guess, const std::string& target) {
    FeedbackResult result;
    result.perLetterColors.resize(5, 0);

    int correct = 0, present = 0, wrong = 0;

    for (int i = 0; i < 5; ++i) {
        if (guess[i] == target[i]) {
            result.perLetterColors[i] = 2;
            ++correct;
        }
        else if (target.find(guess[i]) != std::string::npos) {
            result.perLetterColors[i] = 1;
            ++present;
        }
        else {
            result.perLetterColors[i] = 0;
            ++wrong;
        }
    }

    if (currentMode_ == GameMode::Hard) {
        if (guess != target) {
            for (int& color : result.perLetterColors) {
                if (color == 2) color = 1;
            }
        }
    }
    else if (currentMode_ == GameMode::Memory) {
        result.memorySummary = "Correct: " + std::to_string(correct) +
            " | Present: " + std::to_string(present) +
            " | Wrong: " + std::to_string(wrong);
        result.perLetterColors.clear();
    }

    return result;
}
