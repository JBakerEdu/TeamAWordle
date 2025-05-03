#pragma once

namespace TeamAWordle {

    public ref class SettingsForm : public System::Windows::Forms::Form {
    public:

        static bool LoadSettingsFromFile();
        static void SaveSettingsToFile(bool allowDoubleLetters);

        SettingsForm(bool allowDoubleLetters)
        {
            InitializeComponent();
            this->chkAllowDoubleLetters->Checked = allowDoubleLetters;
        }

        bool GetAllowDoubleLetters()
        {
            return this->chkAllowDoubleLetters->Checked;
        }

    protected:
        ~SettingsForm() {}

    private:
        System::Windows::Forms::CheckBox^ chkAllowDoubleLetters;
        System::Windows::Forms::Button^ okButton;
        System::Windows::Forms::Button^ cancelButton;

        void InitializeComponent()
        {
            this->chkAllowDoubleLetters = gcnew System::Windows::Forms::CheckBox();
            this->okButton = gcnew System::Windows::Forms::Button();
            this->cancelButton = gcnew System::Windows::Forms::Button();
            this->SuspendLayout();

            this->chkAllowDoubleLetters->AutoSize = true;
            this->chkAllowDoubleLetters->Location = System::Drawing::Point(20, 20);
            this->chkAllowDoubleLetters->Text = L"Allow Double Letters";

            this->okButton->Text = L"OK";
            this->okButton->Location = System::Drawing::Point(20, 60);
            this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;

            this->cancelButton->Text = L"Cancel";
            this->cancelButton->Location = System::Drawing::Point(100, 60);
            this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;

            this->Controls->Add(this->chkAllowDoubleLetters);
            this->Controls->Add(this->okButton);
            this->Controls->Add(this->cancelButton);

            this->ClientSize = System::Drawing::Size(220, 110);
            this->Text = L"Settings";
            this->AcceptButton = this->okButton;
            this->CancelButton = this->cancelButton;

            this->ResumeLayout(false);
            this->PerformLayout();
        }
    };
}
