#pragma once

namespace TeamAWordle {

    public ref class SettingsForm : public System::Windows::Forms::Form {
    public:
        static void LoadColorsFromFile(System::Drawing::Color% correct, System::Drawing::Color% present, System::Drawing::Color% wrong);

        SettingsForm(bool allowDoubleLetters) {
            LoadColorsFromFile(correctColor, presentColor, wrongColor);


            // UI Layout
            chkAllowDoubleLetters = gcnew System::Windows::Forms::CheckBox();
            chkAllowDoubleLetters->AutoSize = true;
            chkAllowDoubleLetters->Location = System::Drawing::Point(20, 20);
            chkAllowDoubleLetters->Text = L"Allow Double Letters";
            chkAllowDoubleLetters->Checked = allowDoubleLetters;

            btnCorrectColor = gcnew System::Windows::Forms::Button();
            btnCorrectColor->Text = L"Correct Letter Color";
            btnCorrectColor->Location = System::Drawing::Point(20, 60);
            btnCorrectColor->Size = System::Drawing::Size(180, 30);
            btnCorrectColor->BackColor = correctColor;
            btnCorrectColor->Click += gcnew System::EventHandler(this, &SettingsForm::OnCorrectColor_Click);

            btnPresentColor = gcnew System::Windows::Forms::Button();
            btnPresentColor->Text = L"Present Letter Color";
            btnPresentColor->Location = System::Drawing::Point(20, 100);
            btnPresentColor->Size = System::Drawing::Size(180, 30);
            btnPresentColor->BackColor = presentColor;
            btnPresentColor->Click += gcnew System::EventHandler(this, &SettingsForm::OnPresentColor_Click);

            btnWrongColor = gcnew System::Windows::Forms::Button();
            btnWrongColor->Text = L"Wrong Letter Color";
            btnWrongColor->Location = System::Drawing::Point(20, 140);
            btnWrongColor->Size = System::Drawing::Size(180, 30);
            btnWrongColor->BackColor = wrongColor;
            btnWrongColor->Click += gcnew System::EventHandler(this, &SettingsForm::OnWrongColor_Click);

            okButton = gcnew System::Windows::Forms::Button();
            okButton->Text = L"OK";
            okButton->Location = System::Drawing::Point(20, 200);
            okButton->DialogResult = System::Windows::Forms::DialogResult::OK;

            cancelButton = gcnew System::Windows::Forms::Button();
            cancelButton->Text = L"Cancel";
            cancelButton->Location = System::Drawing::Point(120, 200);
            cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;

            this->Controls->Add(chkAllowDoubleLetters);
            this->Controls->Add(btnCorrectColor);
            this->Controls->Add(btnPresentColor);
            this->Controls->Add(btnWrongColor);
            this->Controls->Add(okButton);
            this->Controls->Add(cancelButton);

            btnCorrectColor->BackColor = correctColor;
            btnPresentColor->BackColor = presentColor;
            btnWrongColor->BackColor = wrongColor;


            this->ClientSize = System::Drawing::Size(240, 260);
            this->Text = L"Settings";
            this->AcceptButton = okButton;
            this->CancelButton = cancelButton;
        }

        bool GetAllowDoubleLetters() { return chkAllowDoubleLetters->Checked; }
        System::Drawing::Color GetCorrectColor() { return correctColor; }
        System::Drawing::Color GetPresentColor() { return presentColor; }
        System::Drawing::Color GetWrongColor() { return wrongColor; }

        static bool LoadSettingsFromFile();
        static void SaveSettingsToFile(bool allowDoubleLetters, System::Drawing::Color correct, System::Drawing::Color present, System::Drawing::Color wrong);

    protected:
        ~SettingsForm() {}

    private:
        System::Windows::Forms::CheckBox^ chkAllowDoubleLetters;
        System::Windows::Forms::Button^ okButton;
        System::Windows::Forms::Button^ cancelButton;
        System::Windows::Forms::Button^ btnCorrectColor;
        System::Windows::Forms::Button^ btnPresentColor;
        System::Windows::Forms::Button^ btnWrongColor;

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
