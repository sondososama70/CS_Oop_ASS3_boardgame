//
// Created by HP on 11/26/2025.
//

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

bool FourxFour_Board::in_bounds(int r, int c) const {
    if (r >=0 && r <= 3 && c >= 0 && c <= 3) {
        return true;
    }
    return false;
}

bool FourxFour_Board::is_adjacent(int r, int c, int newr, int newc) const {
    if (abs(r - newr)+ abs(c-newc)==1) {
        return true;
    }
    return false;
}

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

bool FourxFour_Board::is_win(Player<char> *player) {
    const char sym =player->get_symbol();
    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };
    for (int i = 0; i <3; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }
    for (int i = 1; i <rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }
    for (int i = 1; i <rows; ++i) {
        if ((all_equal(board[i][1], board[i][2], board[i][3]) && board[i][1] == sym) ||
            (all_equal(board[1][i], board[2][i], board[3][i]) && board[1][i] == sym))
            return true;
    }
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
            return true;

    if ((all_equal(board[0][1], board[1][2], board[2][3]) && board[1][2] == sym) ||
        (all_equal(board[0][3], board[1][2], board[2][1]) && board[1][2 ] == sym))
        return true;

    if ((all_equal(board[1][0], board[2][1], board[3][2]) && board[2][1] == sym) ||
        (all_equal(board[1][2], board[2][1], board[3][0]) && board[2][1] == sym))
        return true;

    if ((all_equal(board[1][1], board[2][2], board[3][3]) && board[2][2] == sym) ||
        (all_equal(board[1][3], board[2][2], board[3][1]) && board[2][2] == sym))
        return true;



    return false;

}

bool FourxFour_Board::is_draw(Player<char> *player) {
    return (n_moves==16 && !is_win(player));
}

bool FourxFour_Board::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}


//end of board implementation


FourxFour_UI::FourxFour_UI() : UI<char>("Welcome , The Game has started",3) {}
FourxFour_UI::~FourxFour_UI() { }
Player<char> *FourxFour_UI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);

}

Move<char>* FourxFour_UI::get_move(Player<char>* player) {
    int oldX, oldY, newX, newY;


    FourxFour_Board* board = dynamic_cast<FourxFour_Board*>(player->get_board_ptr());
    if (!board) {
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

            if (!board->in_bounds(oldX, oldY) || !board->in_bounds(newX, newY)) {
                cout << "Out of bounds! Try again.\n";
                continue;
            }

            if (!board->is_adjacent(oldX, oldY, newX, newY)) {
                cout << "Move not adjacent! Try again.\n";
                continue;
            }

            if (board->get_board_matrix()[oldX][oldY] != player->get_symbol()) {
                cout << "Not your token at the selected cell! Try again.\n";
                continue;
            }

            if (board->get_board_matrix()[newX][newY] != '.') {
                cout << "Destination cell is not empty! Try again.\n";
                continue;
            }

            valid = true;
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        bool valid = false;
        while (!valid) {
            oldX = rand() % board->get_rows();
            oldY = rand() % board->get_columns();
            newX = rand() % board->get_rows();
            newY = rand() % board->get_columns();

            if (board->get_board_matrix()[oldX][oldY] != player->get_symbol())
                continue;

            if (!board->is_adjacent(oldX, oldY, newX, newY))
                continue;

            if (board->get_board_matrix()[newX][newY] != '.')
                continue;

            valid = true;
        }
        cout << "Computer moves from (" << oldX << "," << oldY << ") to ("
             << newX << "," << newY << ")\n";
    }


    return new FourxFour_Move(oldX, oldY, newX, newY, player->get_symbol());
}

// end of UI implementation