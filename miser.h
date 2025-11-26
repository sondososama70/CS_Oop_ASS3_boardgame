#pragma once
#include "BoardGame_Classes.h"

class miser : public Board<char> {
public:
    miser() ;
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
};
class MiserUI : public UI<char> {
public:
    MiserUI();
    Player<char>** setup_players() override;
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;


};
