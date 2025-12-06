//
// Created by HP on 12/1/2025.
//

#ifndef CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H
#define CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H

#include "BoardGame_Classes.h"
using namespace std;

class pyramidTicTacToe_board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    pyramidTicTacToe_board();
    bool update_board(Move<char> *move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    bool in_bounds(int row, int col);

    int evaluate(char ai_symbol, char human_symbol);
    int minimax(pyramidTicTacToe_board* board, int depth, bool isMax, char ai, char human) ;
    pair<int,int> best_move(pyramidTicTacToe_board* board,char aiSymbol, char humanSymbol);
    bool is_win_symbol( char sym,const vector<vector<char>>& currentBoard);

    vector<pair<int,int>> empty_cells() ;
    bool is_valid_move(int r, int c);
    bool is_winner(char symbol);
    bool is_full();

    char get_cell(int r, int c) {
        return board[r][c];
    }
    void set_cell(int r, int c, char symbol) {
        board[r][c] = symbol;
    }

};

class pyramid_tic_tac_toe_UI : public UI<char> {
public:
    pyramid_tic_tac_toe_UI();
    ~pyramid_tic_tac_toe_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

class Pyramid_AI_Player : public Player<char> {
public:
    Pyramid_AI_Player(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::COMPUTER) {}
    virtual Move<char>* get_move(Board<char>* board);
};




#endif //CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H