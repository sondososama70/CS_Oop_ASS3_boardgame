#include "Memory_XO.h"
using namespace std;

Memory_XO::Memory_XO() : Board(3 , 3) {
    // Initialize all cells with blank_symbol
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
            hiddenboard[i][j] = 0;
        }
    }
}

bool Memory_XO::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();

    if (x >= 0 && x < 3 && y >= 0 && y < 3 && hiddenboard[x][y] == 0) {
        hiddenboard[x][y] = move->get_symbol();
        board[x][y] = '?';
        n_moves++;
        return true;

    }
    return false;

}

bool Memory_XO::is_win(Player<char> *player) {
    char symbol = player->get_symbol();
    for (int i = 0; i < 3; i++) {
        if (hiddenboard[i][0] == symbol && hiddenboard[i][1] == symbol && hiddenboard[i][2] == symbol) return true;
        if (hiddenboard[0][i] == symbol && hiddenboard[1][i] == symbol && hiddenboard[2][i] == symbol) return true;
    }
    if (hiddenboard[0][0] == symbol && hiddenboard[1][1] == symbol && hiddenboard[2][2] == symbol) return true;
    if (hiddenboard[0][2] == symbol && hiddenboard[1][1] == symbol && hiddenboard[2][0] == symbol) return true;
    return false;
}

bool Memory_XO::is_lose(Player<char> *) {
    return false;
}

bool Memory_XO::is_draw(Player<char> *player) {
    return (n_moves == 9 && !is_lose(player));
}

bool Memory_XO::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);

}

//UI implementation:
Memory_XO_UI::Memory_XO_UI() : UI<char>("Welcome to Memory Tic-Tac-Toe! (Hidden Symbols)", 3) {}

Player<char>** Memory_XO_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> choices = {"Human", "Computer"};

    string name1;
    cout << "Enter name of Player 1 (Symbol X): ";
    cin >> name1;
    PlayerType type1 = get_player_type_choice("Player 1", choices);
    players[0] = create_player(name1, 'X', type1);

    string name2;
    cout << "Enter name of Player 2 (Symbol O): ";
    cin >> name2;
    PlayerType type2 = get_player_type_choice("Player 2", choices);
    players[1] = create_player(name2, 'O', type2);

    return players;
}

Player<char>* Memory_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
Move<char>* Memory_XO_UI::get_move(Player<char>* player) {

    if (player->get_type() == PlayerType::COMPUTER) {
        int x = rand() % 3;
        int y = rand() % 3;
        return new Move<char>(x, y, player->get_symbol());
    }

    int x, y;
    while(true) {
        cout << player->get_name() << " (" << player->get_symbol() << ")"
             << ", Please enter x and y : ";

        if (cin >> x >> y) {
            return new Move<char>(x, y, player->get_symbol());
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Numbers only.\n";
        }
    }
}