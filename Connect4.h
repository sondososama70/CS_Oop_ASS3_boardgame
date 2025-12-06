
#ifndef CONNECT4_H
#define CONNECT4_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

//CONNECT4 BOARD

class Connect4_Board : public Board<char> {
public:
    Connect4_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

//CONNECT4 PLAYER

class Connect4_Player : public Player<char> {
public:
    Connect4_Player(string n, char s, PlayerType t);
};

//CONNECT4 UI
class Connect4_UI : public UI<char> {
public:
    Connect4_UI();
    ~Connect4_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif

