/**
 * @file FiveByFive.h
 * @brief Defines the 5x5 Tic-Tac-Toe game board and UI classes.
 *
 * This file contains the declarations for the FiveByFive game logic,
 * inheriting from the generic Board and UI classes defined in BoardGame_Classes.h.
 */
#ifndef FIVEBYFIVE_H
#define FIVEBYFIVE_H
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class FiveByFive
 * @brief Represents the 5x5 Tic-Tac-Toe game board where the winner is determined by counting 3-in-a-row sequences.
 * @details The game is played on a 5x5 board, and the winner is the player who has more 3-in-a-row sequences
 * (horizontal, vertical, or diagonal) when the board is full (24 moves).
 * Inherits from Board<char>.
 *
 * @see Board
 */
class FiveByFive : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
    /**
     * @brief Helper function to count the number of 3-in-a-row sequences for a given symbol.
     * @param sym The character symbol ('X' or 'O') to count sequences for.
     * @return The total number of 3-in-a-row sequences found on the board.
     */
    int count_sequences(char sym);
public:
    /**
     * @brief Default constructor that initializes a 5x5 board.
     * @details Initializes all cells with the blank symbol ('.').
     */
    FiveByFive();
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);
    /**
     * @brief Checks if the given player has won the game.
     * @details A win occurs if the player has more 3-in-a-row sequences than their opponent after 24 moves.
     * @param player Pointer to the player being checked.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player);
    /**
     * @brief Checks if the given player has lost the game.
     * @details A loss occurs if the player has fewer 3-in-a-row sequences than their opponent after 24 moves.
     * @param player Pointer to the player being checked.
     * @return true if the player has lost, false otherwise.
     */
    bool is_lose(Player<char>*);
    /**
     * @brief Checks if the game has ended in a draw.
     * @details A draw occurs if both players have the same number of 3-in-a-row sequences after 24 moves.
     * @param player Pointer to the player being checked.
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player);
    /**
     * @brief Determines if the game is over (when all but one cell are filled).
     * @param player Pointer to the player to evaluate (ignored).
     * @return true if 24 moves have been made, false otherwise.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class FiveByFive_UI
 * @brief User Interface class for the 5x5 Tic-Tac-Toe game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * 5x5 game-specific functionality for player setup and move input.
 *
 * @see UI
 */
class FiveByFive_UI : public UI<char> {
public:
    /**
     * @brief Constructs a FiveByFive_UI object.
     * @details Initializes the base `UI<char>` class with the welcome message "Welcome to 5x5 Tic-Tac-Toe" and board size 5.
     */
    FiveByFive_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe", 5) {}
    /**
     * @brief Destructor for FiveByFive_UI.
     */
    ~FiveByFive_UI() {}

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        return new Player<char>(name, symbol, type);
    }

    /**
     * @brief Retrieves the next move from a player.
     * @details Prompts human players for row and column (0-4). Generates random valid coordinates for computer players.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object representing the player's action.
     */
    virtual Move<char>* get_move(Player<char>* player) override {
        int row , column;
        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column: ";
            cin >> row >> column;
        }
        else if (player->get_type() == PlayerType::COMPUTER) {
            // Simple random move for computer player
            row = rand() % player->get_board_ptr()->get_rows();
            column = rand() % player->get_board_ptr()->get_columns();
            cout << "Computer " << player->get_name() << " chooses: (" << row << ", " << column << ")\n";
        }
        return new Move<char>(row, column, player->get_symbol());
    }
};

#endif //FIVEBYFIVE_H





// #ifndef FIVEBYFIVE_H
// #define FIVEBYFIVE_H
// #include "BoardGame_Classes.h"
// using namespace std;
//
// class FiveByFive : public Board<char> {
// private:
//     char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
//     int count_sequences(char sym);
// public:
//     FiveByFive();
//     bool update_board(Move<char>* move);
//     bool is_win(Player<char>* player);
//     bool is_lose(Player<char>*);
//     bool is_draw(Player<char>* player);
//     bool game_is_over(Player<char>* player);
// };
// class FiveByFive_UI : public UI<char> {
// public:
//     FiveByFive_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe", 5) {}
//     ~FiveByFive_UI() {}
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override {
//         return new Player<char>(name, symbol, type);
//     }
//
//     virtual Move<char>* get_move(Player<char>* player) override {
//         int row , column;
//         if (player->get_type() == PlayerType::HUMAN) {
//             cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column: ";
//             cin >> row >> column;
//         }
//         else if (player->get_type() == PlayerType::COMPUTER) {
//             // Simple random move for computer player
//             row = rand() % player->get_board_ptr()->get_rows();
//             column = rand() % player->get_board_ptr()->get_columns();
//             cout << "Computer " << player->get_name() << " chooses: (" << row << ", " << column << ")\n";
//         }
//         return new Move<char>(row, column, player->get_symbol());
//     }
// };
//
// #endif //FIVEBYFIVE_H
