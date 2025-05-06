#pragma once
#include "GameModeController.h"

namespace TeamAWordle {

    /// <summary>
    /// Provides a form for configuring user preferences for gameplay.
    /// </summary>
    public ref class SettingsForm : public System::Windows::Forms::Form {
    public:

        /// <summary>
        /// Loads color settings from the settings file.
        /// </summary>
        /// <param name="correct">Reference to store the correct letter color.</param>
        /// <param name="present">Reference to store the present letter color.</param>
        /// <param name="wrong">Reference to store the wrong letter color.</param>
        static void LoadColorsFromFile(System::Drawing::Color% correct, System::Drawing::Color% present, System::Drawing::Color% wrong);

        /// <summary>
        /// Loads the selected game mode from the settings file.
        /// </summary>
        /// <returns>The GameMode enum loaded from file.</returns>
        static GameMode TeamAWordle::SettingsForm::LoadGameModeFromFile();

        /// <summary>
        /// Gets the selected game mode from the combo box.
        /// </summary>
        /// <returns>The currently selected GameMode enum value.</returns>
        GameMode GetSelectedGameMode() {
            switch (cmbGameMode->SelectedIndex) {
            case 1: return GameMode::Hard;
            case 2: return GameMode::Lightning;
            case 3: return GameMode::Memory;
            default: return GameMode::Original;
            }
        }

        /// <summary>
        /// Constructs a SettingsForm with given values for initialization.
        /// </summary>
        /// <param name="allowDoubleLetters">If true, double letters are allowed.</param>
        /// <param name="currentMode">The current selected GameMode.</param>
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

            this->ClientSize = System::Drawing::Size(225, 335);
            this->Text = L"Settings";
            this->AcceptButton = okButton;
            this->CancelButton = cancelButton;
        }

        /// <summary>Returns whether double letters are allowed in guesses.</summary>
        /// <returns>True if allowed; otherwise, false.</returns>
        bool GetAllowDoubleLetters() { return chkAllowDoubleLetters->Checked; }

        /// <summary>Gets the currently selected color for correct guesses.</summary>
        /// <returns>The selected correct letter color.</returns>
        System::Drawing::Color GetCorrectColor() { return correctColor; }

        /// <summary>Gets the currently selected color for present letters.</summary>
        /// <returns>The selected present letter color.</returns>
        System::Drawing::Color GetPresentColor() { return presentColor; }

        /// <summary>Gets the currently selected color for incorrect letters.</summary>
        /// <returns>The selected wrong letter color.</returns>
        System::Drawing::Color GetWrongColor() { return wrongColor; }

        /// <summary>
        /// Loads the boolean setting for allowing double letters from the settings file.
        /// </summary>
        /// <returns>True if allowed; otherwise, false.</returns>
        static bool LoadSettingsFromFile();

        /// <summary>
        /// Saves all current settings to the settings file.
        /// </summary>
        /// <param name="allowDoubleLetters">Allow double letters setting.</param>
        /// <param name="correct">Correct color value.</param>
        /// <param name="present">Present color value.</param>
        /// <param name="wrong">Wrong color value.</param>
        /// <param name="mode">Selected GameMode.</param>
        static void SaveSettingsToFile(bool allowDoubleLetters, System::Drawing::Color correct, System::Drawing::Color present, System::Drawing::Color wrong, GameMode mode);

    protected:
        /// <summary>
        /// Destructor for the SettingsForm.
        /// </summary>
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

        /// <summary>
        /// Opens color dialog to change the correct letter color.
        /// </summary>
        void OnCorrectColor_Click(System::Object^ sender, System::EventArgs^ e) {
            System::Windows::Forms::ColorDialog^ dialog = gcnew System::Windows::Forms::ColorDialog();
            dialog->Color = correctColor;
            if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                correctColor = dialog->Color;
                btnCorrectColor->BackColor = correctColor;
            }
        }

        /// <summary>
        /// Opens color dialog to change the present letter color.
        /// </summary>
        void OnPresentColor_Click(System::Object^ sender, System::EventArgs^ e) {
            System::Windows::Forms::ColorDialog^ dialog = gcnew System::Windows::Forms::ColorDialog();
            dialog->Color = presentColor;
            if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                presentColor = dialog->Color;
                btnPresentColor->BackColor = presentColor;
            }
        }

        /// <summary>
        /// Opens color dialog to change the wrong letter color.
        /// </summary>
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
