#include "MainForm.h"
#include "WordList.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TeamAWordle::MainForm form;
	Application::Run(% form);

	return 0;
}

namespace TeamAWordle {

    /**
	MainForm::MainForm(void)
    {
        InitializeComponent();
        WordList wordList("dictionary.txt");
        std::string sel = wordList.getRandomWord();
        if (sel.empty()) {
            MessageBox::Show("Failed to load dictionary or select a word.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            this->Close();
            return;
        }

        MessageBox::Show("The target word is: " + gcnew String(sel.c_str()), "Debug", MessageBoxButtons::OK, MessageBoxIcon::Information);

        targetWord = gcnew String(sel.c_str());
        currentGuess = String::Empty;
        currentRow = 0;
        currentCol = 0;
        this->enterButton->Enabled = false;
        this->backspaceButton->Enabled = false;
    }
    */
    
    MainForm::MainForm(void)
    {
        InitializeComponent();
        StartNewGame();
    }

    MainForm::~MainForm()
    {
        if (components)
            delete components;
    }

    void MainForm::StartNewGame()
	{
		currentRow = 0;
		currentCol = 0;
		currentGuess = String::Empty;

		for (int i = 0; i < 30; i++)
		{
			gridLabels[i]->Text = String::Empty;
			gridLabels[i]->BackColor = SystemColors::Window;
		}
		enterButton->Enabled = false;
		backspaceButton->Enabled = false;
		Random^ rnd = gcnew Random();
		array<String^>^ wordList = gcnew array<String^>{ L"APPLE", L"FRUIT", L"BIRDS" };
		targetWord = wordList[rnd->Next(wordList->Length)];
        ResetKeyboardColors();
	}

    void MainForm::OnLetterButton_Click(Object^ sender, EventArgs^ e)
    {
        if (currentCol >= 5 || currentRow >= 6) return;
        Button^ btn = safe_cast<Button^>(sender);
        gridLabels[currentRow * 5 + currentCol]->Text = btn->Text;
        currentGuess += btn->Text;
        currentCol++;
        this->enterButton->Enabled = (currentCol == 5);
        this->backspaceButton->Enabled = (currentCol > 0);
        this->ActiveControl = nullptr;
    }

    void MainForm::OnBackspaceButton_Click(Object^ sender, EventArgs^ e)
    {
        if (currentCol <= 0) return;
        currentCol--;
        gridLabels[currentRow * 5 + currentCol]->Text = String::Empty;
        currentGuess = currentGuess->Substring(0, currentGuess->Length - 1);
        this->enterButton->Enabled = false;
        this->backspaceButton->Enabled = (currentCol > 0);
    }

    void MainForm::OnEnterButton_Click(Object^ sender, EventArgs^ e)
    {
        if (currentCol != 5) return;
        bool gameEnded = CheckGuess();
        if (gameEnded) {
            return;
        }
        currentGuess = String::Empty;
        currentCol = 0;
        ++currentRow;

        ActiveControl = nullptr;
        enterButton->Enabled = false;
        backspaceButton->Enabled = false;
    }

    bool MainForm::CheckGuess()
    {
        bool allGreen = true;

        for (int i = 0; i < 5; ++i)
        {
            Char guessChar = currentGuess[i];
            Label^ lbl = gridLabels[currentRow * 5 + i];
            Color color;

            if (guessChar == targetWord[i]) {
                color = Color::Green;
            }
            else if (targetWord->Contains(guessChar.ToString())) {
                color = Color::Gold;
                allGreen = false;
            }
            else {
                color = Color::LightGray;
                allGreen = false;
            }

            lbl->BackColor = color;
            UpdateKeyboardColor(guessChar, color);
        }

        if (allGreen || currentRow == 5)
        {
            GameOver(allGreen);
            return true;
        }
        return false;
    }

    Button^ MainForm::FindButtonForLetter(Char letter)
    {
        for each (Button ^ btn in letterButtons)
        {
            if (btn != nullptr && btn->Text->Equals(letter.ToString()))
                return btn;
        }
        return nullptr;
    }

    void MainForm::UpdateKeyboardColor(Char letter, Color newColor) {
        Button^ btn = FindButtonForLetter(letter);
        if (btn == nullptr) return;

        Color existingColor = btn->BackColor;

        if (existingColor == Color::Green)
            return;

        if (existingColor == Color::Gold && newColor == Color::LightGray)
            return; 

        btn->BackColor = newColor;
    }

    void MainForm::ResetKeyboardColors()
    {
        for each (Button ^ btn in letterButtons)
        {
            if (btn != nullptr)
                btn->BackColor = SystemColors::Control;
        }
    }

    void MainForm::GameOver(bool won)
    {
        String^ msg = won
            ? "Congratulations! You guessed the word.\nPlay again?"
            : "Game over — the word was: " + targetWord + "\nPlay again?";

        auto result = MessageBox::Show(
            msg,
            "Wordle",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Question);

        if (result == System::Windows::Forms::DialogResult::Yes)
            StartNewGame();
        else
            this->Close();
    }
}

