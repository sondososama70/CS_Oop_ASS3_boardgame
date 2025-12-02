#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
#include <string>
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

class miser : public Board<char> {
public:
    miser() ;
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
    char get_cell(int r, int c);
    void set_cell(int r, int c, char symbol);
};
class MiserUI : public UI<char> {
public:
    MiserUI();
    Player<char>** setup_players() override;
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;


};
class MisereAI : public Player<char> {
public:
    MisereAI(string name, char symbol);
    Move<char>* get_move(Player<char>* p);
private:
    int minimax(miser* board, int depth, bool isMaximizing);
};