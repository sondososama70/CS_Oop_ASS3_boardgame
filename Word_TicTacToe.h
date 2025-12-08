/**
 * @file Word_TicTacToe.h
 * @brief Defines the Word_TicTacToe game board and UI classes.
 *
 * This file contains the declarations for the Word_TicTacToe game logic,
 * inheriting from the generic Board and UI classes defined in BoardGame_Classes.h.
 */
#ifndef WORD_TICTACTOE_H
#define WORD_TICTACTOE_H
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Word_TicTacToe
 * @brief Implements the game logic for Word TicTacToe on a 3x3 board.
 * @details Players win by forming a valid 3-letter word horizontally, vertically, or diagonally.
 * The game uses an external dictionary file for validation.
 * Inherits from Board<char>.
 *
 * @see Board
 */
class Word_TicTacToe : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
public:
    /**
     * @brief Default constructor that initializes a 3x3 Word TicTacToe board.
     * @details Initializes all cells with the blank symbol ('.') and loads the dictionary.
     */
    Word_TicTacToe();
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the Move object containing coordinates and symbol (letter).
     * @return true if the board was updated successfully, false otherwise (e.g., invalid coordinates or cell occupied).
     */
    bool update_board(Move<char>* move);
    /**
     * @brief Checks if the current state is a win for any player.
     * @param player Pointer to the current player (not directly used for the check).
     * @return true if a 3-letter word is formed along any line, false otherwise.
     */
    bool is_win(Player<char>* player);
    /**
     * @brief Checks if the current state is a loss for the player.
     * @param player Pointer to the current player.
     * @return Always returns false (not used in Word TicTacToe logic).
     */
    bool is_lose(Player<char>*);
    /**
     * @brief Checks if the current state is a draw.
     * @param player Pointer to the current player.
     * @return true if the board is full and no winning word has been formed.
     */
    bool is_draw(Player<char>* player);
    /**
     * @brief Checks if the game is over (win or draw).
     * @param player Pointer to the current player.
     * @return true if the game has ended.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class Word_TicTacToe_UI
 * @brief User Interface class for Word TicTacToe.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * game-specific functionality for player setup and letter/coordinate input.
 *
 * @see UI
 */
class Word_TicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructor for the UI, initializing the welcome message and board dimensions.
     * @details Initializes the base `UI<char>` class with the welcome message "Welcome to Word TicTacToe" and board size 3.
     */
    Word_TicTacToe_UI();
    /**
     * @brief Destructor for the UI class.
     */
    ~Word_TicTacToe_UI();

    /**
     * @brief Creates a new Player object (human or computer).
     * @param name Reference to the player's name string.
     * @param symbol The character symbol (letter) assigned to the player.
     * @param type The PlayerType (\c HUMAN or \c COMPUTER).
     * @return A pointer to the newly created Player<char> object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    /**
     * @brief Prompts the user or generates a move for the computer.
     * @details For human players, prompts for row, column, and a letter with input validation.
     * For computer players, generates a simple random move.
     * @param player Pointer to the Player whose turn it is.
     * @return A pointer to a newly created Move<char> object.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif //WORD_TICTACTOE_H






// #ifndef WORD_TICTACTOE_H
// #define WORD_TICTACTOE_H
// #include "BoardGame_Classes.h"
// using namespace std;
//
// class Word_TicTacToe : public Board<char> {
// private:
//     char blank_symbol = '.';
// public:
//     Word_TicTacToe();
//     bool update_board(Move<char>* move);
//     bool is_win(Player<char>* player);
//     bool is_lose(Player<char>*);
//     bool is_draw(Player<char>* player);
//     bool game_is_over(Player<char>* player);
// };
//
// class Word_TicTacToe_UI : public UI<char> {
// public:
//     Word_TicTacToe_UI();
//     ~Word_TicTacToe_UI();
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override;
//     Move<char>* get_move(Player<char>* player) override;
// };
//
// #endif //WORD_TICTACTOE_H