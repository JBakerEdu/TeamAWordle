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

void TeamAWordle::SettingsForm::SaveSettingsToFile(bool allowDoubleLetters, System::Drawing::Color correct, System::Drawing::Color present, System::Drawing::Color wrong) {
    std::ofstream file("settings.txt", std::ios::trunc);
    file << "allowDoubleLetters=" << (allowDoubleLetters ? "true" : "false") << std::endl;
    file << "correctColor=" << correct.ToArgb() << std::endl;
    file << "presentColor=" << present.ToArgb() << std::endl;
    file << "wrongColor=" << wrong.ToArgb() << std::endl;
}
