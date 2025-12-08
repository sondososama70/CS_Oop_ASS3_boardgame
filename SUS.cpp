
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
// Display scores
// --------------------------------------
void SUS::display_scores() const {
    cout << "SCORES \n";
    cout << "S: " << score_p1 << " points\n";
    cout << "U: " << score_p2 << " points\n";
}

// --------------------------------------
// Update board with score calculation
// --------------------------------------
bool SUS::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();

    // Check if cell is empty
    if (board[r][c] != '.') {
        cout << "Cell [" << r << "," << c << "] is already occupied\n";
        return false;
    }

    // Count SUS sequences BEFORE the move
    int before = count_SUS();

    // Make the move
    board[r][c] = move->get_symbol();
    n_moves++;

    // Count SUS sequences AFTER the move
    int after = count_SUS();
    int delta = after - before;

    // Update scores if new SUS sequences were created
    if (delta > 0) {
        if (move->get_symbol() == 'S') {
            score_p1 += delta;
            cout << "\n S scored " << delta << " point(s)! ";
            if (delta == 1) cout << "(New S-U-S sequence)\n";
            else cout << "(Multiple new S-U-S sequences)\n";
        } else {
            score_p2 += delta;
            cout << "\n U scored " << delta << " point(s)! ";
            if (delta == 1) cout << "(New S-U-S sequence)\n";
            else cout << "(Multiple new S-U-S sequences)\n";
        }
    }

    // Display updated scores
    display_scores();

    return true;
}

// --------------------------------------
// Count ALL S-U-S sequences on board
// --------------------------------------
int SUS::count_SUS() {
    int count = 0;

    // 1. Check ALL horizontal S-U-S patterns
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == 'S' &&
            board[row][1] == 'U' &&
            board[row][2] == 'S') {
            count++;
        }
    }

    // 2. Check ALL vertical S-U-S patterns
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == 'S' &&
            board[1][col] == 'U' &&
            board[2][col] == 'S') {
            count++;
        }
    }

    // 3. Check main diagonal (top-left to bottom-right)
    if (board[0][0] == 'S' &&
        board[1][1] == 'U' &&
        board[2][2] == 'S') {
        count++;
    }

    // 4. Check anti-diagonal (top-right to bottom-left)
    if (board[0][2] == 'S' &&
        board[1][1] == 'U' &&
        board[2][0] == 'S') {
        count++;
    }

    return count;
}
// Win = who has highest SUS
bool SUS::is_win(Player<char>* player) {
    if (!game_is_over(player)) {
        return false;
    }
    char symbol = player->get_symbol();

    if (symbol == 'S') {
        if (score_p1 > score_p2) {
            cout << "\n 'S' WINS " << score_p1 << " points vs U's " << score_p2 << " points\n";
            return true;
        }
    } else { // Player is U
        if (score_p2 > score_p1) {
            cout << "\n 'U' WINS!** " << score_p2 << " points vs S's " << score_p1 << " points\n";
            return true;
        }
    }

    return false;
}


// --------------------------------------
// Check if player has lost
// --------------------------------------
bool SUS::is_lose(Player<char>* player) {
    // In SUS, losing means opponent has higher score
    if (!game_is_over(player)) {
        return false;
    }

    char symbol = player->get_symbol();

    if (symbol == 'S') {
        return score_p1 < score_p2;
    } else { // Player is U
        return score_p2 < score_p1;
    }
}

// --------------------------------------
// Check if game is a draw
// --------------------------------------
bool SUS::is_draw(Player<char>* player) {
    // Game is draw when board is full AND scores are equal
    if (n_moves == 9 && score_p1 == score_p2) {
        cout << "\n  #DRAW both players have: " << score_p1 << " points\n";
        return true;
    }
    return false;
}

// --------------------------------------
// Check if game is over
// --------------------------------------
bool SUS::game_is_over(Player<char>* player) {
    return (n_moves == 9);
}
int SUS::get_score_s() const {
    return score_p1;
}

// --------------------------------------
// Get U score (for UI display)
// --------------------------------------
int SUS::get_score_u() const {
    return score_p2;
}