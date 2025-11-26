
#include "BoardGame_Classes.h"
#include "SUS.h"
#include <iostream>


using namespace std;

SUS::SUS() : Board (3, 3) {
    score_p1 = 0;
    score_p2 = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '.';
}

// --------------------------------------
// Update board
bool SUS::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();

    if (board[r][c] != '.')
        return false;

    int before = count_SUS();

    board[r][c] = move->get_symbol();
    n_moves++;

    int after = count_SUS();
    int delta = after - before;
    if (delta > 0) {
        if (move->get_symbol() == 'S')
            score_p1 += delta;
        else
            score_p2 += delta;
    }

    return true;
}


// --------------------------------------
// Count number of S-U-S found on board
int SUS::count_SUS() {
    int count = 0;

    // Horizontal
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 1; j++)
            if (board[i][j] == 'S' &&
                board[i][j+1] == 'U' &&
                board[i][j+2] == 'S')
                count++;

    // Vertical
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 1; i++)
            if (board[i][j] == 'S' &&
                board[i+1][j] == 'U' &&
                board[i+2][j] == 'S')
                count++;

    // Diagonals
    if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S')
        count++;

    if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S')
        count++;

    return count;
}

// Win = who has highest SUS
bool SUS::is_win(Player<char>* player) {
    if (!game_is_over(player))
        return false;

    if (player->get_symbol() == 'S') {
        return score_p1 > score_p2 ;
    }
    else {
        return score_p2 > score_p1 ;
    }
}

bool SUS::is_lose(Player<char>*) {
    return false;
}

// --------------------------------------
bool SUS::is_draw(Player<char>*) {
    return (n_moves == 9 && score_p1 == score_p2);
    }



// --------------------------------------
bool SUS::game_is_over(Player<char>*) {
    return n_moves == 9;
}
