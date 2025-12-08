/**
 * @file pyramidTicTacToe.h
 * @brief Defines the classes for the Pyramid Tic-Tac-Toe game.
 *
 * This game is played on a non-standard, pyramid-shaped board structure.
 * It includes an specialized board, UI, and an AI player.
 */

#ifndef CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H
#define CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class pyramidTicTacToe_board
 * @brief Represents the game board and logic for Pyramid Tic-Tac-Toe.
 *
 * This board has a non-rectangular structure, likely with varying row lengths,
 * and includes advanced AI functions like Minimax.
 *
 * @see Board
 */
class pyramidTicTacToe_board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
    /**
     * @brief Constructor for the pyramidTicTacToe_board.
     * @details Initializes the board structure for the pyramid game.
     */
    pyramidTicTacToe_board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the Move object containing coordinates and symbol.
     * @return true if the board was updated successfully, false otherwise.
     */
    bool update_board(Move<char> *move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if a win condition is met, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false in this implementation.
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if a draw condition is met, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Checks if the given coordinates are within the board's valid play area.
     * @param row The row index.
     * @param col The column index.
     * @return true if the coordinates are in bounds, false otherwise.
     */
    bool in_bounds(int row, int col);

    /**
     * @brief Evaluates the current board state for the AI.
     * @param ai_symbol The AI's symbol.
     * @param human_symbol The opponent's symbol.
     * @return An integer representing the heuristic score of the board.
     */
    int evaluate(char ai_symbol, char human_symbol);

    /**
     * @brief Implements the Minimax search algorithm.
     * @param board Pointer to the current game board instance (or a copy).
     * @param depth The current depth of the search.
     * @param isMax Flag indicating if the current call is for the maximizing player.
     * @param ai The AI's symbol.
     * @param human The opponent's symbol.
     * @return The optimal score achievable from the current state.
     */
    int minimax(pyramidTicTacToe_board* board, int depth, bool isMax, char ai, char human) ;

    /**
     * @brief Determines the optimal move (coordinates) for the AI player.
     * @param board Pointer to the current game board instance.
     * @param aiSymbol The AI's symbol.
     * @param humanSymbol The opponent's symbol.
     * @return A pair of (row, column) representing the best calculated move.
     */
    pair<int,int> best_move(pyramidTicTacToe_board* board,char aiSymbol, char humanSymbol);

    /**
     * @brief Checks for a win condition specifically for a given symbol on a board state.
     * @param sym The character symbol to check for a win.
     * @param currentBoard The current state of the board matrix.
     * @return true if the symbol has won, false otherwise.
     */
    bool is_win_symbol( char sym,const vector<vector<char>>& currentBoard);

    /**
     * @brief Gets a list of all currently empty cells on the board.
     * @return A vector of (row, column) pairs for empty cells.
     */
    vector<pair<int,int>> empty_cells() ;

    /**
     * @brief Checks if a move to the specified cell is valid (in bounds and empty).
     * @param r The row index.
     * @param c The column index.
     * @return true if the move is valid, false otherwise.
     */
    bool is_valid_move(int r, int c);

    /**
     * @brief Checks if the given symbol has won the game.
     * @param symbol The character symbol to check.
     * @return true if the symbol has won, false otherwise.
     */
    bool is_winner(char symbol);

    /**
     * @brief Checks if the board is completely full.
     * @return true if the board is full, false otherwise.
     */
    bool is_full();

    /**
     * @brief Retrieves the symbol at the specified cell.
     * @param r The row index.
     * @param c The column index.
     * @return The character symbol at (r, c).
     */
    char get_cell(int r, int c) {
        return board[r][c];
    }

    /**
     * @brief Sets the symbol at the specified cell.
     * @param r The row index.
     * @param c The column index.
     * @param symbol The character symbol to place.
     */
    void set_cell(int r, int c, char symbol) {
        board[r][c] = symbol;
    }

};

/**
 * @class pyramid_tic_tac_toe_UI
 * @brief User Interface class for Pyramid Tic-Tac-Toe.
 *
 * @see UI
 */
class pyramid_tic_tac_toe_UI : public UI<char> {
public:
    /**
     * @brief Constructs a pyramid_tic_tac_toe_UI object.
     */
    pyramid_tic_tac_toe_UI();
    /**
     * @brief Destructor for pyramid_tic_tac_toe_UI.
     */
    ~pyramid_tic_tac_toe_UI();

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

/**
 * @class Pyramid_AI_Player
 * @brief Represents an AI player with logic specifically for the Pyramid Tic-Tac-Toe game.
 *
 * @see Player
 */
class Pyramid_AI_Player : public Player<char> {
public:
    /**
     * @brief Constructor for Pyramid_AI_Player.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O').
     */
    Pyramid_AI_Player(string name, char symbol)
        : Player<char>(name, symbol, PlayerType::COMPUTER) {}

    /**
     * @brief Determines and returns the optimal move for the AI player.
     * @param board Pointer to the active game board.
     * @return A pointer to a new `Move<char>` object.
     */
    virtual Move<char>* get_move(Board<char>* board);
};


#endif //CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H


// //
// // Created by HP on 12/1/2025.
// //
//
// #ifndef CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H
// #define CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H
//
// #include "BoardGame_Classes.h"
// using namespace std;
//
// class pyramidTicTacToe_board : public Board<char> {
// private:
//     char blank_symbol = '.';
//
// public:
//     pyramidTicTacToe_board();
//     bool update_board(Move<char> *move);
//     bool is_win(Player<char>* player);
//     bool is_lose(Player<char>*) { return false; };
//     bool is_draw(Player<char>* player);
//     bool game_is_over(Player<char>* player);
//     bool in_bounds(int row, int col);
//
//     int evaluate(char ai_symbol, char human_symbol);
//     int minimax(pyramidTicTacToe_board* board, int depth, bool isMax, char ai, char human) ;
//     pair<int,int> best_move(pyramidTicTacToe_board* board,char aiSymbol, char humanSymbol);
//     bool is_win_symbol( char sym,const vector<vector<char>>& currentBoard);
//
//     vector<pair<int,int>> empty_cells() ;
//     bool is_valid_move(int r, int c);
//     bool is_winner(char symbol);
//     bool is_full();
//
//     char get_cell(int r, int c) {
//         return board[r][c];
//     }
//     void set_cell(int r, int c, char symbol) {
//         board[r][c] = symbol;
//     }
//
// };
//
// class pyramid_tic_tac_toe_UI : public UI<char> {
// public:
//     pyramid_tic_tac_toe_UI();
//     ~pyramid_tic_tac_toe_UI();
//     Player<char>* create_player(string& name, char symbol, PlayerType type);
//     virtual Move<char>* get_move(Player<char>* player);
// };
//
// class Pyramid_AI_Player : public Player<char> {
// public:
//     Pyramid_AI_Player(string name, char symbol)
//         : Player<char>(name, symbol, PlayerType::COMPUTER) {}
//     virtual Move<char>* get_move(Board<char>* board);
// };
//
//
//
//
// #endif //CS_ASSIGNMENT2_SOUND_PYRAMIDTICTACTOE_H