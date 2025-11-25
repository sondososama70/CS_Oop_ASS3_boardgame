#ifndef SOS_BOARD_H
#define SOS_BOARD_H

#include "BoardGame_Classes.h"

class SOS_Board : public Board<char> {
public:
    SOS_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

#endif
