// #pragma once
// #include "BoardGame_Classes.h"
//
// class X_O_UI : public UI<char> {
// public:
//     X_O_UI() : UI("Welcome to Tic Tac Toe!", 3) {}
//
//     Move<char>* get_move(Player<char>* player) override {
//         int x, y;
//         cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column: ";
//         cin >> x >> y;
//         return new Move<char>(x, y, player->get_symbol());
//     }
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override {
//         return new Player<char>(name, symbol, type);
//     }
// };
// #pragma once
// #include "BoardGame_Classes.h"
//
// class Numerical_UI : public UI<int> {
// public:
//     Numerical_UI() : UI("Welcome to Numerical Tic Tac Toe!", 3) {}
//
//     Move<int>* get_move(Player<int>* player) override {
//         int x, y, num;
//         cout << player->get_name() << " (" << player->get_symbol() << ") enter number, row, column: ";
//         cin >> num >> x >> y;
//         return new Move<int>(x, y, num);
//     }
//     Player<int>* create_player(string& name, int /*symbol*/, PlayerType type) override {
//         // بدل ما ندي كل لاعب رمز X أو O، نخليه برقم مميز نختاره يدويًا
//         int actualSymbol = (name == "Player X" ? 1 : 2);
//         return new Player<int>(name, actualSymbol, type);
//     }
//
// };
#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class Numerical_UI : public UI<int> {
public:
    Numerical_UI() : UI("Welcome to Numerical Tic Tac Toe!", 3) {}

    Move<int>* get_move(Player<int>* player) override {
        int x, y, num;
        cout << player->get_name() << " enter number, row, column: ";
        cin >> num >> x >> y;
        return new Move<int>(x, y, num);
    }

    Player<int>* create_player(string& name, int /*symbol*/, PlayerType type) override {
        int actualSymbol = (name == "Player X" ? 1 : 2);
        return new Player<int>(name, actualSymbol, type);
    }
};
