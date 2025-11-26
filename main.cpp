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
    cout << "\n=== SUS GAME ===\n";

    SUS board;
    SUS_UI ui;

    string name1, name2;
    char sym1, sym2;

    cout << "Enter Player 1 name: ";
    cin >> name1;

    cout << "Choose symbol for Player 1 (S or U): ";
    cin >> sym1;

    // Validate
    while (sym1 != 'S' && sym1 != 'U' && sym1 != 's' && sym1 != 'u') {
        cout << "Invalid! Choose S or U: ";
        cin >> sym1;
    }
    sym1 = toupper(sym1);

    // Player 2 automatically gets the other symbol
    sym2 = (sym1 == 'S' ? 'U' : 'S');

    cout << "Enter Player 2 name: ";
    cin >> name2;

    cout << name2 << " will use symbol: " << sym2 << "\n\n";

    Player<char>* p1 = ui.create_player(name1, sym1, PlayerType::HUMAN);
    Player<char>* p2 = ui.create_player(name2, sym2, PlayerType::HUMAN);

    Player<char>* players[2];

    // Player with S always starts first
    if (sym1 == 'S') {
        players[0] = p1;
        players[1] = p2;
    } else {
        players[0] = p2;
        players[1] = p1;
    }

    GameManager<char> game(&board, players, &ui);
    game.run();

    cout << "\n=== GAME OVER ===\n";

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
        case 2:
            playNumericalGame();
            break;

        case 1:
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
