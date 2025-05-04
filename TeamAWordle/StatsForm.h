#pragma once

#include "PlayerStats.h"

namespace TeamAWordle
{
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class StatsForm : public Form
    {
    public:
        StatsForm(PlayerStats stats)
        {
            this->Text = "Statistics";
            this->Size = System::Drawing::Size(300, 300);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterParent;
            this->MaximizeBox = false;
            this->MinimizeBox = false;

            TableLayoutPanel^ layout = gcnew TableLayoutPanel();
            layout->Dock = DockStyle::Fill;
            layout->RowCount = 10;
            layout->ColumnCount = 2;
            layout->AutoSize = true;

            // Total games played
            Label^ labelGames = gcnew Label();
            labelGames->Text = "Games Played:";
            layout->Controls->Add(labelGames, 0, 0);

            Label^ valueGames = gcnew Label();
            valueGames->Text = stats.getTotalGames().ToString();
            layout->Controls->Add(valueGames, 1, 0);

            // Win %
            Label^ labelWinPct = gcnew Label();
            labelWinPct->Text = "Win %:";
            layout->Controls->Add(labelWinPct, 0, 1);

            int wins = stats.getWins();
            int games = stats.getTotalGames();
            int winPercent = (games > 0) ? (wins * 100 / games) : 0;

            Label^ valueWinPct = gcnew Label();
            valueWinPct->Text = winPercent.ToString() + "%";
            layout->Controls->Add(valueWinPct, 1, 1);

            // Current streak
            Label^ labelCurrentStreak = gcnew Label();
            labelCurrentStreak->Text = "Current Streak:";
            layout->Controls->Add(labelCurrentStreak, 0, 2);

            Label^ valueCurrentStreak = gcnew Label();
            valueCurrentStreak->Text = stats.getCurrentStreak().ToString();
            layout->Controls->Add(valueCurrentStreak, 1, 2);

            // Max streak
            Label^ labelMaxStreak = gcnew Label();
            labelMaxStreak->Text = "Max Streak:";
            layout->Controls->Add(labelMaxStreak, 0, 3);

            Label^ valueMaxStreak = gcnew Label();
            valueMaxStreak->Text = stats.getMaxStreak().ToString();
            layout->Controls->Add(valueMaxStreak, 1, 3);

            // Guess Distribution header
            Label^ labelDistHeader = gcnew Label();
            labelDistHeader->Text = "Guess Distribution:";
            layout->Controls->Add(labelDistHeader, 0, 4);

            Label^ blank = gcnew Label();
            blank->Text = "";
            layout->Controls->Add(blank, 1, 4);

            // Guess counts (1 to 6)
            for (int i = 1; i <= 6; ++i)
            {
                Label^ guessLabel = gcnew Label();
                guessLabel->Text = "  " + i.ToString() + (i == 1 ? " guess:" : " guesses:");
                layout->Controls->Add(guessLabel, 0, 4 + i);

                Label^ guessValue = gcnew Label();
                guessValue->Text = stats.getGuessCount(i).ToString();
                layout->Controls->Add(guessValue, 1, 4 + i);
            }

            this->Controls->Add(layout);
        }
    };
}