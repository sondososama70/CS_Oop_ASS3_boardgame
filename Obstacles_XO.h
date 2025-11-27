#ifndef OBSTACLES_XO_H
#define OBSTACLES_XO_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

class Obstacles_XO : public Board<char> {
private:
    char blank_symbol = '.';
    char obstacle_symbol = '#';
    vector<pair<int, int>> obstacles;

public:
    Obstacles_XO();
    bool update_board(Move<char>* move);
    void add_obstacles();
    bool is_win(Player<char> *) override;
    bool is_lose(Player<char> *) override;
    bool is_draw(Player<char> *) override;
    bool game_is_over(Player<char>* player);
    void print_board();
};

class Obstacles_XO_UI : public UI<char> {
private:
    int round_count = 0;

public:
    Obstacles_XO_UI() : UI<char>("Welcome to Obstacles Tic-Tac-Toe", 6) {}
    ~Obstacles_XO_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    virtual Move<char>* get_move(Player<char>* player) override {
        int row, column;
        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column (0-5): ";
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

    void post_move_processing(Board<char>* board, Player<char>* current_player) {
        round_count++;

        // Add obstacles after every round
        if (round_count % 2 == 0) {
            cout << "\n--- Adding 2 new obstacles ---\n";
            Obstacles_XO* obs_board = dynamic_cast<Obstacles_XO*>(board);
            if (obs_board) {
                obs_board->add_obstacles();
                obs_board->print_board();
            }
        }
    }
};

#endif //OBSTACLES_XO_H


