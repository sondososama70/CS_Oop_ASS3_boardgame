#ifndef SOS_UI_H
#define SOS_UI_H

#include "BoardGame_Classes.h"
#include "SOS_Board.h"

class SOS_UI : public UI<char> {
public:
    SOS_UI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
