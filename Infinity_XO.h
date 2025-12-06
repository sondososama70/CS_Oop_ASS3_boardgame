#ifndef INFINITY_XO_H
#define INFINITY_XO_H
#include <queue>

#include "BoardGame_Classes.h"
using namespace std;

class Infinity_XO : public Board<char> {
private:
    char blank_symbol = '.';
public:
    Infinity_XO();
    bool update_board(Move<char> *move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    // queue<pair<int, int>> moves;
    // void removedMoves();
    queue<pair<int,int>> moves;
};

class Infinity_XO_UI : public UI<char> {
public:
    Infinity_XO_UI();
    ~Infinity_XO_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};


#endif //INFINITY_XO_H