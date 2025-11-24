#include <iostream>
#include "BoardGame_Classes.h"
#include "XO_Board.h"
#include "XO_UI.h"

void displayMainMenu() {
    cout << "Numerical Tic Tac Toe game" << endl;
    cout << "1. Start New Game (Player vs Player)" << endl;
    cout << "2. Game Rules" << endl;
    cout << "3. Exit" << endl;
    cout << "Please enter your choice (1-4): ";
}
void displayGameRules() {
    cout << "Game Rules:" << endl;
    cout << "1. This is a 3x3 Numerical Tic Tac Toe game" << endl;
    cout << "2. Player 1 uses ODD numbers (1, 3, 5, 7, 9)" << endl;
    cout << "3. Player 2 uses EVEN numbers (2, 4, 6, 8)" << endl;
    cout << "4. Players take turns placing numbers on the board" << endl;
    cout << "5. Each number can be used only once in the entire game" << endl;
    cout << "6. The first player to get 3 numbers in a row (any row, column, or diagonal) that sum to 15 wins" << endl;
    cout << "7. If all 9 cells are filled and no player has a sum of 15 the game ends in a draw" << endl;
    cout << endl;
}

bool confirmExit() {
    char choice;
    cout << "Are you sure you want to exit? (Yes/No): " << endl;
    cin >> choice;
    return choice;
}
int getMenuChoice() {
    int choice;
    cin >> choice;
    return choice;
}
void playNumericalGame() {
    Numerical_UI ui;

    string name1, name2;
    cout << "Enter name of Player 1 (odd numbers): ";
    cin >> name1;
    cout << "Enter name of Player 2 (even numbers): ";
    cin >> name2;

    Player<int>* player1 = ui.create_player(name1, 1, PlayerType::HUMAN);
    Player<int>* player2 = ui.create_player(name2, 2, PlayerType::HUMAN);

    Player<int>* players[2] = { player1, player2 };

    Numerical_Board board;

    GameManager<int> game(&board, players, &ui);
    game.run();

    if (board.is_win(player1)) {
        cout << player1->get_name() << " wins" << endl;
    }
    else if (board.is_win(player2)) {
        cout << player2->get_name() << " wins" << endl;
    }
    else {
        cout << "It's a draw" << endl;
    }

    cout << "Game Over" << endl;

}

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
                displayGameRules();
                break;

            case 3:
                if (confirmExit()) {
                    exitProgram = true;
                    cout << "Thank you for playing" << endl;
                }
                break;

            default:
                cout << "Invalid choice, Please enter a number between (1-4)" << endl;
                break;
        }
    }

    return 0;
};


// yarb