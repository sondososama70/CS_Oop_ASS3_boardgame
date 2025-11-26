#ifndef FIVEBYFIVE_H
#define FIVEBYFIVE_H
#include "BoardGame_Classes.h"
using namespace std;

class FiveByFive : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
public:
    FiveByFive();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};
class FiveByFive_UI : public UI<char> {
public:
    FiveByFive_UI();
    ~FiveByFive_UI();
    Player<char>* create_player(string name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

#endif //FIVEBYFIVE_H
