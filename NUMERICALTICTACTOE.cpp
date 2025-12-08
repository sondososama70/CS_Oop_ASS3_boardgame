#include "BoardGame_Classes.h"
#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include "NUMERICALTICTACTOE.h"
NumericalBoard::NumericalBoard() : Board(3, 3) {
    n_moves = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = 0;
        }
    }
}

/**
 * @brief Attempt to place a number at (x,y).
 * Validates bounds, cell vacancy, number range, uniqueness and parity rule.
 * @param move Pointer to Move<int> with coordinates and the number to place.
 * @return true if placement successful; false otherwise.
 */
bool NumericalBoard::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0) {
      cout << "Invalid cell" << endl;
      return false;
    }
    if (num < 1 || num > 9 ) {
        cout << " Number must be between 1 and 9 " << endl;
        return false;
    }
    if (used_numbers.count(num)) {
        cout << " Number already played " << endl;
        return false;
    }
    bool isOdd = (num % 2 != 0);
    bool firstPlayerTurn = (n_moves % 2 == 0);
    if ((firstPlayerTurn && !isOdd) || (!firstPlayerTurn && isOdd)) {
        return false;
    }
    board[x][y] = num;
    used_numbers.insert(num);
    n_moves++;
    return true;
}

/**
 * @brief Check whether any row/column/diagonal sums to 15 using placed numbers.
 * @return true if there exists a line summing to 15.
 */
bool NumericalBoard:: checkSum() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] && board[i][1] && board[i][2] &&
           (board[i][0] + board[i][1] + board[i][2] == 15)) return true;
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] && board[1][i] && board[2][i] &&
           (board[0][i] + board[1][i] + board[2][i] == 15)) return true;
    }
    if (board[0][0] && board[1][1] && board[2][2] &&
       (board[0][0] + board[1][1] + board[2][2] == 15)) return true;
    if (board[0][2] && board[1][1] && board[2][0] &&
       (board[0][2] + board[1][1] + board[2][0] == 15)) return true;

    return false;
}

/**
 * @brief Game win if any line sums to 15.
 */
bool NumericalBoard::is_win(Player<int>* player) { return checkSum(); }

/**
 * @brief No separate lose implementation for this game.
 */
bool NumericalBoard::is_lose(Player<int>* player) { return false; }

/**
 * @brief Draw when board full and no winning sum.
 */
bool NumericalBoard::is_draw(Player<int>* player) { return (n_moves == 9 && !is_win(player)); }

/**
 * @brief Game over when win or draw.
 */
bool NumericalBoard::game_is_over(Player<int>* player) { return is_win(player) || is_draw(player); }

/**
 * @class NumericalUI
 * @brief User interface for numerical tic-tac-toe: player setup and move input.
 */

/**
 * @brief Construct a new NumericalUI.
 */
NumericalUI::NumericalUI() : UI("Welcome to Numerical Tic Tac Toe", 3) {}

/**
 * @brief Prompt for two player names and return created Player<int>* array.
 * Player 1 (odds) and Player 2 (evens).
 */
Player<int>** NumericalUI :: setup_players() {
    Player<int>** players = new Player<int>*[2];
    string name1, name2;

    cout << "Enter name of Player 1 (odd numbers): ";
    cin >> name1;
    players[0] = create_player(name1, 1, PlayerType::HUMAN);

    cout << "Enter name of Player 2 (even numbers): ";
    cin >> name2;
    players[1] = create_player(name2, 2, PlayerType::HUMAN);

    return players;
}

/**
 * @brief Get a move from the player: asks for x,y and the number to place.
 * @param player Pointer to requesting player.
 * @return allocated Move<int>* with coordinates and number.
 */
Move<int>* NumericalUI::get_move(Player<int>* player) {
    int x, y, num;
    cout << player->get_name() << " (Symbol: " << player->get_symbol() << ")"
         << ", Please enter x, y, and number: ";
    cin >> x >> y >> num;
    return new Move<int>(x, y, num);
}

/**
 * @brief Create and return a Player<int> instance.
 */
Player<int>* NumericalUI::create_player(string& name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}