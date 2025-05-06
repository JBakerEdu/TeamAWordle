#pragma once
#include "SettingsForm.h"

namespace TeamAWordle
{
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class UsernameForm : public Form
    {
    public:
        String^ EnteredUsername;
        Label^ errorLabel;

        UsernameForm()
        {
            this->Text = "Sign In to Wordle";
            this->Size = Drawing::Size(300, 200);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MinimizeBox = false;
            this->MaximizeBox = false;
            this->ShowInTaskbar = false;

            Label^ label = gcnew Label();
            label->Text = "Username:";
            label->Location = Point(10, 20);
            label->AutoSize = true;
            this->Controls->Add(label);

            TextBox^ textBox = gcnew TextBox();
            textBox->Location = Point(80, 18);
            textBox->Width = 180;
            this->Controls->Add(textBox);

            errorLabel = gcnew Label();
            errorLabel->Text = "";
            errorLabel->ForeColor = Color::Red;
            errorLabel->Location = Point(78, 42);
            errorLabel->AutoSize = true;
            this->Controls->Add(errorLabel);

            Label^ settingsLabel = gcnew Label();
            settingsLabel->Text = "Enter New Game Settings: ";
            settingsLabel->Location = Point(30, 74);
            settingsLabel->AutoSize = true;
            this->Controls->Add(settingsLabel);

            Button^ settingsButton = gcnew Button();
            settingsButton->Text = "Settings";
            settingsButton->Location = Point(170, 70);
            settingsButton->Click += gcnew EventHandler(this, &UsernameForm::OnSettingsClicked);
            this->Controls->Add(settingsButton);

            Label^ settingsLabelWarning = gcnew Label();
            settingsLabelWarning->Text = "Game Settings persist from last game play.";
            settingsLabelWarning->ForeColor = Color::Red;
            settingsLabelWarning->Location = Point(38, 96);
            settingsLabelWarning->AutoSize = true;
            this->Controls->Add(settingsLabelWarning);

            Button^ okButton = gcnew Button();
            okButton->Text = "Start Game";
            okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
            okButton->Location = Point(100, 130);
            this->AcceptButton = okButton;
            this->Controls->Add(okButton);

            this->FormClosing += gcnew FormClosingEventHandler(this, &UsernameForm::OnFormClosing);
            this->textBox = textBox;
        }

    private:
        TextBox^ textBox;

        void OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
        {
            if (this->DialogResult == System::Windows::Forms::DialogResult::OK)
            {
                if (String::IsNullOrWhiteSpace(textBox->Text))
                {
                    errorLabel->Text = "Username cannot be empty.";
                    e->Cancel = true;
                    return;
                }

                errorLabel->Text = "";
                EnteredUsername = textBox->Text->Trim();
            }
        }

        void OnSettingsClicked(Object^ sender, EventArgs^ e)
        {
            bool allowDoubleLetters = SettingsForm::LoadSettingsFromFile();
            GameMode mode = SettingsForm::LoadGameModeFromFile();

            SettingsForm^ settingsForm = gcnew SettingsForm(allowDoubleLetters, mode);

            if (settingsForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                bool newAllowDoubleLetters = settingsForm->GetAllowDoubleLetters();
                GameMode newMode = settingsForm->GetSelectedGameMode();

                SettingsForm::SaveSettingsToFile(
                    newAllowDoubleLetters,
                    settingsForm->GetCorrectColor(),
                    settingsForm->GetPresentColor(),
                    settingsForm->GetWrongColor(),
                    newMode
                );
                MessageBox::Show("Settings saved.");
            }
            delete settingsForm;
        }
    };
}
