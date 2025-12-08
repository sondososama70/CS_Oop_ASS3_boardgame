// #include "Obstacles_XO.h"
// using namespace std;
//
// Obstacles_XO::Obstacles_XO() : Board(6, 6) {
//     for (auto& row : board) {
//         for (auto& cell : row) {
//             cell = blank_symbol;
//         }
//     }
// }
// bool Obstacles_XO::update_board(Move<char> *move) {
//     int x = move->get_x();
//     int y = move->get_y();
//     char mark = move->get_symbol();
//
//     if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
//         (board[x][y] == blank_symbol || mark == 0)) {
//
//         if (mark == 0) { // Undo move
//             n_moves--;
//             board[x][y] = blank_symbol;
//         }
//         else {         // Apply move
//             n_moves++;
//             board[x][y] = toupper(mark);
//         }
//         return true;
//         }
//     return false;
// }

#include "Obstacles_XO.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief Construct Obstacles_XO and initialize random seed and blank board.
 */
Obstacles_XO::Obstacles_XO() : Board(6, 6) {
    srand(time(0)); // Seed random number generator
    n_moves = 0;
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}

/**
 * @brief Apply a move unless the cell is blocked/occupied or out-of-bounds.
 */
bool Obstacles_XO::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Check if position is valid and not occupied by obstacle or other player
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Please choose between 0-5.\n";
        return false;
    }

    if (board[x][y] == obstacle_symbol) {
        cout << "This cell is blocked by an obstacle!\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "This cell is already occupied!\n";
        return false;
    }

    // Apply move
    n_moves++;
    board[x][y] = toupper(mark);

    if (n_moves % 2 == 0 && n_moves != 0) {
        add_obstacles();
    }


    return true;
}

/**
 * @brief Add up to two obstacles into random blank cells.
 */
void Obstacles_XO::add_obstacles() {
    int obstacles_added = 0;
    int max_attempts = 20; // Prevent infinite loop

    while (obstacles_added < 2 && max_attempts > 0) {
        int x = rand() % 6;
        int y = rand() % 6;

        if (board[x][y] == blank_symbol) {
            board[x][y] = obstacle_symbol;
            obstacles.push_back({x, y});
            obstacles_added++;
        }
        max_attempts--;
    }
}

/**
 * @brief Check whether the player has 4-in-a-row (wins) ignoring obstacles.
 */
bool Obstacles_XO::is_win(Player<char> *player) {
    const char sym = player->get_symbol();
    auto all_equal = [&](char a, char b, char c , char d) {
        return (a == b && b == c && c == d && a == sym);
    };
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            if (all_equal(board[i][j], board[i][j+1], board[i][j+2], board[i][j+3])) return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            if (all_equal(board[i][j], board[i+1][j], board[i+2][j], board[i+3][j])) return true;
        }
    }
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (all_equal(board[i][j],board[i+1][j+1],board[i+2][j+2],board[i+3][j+3]) ) {
                return true;
            }
        }
    }
    for (int i=0;i<3;i++) {
        for (int j=3;j<6;j++) {
            if (all_equal(board[i][j],board[i+1][j-1],board[i+2][j-2],board[i+3][j-3])) {
                return true;
            }
        }
    }
    return false;
}
bool Obstacles_XO::is_lose(Player<char> *) {
    return false;
}

/**
 * @brief Determine draw: no blank '.' cells and no win.
 */
bool Obstacles_XO::is_draw(Player<char> *player) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (board[i][j] == '.')
                return false;
        }
    }
    return !is_win(player);
}

/**
 * @brief Game over when win or draw.
 */
bool Obstacles_XO::game_is_over(Player<char> *player) {
    if (is_win(player))
        return true;
    return is_draw(player);
}

/**
 * @brief Print the current board to stdout.
 */
void Obstacles_XO::print_board() {
    cout << "\nCurrent Board:\n";
    cout << "  ";
    for (int j = 0; j < columns; j++) {
        cout << j << " ";
    }
    cout << "\n";

    for (int i = 0; i < rows; i++) {
        cout << i << " ";
        for (int j = 0; j < columns; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}