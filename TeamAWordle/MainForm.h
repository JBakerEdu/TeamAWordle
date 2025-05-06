#pragma once
#include <memory>
#include <msclr/marshal_cppstd.h>
#include "GameModeController.h"
#include "SettingsForm.h"

class GameSession;
class PlayerStats;
class UserProfile;

namespace TeamAWordle
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// MainForm is the primary interface for playing the Wordle game.
    /// </summary>
    public ref class MainForm : public Form
    {
    public:
        /// <summary>
        /// Initializes a new instance of the MainForm class with a given username.
        /// </summary>
        /// <param name="username">The username of the player.</param>
        MainForm(String^ username);

    protected:
        /// <summary>
        /// Cleans up resources used by the form.
        /// </summary>
        ~MainForm();

    private:
        /// <summary>Manages the current game session.</summary>
        GameSession* session_;

        /// <summary>Handles logic for the selected game mode.</summary>
        GameModeController* modeController_;

        /// <summary>Stores user profile data and preferences.</summary>
        UserProfile* user_;

        /// <summary>Container for the components used by the form.</summary>
        System::ComponentModel::Container^ components;

        /// <summary>The layout panel for the guess grid.</summary>
        TableLayoutPanel^ guessGridPanel;

        /// <summary>Labels representing the guess grid cells.</summary>
        array<Label^>^ gridLabels;

        /// <summary>The panel containing the virtual keyboard.</summary>
        Panel^ keyboardPanel;

        /// <summary>Array of letter buttons on the keyboard.</summary>
        array<Button^>^ letterButtons;

        /// <summary>Button used to submit a guess.</summary>
        Button^ enterButton;

        /// <summary>Button used to delete the last character in the guess.</summary>
        Button^ backspaceButton;

        /// <summary>The target word the player must guess.</summary>
        String^ targetWord;

        /// <summary>The current guess input by the player.</summary>
        String^ currentGuess;

        /// <summary>The current row index of the guess grid.</summary>
        int currentRow;

        /// <summary>The current column index of the guess grid.</summary>
        int currentCol;

        /// <summary>Indicates whether double letters are allowed in guesses.</summary>
        bool allowDoubleLetters_;

        /// <summary>Color used for correctly guessed letters.</summary>
        Color correctColor_;

        /// <summary>Color used for present but misplaced letters.</summary>
        Color presentColor_;

        /// <summary>Color used for incorrect letters.</summary>
        Color wrongColor_;

        /// <summary>List of feedback labels used in memory mode.</summary>
        Generic::List<Label^>^ memorySummaryLabels;

        /// <summary>The currently selected game mode.</summary>
        GameMode selectedMode_;

        /// <summary>Timer used for lightning mode countdowns.</summary>
        Timer^ lightningTimer_;

        /// <summary>Remaining seconds for the current lightning mode round.</summary>
        int lightningSecondsRemaining_;

        /// <summary>Label displaying the countdown timer in lightning mode.</summary>
        Label^ lightningTimerLabel_;

#pragma region Windows Form Designer generated code


        /// <summary>
    	/// Initializes all UI components and lays out controls for the MainForm.
    	/// </summary>
    	void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            this->AutoScaleMode = Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = Drawing::Size(400, 780);
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

            lightningTimerLabel_ = gcnew Label();
            lightningTimerLabel_->Text = "60s";
            lightningTimerLabel_->Font = gcnew Drawing::Font("Microsoft Sans Serif", 12, FontStyle::Bold);
            lightningTimerLabel_->ForeColor = Color::Black;
            lightningTimerLabel_->AutoSize = true;
            lightningTimerLabel_->Location = Point(23, 60);
            lightningTimerLabel_->Visible = false;
            this->Controls->Add(lightningTimerLabel_);

            lightningTimer_ = gcnew Timer();
            lightningTimer_->Interval = 1000;
            lightningTimer_->Tick += gcnew EventHandler(this, &MainForm::OnLightningTimerTick);

            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &MainForm::MainForm_KeyDown);
            this->guessGridPanel = gcnew TableLayoutPanel();
            this->guessGridPanel->ColumnCount = 5;
            this->guessGridPanel->RowCount = 12;
            this->guessGridPanel->Location = Point(20, 90);
            this->guessGridPanel->Size = Drawing::Size(360, 480);

            for (int i = 0; i < 5; i++)
            {
                this->guessGridPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 20));
            }
            for (int i = 0; i < 12; i++) {
                float height = (i % 2 == 0) ? 60.0f : 20.0f;
                this->guessGridPanel->RowStyles->Add(gcnew RowStyle(SizeType::Absolute, height));
            }

            this->gridLabels = gcnew array<Label^>(30);
            this->memorySummaryLabels = gcnew System::Collections::Generic::List<Label^>();

            for (int r = 0; r < 6; r++) {
                for (int c = 0; c < 5; c++) {
                    int idx = r * 5 + c;
                    Label^ lbl = gcnew Label();
                    lbl->BorderStyle = BorderStyle::FixedSingle;
                    lbl->Dock = DockStyle::Fill;
                    lbl->Font = gcnew Drawing::Font(L"Microsoft Sans Serif", 20);
                    lbl->TextAlign = ContentAlignment::MiddleCenter;
                    this->guessGridPanel->Controls->Add(lbl, c, r * 2);
                    this->gridLabels[idx] = lbl;
                }

                Label^ summaryLbl = gcnew Label();
                summaryLbl->Text = "Feed Back Label";
                summaryLbl->Visible = true;
                summaryLbl->AutoSize = true;
                summaryLbl->ForeColor = Color::Black;
                summaryLbl->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8);
                this->guessGridPanel->Controls->Add(summaryLbl, 0, r * 2 + 1);
                this->guessGridPanel->SetColumnSpan(summaryLbl, 5);

                this->memorySummaryLabels->Add(summaryLbl);
            }

            this->Controls->Add(this->guessGridPanel);

            this->keyboardPanel = gcnew Panel();
            this->keyboardPanel->Location = Point(20, 585);
            this->keyboardPanel->Size = Drawing::Size(360, 180);

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
                    btn->Size = Drawing::Size(30, 40);
                    btn->Location = Point(xOffset, yOffset);
                    btn->Click += gcnew EventHandler(this, &MainForm::OnLetterButton_Click);
                    this->keyboardPanel->Controls->Add(btn);
                    this->letterButtons[btnIndex++] = btn;
                    btn->TabStop = false;
                    xOffset += 30;
                }
                yOffset += 50;
            }

            this->enterButton = gcnew Button();
            this->enterButton->Text = L"Enter";
            this->enterButton->Size = Drawing::Size(60, 40);
            this->enterButton->Location = Point(0, yOffset);
            this->enterButton->Click += gcnew EventHandler(this, &MainForm::OnEnterButton_Click);
            this->keyboardPanel->Controls->Add(this->enterButton);

            this->backspaceButton = gcnew Button();
            this->backspaceButton->Text = L"<";
            this->backspaceButton->Size = Drawing::Size(60, 40);
            this->backspaceButton->Location = Point(300, yOffset);
            this->backspaceButton->Click += gcnew EventHandler(this, &MainForm::OnBackspaceButton_Click);
            this->keyboardPanel->Controls->Add(this->backspaceButton);

            this->Controls->Add(this->keyboardPanel);

        }
#pragma endregion

        /// <summary>
        /// Finds the button corresponding to a specific letter.
        /// </summary>
        /// <param name="letter">The character to find a button for.</param>
        /// <returns>The matching Button control.</returns>
        Button^ FindButtonForLetter(Char letter);

        /// <summary>
        /// Updates the keyboard button color for a given letter.
        /// </summary>
        /// <param name="letter">The letter to update.</param>
        /// <param name="newColor">The new color to apply.</param>
        void UpdateKeyboardColor(Char letter, Color newColor);

        /// <summary>
        /// Applies feedback in Memory mode based on the guess.
        /// </summary>
        /// <param name="feedback">The feedback result structure.</param>
        /// <param name="isCorrect">Whether the guess was correct.</param>
        void ApplyMemoryModeFeedback(const FeedbackResult& feedback, bool isCorrect);

        /// <summary>Resets the keyboard color states to initial.</summary>
        void ResetKeyboard();

        /// <summary>Clears feedback labels and resets their states.</summary>
        void ResetGameModesLabels();

        /// <summary>Chooses and sets a new target word for the round.</summary>
        void GetNewTargetWord();

        /// <summary>Clears the guess board labels for a new round.</summary>
        void ResetGuessedBoardLabels();

        /// <summary>
        /// Handles letter button clicks and appends letters to the guess.
        /// </summary>
        void OnLetterButton_Click(Object^ sender, EventArgs^ e);

        /// <summary>Handles the backspace button click event.</summary>
        void OnBackspaceButton_Click(Object^ sender, EventArgs^ e);

        /// <summary>Handles the enter button click event to submit guesses.</summary>
        void OnEnterButton_Click(Object^ sender, EventArgs^ e);

        /// <summary>
        /// Handles lightning timer tick to update countdown and enforce limits.
        /// </summary>
        void OnLightningTimerTick(Object^ sender, EventArgs^ e);

        /// <summary>Validates and checks the submitted guess.</summary>
        /// <returns>True if the guess was valid; otherwise, false.</returns>
        bool CheckGuess();

        /// <summary>Begins a new game round with reset state and target word.</summary>
        void StartNewGame();

        /// <summary>
        /// Ends the game and displays a win/loss message.
        /// </summary>
        /// <param name="won">True if the player won; otherwise, false.</param>
        void GameOver(bool won);


        /// <summary>Handles keyboard input.</summary>
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

        /// <summary>Handles settings button click and updates settings.</summary>
        void MainForm::OnSettings_Click(Object^ sender, EventArgs^ e) {
            SettingsForm^ settingsForm = gcnew SettingsForm(allowDoubleLetters_, selectedMode_);

            if (settingsForm->ShowDialog() == Windows::Forms::DialogResult::OK) {
                allowDoubleLetters_ = settingsForm->GetAllowDoubleLetters();
                correctColor_ = settingsForm->GetCorrectColor();
                presentColor_ = settingsForm->GetPresentColor();
                wrongColor_ = settingsForm->GetWrongColor();

                selectedMode_ = settingsForm->GetSelectedGameMode();

                if (modeController_ != nullptr) {
                    delete modeController_;
                }
                modeController_ = new GameModeController(selectedMode_);

                SettingsForm::SaveSettingsToFile(allowDoubleLetters_, correctColor_, presentColor_, wrongColor_, selectedMode_);

                MessageBox::Show("Settings saved. A new game will now begin with the new settings applied.");
                StartNewGame();
            }
            delete settingsForm;
        }

        /// <summary>Handles starting a new game.</summary>
        void OnStartNewGame_Click(Object^ sender, EventArgs^ e) {
            StartNewGame();
        }

        /// <summary>Handles ending and closing the current game.</summary>
        void OnEndGame_Click(Object^ sender, EventArgs^ e) {
            this->Close();
        }
    };
}