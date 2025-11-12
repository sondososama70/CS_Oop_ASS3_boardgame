#include <iostream>

    // #include "BoardGame_Classes.h"
    // #include "XO_Board.h"
    // #include "XO_UI.h"
    //
    // int main() {
    //     X_O_UI ui;
    //     Player<char>** players = ui.setup_players();
    //     X_O_Board board;
    //
    //     GameManager<char> game(&board, players, &ui);
    //     game.run();
    //
    //     return 0;
    // }
#include "BoardGame_Classes.h"
#include "XO_Board.h"
#include "XO_UI.h"

    int main() {

        Numerical_UI ui;

        string name1, name2;
        cout << "Enter name of Player 1 (odd numbers): ";
        cin >> name1;
        cout << "Enter name of Player 2 (even numbers): ";
        cin >> name2;

        Player<int>* p1 = ui.create_player(name1, 1, PlayerType::HUMAN);
        Player<int>* p2 = ui.create_player(name2, 2, PlayerType::HUMAN);

        Player<int>* players[2] = { p1, p2 };

        Numerical_Board board;

        GameManager<int> game(&board, players, &ui);
        game.run();

        cout << " Game Over! " << endl;

        if (board.is_win(p1)) {
            cout << p1->get_name() << " wins! " << endl;
        }
        else if (board.is_win(p2)) {
            cout << p2->get_name() << " wins! " << endl;
        }
        else {
            cout << " It's a draw! " << endl;
        }

        return 0;
    };