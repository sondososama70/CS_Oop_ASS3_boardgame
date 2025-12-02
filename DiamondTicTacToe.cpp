#include "DiamondTicTacToe.h"
#include "BoardGame_Classes.h"
#include <iostream>
#include <algorithm>

using namespace std;

DiamondTicTacToe::DiamondTicTacToe() : Board<char>(5, 5) {
    n_moves = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (!inside_diamond(i, j)) {
                board[i][j] = '#';
            } else {
                board[i][j] = 0;
            }
        }
    }
}
char DiamondTicTacToe::get_cell(int r, int c) {
    return board[r][c];
}
void DiamondTicTacToe::set_cell(int r, int c, char symbol) {
    board[r][c] = symbol;
    if (symbol != 0 && symbol != '#') n_moves++;
    else if (symbol == 0) n_moves--;
}
bool DiamondTicTacToe::inside_diamond(int r, int c) {
    if (r == 0 || r == 4) return (c == 2);
    if (r == 1 || r == 3) return (c >= 1 && c <= 3);
    if (r == 2) return true;
    return false;
}
bool DiamondTicTacToe::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (x >= 0 && x < 5 && y >= 0 && y < 5 && inside_diamond(x, y) && board[x][y] == 0) {
        board[x][y] = move->get_symbol();
        n_moves++;
        return true;
    }
    return false;
}
int DiamondTicTacToe::checkLine(char symbol, int r, int c, int lr, int lc) {
    int count = 0;
    while (r >= 0 && r < 5 && c >= 0 && c < 5 && board[r][c] == symbol) {
        count++;
        r += lr;
        c += lc;
    }
    return count;
}
bool DiamondTicTacToe::is_win(Player<char>* player) {
    char s = player->get_symbol();
    bool has_3[4] = {false};
    bool has_4[4] = {false};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] != s) continue;

            int len = checkLine(s, i, j, 0, 1);
            if (len == 3) has_3[0] = true; if (len == 4) has_4[0] = true;

            len = checkLine(s, i, j, 1, 0);
            if (len == 3) has_3[1] = true; if (len == 4) has_4[1] = true;

            len = checkLine(s, i, j, 1, 1);
            if (len == 3) has_3[2] = true; if (len == 4) has_4[2] = true;

            len = checkLine(s, i, j, 1, -1);
            if (len == 3) has_3[3] = true; if (len == 4) has_4[3] = true;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (has_3[i]) {
            for (int j = 0; j < 4; j++) {
                if (has_4[j] && i != j) return true;
            }
        }
    }
    return false;
}

bool DiamondTicTacToe::is_lose(Player<char>* player) {
    return false;
}

bool DiamondTicTacToe::is_draw(Player<char>* player) {
    return (n_moves == 13 && !is_win(player));
}

bool DiamondTicTacToe::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

DiamondTicTacToeUI::DiamondTicTacToeUI() : UI<char>("Welcome to Diamond Tic-Tac-Toe! (Form a line of 3 and 4)", 3) {
}

Player<char>* DiamondTicTacToeUI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER) {
        return new DiamondAI(name, symbol);
    }
    return new Player<char>(name, symbol, type);
}

Player<char>** DiamondTicTacToeUI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> choices = {"Human", "Computer"};

    string name1 = get_player_name("Player 1 (X)");
    PlayerType type1 = get_player_type_choice("Player 1", choices);
    players[0] = create_player(name1, 'X', type1);

    string name2 = get_player_name("Player 2 (O)");
    PlayerType type2 = get_player_type_choice("Player 2", choices);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

Move<char>* DiamondTicTacToeUI::get_move(Player<char>* p) {
    if (p->get_type() == PlayerType::COMPUTER) {
        DiamondAI* ai = dynamic_cast<DiamondAI*>(p);
        if (ai != nullptr) {
            return ai->get_move(p);
        }
    }
    int x, y;
    while (true) {
        cout << p->get_name() << " (" << p->get_symbol() << ") please enter row and col : ";
        if (cin >> x >> y) {
            cin.ignore(1000, '\n');
            return new Move<char>(x, y, p->get_symbol());
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter numbers only.\n";
        }
    }
}

DiamondAI::DiamondAI(string name, char symbol) : Player<char>(name, symbol, PlayerType::COMPUTER) {}

Move<char>* DiamondAI::get_move(Player<char>* p) {
    DiamondTicTacToe* board = dynamic_cast<DiamondTicTacToe*>(this->boardPtr);

    int bestVal = -100000;
    Move<char>* bestMove = nullptr;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board->inside_diamond(i, j) && board->get_cell(i, j) == 0) {

                board->set_cell(i, j, symbol);
                int moveVal = minimax(board, 0, false);
                board->set_cell(i, j, 0);

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    delete bestMove;
                    bestMove = new Move<char>(i, j, symbol);
                }
            }
        }
    }
    return bestMove;
}

int DiamondAI::minimax(DiamondTicTacToe* board, int depth, bool isMaximizing) {

    if (depth > 4) return 0;

    if (board->is_win(this)) return 10 - depth;

    char dummyplayer = (symbol == 'X') ? 'O' : 'X';
    Player<char> dummy("dummy", dummyplayer, PlayerType::HUMAN);
    if (board->is_win(&dummy)) return -10 + depth;

    if (board->is_draw(this)) return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board->inside_diamond(i, j) && board->get_cell(i, j) == 0) {
                    board->set_cell(i, j, symbol);
                    best = max(best, minimax(board, depth + 1, false));
                    board->set_cell(i, j, 0);
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        char dummyplayer = (symbol == 'X') ? 'O' : 'X';
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board->inside_diamond(i, j) && board->get_cell(i, j) == 0) {
                    board->set_cell(i, j, dummyplayer);
                    best = min(best, minimax(board, depth + 1, true));
                    board->set_cell(i, j, 0);
                }
            }
        }
        return best;
    }
}