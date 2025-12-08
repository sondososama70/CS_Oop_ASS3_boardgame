/**
 * @file fourxfourTicTacToe.h
 * @brief Defines the classes for the 4x4 Reversi-style Tic-Tac-Toe game.
 *
 * This game is played on a 4x4 board and may involve moving or replacing existing pieces.
 * It includes a specialized move class and advanced AI planning methods.
 */

#ifndef CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H
#define CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
class FourxFour_Move; // Forward declaration
using namespace std;

/**
 * @class FourxFour_Board
 * @brief Represents the game board and logic for the 4x4 Tic-Tac-Toe variant.
 *
 * This class inherits from the generic `Board<char>` and includes functions
 * to handle the 4x4 grid, adjacency, winning conditions, and AI move generation.
 *
 * @see Board
 */
class FourxFour_Board :public Board<char> {
protected:
    /**
     * @brief Initializes the starting positions of the game.
     * @details This function is likely used to set up the initial pieces for this game variant.
     */
    void init_start_positions();

public :
    /**
     * @brief Default constructor that initializes a 4x4 board.
     */
    FourxFour_Board();
    /**
     * @brief Destructor for FourxFour_Board.
     */
    ~FourxFour_Board();
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

    /**
     * @brief Checks if the given coordinates are within the board boundaries.
     * @param r The row index.
     * @param c The column index.
     * @return true if the coordinates are in bounds (0-3), false otherwise.
     */
    bool in_bounds(int r, int c) const;

    /**
     * @brief Checks if the 'new' position is adjacent to the 'old' position.
     * @param r The row of the old position.
     * @param c The column of the old position.
     * @param newr The row of the new position.
     * @param newc The column of the new position.
     * @return true if the new position is adjacent (horizontally, vertically, or diagonally), false otherwise.
     */
    bool is_adjacent(int r, int c, int newr, int newc) const;

    /**
     * @brief Updates the board with a player's move.
     * @details For this 4x4 variant, the move may represent placing a new piece or moving an existing one.
     * @param move Pointer to a Move<char> object (specifically a FourxFour_Move) containing move details.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the player has won the game (e.g., 4-in-a-row).
     * @param player Pointer to the player being checked.
     * @return true if a win condition is met, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the player has lost the game.
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
     * @brief Gets a list of coordinates adjacent to a given cell.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @return A vector of (row, column) pairs representing adjacent cells.
     */
    vector<pair<int,int>> get_adjacent(int row, int col) ;

    /**
     * @brief Checks if the specified player symbol has a winning alignment on the current board.
     * @param player The character symbol ('X' or 'O') to check for a win.
     * @return true if the player has won, false otherwise.
     */
    bool checking_win(char player);

    /**
     * @brief Generates all possible valid moves for a given player symbol from the current board state.
     * @param player_symbol The symbol ('X' or 'O') of the player to find moves for.
     * @return A vector of pointers to `FourxFour_Move` objects.
     */
    vector<FourxFour_Move*> get_all_valid_moves(char player_symbol);

    /**
     * @brief Evaluates the current board state for the AI using heuristic 1.
     * @param ai_symbol The AI's symbol.
     * @param human_symbol The opponent's symbol.
     * @return An integer representing the heuristic score of the board.
     */
    int evaluate1(char ai_symbol, char human_symbol);

    /**
     * @brief Implements the Minimax search algorithm with Alpha-Beta pruning.
     * @param ai_symbol The AI's symbol.
     * @param human_symbol The opponent's symbol.
     * @param isMaximizingPlayer Flag indicating if the current call is for the maximizing (AI) player.
     * @param alpha The alpha cutoff value.
     * @param beta The beta cutoff value.
     * @param depth The current depth of the search.
     * @return The optimal score achievable from the current state.
     */
    int minimax(char ai_symbol, char human_symbol, bool isMaximizingPlayer, int alpha, int beta, int depth) ;

    /**
     * @brief Determines the optimal move for the AI player.
     * @param ai The AI's symbol.
     * @param human The opponent's symbol.
     * @return A pointer to the best calculated `FourxFour_Move`.
     */
    FourxFour_Move* best_move(char ai, char human);

    /**
     * @brief Evaluates the current board state for the AI using heuristic 2.
     * @param ai_symbol The AI's symbol.
     * @param human_symbol The opponent's symbol.
     * @return An integer representing the heuristic score of the board.
     */
    int evaluation2(char ai_symbol, char human_symbol);

    /**
     * @brief Counts the number of alignments (e.g., 2-in-a-row, 3-in-a-row) for a given symbol.
     * @param symbol The character symbol ('X' or 'O') to count alignments for.
     * @param length The required length of the alignment (e.g., 2 for 2-in-a-row).
     * @return The total count of alignments of the specified length.
     */
    int count_alignment(char symbol, int length);
};

/**
 * @class FourxFour_UI
 * @brief User Interface class for the 4x4 Tic-Tac-Toe game.
 *
 * Handles player setup and collects move input, which may involve four coordinates
 * for the old and new positions of a piece.
 *
 * @see UI
 */
class FourxFour_UI : public UI<char> {
public:
    /**
     * @brief Constructs a FourxFour_UI object.
     */
    FourxFour_UI();
    /**
     * @brief Destructor for FourxFour_UI.
     */
    ~FourxFour_UI();

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move (old and new coordinates) from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object, specifically `FourxFour_Move`.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

/**
 * @class FourxFour_Move
 * @brief Represents a specific move in the 4x4 game, which involves an old and a new position.
 *
 * Inherits from the generic `Move<char>` class, reusing the base class's coordinates for the old position.
 *
 * @see Move
 */
class FourxFour_Move : public Move<char> {
private:
    int newX, newY; ///< The row and column of the piece's new position.
public:
    /**
     * @brief Constructor for FourxFour_Move.
     * @param oldr_ The old row index (used by base class).
     * @param oldc_ The old column index (used by base class).
     * @param newr_ The new row index.
     * @param newc_ The new column index.
     * @param s The character symbol ('X' or 'O') of the piece being moved.
     */
    FourxFour_Move(int oldr_, int oldc_, int newr_, int newc_, char s) :Move<char>(oldr_, oldc_, s), newX(newr_), newY(newc_) {};

    /**
     * @brief Gets the new row index.
     * @return The new row index.
     */
    int getNewX() const { return newX; };

    /**
     * @brief Gets the new column index.
     * @return The new column index.
     */
    int getNewY() const { return newY; };
};


#endif //CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H




// //
// // Created by HP on 11/26/2025.
// //
//
// #ifndef CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H
// #define CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H
//
// #include "BoardGame_Classes.h"
// class FourxFour_Move;
// using namespace std;
//
// class FourxFour_Board :public Board<char> {
// protected:
//     void init_start_positions();
//
// public :
//     FourxFour_Board();
//     ~FourxFour_Board();
//     char blank_symbol = '.';
//     bool in_bounds(int r, int c) const;
//     bool is_adjacent(int r, int c, int newr, int newc) const;
//     bool update_board(Move<char>* move);
//     bool is_win(Player<char>* player);
//     bool is_lose(Player<char>*) { return false; };
//     bool is_draw(Player<char>* player);
//     bool game_is_over(Player<char>* player);
//     vector<pair<int,int>> get_adjacent(int row, int col) ;
//     bool checking_win(char player);
//     vector<FourxFour_Move*> get_all_valid_moves(char player_symbol);
//     int evaluate1(char ai_symbol, char human_symbol);
//     int minimax(char ai_symbol, char human_symbol, bool isMaximizingPlayer, int alpha, int beta, int depth) ;
//     FourxFour_Move* best_move(char ai, char human);
//     int evaluation2(char ai_symbol, char human_symbol);
//     int count_alignment(char symbol, int length);
// };
//
// class FourxFour_UI : public UI<char> {
// public:
//     FourxFour_UI();
//     ~FourxFour_UI();
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type);
//     virtual Move<char>* get_move(Player<char>* player);
// };
//
// class FourxFour_Move : public Move<char> {
// private:
//     int newX, newY;
// public:
//     FourxFour_Move(int oldr_, int oldc_, int newr_, int newc_, char s) :Move<char>(oldr_, oldc_, s), newX(newr_), newY(newc_) {};
//     int getNewX() const { return newX; };
//     int getNewY() const { return newY; };
// };
//
//
// #endif //CS_ASSIGNMENT2_SOUND_FOURXFOURTICTACTOE_CLASSES_H