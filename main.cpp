#include <iostream>
#include "BoardGame_Classes.h"
#include "XO_Board.h"
#include "XO_UI.h"
#include "SUS.h"
#include "XO_Classes.h"

using namespace std;

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1. SUS Game\n";
    cout << "2. Four in a row Game\n";
    cout << "3. 5x5 Tic-Tac-Toe Game\n";
    cout << "4. Word Tic-Tac-Toe Game\n";
    cout << "5. Misère Tic-Tac-Toe Game\n";
    cout << "6. Diamond Tic-Tac-Toe Game\n";
    cout << "7. 4x4 Tic-Tac-Toe Game\n";
    cout << "8. Pyramid Tic-Tac-Toe Game\n";
    cout << "9. Numerical Tic-Tac-Toe Game\n";
    cout << "10. Obstacles Tic-Tac-Toe Game\n";
    cout << "11. Infinity Tic-Tac-Toe Game\n";
    cout << "12. Ultimate Tic Tac Toe Game\n";
    cout << "13.Memory Tic-Tac-Toe Game\n";
    cout << "14. Exit\n";
    cout << "Choose (1-14): ";
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

// ===================== PLAY SUS GAME =====================
void playSUSGame() {
    SUS board;
    SUS_UI ui;

    string n1, n2;

    cout << "Enter Player 1 name (uses S): ";
    cin >> n1;
    cout << "Enter Player 2 name (uses U): ";
    cin >> n2;

    Player<char>* p1 = new Player<char>(n1, 'S', PlayerType::HUMAN);
    Player<char>* p2 = new Player<char>(n2, 'U', PlayerType::HUMAN);

    Player<char>* players[2] = { p1, p2 };

    GameManager<char> game(&board, players, &ui);
    game.run();

    delete p1;
    delete p2;
}


// =========================Numerical TicTacToe=========================//

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


//=====================MAIN======================//

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
            playSUSGame();
            break;

        case 3:
            if (confirmExit()) exitProgram = true;
            break;

        default:
            cout << "Invalid choice!\n";
            break;
        }
    }

    return 0;
}
