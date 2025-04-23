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

