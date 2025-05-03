#pragma once

namespace TeamAWordle
{
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing; // ? Required for Size, Point, etc.

    public ref class UsernameForm : public Form
    {
    public:
        String^ EnteredUsername;

        UsernameForm()
        {
            this->Text = "Enter Username";
            this->Size = Drawing::Size(300, 150);
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

            Button^ okButton = gcnew Button();
            okButton->Text = "OK";
            okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
            okButton->Location = Point(100, 60);
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
                    MessageBox::Show("Username cannot be empty.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    e->Cancel = true;
                    return;
                }

                EnteredUsername = textBox->Text->Trim();
            }
        }
    };
}