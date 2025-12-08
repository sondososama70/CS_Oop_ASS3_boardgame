#include <iostream>
#include "BoardGame_Classes.h"
#include "SUS.h"
#include "Connect4.h"
#include "miser.h"
#include "NUMERICALTICTACTOE.h"
#include "fourxfourTicTacToe.h"
#include "FiveByFive.h"
#include "Obstacles_XO.h"
#include "Word_TicTacToe.h"
#include "DiamondTicTacToe.h"
#include "Infinity_XO.h"
#include "pyramidTicTacToe.h"
#include "Memory_XO.h"

using namespace std;
template <typename T>

void startGame(Board<T>* board, UI<T>* ui) {
    Player<T>** players = ui->setup_players();
    GameManager<T> game(board, players, ui);
    game.run();
    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1. SUS Game\n";
    cout << "2. Four in a row Game\n";
    cout << "3. 5x5 Tic-Tac-Toe Game\n";
    cout << "4. Word Tic-Tac-Toe Game\n";
    cout << "5. Misere Tic-Tac-Toe Game\n";
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
    int type1, type2;

    // Player 1
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

    // Choose player type
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Computer (AI)\n";
    cout << "Choice: ";
    cin >> type1;

    // Player 2 automatically gets the other symbol
    sym2 = (sym1 == 'S' ? 'U' : 'S');

    cout << "\nPlayer 2 will use symbol: " << sym2 << "\n";
    cout << "Enter Player 2 name: ";
    cin >> name2;

    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Computer (AI)\n";
    cout << "Choice: ";
    cin >> type2;

    Player<char>* p1;
    Player<char>* p2;

    // Create players based on type
    if (type1 == 2) { // AI player
        p1 = new SUS_AI_Player(name1, sym1, PlayerType::COMPUTER);
    } else { // Human player
        p1 = new Player<char>(name1, sym1, PlayerType::HUMAN);
    }

    if (type2 == 2) { // AI player
        p2 = new SUS_AI_Player(name2, sym2, PlayerType::COMPUTER);
    } else { // Human player
        p2 = new Player<char>(name2, sym2, PlayerType::HUMAN);
    }

    // Give AI players the game board reference
    if (type1 == 2) {
        SUS_AI_Player* ai1 = dynamic_cast<SUS_AI_Player*>(p1);
        if (ai1) {
            ai1->set_game_board(&board);
        }
    }
    if (type2 == 2) {
        SUS_AI_Player* ai2 = dynamic_cast<SUS_AI_Player*>(p2);
        if (ai2) {
            ai2->set_game_board(&board);
        }
    }

    Player<char>* players[2];

    // Player with S always starts first
    if (sym1 == 'S') {
        players[0] = p1;
        players[1] = p2;
    } else {
        players[0] = p2;
        players[1] = p1;
    }

    // Set board pointer for all players
    players[0]->set_board_ptr(&board);
    players[1]->set_board_ptr(&board);

    cout << "\n=== Game Started ===\n";
    cout << "S starts first!\n\n";

    GameManager<char> game(&board, players, &ui);
    game.run();

    cout << "\n=== GAME OVER ===\n";

    delete p1;
    delete p2;
}
//======conect4=======//
void playConnect4Game() {
    Connect4_Board* board = new Connect4_Board();
    Connect4_UI* ui = new Connect4_UI();

    string name1, name2;
    cout << "Enter Player 1 name (X): ";
    cin >> name1;
    cout << "Enter Player 2 name (O): ";
    cin >> name2;

    Player<char>* p1 = new Player<char>(name1, 'X', PlayerType::HUMAN);
    Player<char>* p2 = new Player<char>(name2, 'O', PlayerType::HUMAN);

    Player<char>* players[2] = {p1, p2};

    GameManager<char> game(board, players, ui);
    game.run();

    delete p1;
    delete p2;
    delete board;
    delete ui;

}

// ===================== PLAY 5x5 TIC-TAC-TOE GAME =====================
void playFiveByFiveGame() {
    FiveByFive board;
    FiveByFive_UI ui;

    string name1, name2;
    int choice1 , choice2;
    PlayerType type1 , type2;

    //Player 1:
    cout << "Enter Player 1 name (X): ";
    cin >> name1;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n" << "2. Computer\n" << "Choose (1 or 2): ";
    cin >> choice1;

    while (choice1 < 1 || choice1 > 2) {
        cout << "Invalid choice , Choose 1 (Human) or 2 (Computer): ";
        cin >> choice1;
    }
    type1 = (choice1 == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;

    //Player 2:
    cout << "Enter Player 2 name (O): ";
    cin >> name2;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n" << "2. Computer\n" << "Choose (1 or 2): ";
    cin >> choice2;

    while (choice2 < 1 || choice2 > 2) {
        cout << "Invalid choice , Choose 1 (Human) or 2 (Computer): ";
        cin >> choice2;
    }
    type2 = (choice2 == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;

    Player<char>* p1 = ui.create_player(name1, 'X', type1);
    Player<char>* p2 = ui.create_player(name2, 'O', type2);
    Player<char>* players[2] = {p1, p2};

    GameManager<char> game(&board, players, &ui);
    game.run();

    delete p1;
    delete p2;
}

// ===================== PLAY Word TIC-TAC-TOE GAME =====================
void playWordTicTacToeGame() {
    Word_TicTacToe board;
    Word_TicTacToe_UI ui;

    string name1, name2;
    int choice1, choice2;
    PlayerType type1, type2;

    //Player 1:
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n" << "2. Computer\n" << "Choose (1 or 2): ";
    cin >> choice1;

    while (choice1 < 1 || choice1 > 2) {
        cout << "Invalid choice , Choose 1 (Human) or 2 (Computer): ";
        cin >> choice1;
    }
    type1 = (choice1 == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;

    //Player 2:
    cout << "Enter Player 2 name: ";
    cin >> name2;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n" << "2. Computer\n" << "Choose (1 or 2): ";
    cin >> choice2;

    while (choice2 < 1 || choice2 > 2) {
        cout << "Invalid choice , Choose 1 (Human) or 2 (Computer): ";
        cin >> choice2;
    }
    type2 = (choice2 == 1) ? PlayerType::HUMAN : PlayerType::COMPUTER;

    Player<char>* p1 = ui.create_player(name1, ' ', type1);
    Player<char>* p2 = ui.create_player(name2, ' ', type2);

    Player<char>* players[2] = {p1, p2};

    GameManager<char> game(&board, players, &ui);
    game.run();

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
                 playSUSGame() ;
                 break;
             case 2:
                playConnect4Game();

                 break;
             case 3:
                 playFiveByFiveGame();
                 break;
             case 4:
                playWordTicTacToeGame();
                break;
             case 5:
                 cout << "\nStarting Misere Tic Tac Toe...\n";
                 startGame(new miser(), new MiserUI());
                 break;
             case 6:
                  startGame(new DiamondTicTacToe() , new DiamondTicTacToeUI());
                 break;
             case 7:
                 startGame(new FourxFour_Board(), new FourxFour_UI());
                 break;
             case 8:
                  startGame(new pyramidTicTacToe_board, new pyramid_tic_tac_toe_UI());
                 break;
             case 9:
                 cout << "\nStarting Numerical Tic Tac Toe...\n";
                 startGame(new NumericalBoard(), new NumericalUI());
                 break;
             case 10:
                 startGame(new Obstacles_XO(), new Obstacles_XO_UI());
                 break;
             case 11:
                  startGame(new Infinity_XO(), new Infinity_XO_UI());
                 break;
             case 12:
                 // Bonus Game 1
                 break;
             case 13:
                startGame(new Memory_XO(), new Memory_XO_UI());
                 break;
             case 14:
                 cout << "\nGoodbye, Thanks for playing.\n";
                 exitProgram = true;
                 break;
             default:
                 cout << "\nInvalid choice , Please choose a number between 1 and 14.\n";
                 break;
        }
    }
    return 0;
};
