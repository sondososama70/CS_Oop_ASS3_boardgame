#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

class Numerical_UI : public UI<int> {
public:
    Numerical_UI() : UI(" Welcome to Numerical Tic Tac Toe ", 3) {}

    Move<int>* get_move(Player<int>* player) override {
        int x, y, num;
        cout << player->get_name() << " enter number, row, column: ";
        cin >> num >> x >> y;
        return new Move<int>(x, y, num);
    }

    Player<int>* create_player(string& name, int , PlayerType type) override {
        int actualSymbol = (name == "Player X" ? 1 : 2);
        return new Player<int>(name, actualSymbol, type);
    }
};
