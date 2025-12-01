//
// Created by HP on 12/1/2025.
//

#ifndef CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H
#define CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H

#include "BoardGame_Classes.h"
using namespace std;

class pyramidTicTacToe_board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    pyramidTicTacToe_board();
    bool update_board(Move<char> *move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    bool in_bounds(int row, int col);

};

class pyramid_tic_tac_toe_UI : public UI<char> {
public:
    pyramid_tic_tac_toe_UI();
    ~pyramid_tic_tac_toe_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

#endif //CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H