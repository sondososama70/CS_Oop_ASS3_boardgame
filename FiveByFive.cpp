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
        (board[x][y] == blank_symbol)) {

        n_moves++;
        board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

bool FiveByFive::is_win(Player<char> *player) {
    // Only determine win after all moves are completed
    if (n_moves < 24) return false;

    const char sym = player->get_symbol();
    const char other_sym = (sym == 'X') ? 'O' : 'X';

    int player_sequences = count_sequences(sym);
    int opponent_sequences = count_sequences(other_sym);

    return player_sequences > opponent_sequences;
}

bool FiveByFive::is_lose(Player<char> *player) {
    // Only determine lose after all moves are completed
    if (n_moves < 24) return false;

    const char sym = player->get_symbol();
    const char other_sym = (sym == 'X') ? 'O' : 'X';

    int player_sequences = count_sequences(sym);
    int opponent_sequences = count_sequences(other_sym);

    return player_sequences < opponent_sequences;
}

bool FiveByFive::is_draw(Player<char> *player) {
    // Game is a draw when all cells are filled and sequences are equal
    if (n_moves == 24) {
        int x_sequences = count_sequences('X');
        int o_sequences = count_sequences('O');

        return x_sequences == o_sequences;
    }
    return false;
}

bool FiveByFive::game_is_over(Player<char> *player) {
    return (n_moves == 24);
}

// Helper function to count 3-in-a-row sequences for any symbol
int FiveByFive::count_sequences(char sym) {
    int count = 0;

    // Check horizontal sequences
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            if (board[i][j] == sym && board[i][j+1] == sym && board[i][j+2] == sym) {
                count++;
            }
        }
    }

    // Check vertical sequences
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i <= rows - 3; ++i) {
            if (board[i][j] == sym && board[i+1][j] == sym && board[i+2][j] == sym) {
                count++;
            }
        }
    }

    // Check diagonal sequences (top-left to bottom-right)
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            if (board[i][j] == sym && board[i+1][j+1] == sym && board[i+2][j+2] == sym) {
                count++;
            }
        }
    }

    // Check anti-diagonal sequences (top-right to bottom-left)
    for (int i = 0; i <= rows - 3; ++i) {
        for (int j = 2; j < columns; ++j) {
            if (board[i][j] == sym && board[i+1][j-1] == sym && board[i+2][j-2] == sym) {
                count++;
            }
        }
    }
    return count;
}