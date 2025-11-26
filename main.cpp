#include <iostream>
#include "BoardGame_Classes.h"
#include "SOS_Board.h"
#include "SOS_UI.h"


#include "NumericalTicTacToe.h" // Lazem ykon nafs esm el file el .h 3andik
#include "miser.h"              // Lazem ykon nafs esm el file el .h 3andik

using namespace std;

//===================== PLAY SUS GAME =====================//
void playSOSGame() {
    SOS_UI ui;

    string name1, name2;
    cout << "Enter Player 1 name (uses S): ";
    cin >> name1;

    cout << "Enter Player 2 name (uses U): ";
    cin >> name2;

    Player<char>* p1 = ui.create_player(name1, 'S', PlayerType::HUMAN);
    Player<char>* p2 = ui.create_player(name2, 'U', PlayerType::HUMAN);

    Player<char>* players[2] = { p1, p2 };

    SOS_Board board;
    GameManager<char> game(&board, players, &ui);

    game.run();

    cout << "\nGame Over!\n";

    delete p1;
    delete p2;
}

//=========================== 5x5 TicTacToe ===========================//
void play5x5TicTacToeGame() {
    // Here is 5x5
}

int main() {
    int choice;

    while (true) {
        cout << "\n====================================\n";
        cout << "       GAME SELECTION MENU          \n";
        cout << "====================================\n";
        cout << "1. Play Numerical Tic-Tac-Toe\n";
        cout << "2. Play SUS Game\n";
        cout << "3. Play 5x5 TicTacToe Game\n";
        cout << "4. Play Misere (Miser) Tic-Tac-Toe\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        if (choice == 1) {
            // --- NUMERICAL GAME ---
            cout << "\n--- Starting Numerical Tic-Tac-Toe ---\n";
            Board<int>* board = new NumericalBoard();
            UI<int>* ui = new NumericalUI();

            Player<int>** players = ui->setup_players();
            GameManager<int> game(board, players, ui);
            game.run();

            // Clean up
            delete board; delete ui;
            delete players[0]; delete players[1]; delete[] players;
        }
        else if (choice == 2) {
            // --- SUS GAME ---
            cout << "\n--- Starting SUS Game ---\n";
            playSOSGame();
        }
        else if (choice == 3) {
            // --- 5x5 TIC TAC TOE GAME ---
            cout << "\n--- Starting 5x5 Tic-Tac-Toe ---\n";
            play5x5TicTacToeGame();
        }
        else if (choice == 4) {
            // --- 5x5 TIC TAC TOE GAME ---
            cout << "\n--- Starting 5x5 Tic-Tac-Toe ---\n";
            play5x5TicTacToeGame();
        }
        else if (choice == 5) {
            // --- MISER GAME ---
            cout << "\n--- Starting Misere Tic-Tac-Toe ---\n";
            // Check en esm el class 'miser' zay ma enta katbah f file miser.h
            Board<char>* board = new miser();
            UI<char>* ui = new MiserUI();

            Player<char>** players = ui->setup_players();
            GameManager<char> game(board, players, ui);
            game.run();

            // Clean up
            delete board; delete ui;
            delete players[0]; delete players[1]; delete[] players;
        }
        else if (choice == 5) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}

// #include <iostream>
// #include "BoardGame_Classes.h"
// #include "XO_Board.h"
// #include "XO_UI.h"
// #include "SOS_Board.h"
// #include "SOS_UI.h"
// #include "XO_Classes.h"
// #include "5x5TicTacToe_Board.h"
// #include "5x5TicTacToe_UI.h"
//
// using namespace std;
//
// void displayMainMenu() {
//     cout << "\n===== MAIN MENU =====\n";
//     cout << "1. Numerical Tic Tac Toe\n";
//     cout << "2. SUS Game\n";
//     cout << "3. 5x5 Tic Tac Toe\n";
//     cout << "4. Exit\n";
//     cout << "Choose (1-4): ";
// }
//
// bool confirmExit() {
//     char c;
//     cout << "Are you sure you want to exit? (y/n): ";
//     cin >> c;
//     return (c == 'y' || c == 'Y');
// }
//
// int getMenuChoice() {
//     int choice;
//     cin >> choice;
//     return choice;
// }
//
//
// // ===================== PLAY SUS GAME =====================
// void playSOSGame() {
//     SOS_UI ui;
//
//     string name1, name2;
//     cout << "Enter Player 1 name (uses S): ";
//     cin >> name1;
//
//     cout << "Enter Player 2 name (uses U): ";
//     cin >> name2;
//
//     Player<char>* p1 = ui.create_player(name1, 'S', PlayerType::HUMAN);
//     Player<char>* p2 = ui.create_player(name2, 'U', PlayerType::HUMAN);
//
//     Player<char>* players[2] = { p1, p2 };
//
//     SOS_Board board;
//     GameManager<char> game(&board, players, &ui);
//
//     game.run();
//
//     cout << "\nGame Over!\n";
//
//     delete p1;
//     delete p2;
// }
//
// // =========================== 5x5 TicTacToe ============================ //
// void play5x5TicTacToeGame() {
//     FiveXFive_UI ui;
//
//     string name1, name2;
//     cout << "Enter Player 1 name (X): ";
//     cin >> name1;
//
//     cout << "Enter Player 2 name (O): ";
//     cin >> name2;
//
//     Player<char>* p1 = ui.create_player(name1, 'X', PlayerType::HUMAN);
//     Player<char>* p2 = ui.create_player(name2, 'O', PlayerType::HUMAN);
//
//     Player<char>* players[2] = { p1, p2 };
//
//     FiveXFive_Board board;
//     GameManager<char> game(&board, players, &ui);
//
//     game.run();
//
//     cout << "\nGame Over!\n";
//
//     delete p1;
//     delete p2;
// }
//
// // ========================= Numerical TicTacToe ========================= //
//
// void playNumericalGame() {
//     Numerical_UI ui;
//
//     cout << "\n=== Numerical Tic Tac Toe ===\n";
//
//     string name1, name2;
//     cout << "Enter Player 1 name (odd numbers): ";
//     cin >> name1;
//
//     cout << "Enter Player 2 name (even numbers): ";
//     cin >> name2;
//
//     Player<int>* p1 = ui.create_player(name1, 1, PlayerType::HUMAN);
//     Player<int>* p2 = ui.create_player(name2, 2, PlayerType::HUMAN);
//
//     Player<int>* players[2] = { p1, p2 };
//
//     Numerical_Board board;
//     GameManager<int> game(&board, players, &ui);
//
//     game.run();
//
//     if (board.is_win(p1))
//         cout << p1->get_name() << " wins!\n";
//     else if (board.is_win(p2))
//         cout << p2->get_name() << " wins!\n";
//     else
//         cout << "It's a Draw!\n";
//
//     delete p1;
//     delete p2;
// }
//
// // ========================= MAIN ========================= //
//
// int main() {
//     int choice;
//     bool exitProgram = false;
//
//     while (!exitProgram) {
//         displayMainMenu();
//         choice = getMenuChoice();
//
//         switch (choice) {
//         case 1:
//             playNumericalGame();
//             break;
//
//         case 3:
//             playSOSGame();
//             break;
//
//         case 4:
//             play5x5TicTacToeGame();
//             break;
//
//         case 5:
//             if (confirmExit()) exitProgram = true;
//             break;
//
//         default:
//             cout << "Invalid choice!\n";
//             break;
//         }
//     }
//
//     return 0;
// }
