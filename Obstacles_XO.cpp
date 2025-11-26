#include "Obstacles_XO.h"
using namespace std;

Obstacles_XO::Obstacles_XO() : Board(6, 6) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}
bool Obstacles_XO::update_board(Move<char> *move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
        }
    return false;
}

bool Obstacles_XO::is_win(Player<char> *) {

}
bool Obstacles_XO::is_lose(Player<char> *) {

}
bool Obstacles_XO::is_draw(Player<char> *) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (board[i][j] == '.')  
                return false;
        }
    }
    return !is_win(player);
}


bool Obstacles_XO::game_is_over(Player<char> *player) {
    if (is_win(player))
        return true;
    return is_draw(player);

}