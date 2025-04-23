#include "MainForm.h"

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

    /// <summary>
    /// This helps with seting up main and calls the init function
    /// </summary>
    /// <param name="">void</param>
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

    void MainForm::OnLetterButton_Click(Object^ sender, EventArgs^ e)
    {
        if (currentCol >= 5 || currentRow >= 6) return;
        Button^ btn = safe_cast<Button^>(sender);
        gridLabels[currentRow * 5 + currentCol]->Text = btn->Text;
        currentGuess += btn->Text;
        currentCol++;
    }

    void MainForm::OnBackspaceButton_Click(Object^ sender, EventArgs^ e)
    {
        if (currentCol <= 0) return;
        currentCol--;
        gridLabels[currentRow * 5 + currentCol]->Text = String::Empty;
        currentGuess = currentGuess->Substring(0, currentGuess->Length - 1);
    }

    void MainForm::OnEnterButton_Click(Object^ sender, EventArgs^ e)
    {
        if (currentCol != 5) return;
        CheckGuess();
        currentGuess = String::Empty;
        currentCol = 0;
        currentRow++;
    }

    void MainForm::CheckGuess()
    {
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
            }
            else
            {
                lbl->BackColor = Color::LightGray;
            }
        }
    }
}

