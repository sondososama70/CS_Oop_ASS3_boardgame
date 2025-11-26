#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"

class SUS_UI : public UI<char> {
public:
    SUS_UI() : UI("Welcome to SUS Game!", 3) {}

    // Get move from user
    Move<char>* get_move(Player<char>* player) override {
        int r, c;
        cout << player->get_name() << " (" << player->get_symbol() << ") enter move (row col): ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }

    // Create player
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }
};


class SUS : public Board<char> {
    private:
    int score_p1;
    int score_p2;

public:
    SUS();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override ;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int count_SUS();
};

#endif
