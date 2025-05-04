#include "SettingsForm.h"
#include <fstream>
#include <string>
#include <msclr/marshal_cppstd.h>

bool TeamAWordle::SettingsForm::LoadSettingsFromFile() {
    std::ifstream file("settings.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("allowDoubleLetters=") == 0) {
            std::string value = line.substr(19);
            return value == "true";
        }
    }
    return true;
}

void TeamAWordle::SettingsForm::LoadColorsFromFile(System::Drawing::Color% correct, System::Drawing::Color% present, System::Drawing::Color% wrong) {
    std::ifstream file("settings.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("correctColor=") == 0) {
            int argb = std::stoi(line.substr(13));
            correct = System::Drawing::Color::FromArgb(argb);
        }
        else if (line.find("presentColor=") == 0) {
            int argb = std::stoi(line.substr(13));
            present = System::Drawing::Color::FromArgb(argb);
        }
        else if (line.find("wrongColor=") == 0) {
            int argb = std::stoi(line.substr(11));
            wrong = System::Drawing::Color::FromArgb(argb);
        }
    }
}

GameMode TeamAWordle::SettingsForm::LoadGameModeFromFile() {
    std::ifstream file("settings.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("gameMode=") == 0) {
            int value = std::stoi(line.substr(9));
            if (value >= 0 && value <= 3) {
                return static_cast<GameMode>(value);
            }
        }
    }
    return GameMode::Original;
}


void TeamAWordle::SettingsForm::SaveSettingsToFile(bool allowDoubleLetters, System::Drawing::Color correct, System::Drawing::Color present, System::Drawing::Color wrong, GameMode mode) {
    System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter("settings.txt");
    writer->WriteLine("allowDoubleLetters=" + allowDoubleLetters.ToString());
    writer->WriteLine("correctColor=" + correct.ToArgb());
    writer->WriteLine("presentColor=" + present.ToArgb());
    writer->WriteLine("wrongColor=" + wrong.ToArgb());
    writer->WriteLine("gameMode=" + static_cast<int>(mode).ToString());

    writer->Close();
}


