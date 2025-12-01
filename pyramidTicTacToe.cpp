//
// Created by HP on 12/1/2025.
//

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
bool pyramidTicTacToe_board::in_bounds(int row, int col) {
        if (row < 0 || row >= 3) return false;
        switch(row) {
            case 0: return col == 2;
            case 1: return col >= 1 && col <= 3;
            case 2: return col >= 0 && col <= 4;
            default: return false;
        }
}

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
bool pyramidTicTacToe_board::is_win(Player<char> *player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };

    // diagonals
    if ((all_equal(board[0][2], board[1][3], board[2][4]) && board[1][3] == sym)||(all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym)) {
        return true;
    }

    // vertical
    if ((all_equal(board[0][2], board[1][2], board[2][2]) && board[1][2] == sym)) {
        return true;
    }

    //horizontal
    if ((all_equal(board[1][1], board[1][2], board[1][3]) && board[1][2] == sym)||
        (all_equal(board[2][0], board[2][1], board[2][2]) && board[2][1] == sym)||
        (all_equal(board[2][1], board[2][2], board[2][3]) && board[2][2] == sym)||
        (all_equal(board[2][2], board[2][3], board[2][4]) && board[2][3] == sym) ) {
        return true;
    }

    return false;
}

bool pyramidTicTacToe_board::is_draw(Player<char> *player) {
    return (n_moves==9 && !is_win(player));
}

bool pyramidTicTacToe_board::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}


//end of board implementation

pyramid_tic_tac_toe_UI::pyramid_tic_tac_toe_UI() :UI<char>("Pyramid Tic Tac Toe Game has started",3) {}

pyramid_tic_tac_toe_UI::~pyramid_tic_tac_toe_UI() {}

Player<char>* pyramid_tic_tac_toe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

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
        bool valid_move = false;
        while (!valid_move) {
            row=rand() % board->get_rows();
            col=rand() % board->get_columns();
            if (board->get_board_matrix()[row][col] != '.') {
                continue;
            }
            if (!board->in_bounds(row, col)) {
                continue;
            }
            valid_move = true;
        }
        cout << "the computer chose " << row << ", " << col << "\n";
    }
    return new Move<char> (row, col,player->get_symbol());
}

//end of UI implemetation