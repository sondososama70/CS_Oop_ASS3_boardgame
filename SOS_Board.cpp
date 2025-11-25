#include "SOS_Board.h"

SOS_Board::SOS_Board()
    : Board(3, 3) {
    // initialize board with empty spaces
    for (auto &row : board)
        for (auto &cell : row)
            cell = ' ';
}

bool SOS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    if (board[x][y] != ' ') return false;

    board[x][y] = s;
    n_moves++;
    return true;
}

bool SOS_Board::is_win(Player<char>* player) {
    char L = player->get_symbol();

    int count = 0;

    // check all lines containing SOS
    // Horizontal
    for (int r = 0; r < 3; r++) {
        if (board[r][0]=='S' && board[r][1]=='U' && board[r][2]=='S')
            count++;
    }

    // Vertical
    for (int c = 0; c < 3; c++) {
        if (board[0][c]=='S' && board[1][c]=='U' && board[2][c]=='S')
            count++;
    }

    // Diagonals
    if (board[0][0]=='S' && board[1][1]=='U' && board[2][2]=='S') count++;
    if (board[0][2]=='S' && board[1][1]=='U' && board[2][0]=='S') count++;

    // winning condition: board full and player has most sequences
    return false; // GameManager will not use scoring here
}

bool SOS_Board::is_draw(Player<char>* player) {
    return n_moves == 9;
}

bool SOS_Board::game_is_over(Player<char>* player) {
    return n_moves == 9;
}
