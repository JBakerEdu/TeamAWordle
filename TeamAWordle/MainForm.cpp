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
        array<String^>^ wordList = gcnew array<String^>{ L"APPLE", L"FRUIT", L"BIRDS" };
        Random^ rnd = gcnew Random();
        targetWord = wordList[rnd->Next(wordList->Length)];
        currentGuess = String::Empty;
        currentRow = 0;
        currentCol = 0;
    }

    MainForm::~MainForm()
    {
        if (components)
            delete components;
    }

    void MainForm::StartNewGame()
	{
		// Reset the game state
		currentRow = 0;
		currentCol = 0;
		currentGuess = String::Empty;

		// Clear the grid labels
		for (int i = 0; i < 30; i++)
		{
			gridLabels[i]->Text = String::Empty;
			gridLabels[i]->BackColor = SystemColors::Window;
		}

		// Enable/disable buttons
		enterButton->Enabled = false;
		backspaceButton->Enabled = false;

		// Select a new target word
		Random^ rnd = gcnew Random();
		array<String^>^ wordList = gcnew array<String^>{ L"APPLE", L"FRUIT", L"BIRDS" };
		targetWord = wordList[rnd->Next(wordList->Length)];
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
        CheckGuess();
        currentGuess = String::Empty;
        currentCol = 0;
        currentRow++;
        this->enterButton->Enabled = false;
        this->backspaceButton->Enabled = false;
    }

    void MainForm::CheckGuess()
    {
        bool allGreen = true;
        for (int i = 0; i < 5; i++)
        {
            Char guessChar = currentGuess[i];
            Label^ lbl = gridLabels[currentRow * 5 + i];

            if (guessChar == targetWord[i])
            {
                lbl->BackColor = Color::Green;
            }
            else if (targetWord->Contains(guessChar.ToString()))
            {
                lbl->BackColor = Color::Yellow;
                allGreen = false;
            }
            else
            {
                lbl->BackColor = Color::LightGray;
                allGreen = false;
            }
        }

        if (allGreen)
        {
            GameOver(true);
        }
        else if (currentRow == 5)
        {
            GameOver(false);
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
            ResetGame();
        else
            this->Close();
    }

    void MainForm::ResetGame()
    {
        WordList wordList("dictionary.txt");
        std::string sel = wordList.getRandomWord();
        targetWord = sel.empty()
            ? gcnew String("error")
            : gcnew String(sel.c_str());

        for (int i = 0; i < 30; i++)
        {
            gridLabels[i]->Text = String::Empty;
            gridLabels[i]->BackColor = SystemColors::Window;
        }
        currentRow = -1;
        currentCol = 0;
        currentGuess = String::Empty;

        enterButton->Enabled = false;
        backspaceButton->Enabled = false;
    }
}

