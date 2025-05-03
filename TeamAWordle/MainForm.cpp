#include "MainForm.h"
#include "WordList.h"
#include "GuessValidator.h"
#include <msclr/marshal_cppstd.h>
#include "GameSession.h"
#include "PlayerStats.h"

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
    
    MainForm::MainForm(void)
    {
        InitializeComponent();
        allowDoubleLetters_ = SettingsForm::LoadSettingsFromFile();
        SettingsForm::LoadColorsFromFile(correctColor_, presentColor_, wrongColor_);
        stats_ = new PlayerStats();

        try {
            session_ = new GameSession("dictionary.txt");
        }
        catch (const std::exception& ex) {
            MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            Close();
            return;
        }

        StartNewGame();
    }

    MainForm::~MainForm()
    {
        if (session_ != nullptr) {
            delete session_;
            session_ = nullptr;
        }

        if (components != nullptr) {
            delete components;
            components = nullptr;
        }

        delete stats_;
    }

    void MainForm::StartNewGame()
    {
        if (session_ != nullptr) {
            delete session_;
            session_ = nullptr;
        }

        try {
            session_ = new GameSession("dictionary.txt", allowDoubleLetters_);
        }
        catch (const std::exception& ex) {
            MessageBox::Show(gcnew String(ex.what()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            this->Close();
            return;
        }

        currentRow = 0;
        currentCol = 0;
        currentGuess = String::Empty;

        for (int i = 0; i < 30; i++) {
            gridLabels[i]->Text = String::Empty;
            gridLabels[i]->BackColor = SystemColors::Window;
        }

        ResetKeyboardColors();

        std::string nativeTarget = session_->getTargetWord();
        String^ upper = gcnew String(nativeTarget.c_str());
        upper = upper->ToUpper();

        this->Tag = upper;
        enterButton->Enabled = false;
        backspaceButton->Enabled = false;

        MessageBox::Show("DEBUG Target: " + upper);
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
        if (currentCol == 0) return;

    	currentCol--;
        gridLabels[currentRow * 5 + currentCol]->Text = String::Empty;
        currentGuess = currentGuess->Substring(0, currentGuess->Length - 1);

    	this->enterButton->Enabled = false;
        this->backspaceButton->Enabled = (currentCol > 0);
    }

    void MainForm::OnEnterButton_Click(Object^ sender, EventArgs^ e)
    {
        if (currentCol != 5) return;

        std::string guessStd = msclr::interop::marshal_as<std::string>(currentGuess->ToLowerInvariant());
        GuessValidationResult res = session_->validate(guessStd);

        if (res != GuessValidationResult::Valid)
        {
            String^ msg =
                (res == GuessValidationResult::NotFiveLetters)
                ? "Your guess must be exactly 5 letters (A-Z)."
                : "That word is not in the dictionary";

            MessageBox::Show(msg, "Invalid Guess", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
            return;
        }

    	bool gameEnded = CheckGuess();
        if (gameEnded) return;

        currentGuess = String::Empty;
        currentCol = 0;
        ++currentRow;

        enterButton->Enabled = false;
        backspaceButton->Enabled = false;
        ActiveControl = nullptr;
    }

    bool MainForm::CheckGuess()
    {
        bool allGreen = true;
        String^ targetUpper = safe_cast<String^>(this->Tag);

        for (int i = 0; i < 5; ++i)
        {
            Char g = currentGuess[i];
            Label^ cell = gridLabels[currentRow * 5 + i];
            Color newColor;

            if (g == targetUpper[i])
                newColor = correctColor_;
            else if (targetUpper->Contains(g.ToString()))
            {
                newColor = presentColor_;
                allGreen = false;
            }
            else
            {
                newColor = wrongColor_;
                allGreen = false;
            }
            cell->BackColor = newColor;
            UpdateKeyboardColor(g, newColor);
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

        if (existingColor.ToArgb() == correctColor_.ToArgb())
            return;

        if (existingColor.ToArgb() == presentColor_.ToArgb() && newColor.ToArgb() == wrongColor_.ToArgb())
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
        int guessesUsed = currentRow + 1;

        stats_->recordGame(won, guessesUsed);

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

