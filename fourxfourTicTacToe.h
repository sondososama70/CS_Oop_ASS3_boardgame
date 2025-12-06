//
// Created by HP on 11/26/2025.
//

#ifndef CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H
#define CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
class FourxFour_Move;
using namespace std;

class FourxFour_Board :public Board<char> {
protected:
    void init_start_positions();

public :
    FourxFour_Board();
    ~FourxFour_Board();
    char blank_symbol = '.';
    bool in_bounds(int r, int c) const;
    bool is_adjacent(int r, int c, int newr, int newc) const;
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    vector<pair<int,int>> get_adjacent(int row, int col) ;
    bool checking_win(char player);
    vector<FourxFour_Move*> get_all_valid_moves(char player_symbol);
    int evaluate1(char ai_symbol, char human_symbol);
    int minimax(char ai_symbol, char human_symbol, bool isMaximizingPlayer, int alpha, int beta, int depth) ;
    FourxFour_Move* best_move(char ai, char human);
    int evaluation2(char ai_symbol, char human_symbol);
    int count_alignment(char symbol, int length);
};

class FourxFour_UI : public UI<char> {
public:
    FourxFour_UI();
    ~FourxFour_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

class FourxFour_Move : public Move<char> {
private:
    int newX, newY;
public:
    FourxFour_Move(int oldr_, int oldc_, int newr_, int newc_, char s) :Move<char>(oldr_, oldc_, s), newX(newr_), newY(newc_) {};
    int getNewX() const { return newX; };
    int getNewY() const { return newY; };
};


#endif //CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H