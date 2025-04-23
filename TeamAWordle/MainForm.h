#pragma once

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

#pragma region Windows Form Designer generated code

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(400, 600);
            this->Text = L"Wordle Game Baker and Klamforth";
            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &MainForm::MainForm_KeyDown);
            this->guessGridPanel = gcnew TableLayoutPanel();
            this->guessGridPanel->ColumnCount = 5;
            this->guessGridPanel->RowCount = 6;
            this->guessGridPanel->Location = System::Drawing::Point(20, 20);
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
            this->keyboardPanel->Location = System::Drawing::Point(20, 400);
            this->keyboardPanel->Size = System::Drawing::Size(360, 180);

            array<String^>^ rows = gcnew array<String^>{ L"QWERTYUIOP", L"ASDFGHJKL", L"ZXCVBNM" };
            this->letterButtons = gcnew array<Button^>(26);
            int btnIndex = 0;
            int yOffset = 0;
            for each (String ^ rowText in rows)
            {
                int xOffset = 0;
                for each (Char ch in rowText)
                {
                    Button^ btn = gcnew Button();
                    btn->Text = ch.ToString();
                    btn->Size = System::Drawing::Size(30, 40);
                    btn->Location = System::Drawing::Point(xOffset, yOffset);
                    btn->Click += gcnew System::EventHandler(this, &MainForm::OnLetterButton_Click);
                    this->keyboardPanel->Controls->Add(btn);
                    this->letterButtons[btnIndex++] = btn;
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

        void OnLetterButton_Click(Object^ sender, EventArgs^ e);
        void OnBackspaceButton_Click(Object^ sender, EventArgs^ e);
        void OnEnterButton_Click(Object^ sender, EventArgs^ e);
        void CheckGuess();
        void ResetGame();
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
    };
}