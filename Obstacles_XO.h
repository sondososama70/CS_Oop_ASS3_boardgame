#ifndef OBSTACLES_XO_H
#define OBSTACLES_XO_H
#include "BoardGame_Classes.h"
using namespace std;

class Obstacles_XO : public Board<char> {
private:
    char blank_symbol = '.';

public:
    Obstacles_XO();
    bool update_board(Move<char>* move);
    bool is_win(Player<char> *) override;
    bool is_lose(Player<char> *) override;
    bool is_draw(Player<char> *) override;
    bool game_is_over(Player<char>* player);
};

class Obstacles_XO_UI : public UI<char> {
public:
    Obstacles_XO_UI() : UI<char>("Welcome to Obstacles Tic-Tac-Toe", 6) {}
    ~Obstacles_XO_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    virtual Move<char>* get_move(Player<char>* player) override {
        int row , column;
        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column: ";
            cin >> row >> column;
        }
        else if (player->get_type() == PlayerType::COMPUTER) {
            // Simple random move for computer player
            row = rand() % player->get_board_ptr()->get_rows();
            column = rand() % player->get_board_ptr()->get_columns();
            cout << "Computer " << player->get_name() << " chooses: (" << row << ", " << column << ")\n";
        }
        return new Move<char>(row, column, player->get_symbol());
    }
};

#endif //OBSTACLES_XO_H