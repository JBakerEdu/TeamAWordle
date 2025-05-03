#pragma once
#include <memory>
#include <msclr/marshal_cppstd.h>
#include "WordList.h"
#include "GuessValidator.h"
#include "SettingsForm.h"

class GameSession;

namespace TeamAWordle
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Summary for MainForm
    /// </summary>
    public ref class MainForm : public Form
    {
    public:
        MainForm(void);

    protected:
        ~MainForm();

    private:
        GameSession* session_;

        System::ComponentModel::Container^ components;

        TableLayoutPanel^ guessGridPanel;
        array<Label^>^ gridLabels;
        Panel^ keyboardPanel;
        array<Button^>^ letterButtons;
        Button^ enterButton;
        Button^ backspaceButton;
        String^ targetWord;
        String^ currentGuess;
        int currentRow;
        int currentCol;
        bool allowDoubleLetters_;
        System::Drawing::Color correctColor_;
        System::Drawing::Color presentColor_;
        System::Drawing::Color wrongColor_;


#pragma region Windows Form Designer generated code

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(400, 650);
            this->Text = L"Wordle Game Baker and Klamfoth";

            Panel^ navBar = gcnew Panel();
            navBar->Dock = DockStyle::Top;
            navBar->Height = 50;
            navBar->BackColor = SystemColors::ControlDark;

            Button^ btnStartNewGame = gcnew Button();
            btnStartNewGame->Text = "New Game";
            btnStartNewGame->Location = Point(10, 10);
            btnStartNewGame->Size = Drawing::Size(90, 30);
            btnStartNewGame->Click += gcnew EventHandler(this, &MainForm::OnStartNewGame_Click);

            Button^ btnEndGame = gcnew Button();
            btnEndGame->Text = "End Game";
            btnEndGame->Location = Point(110, 10);
            btnEndGame->Size = Drawing::Size(90, 30);
            btnEndGame->Click += gcnew EventHandler(this, &MainForm::OnEndGame_Click);

            Button^ btnSettings = gcnew Button();
            btnSettings->Text = "Settings";
            btnSettings->Size = Drawing::Size(90, 30);
            btnSettings->Location = Point(300, 10);
            btnSettings->Click += gcnew EventHandler(this, &MainForm::OnSettings_Click);

            navBar->Controls->Add(btnStartNewGame);
            navBar->Controls->Add(btnEndGame);
            navBar->Controls->Add(btnSettings);
            this->Controls->Add(navBar);

            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &MainForm::MainForm_KeyDown);
            this->guessGridPanel = gcnew TableLayoutPanel();
            this->guessGridPanel->ColumnCount = 5;
            this->guessGridPanel->RowCount = 6;
            this->guessGridPanel->Location = System::Drawing::Point(20, 70);
            this->guessGridPanel->Size = System::Drawing::Size(360, 360);
            for (int i = 0; i < 5; i++) this->guessGridPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 20));
            for (int i = 0; i < 6; i++) this->guessGridPanel->RowStyles->Add(gcnew RowStyle(SizeType::Percent, 16.66F));
            this->gridLabels = gcnew array<Label^>(30);
            for (int r = 0; r < 6; r++)
            {
                for (int c = 0; c < 5; c++)
                {
                    int idx = r * 5 + c;
                    Label^ lbl = gcnew Label();
                    lbl->BorderStyle = BorderStyle::FixedSingle;
                    lbl->Dock = DockStyle::Fill;
                    lbl->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20);
                    lbl->TextAlign = ContentAlignment::MiddleCenter;
                    this->guessGridPanel->Controls->Add(lbl, c, r);
                    this->gridLabels[idx] = lbl;
                }
            }
            this->Controls->Add(this->guessGridPanel);

            this->keyboardPanel = gcnew Panel();
            this->keyboardPanel->Location = System::Drawing::Point(20, 450);
            this->keyboardPanel->Size = System::Drawing::Size(360, 180);

            array<String^>^ rows = gcnew array<String^>{ L"QWERTYUIOP", L"ASDFGHJKL", L"ZXCVBNM" };
            this->letterButtons = gcnew array<Button^>(26);
            int btnIndex = 0;
            int yOffset = 0;
            int panelWidth = this->keyboardPanel->Width;
            for each (String ^ rowText in rows)
            {
                int rowLength = rowText->Length;
                int xOffset = (panelWidth - rowLength * 30) / 2;
                for each (Char ch in rowText)
                {
                    Button^ btn = gcnew Button();
                    btn->Text = ch.ToString();
                    btn->Size = System::Drawing::Size(30, 40);
                    btn->Location = System::Drawing::Point(xOffset, yOffset);
                    btn->Click += gcnew System::EventHandler(this, &MainForm::OnLetterButton_Click);
                    this->keyboardPanel->Controls->Add(btn);
                    this->letterButtons[btnIndex++] = btn;
                    btn->TabStop = false;
                    xOffset += 30;
                }
                yOffset += 50;
            }

            this->enterButton = gcnew Button();
            this->enterButton->Text = L"Enter";
            this->enterButton->Size = System::Drawing::Size(60, 40);
            this->enterButton->Location = System::Drawing::Point(0, yOffset);
            this->enterButton->Click += gcnew System::EventHandler(this, &MainForm::OnEnterButton_Click);
            this->keyboardPanel->Controls->Add(this->enterButton);

            this->backspaceButton = gcnew Button();
            this->backspaceButton->Text = L"<";
            this->backspaceButton->Size = System::Drawing::Size(60, 40);
            this->backspaceButton->Location = System::Drawing::Point(300, yOffset);
            this->backspaceButton->Click += gcnew System::EventHandler(this, &MainForm::OnBackspaceButton_Click);
            this->keyboardPanel->Controls->Add(this->backspaceButton);

            this->Controls->Add(this->keyboardPanel);

        }
#pragma endregion

        Button^ FindButtonForLetter(Char letter);
        void UpdateKeyboardColor(Char letter, Color newColor);
        void ResetKeyboardColors();
        void OnLetterButton_Click(Object^ sender, EventArgs^ e);
        void OnBackspaceButton_Click(Object^ sender, EventArgs^ e);
        void OnEnterButton_Click(Object^ sender, EventArgs^ e);
        bool CheckGuess();
        void StartNewGame();
        void GameOver(bool won);
        void MainForm_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            String^ keyStr = e->KeyCode.ToString();
            if (keyStr->Length == 1 && Char::IsLetter(keyStr[0]))
            {
                keyStr = keyStr->ToUpper();
                for each (Button ^ btn in letterButtons)
                {
                    if (btn->Text->Equals(keyStr))
                    {
                        OnLetterButton_Click(btn, EventArgs::Empty);
                        e->Handled = true;
                        return;
                    }
                }
            }
            else if (e->KeyCode == Keys::Enter)
            {
                OnEnterButton_Click(this, EventArgs::Empty);
                e->Handled = true;
                return;
            }
            else if (e->KeyCode == Keys::Back)
            {
                OnBackspaceButton_Click(this, EventArgs::Empty);
                e->Handled = true;
                return;
            }
            e->SuppressKeyPress = true;
        }

        void MainForm::OnSettings_Click(Object^ sender, EventArgs^ e) {
            SettingsForm^ settingsForm = gcnew SettingsForm(allowDoubleLetters_);

            if (settingsForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                allowDoubleLetters_ = settingsForm->GetAllowDoubleLetters();

                // THIS IS REQUIRED
                correctColor_ = settingsForm->GetCorrectColor();
                presentColor_ = settingsForm->GetPresentColor();
                wrongColor_ = settingsForm->GetWrongColor();

                SettingsForm::SaveSettingsToFile(
                    allowDoubleLetters_,
                    correctColor_,
                    presentColor_,
                    wrongColor_
                );

                MessageBox::Show("Settings saved.");
            }

            delete settingsForm;
        }


        void OnStartNewGame_Click(Object^ sender, EventArgs^ e) {
            StartNewGame();
        }

        void OnEndGame_Click(Object^ sender, EventArgs^ e) {
            this->Close();
        }
    };
}