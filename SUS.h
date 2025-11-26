#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"

class SUS_UI : public UI<char> {
public:
    SUS_UI() : UI("=== SUS Game ===", 3) {}

    // Create player (same style as XO or Numerical)
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    // Get move from player
    Move<char>* get_move(Player<char>* player) override {
        int r, c;
        cout << player->get_name() << " (" << player->get_symbol()
             << ") enter row and column: ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
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
