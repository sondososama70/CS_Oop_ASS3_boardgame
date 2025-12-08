/**
 * @file SUS.h
 * @brief Defines the classes for the SUS game, including the AI Player and UI.
 *
 * This game uses a scoring system, where the objective is to maximize a player's
 * score based on the specific "SUS" pattern on the board.
 */
#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
#include <vector>
#include <iostream>

/**
 * @class SUS
 * @brief Implements the game logic for the SUS Game (a scoring variant of Tic-Tac-Toe).
 *
 * The game is played on a 3x3 board, where the winner is determined by counting
 * specific patterns ("SUS") after the board is full.
 *
 * @see Board
 */
class SUS : public Board<char> {
private:
    int score_p1; ///< Score for player 1.
    int score_p2; ///< Score for player 2.

public:
    /**
     * @brief Constructor for the SUS board.
     */
    SUS();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the Move object containing coordinates and symbol.
     * @return true if the board was updated successfully, false otherwise.
     */
    bool update_board(Move<char>* move) override;
    /**
     * @brief Checks if the given player has won the game (by having a higher score after the board is full).
     * @param player Pointer to the player being checked.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;
    /**
     * @brief Checks if the given player has lost the game (by having a lower score after the board is full).
     * @param player Pointer to the player being checked.
     * @return true if the player has lost, false otherwise.
     */
    bool is_lose(Player<char>* player) override ;
    /**
     * @brief Checks if the game has ended in a draw (by having equal scores after the board is full).
     * @param player Pointer to the player being checked.
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;
    /**
     * @brief Determines if the game is over (when the board is full - 9 moves).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Counts the score/pattern occurrences for a player (either 'S' or 'U').
     * @return The calculated score/count of the 'SUS' pattern.
     */
    int count_SUS();
    /**
     * @brief Gets the current score for the player using symbol 'S'.
     * @return The score of player 1.
     */
    int get_score_s() const;
    /**
     * @brief Gets the current score for the player using symbol 'U'.
     * @return The score of player 2.
     */
    int get_score_u() const;

    /**
     * @brief Prints the current scores for both players.
     */
    void display_scores() const;
};


/**
 * @class SUS_AI_Player
 * @brief Represents an AI player with logic specifically for the SUS game.
 *
 * Implements a simple AI strategy to prioritize completing 'SUS' patterns or blocking the opponent.
 *
 * @see Player
 */
class SUS_AI_Player : public Player<char> {
private:
    SUS* gameBoard; ///< Pointer to the active game board for move evaluation.

public:
    /**
     * @brief Constructor for SUS_AI_Player.
     * @param name Name of the player.
     * @param symbol Character symbol ('S' or 'U').
     * @param type The type of the player (must be COMPUTER).
     */
    SUS_AI_Player(string name, char symbol, PlayerType type)
        : Player<char>(name, symbol, type) {}

    /**
     * @brief Sets the pointer to the game board.
     * @param board A pointer to the SUS game board.
     */
    void set_game_board(SUS* board) {
        gameBoard = board;
    }

    /**
     * @brief Determines and returns the optimal move for the AI player.
     * @details Uses a simple heuristic: Win > Block > Center > Corner > Any.
     * @return A pointer to a new `Move<char>` object.
     */
    Move<char>* get_move();

private:
    /**
     * @brief Checks if the current board state contains a "SUS" sequence.
     * @param board The current state of the board matrix.
     * @return true if a "SUS" sequence is found, false otherwise.
     */
    bool check_if_creates_sus(const vector<vector<char>>& board);
};

/**
 * @class SUS_UI
 * @brief User Interface class for the SUS Game.
 *
 * Handles player creation, including instantiating the specialized `SUS_AI_Player`.
 *
 * @see UI
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructor for SUS_UI.
     * @details Initializes the base `UI<char>` class with the welcome message and board size 3.
     */
    SUS_UI() : UI("=== SUS Game ===", 3) {}

    /**
     * @brief Creates a player of the specified type.
     * @details Creates a `SUS_AI_Player` for computer players, otherwise creates a base `Player`.
     * @param name Name of the player.
     * @param symbol Character symbol assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::COMPUTER) {
            return new SUS_AI_Player(name, symbol, type);
        }
        return new Player<char>(name, symbol, type);
    }

    /**
     * @brief Retrieves the next move from a player.
     * @details Calls `get_move()` on `SUS_AI_Player` if applicable, otherwise prompts for human input.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object.
     */
    Move<char>* get_move(Player<char>* player) override {
        // If it's a computer player, use AI logic
        SUS_AI_Player* ai_player = dynamic_cast<SUS_AI_Player*>(player);
        if (ai_player) {
            return ai_player->get_move();
        }

        // Human player - get input
        int r, c;
        cout << player->get_name() << " (" << player->get_symbol()
             << ") enter row and column: ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }
};

#endif












// #ifndef SUS_H
// #define SUS_H
//
// #include "BoardGame_Classes.h"
//
// class SUS : public Board<char> {
// private:
//     int score_p1;
//     int score_p2;
//
// public:
//     SUS();
//
//     bool update_board(Move<char>* move) override;
//     bool is_win(Player<char>* player) override;
//     bool is_lose(Player<char>* player) override ;
//     bool is_draw(Player<char>* player) override;
//     bool game_is_over(Player<char>* player) override;
//
//     int count_SUS();
//     int get_score_s() const;
//     int get_score_u() const;
//
//     // Display scores
//     void display_scores() const;
// };
//
//
// // AI PLAYER
//
//
// class SUS_AI_Player : public Player<char> {
// private:
//     SUS* gameBoard;
//
// public:
//     SUS_AI_Player(string name, char symbol, PlayerType type)
//         : Player<char>(name, symbol, type) {}
//
//     void set_game_board(SUS* board) {
//         gameBoard = board;
//     }
//
//     Move<char>* get_move() {
//         cout << name << " (" << symbol << ") is thinking...\n";
//
//         // Get current board
//         vector<vector<char>> board = gameBoard->get_board_matrix();
//
//         // Simple strategy:
//         // 1. Try to complete SUS sequence if possible
//         // 2. Otherwise, block opponent's potential SUS
//         // 3. Otherwise, pick center or corner
//         // 4. Otherwise, pick any empty spot
//
//         // Check all empty cells
//         for (int i = 0; i < 3; i++) {
//             for (int j = 0; j < 3; j++) {
//                 if (board[i][j] == '.') {
//                     // Try this move
//                     board[i][j] = symbol;
//                     if (check_if_creates_sus(board)) {
//                         return new Move<char>(i, j, symbol);
//                     }
//                     board[i][j] = '.'; // Undo
//                 }
//             }
//         }
//
//         // Block opponent
//         char opponent = (symbol == 'S') ? 'U' : 'S';
//         for (int i = 0; i < 3; i++) {
//             for (int j = 0; j < 3; j++) {
//                 if (board[i][j] == '.') {
//                     board[i][j] = opponent;
//                     if (check_if_creates_sus(board)) {
//                         // Block here!
//                         return new Move<char>(i, j, symbol);
//                     }
//                     board[i][j] = '.'; // Undo
//                 }
//             }
//         }
//
//         // Pick center if available
//         if (board[1][1] == '.') {
//             return new Move<char>(1, 1, symbol);
//         }
//
//         // Pick corners
//         int corners[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
//         for (int k = 0; k < 4; k++) {
//             int i = corners[k][0];
//             int j = corners[k][1];
//             if (board[i][j] == '.') {
//                 return new Move<char>(i, j, symbol);
//             }
//         }
//
//         // Pick first available spot
//         for (int i = 0; i < 3; i++) {
//             for (int j = 0; j < 3; j++) {
//                 if (board[i][j] == '.') {
//                     return new Move<char>(i, j, symbol);
//                 }
//             }
//         }
//
//         return new Move<char>(0, 0, symbol); // fallback
//     }
//
// private:
//     bool check_if_creates_sus(const vector<vector<char>>& board) {
//         // Check all possible SUS patterns
//         for (int i = 0; i < 3; i++) {
//             // Check row i
//             if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S') {
//                 return true;
//             }
//             // Check column i
//             if (board[0][i] == 'S' && board[1][i] == 'U' && board[2][i] == 'S') {
//                 return true;
//             }
//         }
//
//         // Check diagonals
//         if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') {
//             return true;
//         }
//         if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') {
//             return true;
//         }
//
//         return false;
//     }
// };
//
// // In SUS.h, update SUS_UI class
// class SUS_UI : public UI<char> {
// public:
//     SUS_UI() : UI("=== SUS Game ===", 3) {}
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override {
//         if (type == PlayerType::COMPUTER) {
//             return new SUS_AI_Player(name, symbol, type);
//         }
//         return new Player<char>(name, symbol, type);
//     }
//
//     Move<char>* get_move(Player<char>* player) override {
//         // If it's a computer player, use AI logic
//         SUS_AI_Player* ai_player = dynamic_cast<SUS_AI_Player*>(player);
//         if (ai_player) {
//             return ai_player->get_move();
//         }
//
//         // Human player - get input
//         int r, c;
//         cout << player->get_name() << " (" << player->get_symbol()
//              << ") enter row and column: ";
//         cin >> r >> c;
//         return new Move<char>(r, c, player->get_symbol());
//     }
// };
//
//
//
//
//
// #endif
