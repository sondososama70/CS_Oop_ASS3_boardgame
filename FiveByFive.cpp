#include "FiveByFive.h"
using namespace std;

FiveByFive::FiveByFive() : Board(5, 5) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}
bool FiveByFive::update_board(Move<char> *move) {
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

bool FiveByFive::is_win(Player<char> *player) {

}

bool FiveByFive::is_draw(Player<char> *player) {

}

bool FiveByFive::game_is_over(Player<char> *player) {

}

