#include "MainForm.h"
#include "GuessValidator.h"
#include <msclr/marshal_cppstd.h>
#include "GameSession.h"

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
        selectedMode_ = SettingsForm::LoadGameModeFromFile();
        modeController_ = new GameModeController(selectedMode_);

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

        if (modeController_ != nullptr) {
            delete modeController_;
            modeController_ = nullptr;
        }

        if (components != nullptr) {
            delete components;
            components = nullptr;
        }
    }

    void MainForm::StartNewGame()
    {
        if (session_ != nullptr) {
            delete session_;
            session_ = nullptr;
        }
        if (modeController_ != nullptr) {
            delete modeController_;
            modeController_ = nullptr;
        }
        modeController_ = new GameModeController(selectedMode_);

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
        std::string tempTarget = session_->getTargetWord();
        String^ upperCase = gcnew String(tempTarget.c_str());
        targetWord = upperCase->ToUpper();
        this->Tag = targetWord;
        enterButton->Enabled = false;
        backspaceButton->Enabled = false;

        for each (Label ^ lbl in memorySummaryLabels) {
            lbl->Text = "";
            lbl->Visible = false;
        }

        if (selectedMode_ == GameMode::Lightning) {
            lightningSecondsRemaining_ = 60;
            lightningTimerLabel_->Text = "Time: 60s";
            lightningTimerLabel_->ForeColor = System::Drawing::Color::Black;
            lightningTimerLabel_->Visible = true;
            lightningTimer_->Start();
        }
        else {
            lightningTimer_->Stop();
            lightningTimerLabel_->Visible = false;
        }





        ///This will need to be in consol not here.... should use ifDef
        MessageBox::Show("DEBUG Target: " + targetWord);







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

    bool MainForm::CheckGuess() {
        if (currentGuess->Length != 5)
            return false;

        String^ guessStr = currentGuess;
        String^ targetStr = targetWord;

        std::string guess = msclr::interop::marshal_as<std::string>(guessStr->ToLowerInvariant());
        std::string target = msclr::interop::marshal_as<std::string>(targetStr->ToLowerInvariant());

        FeedbackResult feedback = modeController_->EvaluateGuess(guess, target);

        if (modeController_->GetMode() == GameMode::Memory) {
            std::string guessStd = msclr::interop::marshal_as<std::string>(currentGuess->ToLowerInvariant());
            std::string targetStd = msclr::interop::marshal_as<std::string>(targetWord->ToLowerInvariant());
            bool isCorrect = (guessStd == targetStd);

            ApplyMemoryModeFeedback(feedback, isCorrect);
        }

        else {
            for (int i = 0; i < 5; ++i) {
                Label^ cell = gridLabels[currentRow * 5 + i];
                Color newColor;

                switch (feedback.perLetterColors[i]) {
                case 2: newColor = correctColor_; break;
                case 1: newColor = presentColor_; break;
                default: newColor = wrongColor_; break;
                }

                cell->BackColor = newColor;
                UpdateKeyboardColor(currentGuess[i], newColor);
            }
        }

        if (guess == target || currentRow == 5) {
            if (selectedMode_ == GameMode::Lightning) {
                lightningTimer_->Stop();
            }
            GameOver(guess == target);
            return true;
        }

        return false;
    }

    void MainForm::ApplyMemoryModeFeedback(const FeedbackResult& feedback, bool isCorrect) {
        if (isCorrect) {
            for (int i = 0; i < 5; ++i) {
                Label^ cell = gridLabels[currentRow * 5 + i];
                cell->BackColor = correctColor_;
                UpdateKeyboardColor(currentGuess[i], correctColor_);
            }
        }
        else {
            if (currentRow < memorySummaryLabels->Count) {
                Label^ summaryLabel = memorySummaryLabels[currentRow];
                summaryLabel->Text = gcnew String(feedback.memorySummary.c_str());
                summaryLabel->Visible = true;
            }
        }
    }

    void MainForm::OnLightningTimerTick(Object^ sender, EventArgs^ e) {
        lightningSecondsRemaining_--;

        if (lightningSecondsRemaining_ <= 0) {
            lightningTimer_->Stop();

            lightningTimerLabel_->Text = "Time is up!";
            GameOver(false);
            return;
        }

        if (lightningSecondsRemaining_ <= 10) {
            lightningTimerLabel_->ForeColor = Color::Red;
        }

        lightningTimerLabel_->Text = "Time: " + lightningSecondsRemaining_.ToString() + "s";
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

