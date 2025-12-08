/**
 * @file Infinity_XO.h
 * @brief Defines the classes for the Infinity Tic-Tac-Toe game.
 *
 * This variant uses a limited 3x3 board where the oldest move is cleared (FIFO)
 * when a new move is made, giving the board a "sliding window" of recent moves.
 */
#ifndef INFINITY_XO_H
#define INFINITY_XO_H
#include <queue>

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Infinity_XO
 * @brief Implements the game logic for Infinity Tic-Tac-Toe (3x3 with move expiration).
 *
 * The game is played on a standard 3x3 board, but after 9 moves, every new move
 * replaces the oldest piece placed on the board.
 *
 * @see Board
 */
class Infinity_XO : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
public:
    /**
     * @brief Constructor for the Infinity_XO game board.
     * @details Initializes the board to 3x3.
     */
    Infinity_XO();
    /**
     * @brief Updates the board with a player's move, handling move expiration if the board is full.
     * @param move Pointer to the Move object containing coordinates and symbol.
     * @return true if the board was updated successfully, false otherwise.
     */
    bool update_board(Move<char> *move);
    /**
     * @brief Checks if the given player has won the game (standard 3-in-a-row).
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    bool is_win(Player<char>* player);
    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false.
     */
    bool is_lose(Player<char>* player);
    /**
     * @brief Checks if the game has ended in a draw.
     * @details A draw is determined by external logic, likely a set move limit or player agreement.
     * @param player Pointer to the player being checked.
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player);
    /**
     * @brief Determines if the game is over.
     * @details This game typically runs until a win condition is met, so it may never return true unless a draw limit is set.
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);
    /**
     * @brief Queue to store the coordinates of moves in FIFO order.
     * @details Used to track the oldest move to be cleared when the board is full.
     */
    queue<pair<int,int>> moves;
};

/**
 * @class Infinity_XO_UI
 * @brief User Interface class for Infinity Tic-Tac-Toe.
 *
 * @see UI
 */
class Infinity_XO_UI : public UI<char> {
public:
    /**
     * @brief Constructor for Infinity_XO_UI.
     */
    Infinity_XO_UI();
    /**
     * @brief Destructor for Infinity_XO_UI.
     */
    ~Infinity_XO_UI();

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object.
     */
    Move<char>* get_move(Player<char>* player) override;
};


#endif //INFINITY_XO_H





// #ifndef INFINITY_XO_H
// #define INFINITY_XO_H
// #include <queue>
//
// #include "BoardGame_Classes.h"
// using namespace std;
//
// class Infinity_XO : public Board<char> {
// private:
//     char blank_symbol = '.';
// public:
//     Infinity_XO();
//     bool update_board(Move<char> *move);
//     bool is_win(Player<char>* player);
//     bool is_lose(Player<char>* player);
//     bool is_draw(Player<char>* player);
//     bool game_is_over(Player<char>* player);
//     queue<pair<int,int>> moves;
// };
//
// class Infinity_XO_UI : public UI<char> {
// public:
//     Infinity_XO_UI();
//     ~Infinity_XO_UI();
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override;
//     Move<char>* get_move(Player<char>* player) override;
// };
//
//
// #endif //INFINITY_XO_H