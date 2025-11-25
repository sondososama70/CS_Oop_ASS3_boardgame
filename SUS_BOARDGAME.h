#ifndef SUS_BOARDGAME
#define SUS_BOARDGAME

#include "BoardGame_Classes.h"

class SUS_Board : public Board<char> {
private:
    int scoreP1;
    int scoreP2;

    int count_SUS();   // helper

public:
    SUS_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
};

#endif
