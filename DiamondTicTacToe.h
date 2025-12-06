#ifndef DIAMONDTICTACTOE_H
#define DIAMONDTICTACTOE_H
#include "BoardGame_Classes.h"


class DiamondTicTacToe : public Board<char> {
    int checkLine(char symbol, int r, int c, int lr, int lc) ;
public:
    DiamondTicTacToe();
    bool inside_diamond(int r, int c);
    bool update_board(Move<char>* move) override ;
    bool is_win(Player<char>* player) override ;
    bool is_lose(Player<char>* player) override ;
    bool is_draw(Player<char>* player) override ;
    bool game_is_over(Player<char>* player) override ;
    char get_cell(int r, int c);
    void set_cell(int r, int c, char symbol);
};

class DiamondTicTacToeUI : public UI<char> {
public:
    DiamondTicTacToeUI();
    ~DiamondTicTacToeUI();
    Player<char>** setup_players() override;
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

class DiamondAI : public Player<char> {
public:
    DiamondAI(string name, char symbol);
    Move<char>* get_move_ai();
    Move<char>* get_move(Player<char>* p); // دالة خاصة للـ AI

private:
    int minimax(DiamondTicTacToe* board, int depth, bool isMaximizing);
};
#endif //DIAMONDTICTACTOE_H
