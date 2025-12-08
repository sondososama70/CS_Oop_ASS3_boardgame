/**
 * @file Connect4.h
 * @brief Defines the classes for the Connect Four game.
 *
 * This file includes the specialized board, player, and UI classes
 * for a Connect Four game, inheriting from the generic BoardGame_Classes.
 */

#ifndef CONNECT4_H
#define CONNECT4_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

/**
 * @class Connect4_Board
 * @brief Represents the Connect Four game board (typically 6 rows x 7 columns).
 *
 * Implements the logic for placing pieces by column and checking for four-in-a-row
 * win conditions.
 *
 * @see Board
 */
class Connect4_Board : public Board<char> {
public:
    /**
     * @brief Constructor for the Connect4_Board.
     * @details Initializes the board structure (likely 6x7).
     */
    Connect4_Board();

    /**
     * @brief Updates the board with a player's move.
     * @details Connect Four moves are typically specified by column, and the piece falls to the lowest available row.
     * @param move Pointer to a Move<char> object containing the target column and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;
    /**
     * @brief Checks if the given player has won the game.
     * @details Checks for four consecutive pieces (horizontal, vertical, or diagonal).
     * @param player Pointer to the player being checked.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;
    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (loss is equivalent to opponent's win).
     */
    bool is_lose(Player<char>* player) override;
    /**
     * @brief Checks if the game has ended in a draw.
     * @details A draw occurs if the board is full and no player has won.
     * @param player Pointer to the player being checked.
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;
    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class Connect4_Player
 * @brief Represents a player in the Connect Four game.
 *
 * @see Player
 */
class Connect4_Player : public Player<char> {
public:
    /**
     * @brief Constructor for the Connect4_Player.
     * @param n The name of the player.
     * @param s The symbol/mark ('X' or 'O') of the player.
     * @param t The type of the player (Human or Computer).
     */
    Connect4_Player(string n, char s, PlayerType t);
};

/**
 * @class Connect4_UI
 * @brief User Interface class for the Connect Four game.
 *
 * @see UI
 */
class Connect4_UI : public UI<char> {
public:
    /**
     * @brief Constructor for Connect4_UI.
     */
    Connect4_UI();
    /**
     * @brief Destructor for Connect4_UI.
     */
    ~Connect4_UI();
    /**
     * @brief Retrieves the next move from a player.
     * @details Prompts the user for the column number to drop a piece.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object.
     */
    Move<char>* get_move(Player<char>* player) override;
    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif





// #ifndef CONNECT4_H
// #define CONNECT4_H
//
// #include "BoardGame_Classes.h"
// #include <iostream>
// using namespace std;
//
// //CONNECT4 BOARD
//
// class Connect4_Board : public Board<char> {
// public:
//     Connect4_Board();
//
//     bool update_board(Move<char>* move) override;
//     bool is_win(Player<char>* player) override;
//     bool is_lose(Player<char>* player) override;
//     bool is_draw(Player<char>* player) override;
//     bool game_is_over(Player<char>* player) override;
// };
//
// //CONNECT4 PLAYER
//
// class Connect4_Player : public Player<char> {
// public:
//     Connect4_Player(string n, char s, PlayerType t);
// };
//
// //CONNECT4 UI
// class Connect4_UI : public UI<char> {
// public:
//     Connect4_UI();
//     ~Connect4_UI();
//     Move<char>* get_move(Player<char>* player) override;
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override;
// };
//
// #endif
//
