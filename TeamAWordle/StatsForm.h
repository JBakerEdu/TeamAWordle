#pragma once

#include "PlayerStats.h"

namespace TeamAWordle
{
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

	/// <summary>
    /// Displays the player's game statistics and prompts whether they want to play again.
    /// </summary>
    public ref class StatsForm : public Form
    {
    public:

        /// <summary>
        /// Indicates whether the player wants to play another game.
        /// </summary>
        property bool PlayAgain;

        /// <summary>
        /// Constructs a new StatsForm to show end-of-game statistics.
        /// </summary>
        /// <param name="stats">The PlayerStats object containing statistics to display.</param>
        /// <param name="gameResultMessage">A message summarizing the game result (win/loss).</param>
        StatsForm(PlayerStats stats, System::String^ gameResultMessage)
        {
            this->Text = "Statistics";
            this->Size = System::Drawing::Size(300, 400);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterParent;
            this->MaximizeBox = false;
            this->MinimizeBox = false;

            TableLayoutPanel^ layout = gcnew TableLayoutPanel();
            layout->Dock = DockStyle::Fill;
            layout->RowCount = 10;
            layout->ColumnCount = 2;
            layout->AutoSize = true;
            layout->Padding = System::Windows::Forms::Padding(10);
            layout->CellBorderStyle = TableLayoutPanelCellBorderStyle::None;

            // Game result label
            Label^ resultLabel = gcnew Label();
            resultLabel->Text = gameResultMessage;
            resultLabel->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
            resultLabel->ForeColor = Color::DarkGreen;
            resultLabel->AutoSize = true;
            layout->Controls->Add(resultLabel, 0, 0);
            layout->SetColumnSpan(resultLabel, 2);

            // Spacing row
            layout->Controls->Add(gcnew Label(), 0, 1);
            layout->SetColumnSpan(layout->GetControlFromPosition(0, 1), 2);

            // Total games played
            Label^ labelGames = gcnew Label();
            labelGames->Text = "Games Played:";
            layout->Controls->Add(labelGames, 0, 2);

            Label^ valueGames = gcnew Label();
            valueGames->Text = stats.getTotalGames().ToString();
            layout->Controls->Add(valueGames, 1, 2);

            // Win %
            Label^ labelWinPct = gcnew Label();
            labelWinPct->Text = "Win %:";
            layout->Controls->Add(labelWinPct, 0, 3);

            int wins = stats.getWins();
            int games = stats.getTotalGames();
            int winPercent = (games > 0) ? (wins * 100 / games) : 0;

            Label^ valueWinPct = gcnew Label();
            valueWinPct->Text = winPercent.ToString() + "%";
            layout->Controls->Add(valueWinPct, 1, 3);

            // Current streak
            Label^ labelCurrentStreak = gcnew Label();
            labelCurrentStreak->Text = "Current Streak:";
            layout->Controls->Add(labelCurrentStreak, 0, 4);

            Label^ valueCurrentStreak = gcnew Label();
            valueCurrentStreak->Text = stats.getCurrentStreak().ToString();
            layout->Controls->Add(valueCurrentStreak, 1, 4);

            // Max streak
            Label^ labelMaxStreak = gcnew Label();
            labelMaxStreak->Text = "Max Streak:";
            layout->Controls->Add(labelMaxStreak, 0, 5);

            Label^ valueMaxStreak = gcnew Label();
            valueMaxStreak->Text = stats.getMaxStreak().ToString();
            layout->Controls->Add(valueMaxStreak, 1, 5);

            // Guess Distribution header
            Label^ labelDistHeader = gcnew Label();
            labelDistHeader->Text = "Guess Distribution:";
            layout->Controls->Add(labelDistHeader, 0, 6);

            Label^ blank = gcnew Label();
            blank->Text = "";
            layout->Controls->Add(blank, 1, 6);

            // Guess counts (1 to 6)
            for (int i = 1; i <= 6; ++i)
            {
                Label^ guessLabel = gcnew Label();
                guessLabel->Text = "  " + i.ToString() + (i == 1 ? " guess:" : " guesses:");
                layout->Controls->Add(guessLabel, 0, 6 + i);

                Label^ guessValue = gcnew Label();
                guessValue->Text = stats.getGuessCount(i).ToString();
                layout->Controls->Add(guessValue, 1, 6 + i);
            }

            // Question prompt
            Label^ question = gcnew Label();
            question->Text = "Would you like to play again?";
            question->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            question->ForeColor = Color::Black;
            question->AutoSize = true;
            question->Margin = System::Windows::Forms::Padding(10, 20, 10, 5);
            layout->Controls->Add(question, 0, 13);
            layout->SetColumnSpan(question, 2);

            // Button Panel
            FlowLayoutPanel^ buttons = gcnew FlowLayoutPanel();
            buttons->FlowDirection = FlowDirection::LeftToRight;
            buttons->Dock = DockStyle::Bottom;
            buttons->Padding = System::Windows::Forms::Padding(10);
            buttons->AutoSize = true;

            Button^ yesBtn = gcnew Button();
            yesBtn->Text = "Yes";
            yesBtn->Width = 100;
            yesBtn->Click += gcnew EventHandler(this, &StatsForm::OnYesClicked);

            Button^ noBtn = gcnew Button();
            noBtn->Text = "No";
            noBtn->Width = 100;
            noBtn->Click += gcnew EventHandler(this, &StatsForm::OnNoClicked);

            buttons->Controls->Add(yesBtn);
            buttons->Controls->Add(noBtn);

            this->Controls->Add(layout);
            this->Controls->Add(buttons);
            this->Controls->Add(layout);
        }
    private:

        /// <summary>
        /// Helper method to create a basic styled label with specified text.
        /// </summary>
        /// <param name="text">The label text to display.</param>
        /// <returns>A configured Label object.</returns>
    	Label^ CreateLabel(String^ text)
    	{
    		Label^ lbl = gcnew Label();
    		lbl->Text = text;
    		lbl->AutoSize = true;
    		lbl->Font = gcnew System::Drawing::Font("Segoe UI", 9);
    		return lbl;
    	}

        /// <summary>
        /// Handles the event when the user clicks "Yes" to play again.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">Event data.</param>
        void OnYesClicked(Object^ sender, EventArgs^ e)
        {
            this->PlayAgain = true;
            this->Close();
        }

        /// <summary>
        /// Handles the event when the user clicks "No" to exit.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">Event data.</param>
        void OnNoClicked(Object^ sender, EventArgs^ e)
        {
            this->PlayAgain = false;
            this->Close();
        }
    };;
}