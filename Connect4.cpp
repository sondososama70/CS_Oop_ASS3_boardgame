#include "Connect4.h"

//CONNECT4 BOARD

Connect4_Board::Connect4_Board() : Board<char>(6, 7) {
    // Initialize board with spaces
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            board[i][j] = ' ';
}

bool Connect4_Board::update_board(Move<char>* move) {
    int col = move->get_y();
    char symbol = move->get_symbol();

    // Column out of bounds
    if (col < 0 || col >= columns)
        return false;

    // Column is full
    if (board[0][col] != ' ')
        return false;

    // Drop piece to lowest empty row
    for (int r = rows - 1; r >= 0; r--) {
        if (board[r][col] == ' ') {
            board[r][col] = symbol;
            n_moves++;
            return true;
        }
    }
    return false;
}

bool Connect4_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    // Horizontal
    for (int r = 0; r < rows; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == s && board[r][c+1] == s &&
                board[r][c+2] == s && board[r][c+3] == s)
                return true;

    // Vertical
    for (int c = 0; c < columns; c++)
        for (int r = 0; r <= rows - 4; r++)
            if (board[r][c] == s && board[r+1][c] == s &&
                board[r+2][c] == s && board[r+3][c] == s)
                return true;

    // Diagonal down-right
    for (int r = 0; r <= rows - 4; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == s && board[r+1][c+1] == s &&
                board[r+2][c+2] == s && board[r+3][c+3] == s)
                return true;

    // Diagonal up-right
    for (int r = 3; r < rows; r++)
        for (int c = 0; c <= columns - 4; c++)
            if (board[r][c] == s && board[r-1][c+1] == s &&
                board[r-2][c+2] == s && board[r-3][c+3] == s)
                return true;

    return false;
}

bool Connect4_Board::is_lose(Player<char>* player) {
    // Connect4 has no losing condition
    return false;
}

bool Connect4_Board::is_draw(Player<char>* player) {
    return (n_moves == rows * columns) && !is_win(player);
}

bool Connect4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//CONNECT4 PLAYER

Connect4_Player::Connect4_Player(string n, char s, PlayerType t)
    : Player<char>(n, s, t) {}

//CONNECT4 UI

Connect4_UI::Connect4_UI()
    : UI<char>("WELCOME TO CONNECT 4!", 6) {}
Connect4_UI::~Connect4_UI() {
}

Move<char>* Connect4_UI::get_move(Player<char>* player) {
    int col;
    cout << player->get_name()
         << " (" << player->get_symbol()
         << ") choose a column (0-6): ";
    cin >> col;

    return new Move<char>(0, col, player->get_symbol());
}

Player<char>* Connect4_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Connect4_Player(name, symbol, type);
}

