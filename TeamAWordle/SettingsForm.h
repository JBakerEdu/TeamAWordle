#pragma once
#include "GameModeController.h"

namespace TeamAWordle {

    public ref class SettingsForm : public System::Windows::Forms::Form {
    public:
        static void LoadColorsFromFile(System::Drawing::Color% correct, System::Drawing::Color% present, System::Drawing::Color% wrong);
        static GameMode TeamAWordle::SettingsForm::LoadGameModeFromFile();

        GameMode GetSelectedGameMode() {
            switch (cmbGameMode->SelectedIndex) {
            case 1: return GameMode::Hard;
            case 2: return GameMode::Lightning;
            case 3: return GameMode::Memory;
            default: return GameMode::Original;
            }
        }

        SettingsForm(bool allowDoubleLetters, GameMode currentMode) {
            LoadColorsFromFile(correctColor, presentColor, wrongColor);

            chkAllowDoubleLetters = gcnew System::Windows::Forms::CheckBox();
            chkAllowDoubleLetters->AutoSize = true;
            chkAllowDoubleLetters->Location = System::Drawing::Point(20, 20);
            chkAllowDoubleLetters->Text = L"Allow Double Letters";
            chkAllowDoubleLetters->Checked = allowDoubleLetters;

            System::Windows::Forms::Label^ lblGameMode = gcnew System::Windows::Forms::Label();
            lblGameMode->Text = L"Select Game Mode:";
            lblGameMode->Location = System::Drawing::Point(20, 55);
            lblGameMode->AutoSize = true;
            this->Controls->Add(lblGameMode);

            cmbGameMode = gcnew System::Windows::Forms::ComboBox();
            cmbGameMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            cmbGameMode->Location = System::Drawing::Point(20, 75);
            cmbGameMode->Size = System::Drawing::Size(180, 25);
            cmbGameMode->Items->AddRange(gcnew cli::array<Object^> {
                "Original", "Hard", "Lightning", "Memory"
            });
            cmbGameMode->SelectedIndex = static_cast<int>(currentMode);
            this->Controls->Add(cmbGameMode);

            System::Windows::Forms::Label^ lblColorPalette = gcnew System::Windows::Forms::Label();
            lblColorPalette->Text = L"Select Color Palette:";
            lblColorPalette->Location = System::Drawing::Point(20, 115);
            lblColorPalette->AutoSize = true;
            this->Controls->Add(lblColorPalette);

            btnCorrectColor = gcnew System::Windows::Forms::Button();
            btnCorrectColor->Text = L"Correct Letter Color";
            btnCorrectColor->Location = System::Drawing::Point(20, 135);
            btnCorrectColor->Size = System::Drawing::Size(180, 30);
            btnCorrectColor->BackColor = correctColor;
            btnCorrectColor->Click += gcnew System::EventHandler(this, &SettingsForm::OnCorrectColor_Click);

            btnPresentColor = gcnew System::Windows::Forms::Button();
            btnPresentColor->Text = L"Present Letter Color";
            btnPresentColor->Location = System::Drawing::Point(20, 180);
            btnPresentColor->Size = System::Drawing::Size(180, 30);
            btnPresentColor->BackColor = presentColor;
            btnPresentColor->Click += gcnew System::EventHandler(this, &SettingsForm::OnPresentColor_Click);

            btnWrongColor = gcnew System::Windows::Forms::Button();
            btnWrongColor->Text = L"Wrong Letter Color";
            btnWrongColor->Location = System::Drawing::Point(20, 225);
            btnWrongColor->Size = System::Drawing::Size(180, 30);
            btnWrongColor->BackColor = wrongColor;
            btnWrongColor->Click += gcnew System::EventHandler(this, &SettingsForm::OnWrongColor_Click);

            okButton = gcnew System::Windows::Forms::Button();
            okButton->Text = L"OK";
            okButton->Location = System::Drawing::Point(20, 275);
            okButton->DialogResult = System::Windows::Forms::DialogResult::OK;

            cancelButton = gcnew System::Windows::Forms::Button();
            cancelButton->Text = L"Cancel";
            cancelButton->Location = System::Drawing::Point(120, 275);
            cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;

            System::Windows::Forms::Label^ lblGameWarning = gcnew System::Windows::Forms::Label();
            lblGameWarning->ForeColor = System::Drawing::Color::Red;
            lblGameWarning->Text = L"Warning: Will Start New Game On Save!!!";
            lblGameWarning->Location = System::Drawing::Point(10, 305);
            lblGameWarning->AutoSize = true;
            this->Controls->Add(lblGameWarning);

            this->Controls->Add(chkAllowDoubleLetters);
            this->Controls->Add(btnCorrectColor);
            this->Controls->Add(btnPresentColor);
            this->Controls->Add(btnWrongColor);
            this->Controls->Add(okButton);
            this->Controls->Add(cancelButton);

            btnCorrectColor->BackColor = correctColor;
            btnPresentColor->BackColor = presentColor;
            btnWrongColor->BackColor = wrongColor;

            this->ClientSize = System::Drawing::Size(240, 335);
            this->Text = L"Settings";
            this->AcceptButton = okButton;
            this->CancelButton = cancelButton;
        }

        bool GetAllowDoubleLetters() { return chkAllowDoubleLetters->Checked; }
        System::Drawing::Color GetCorrectColor() { return correctColor; }
        System::Drawing::Color GetPresentColor() { return presentColor; }
        System::Drawing::Color GetWrongColor() { return wrongColor; }

        static bool LoadSettingsFromFile();
        static void SaveSettingsToFile(bool allowDoubleLetters, System::Drawing::Color correct, System::Drawing::Color present, System::Drawing::Color wrong, GameMode mode);

    protected:
        ~SettingsForm() {}

    private:
        System::Windows::Forms::CheckBox^ chkAllowDoubleLetters;
        System::Windows::Forms::Button^ okButton;
        System::Windows::Forms::Button^ cancelButton;
        System::Windows::Forms::Button^ btnCorrectColor;
        System::Windows::Forms::Button^ btnPresentColor;
        System::Windows::Forms::Button^ btnWrongColor;
        System::Windows::Forms::ComboBox^ cmbGameMode;
        System::Drawing::Color correctColor;
        System::Drawing::Color presentColor;
        System::Drawing::Color wrongColor;

        void OnCorrectColor_Click(System::Object^ sender, System::EventArgs^ e) {
            System::Windows::Forms::ColorDialog^ dialog = gcnew System::Windows::Forms::ColorDialog();
            dialog->Color = correctColor;
            if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                correctColor = dialog->Color;
                btnCorrectColor->BackColor = correctColor;
            }
        }

        void OnPresentColor_Click(System::Object^ sender, System::EventArgs^ e) {
            System::Windows::Forms::ColorDialog^ dialog = gcnew System::Windows::Forms::ColorDialog();
            dialog->Color = presentColor;
            if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                presentColor = dialog->Color;
                btnPresentColor->BackColor = presentColor;
            }
        }

        void OnWrongColor_Click(System::Object^ sender, System::EventArgs^ e) {
            System::Windows::Forms::ColorDialog^ dialog = gcnew System::Windows::Forms::ColorDialog();
            dialog->Color = wrongColor;
            if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                wrongColor = dialog->Color;
                btnWrongColor->BackColor = wrongColor;
            }
        }
    };
}
