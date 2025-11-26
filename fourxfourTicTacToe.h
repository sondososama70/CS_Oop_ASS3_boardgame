//
// Created by HP on 11/26/2025.
//

#ifndef CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H
#define CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
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
};

class FourxFour_UI : public UI<char> {
public:
    // FourxFour_UI(string message, int cell_width)
    //     : UI<char>(message, cell_width) {}
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