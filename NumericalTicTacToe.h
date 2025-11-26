#ifndef NUMERICALTICTACTOE_H
#define NUMERICALTICTACTOE_H

#include "BoardGame_Classes.h"
#include <set>
#include <iostream>
using namespace std;

class NumericalBoard : public Board<int> {
    set<int> used_numbers;
public:
    NumericalBoard();                  // declaration only
    void printBoard();
    bool update_board(Move<int>* move) override;
    bool check_sum_15();
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
};

class NumericalUI : public UI<int> {
public:
    NumericalUI();
    Move<int>* get_move(Player<int>* player) override;
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
};

#endif
