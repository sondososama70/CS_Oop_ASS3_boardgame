#include "Memory_XO.h"
using namespace std;

/**
 * @class Memory_XO
 * @brief Board variant for Memory Tic-Tac-Toe.
 *
 * Attributes:
 * - hiddenboard : 3x3 matrix storing underlying symbols (0 when hidden)
 * - board : visible board (uses '?' for revealed)
 * - n_moves : number of revealed moves
 */

/**
 * @brief Construct a new Memory_XO board.
 *
 * Initializes both visible and hidden boards to 0/empty.
 */
Memory_XO::Memory_XO() : Board(3 , 3) {
    // Initialize all cells with blank_symbol
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
            hiddenboard[i][j] = 0;
        }
    }
}

/**
 * @brief Reveal a hidden symbol at (x,y) by placing the player's symbol in hiddenboard and marking visible board.
 * @param move Pointer to Move<char> containing x, y and symbol to reveal.
 * @return true if reveal succeeded (in bounds and currently hidden), false otherwise.
 */
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

/**
 * @brief Check if the given player has a winning three-in-a-row on the hidden board.
 * @param player Player whose symbol is tested.
 * @return true if player has a winning line in hiddenboard.
 */
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

/**
 * @brief Memory_XO has no explicit lose state separate from win (placeholder).
 * @param unused Player pointer (not used).
 * @return always false.
 */
bool Memory_XO::is_lose(Player<char> *) {
    return false;
}

/**
 * @brief Draw condition: all reveals used and no losing state.
 * @param player Player pointer (unused for draw detection beyond moves).
 * @return true if draw.
 */
bool Memory_XO::is_draw(Player<char> *player) {
    return (n_moves == 9 && !is_lose(player));
}

/**
 * @brief Game ends if a player has a win or the game is a draw.
 * @param player Player pointer to evaluate against win/draw.
 * @return true if the game is over.
 */
bool Memory_XO::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);

}

//UI implementation:

/**
 * @class Memory_XO_UI
 * @brief UI for Memory Tic-Tac-Toe: prompts, player setup and move input.
 */

/**
 * @brief Construct a new Memory_XO_UI object.
 */
Memory_XO_UI::Memory_XO_UI() : UI<char>("Welcome to Memory Tic-Tac-Toe! (Hidden Symbols)", 3) {}

/**
 * @brief Set up two players (human/computer) and return allocated array of Player pointers.
 * @return Player<char>** array of two created players.
 */
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

/**
 * @brief Factory for creating Player objects for this UI.
 * @param name Player name.
 * @param symbol Player symbol.
 * @param type PlayerType enum for human/computer.
 * @return newly allocated Player<char>*.
 */
Player<char>* Memory_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Obtain next Move for the given player. For computer, picks a random cell.
 * For human, asks for x and y coordinates with input validation.
 * @param player Pointer to Player requesting the move.
 * @return allocated Move<char>* with chosen coordinates and symbol.
 */
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