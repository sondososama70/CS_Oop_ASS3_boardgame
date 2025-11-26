#ifndef CS_ASSIGNMENT2_SOUND_MISER_H
#define CS_ASSIGNMENT2_SOUND_MISER_H

#pragma once
#include "BoardGame_Classes.h"


class miser : public Board<char> {
public:
    miser() ;
    void printBoard() ;
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
    void print_board() ;

};
class MiserUI : public UI<char> {
public:
    // 1. Constructor
    MiserUI();

    // 2. Setup Players (Ask for names for X and O)
    Player<char>** setup_players() override;

    // 3. Get Move (Ask for X and Y only)
    Move<char>* get_move(Player<char>* player) override;

    // 4. Create Player Helper
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif //CS_ASSIGNMENT2_SOUND_MISER_H