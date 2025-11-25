#include <iostream>
#include "BoardGame_Classes.h"
#include "XO_Board.h"
#include "XO_UI.h"
#include "SOS_Board.h"
#include "SOS_UI.h"
#include "XO_Classes.h"

using namespace std;

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1. Numerical Tic Tac Toe\n";
    cout << "2. X-O Game\n";
    cout << "3. SUS Game\n";
    cout << "4. Exit\n";
    cout << "Choose (1-4): ";
}

bool confirmExit() {
    char c;
    cout << "Are you sure you want to exit? (y/n): ";
    cin >> c;
    return (c == 'y' || c == 'Y');
}

int getMenuChoice() {
    int choice;
    cin >> choice;
    return choice;
}


// ===================== PLAY SOS GAME =====================
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

//
// =========================
// Numerical TicTacToe
// =========================
//

void playNumericalGame() {
    Numerical_UI ui;

    cout << "\n=== Numerical Tic Tac Toe ===\n";

    string name1, name2;
    cout << "Enter Player 1 name (odd numbers): ";
    cin >> name1;

    cout << "Enter Player 2 name (even numbers): ";
    cin >> name2;

    Player<int>* p1 = ui.create_player(name1, 1, PlayerType::HUMAN);
    Player<int>* p2 = ui.create_player(name2, 2, PlayerType::HUMAN);

    Player<int>* players[2] = { p1, p2 };

    Numerical_Board board;
    GameManager<int> game(&board, players, &ui);

    game.run();

    if (board.is_win(p1))
        cout << p1->get_name() << " wins!\n";
    else if (board.is_win(p2))
        cout << p2->get_name() << " wins!\n";
    else
        cout << "It's a Draw!\n";

    delete p1;
    delete p2;
}

//
// =========================
// XO Game
// =========================
//

void playXOGame() {
    XO_UI ui;

    cout << "\n=== X-O Game ===\n";

    string name1, name2;
    cout << "Enter Player 1 name (X): ";
    cin >> name1;

    cout << "Enter Player 2 name (O): ";
    cin >> name2;

    Player<char>* p1 = ui.create_player(name1, 'X', PlayerType::HUMAN);
    Player<char>* p2 = ui.create_player(name2, 'O', PlayerType::HUMAN);

    Player<char>* players[2] = { p1, p2 };

    Xo_Board board;
    GameManager<char> game(&board, players, &ui);

    game.run();

    delete p1;
    delete p2;
}

//
// =========================
// MAIN
// =========================
//

int main() {
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        displayMainMenu();
        choice = getMenuChoice();

        switch (choice) {
        case 1:
            playNumericalGame();
            break;

        case 2:
            playXOGame();
            break;

        case 3:
            playSOSGame();
            break;

        case 4:
            if (confirmExit()) exitProgram = true;
            break;

        default:
            cout << "Invalid choice!\n";
            break;
        }
    }

    return 0;
}
