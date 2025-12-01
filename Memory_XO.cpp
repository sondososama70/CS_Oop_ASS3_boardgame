#include "Memory_XO.h"
using namespace std;

Memory_XO::Memory_XO() : Board(3 , 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
}

bool Memory_XO::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
        }
    return false;
}

bool Memory_XO::is_win(Player<char> *player) {

}

bool Memory_XO::is_lose(Player<char> *) {

}

bool Memory_XO::is_draw(Player<char> *player) {

}

bool Memory_XO::game_is_over(Player<char> *player) {

}

//UI implementation:
Memory_XO_UI::Memory_XO_UI() : UI<char>("Welcome to the memory XO Board" , 3) {}

Player<char>* Memory_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Memory_XO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}