#include "SUS_BOARDGAME.h"

SUS_Board::SUS_Board() : Board<char>(3,3) {
    scoreP1 = scoreP2 = 0;
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (board[x][y] != '-') return false;

    board[x][y] = sym;
    return true;
}

int SUS_Board::count_SUS() {
    int count = 0;
    // check rows
    for (int r = 0; r < 3; r++)
        if (board[r][0]=='S' && board[r][1]=='U' && board[r][2]=='S')
            count++;

    // check columns
    for (int c = 0; c < 3; c++)
        if (board[0][c]=='S' && board[1][c]=='U' && board[2][c]=='S')
            count++;

    // diagonals
    if (board[0][0]=='S' && board[1][1]=='U' && board[2][2]=='S') count++;
    if (board[0][2]=='S' && board[1][1]=='U' && board[2][0]=='S') count++;

    return count;
}

bool SUS_Board::is_draw(Player<char>* player) {
    return count_SUS() > 0;
}

bool SUS_Board::is_win(Player<char>* player) {
    int c = count_SUS();
    if (player->get_symbol() == 'S')
        scoreP1 = c;
    else
        scoreP2 = c;

    return false;   // no instant win, winner decided at end
}
