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
    const char sym = player->get_symbol();
    int win_count = 0;

    // Only determine win after all moves are completed
    if (n_moves == 24) {
        // Count sequences for both players to determine winner
        char other_sym = (sym == 'X') ? 'O' : 'X';
        int other_count = count_sequences(other_sym);

        return win_count > other_count;
    }
    return false;
}

bool FiveByFive::is_lose(Player<char>*) {
    return false;
}

bool FiveByFive::is_draw(Player<char> *player) {
    if (n_moves == 24) {
        const char sym1 = 'X';
        const char sym2 = 'O';
        int count1 = count_sequences(sym1);
        int count2 = count_sequences(sym2);

        return count1 == count2;
    }
    return false;
}

bool FiveByFive::game_is_over(Player<char> *player) {
    return (n_moves == 24);
}

// Helper function to count 3-in-a-row sequences for any symbol
int FiveByFive::count_sequences(char sym) {
    int count = 0;

    // Check rows
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            if (board[i][j] == sym && board[i][j+1] == sym && board[i][j+2] == sym) {
                count++;
            }
        }
    }
    // Check columns
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i <= rows - 3; ++i) {
            if (board[i][j] == sym && board[i+1][j] == sym && board[i+2][j] == sym) {
                count++;
            }
        }
    }
    // Check diagonals
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            if (board[i][j] == sym && board[i+1][j+1] == sym && board[i+2][j+2] == sym) {
                count++;
            }
        }
    }
    // Check anti-diagonals
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 2; j < columns; ++j) {
            if (board[i][j] == sym && board[i+1][j-1] == sym && board[i+2][j-2] == sym) {
                count++;
            }
        }
    }
    return count;
}

