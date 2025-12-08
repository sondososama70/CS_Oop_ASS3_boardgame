/**
 * @file pyramidTicTacToe.cpp
 * @brief Pyramid-shaped tic-tac-toe game implementation and AI/UI utilities.
 */

#include "pyramidTicTacToe.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

pyramidTicTacToe_board::pyramidTicTacToe_board() :Board(3,5) {
    board = {
        {' ', ' ', '.', ' ', ' '},
        {' ', '.', '.', '.', ' '},
        {'.', '.', '.', '.', '.'}
    };
}

/**
 * @brief Check whether (row,col) refers to a valid playable cell in the pyramid layout.
 */
bool pyramidTicTacToe_board::in_bounds(int row, int col) {
        if (row < 0 || row >= 3) return false;
        switch(row) {
            case 0: return col == 2;
            case 1: return col >= 1 && col <= 3;
            case 2: return col >= 0 && col <= 4;
            default: return false;
        }
}

/**
 * @brief Apply or undo a move at specified pyramid coordinates.
 */
bool pyramidTicTacToe_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (in_bounds(x,y) && (board[x][y] == blank_symbol || mark == 0)) {
        if (mark == 0) {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {
            n_moves++;
            board[x][y]=toupper(mark);
        }
        return true;
    }
    return false;
}

/**
 * @brief Check whether a given symbol has any of the predefined winning lines.
 */
bool pyramidTicTacToe_board::is_win_symbol(char sym, const vector<vector<char>>& currentBoard) {
    vector<vector<pair<int,int>>> lines = {
        //horizontal
        {{1,1}, {1,2}, {1,3}},
        {{2,0}, {2,1}, {2,2}},
        {{2,1}, {2,2}, {2,3}},
        {{2,2}, {2,3}, {2,4}},
        // Diagonals
        {{2,0}, {1,1}, {0,2}},
        {{0,2},{1,3},{2,4}},
        //vertical
        {{2,2}, {1,2}, {0,2}}
    };
    for (const auto& line : lines) {
        if (currentBoard[line[0].first][line[0].second] == sym &&
            currentBoard[line[1].first][line[1].second] == sym &&
            currentBoard[line[2].first][line[2].second] == sym) {
            return true;
            }
    }
    return false;
}

/**
 * @brief Determine if provided player has a win on current board.
 */
bool pyramidTicTacToe_board::is_win(Player<char> *player) {

    return is_win_symbol(player->get_symbol(),this->board);
}

/**
 * @brief Check for draw (9 moves used and no win).
 */
bool pyramidTicTacToe_board::is_draw(Player<char> *player) {
    return (n_moves==9 && !is_win(player));
}

/**
 * @brief Game finished flag.
 */
bool pyramidTicTacToe_board::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}

/**
 * @brief Evaluate board for minimax: +10 for AI win, -10 for human win, else 0.
 */
int pyramidTicTacToe_board::evaluate(char ai, char human) {
    if (is_win_symbol(ai,this->board)) return +10;
    if (is_win_symbol(human,this->board)) return -10;
    return 0;
}

/**
 * @brief Return list of empty playable cells as (row,col) pairs.
 */
vector<pair<int,int>> pyramidTicTacToe_board::empty_cells() {
    vector<pair<int,int>> v;
    for (int r=0; r<rows; r++)
        for (int c=0; c<columns; c++)
            if (board[r][c] == '.')
                v.push_back({r,c});
    return v;
}

/**
 * @brief Validate a candidate move coordinates.
 */
bool pyramidTicTacToe_board::is_valid_move(int r, int c) {
    return in_bounds(r, c) && board[r][c] == '.';
}

/**
 * @brief Check whether pyramid board is full of playable marks.
 */
bool pyramidTicTacToe_board::is_full() {
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            if (is_valid_move(r, c)) return false;
    return true;
}

/**
 * @brief Minimax search implementation for the pyramid board.
 */
int pyramidTicTacToe_board::minimax(pyramidTicTacToe_board* board, int nOfMoves, bool isMax, char ai, char human) {

    int score = board->evaluate(ai, human);
    if (score == 10) return score - nOfMoves;
    if (score == -10) return score + nOfMoves;
    if (board->is_full()) return 0;
    if (isMax) {
        int best = -1000;
        for (int r = 0; r < board->get_rows(); r++) {
            for (int c = 0; c < board->get_columns(); c++) {
                if (board->is_valid_move(r, c)) {
                    board->set_cell(r, c, ai);
                    int score = minimax(board, nOfMoves + 1, false, ai, human);
                    best = max(best, score);
                    board->set_cell(r, c, '.');
                }
            }
        }
        return best;
    }

    else {
        int best = 1000;
        for (int r = 0; r < board->get_rows(); r++) {
            for (int c = 0; c < board->get_columns(); c++) {
                if (board->is_valid_move(r, c)) {
                    board->set_cell(r, c, human);
                    int score = minimax(board, nOfMoves + 1, true, ai, human);
                    best = min(best, score);
                    board->set_cell(r, c, '.');
                }
            }
        }
        return best;
    }
}

/**
 * @brief Compute best move for AI using minimax; returns pair(row,col).
 */
pair<int,int>pyramidTicTacToe_board:: best_move(pyramidTicTacToe_board* board, char ai, char human) {
    int bestVal = -1000;
    pair<int,int> best = {-1, -1};
    for (int r = 0; r < board->get_rows(); r++) {
        for (int c = 0; c < board->get_columns(); c++) {
            if (board->is_valid_move(r, c)) {
                board->set_cell(r, c, ai);
                int moveVal = minimax(board, 1, false, ai, human);
                board->set_cell(r, c, '.');
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    best = {r, c};
                }
            }
        }
    }
    return best;
}

//end of board implementation

/**
 * @class pyramid_tic_tac_toe_UI
 * @brief UI class handling player creation and move acquisition.
 */
pyramid_tic_tac_toe_UI::pyramid_tic_tac_toe_UI() :UI<char>("Pyramid Tic Tac Toe Game has started",3) {}

pyramid_tic_tac_toe_UI::~pyramid_tic_tac_toe_UI() {}

/**
 * @brief Create human or AI player; AI returns Pyramid_AI_Player.
 */
Player<char>* pyramid_tic_tac_toe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    if (type == PlayerType::HUMAN) {
        return new Player<char>(name, symbol, PlayerType::HUMAN);
    }
    return new Pyramid_AI_Player(name, symbol);
}

/**
 * @brief Get a move from the human (validated) or let computer choose best_move.
 */
Move<char> *pyramid_tic_tac_toe_UI::get_move(Player<char> *player) {
    int row, col;
    pyramidTicTacToe_board* board = dynamic_cast<pyramidTicTacToe_board*>(player->get_board_ptr());
        if (player->get_type() == PlayerType::HUMAN) {
            bool valid_move = false;
            while (!valid_move) {
                cout  << "\nPlease enter your move x and y (0 to 4) (choose a cell that has '.'): ";
                cin >> row >> col;
                if (!board->in_bounds(row, col)) {
                    cout << "Out of bounds! Try again.\n";
                    continue;
                }
                if (board->get_board_matrix()[row][col] != '.' && board->get_board_matrix()[row][col] != ' ') {
                    cout << "choosen cell is not empty! Try again.\n";
                    continue;
                }
                valid_move = true;
            }
        }
    else if (player->get_type() == PlayerType::COMPUTER) {
        char opponent = (player->get_symbol() == 'X') ? 'O' : 'X';
        pair<int,int> best = board->best_move(board,player->get_symbol(), opponent);
        row = best.first;
        col = best.second;
        cout << "Computer chose: " << row << ", " << col << "\n";

    }
    return new Move<char> (row, col,player->get_symbol());
}

//end of UI implemetation

Move<char>* Pyramid_AI_Player:: get_move(Board<char>* board) {
    return nullptr;
}