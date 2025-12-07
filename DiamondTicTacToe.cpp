#include "DiamondTicTacToe.h"
#include "BoardGame_Classes.h"
#include <iostream>
#include <algorithm>

using namespace std;

DiamondTicTacToe::DiamondTicTacToe() : Board<char>(7, 7) {
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
    if (r == 0 || r == 6) return (c == 3);
    if (r == 1 || r == 5) return (c >= 2 && c <= 4);
    if (r == 4 || r == 2) return (c >= 1 && c <= 5);
    if (r == 3) return true;
    return false;
}

bool DiamondTicTacToe::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (x >= 0 && x < 7 && y >= 0 && y < 7 && inside_diamond(x, y) && board[x][y] == 0) {
        board[x][y] = move->get_symbol();
        n_moves++;
        return true;
    }
    return false;
}
int DiamondTicTacToe::checkLine(char symbol, int r, int c, int lr, int lc) {
    int count = 0;
    while (r >= 0 && r < 7 && c >= 0 && c < 7 && board[r][c] == symbol) {
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

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
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
    return (n_moves == 25 && !is_win(player));
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
    DiamondTicTacToe* board = dynamic_cast<DiamondTicTacToe*>(boardPtr);
    char opp = (symbol == 'X') ? 'O' : 'X';

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {
            if (!board->inside_diamond(r, c) || board->get_cell(r, c) != 0) continue;

            board->set_cell(r, c, symbol);
            if (board->is_win(this)) {
                board->set_cell(r, c, 0);
                return new Move<char>(r, c, symbol);
            }
            board->set_cell(r, c, 0);
        }
    }
    Player<char> dummy("dummy", opp, PlayerType::HUMAN);
    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {
            if (!board->inside_diamond(r, c) || board->get_cell(r, c) != 0) continue;

            board->set_cell(r, c, opp);
            if (board->is_win(&dummy)) {
                board->set_cell(r, c, 0);
                return new Move<char>(r, c, symbol);
            }
            board->set_cell(r, c, 0);
        }
    }

    int bestDist = 1000;
    Move<char>* bestMove = nullptr;

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 7; c++) {
            if (!board->inside_diamond(r, c) || board->get_cell(r, c) != 0) continue;

            int dist = abs(r - 3) + abs(c - 3);
            if (dist < bestDist) {
                bestDist = dist;
                delete bestMove;
                bestMove = new Move<char>(r, c, symbol);
            }
        }
    }

    return bestMove;
}
