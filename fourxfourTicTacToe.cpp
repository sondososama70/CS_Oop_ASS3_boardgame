/**
 * @file fourxfourTicTacToe.cpp
 * @brief 4x4 moving-token Tic-Tac-Toe variant with AI (minimax) and UI.
 *
 * Implements:
 * - FourxFour_Board: board logic with tokens that move to adjacent cells.
 * - FourxFour_Move: move type carrying source and destination coordinates.
 * - FourxFour_UI: player creation and move solicitation (human/computer).
 */

#include "fourxfourTicTacToe.h"

using namespace std;

FourxFour_Board::FourxFour_Board() : Board(4, 4) {
    init_start_positions();
}
void FourxFour_Board :: init_start_positions() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = blank_symbol;
        }
    }

    board[0][0] = 'O';
    board[0][1] = 'X';
    board[0][2] = 'O';
    board[0][3] = 'X';
    board[3][0] = 'X';
    board[3][1] = 'O';
    board[3][2] = 'X';
    board[3][3] = 'O';
}
FourxFour_Board::~FourxFour_Board() { }

/**
 * @brief Check whether (r,c) are inside board bounds.
 * @return true if in bounds.
 */
bool FourxFour_Board::in_bounds(int r, int c) const {
    if (r >=0 && r <= 3 && c >= 0 && c <= 3) {
        return true;
    }
    return false;
}

/**
 * @brief Return whether two cells are adjacent (Manhattan distance == 1).
 */
bool FourxFour_Board::is_adjacent(int r, int c, int newr, int newc) const {
    if (abs(r - newr)+ abs(c-newc)==1) {
        return true;
    }
    return false;
}

/**
 * @brief Apply a FourxFour_Move: move token from source to destination or perform undo.
 * @param move Pointer to FourxFour_Move.
 * @return true if update applied (destination in bounds), false otherwise.
 */
bool FourxFour_Board::update_board(Move<char> *move) {
    FourxFour_Move* mv = static_cast<FourxFour_Move*>(move);

    int oldX=mv->get_x();
    int oldY=mv->get_y();
    int newX=mv->getNewX();
    int newY=mv->getNewY();
    char mark =mv->get_symbol();

    if (in_bounds(newX,newY)) {
        if (is_adjacent(oldX,oldY,newX,newY)) {
            n_moves++;
            board[newX][newY] = mark;
            board[oldX][oldY] = blank_symbol;
        }
        else if (mark == 0) {
            board[newX][newY] = blank_symbol;
        }
        return true;
    }
    return false;
}

/**
 * @brief Check if player has a 3-in-a-row on 4x4 board according to game rules.
 */
bool FourxFour_Board::is_win(Player<char> *player) {
    const char sym =player->get_symbol();
    return checking_win(sym);

}

bool FourxFour_Board::is_draw(Player<char> *player) {
    return (n_moves==16 && !is_win(player));
}

bool FourxFour_Board::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}


/**
 * @brief Return list of empty adjacent cells to (row,col).
 */
vector<pair<int, int>> FourxFour_Board::get_adjacent(int row, int col) {
    vector<pair<int,int>> moves;
    int TestR[] = {-1, 1, 0, 0};
    int TestC[] = {0, 0, -1, 1};
    for(int i = 0; i < 4; i++) {
        int newr = row + TestR[i];
        int newc = col + TestC[i];
        if(in_bounds(newr,newc) && board[newr][newc] == blank_symbol) {
            moves.push_back({newr, newc});
        }

    }
    return moves;
}


/**
 * @brief Check for a winning 3-in-line for the given player symbol.
 */
bool FourxFour_Board::checking_win( char player) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 2; j++) {
            if(board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player)
                return true;
            if(board[j][i] == player && board[j+1][i] == player && board[j+2][i] == player)
                return true;
        }
    }
    int diagonals[4][3][2] = {
        {{0,0},{1,1},{2,2}}, {{0,1},{1,2},{2,3}},
        {{1,0},{2,1},{3,2}}, {{1,1},{2,2},{3,3}}
    };
    for(auto& d : diagonals) {
        if(board[d[0][0]][d[0][1]] == player &&
           board[d[1][0]][d[1][1]] == player &&
           board[d[2][0]][d[2][1]] == player)
            return true;
    }
    return false;
}


/**
 * @brief Basic evaluation returning large positive/negative for wins.
 */
int FourxFour_Board::evaluate1(char ai_symbol, char human_symbol) {
    if (checking_win(ai_symbol)) return 1000;
    if (checking_win(human_symbol)) return -1000;
    return 0;
}


const int MAX_DEPTH = 3;
/**
 * @brief Minimax with alpha-beta pruning. Depth-limited and returns evaluation score.
 */
int FourxFour_Board::minimax(char ai, char human, bool isMaximizingPlayer, int alpha, int beta, int depth) {
    int score = evaluate1(ai, human);
    if (score != 0) return score;
    if (depth == MAX_DEPTH) {
        return evaluation2(ai, human);
    }
    char current_sym = isMaximizingPlayer ? ai : human;
    vector<FourxFour_Move*> possible_moves = get_all_valid_moves(current_sym);
    if (possible_moves.empty()) {
        return 0;
    }
    int best_score = isMaximizingPlayer ? -100000 : 100000;
    for (size_t i = 0; i < possible_moves.size(); ++i) {
        FourxFour_Move* move = possible_moves[i];
        update_board(move);
        int current_score = minimax(ai, human, !isMaximizingPlayer, alpha, beta, depth + 1);
        board[move->getNewX()][move->getNewY()] = blank_symbol;
        board[move->get_x()][move->get_y()] = current_sym;
        if (isMaximizingPlayer) {
            best_score = max(best_score, current_score);
            alpha = max(alpha, best_score);
        } else {
            best_score = min(best_score, current_score);
            beta = min(beta, best_score);
        }
        delete move;
        if (beta <= alpha) {
            for (size_t j = i + 1; j < possible_moves.size(); ++j) {
                delete possible_moves[j];
            }
            return best_score;
        }
    }
    return best_score;
}

/**
 * @brief Count contiguous alignments of given length for heuristic scoring.
 * @param length length of contiguous alignment to check (e.g., 2)
 */
int FourxFour_Board::count_alignment(char symbol, int length) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - (length - 1); j++) {
            bool matches = true;
            for (int k = 0; k < length; k++) {
                if (board[i][j + k] != symbol) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                count++;
            }
        }
    }
    return count;
}

/**
 * @brief Heuristic evaluation used at depth limit combining alignments and wins.
 */
int FourxFour_Board::evaluation2(char ai, char human) {
    int value = 0;
    if (checking_win(ai)) value += 1000;
    value += count_alignment(ai, 2) * 10;
    value -= count_alignment(human, 2) * 10;
    return value;
}


/**
 * @brief Compute best move for AI by exploring valid moves and running minimax.
 * @return allocated FourxFour_Move* representing best move (caller takes ownership).
 */
FourxFour_Move* FourxFour_Board::best_move(char ai, char human) {
    int bestVal = -100000;
    FourxFour_Move* final_best_move = nullptr;
    int alpha = -100000;
    int beta = 100000;
    const int START_DEPTH = 0;
    vector<FourxFour_Move*> possible_moves = get_all_valid_moves(ai);
    if (possible_moves.empty()) return nullptr;
    vector<FourxFour_Move*> moves_to_delete;
    for (FourxFour_Move* move : possible_moves) {
        update_board(move);
        int moveVal = minimax(ai, human, false, alpha, beta, START_DEPTH + 1);
        board[move->getNewX()][move->getNewY()] = blank_symbol;
        board[move->get_x()][move->get_y()] = ai;
        if (moveVal > bestVal) {
            bestVal = moveVal;
            if (final_best_move) {
                moves_to_delete.push_back(final_best_move);
            }
            final_best_move = move;
        } else {
            moves_to_delete.push_back(move);
        }
        alpha = max(alpha, bestVal);
    }
    for (auto move : moves_to_delete) {
        delete move;
    }
    return final_best_move;
}

/**
 * @brief Enumerate all valid moves (moving any cell that contains player_symbol to adjacent empties).
 * @return vector of allocated FourxFour_Move* (caller must delete).
 */
vector<FourxFour_Move*> FourxFour_Board::get_all_valid_moves(char player_symbol) {
    vector<FourxFour_Move*> moves;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            if (board[r][c] == player_symbol) {
                vector<pair<int, int>> adj_empty_cells = get_adjacent(r, c);
                for (auto& dest : adj_empty_cells) {
                    moves.push_back(new FourxFour_Move(r, c, dest.first, dest.second, player_symbol));
                }
            }
        }
    }
    return moves;
}

//end of board implementation

/**
 * @class FourxFour_UI
 * @brief UI for FourxFour game: player creation and move acquisition.
 */

/**
 * @brief Construct UI instance.
 */
FourxFour_UI::FourxFour_UI() : UI<char>("Welcome , The Game has started",3) {}
FourxFour_UI::~FourxFour_UI() { }

/**
 * @brief Create a human or computer player object.
 */
Player<char> *FourxFour_UI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Get move for a player: for human solicit source/destination validated against board;
 * for computer return result of board.best_move.
 */
Move<char>* FourxFour_UI::get_move(Player<char>* player) {
    int oldX, oldY, newX, newY;
    FourxFour_Board* boardd = dynamic_cast<FourxFour_Board*>(player->get_board_ptr());
    if (!boardd) {
        cout << "Error: board pointer is not FourxFour_Board!" << endl;
        return nullptr;
    }
    if (player->get_type() == PlayerType::HUMAN) {
        bool valid = false;
        while (!valid) {
            cout << "\nEnter the token to move (oldX oldY): ";
            cin >> oldX >> oldY;
            cout << "Enter the destination (newX newY): ";
            cin >> newX >> newY;

            if (!boardd->in_bounds(oldX, oldY) || !boardd->in_bounds(newX, newY)) {
                cout << "Out of bounds! Try again.\n";
                continue;
            }

            if (!boardd->is_adjacent(oldX, oldY, newX, newY)) {
                cout << "Move not adjacent! Try again.\n";
                continue;
            }

            if (boardd->get_board_matrix()[oldX][oldY] != player->get_symbol() ) {
                cout << "Not your token at the selected cell! Try again.\n";
                continue;
            }

            if (boardd->get_board_matrix()[newX][newY] != '.') {
                cout << "Destination cell is not empty! Try again.\n";
                continue;
            }

            valid = true;
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        char ai=player->get_symbol();
        char player2 =(ai=='X')? 'O':'X';
        return boardd->best_move(ai, player2);
    }
    return new FourxFour_Move(oldX, oldY, newX, newY, player->get_symbol());
}

// end of UI implementation