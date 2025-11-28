#ifndef WORD_TICTACTOE_H
#define WORD_TICTACTOE_H
#include "BoardGame_Classes.h"
using namespace std;

class Word_TicTacToe : public Board<char> {
private:
    char blank_symbol = '.';
public:
    Word_TicTacToe();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class Word_TicTacToe_UI : public UI<char> {
public:
    Word_TicTacToe_UI();
    ~Word_TicTacToe_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif //WORD_TICTACTOE_H