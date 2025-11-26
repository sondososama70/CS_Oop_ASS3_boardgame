#include "miser.h"
#include "BoardGame_Classes.h"

miser::miser() : Board<char>(3, 3) {
    n_moves = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = 0;
        }
    }
}
bool miser::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0) {
        cout << "Invalid cell" << endl;
        return false;
    }
        board[x][y] = move->get_symbol();
        n_moves++;
        return true;
}
bool miser::is_win(Player<char>* p) {
    return false;
}
bool miser::is_lose(Player<char>* p) {
    char symbol = p->get_symbol();
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
    return false;
}
bool miser::is_draw(Player<char>* p) {
    return (n_moves == 9 && !is_lose(p));
}
bool miser::game_is_over(Player<char>* p) {
    return is_lose(p) || is_draw(p);
}
MiserUI::MiserUI() : UI("Welcome to Misere Tic Tac Toe Game!", 3) {
}
Player<char>** MiserUI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    string name1;
    cout << "Enter name of Player 1 (Symbol X): ";
    cin >> name1;
    players[0] = create_player(name1, 'X', PlayerType::HUMAN);
    string name2;
    cout << "Enter name of Player 2 (Symbol O): ";
    cin >> name2;
    players[1] = create_player(name2, 'O', PlayerType::HUMAN);
    return players;
}
Move<char>* MiserUI::get_move(Player<char>* player) {
    int x, y;
    cout << player->get_name() << " (" << player->get_symbol() << ")"
         << ", Please enter x and y : ";
    cin >> x >> y;
    return new Move<char>(x, y, player->get_symbol());
}
Player<char>* MiserUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

