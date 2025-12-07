#ifndef DIAMONDTICTACTOE_H
#define DIAMONDTICTACTOE_H
#include "BoardGame_Classes.h"

/**
 * @class DiamondTicTacToe
 * @brief Represents the board and logic for the Diamond Tic-Tac-Toe game.
 * * Inherits from the generic Board class using char as the symbol type.
 * The board is 5x5 but only specific cells form the diamond shape.
 */
class DiamondTicTacToe : public Board<char> {
    /**
     * @brief Checks if a specific line of cells creates a win.
     * @param symbol The player's symbol ('X' or 'O').
     * @param r The starting row index.
     * @param c The starting column index.
     * @param lr The row step (direction).
     * @param lc The column step (direction).
     * @return 1 if the line is formed, 0 otherwise.
     */
    int checkLine(char symbol, int r, int c, int lr, int lc) ;
public:
    /**
     * @brief Constructor to initialize the 5x5 board and setup the diamond shape.
     */
    DiamondTicTacToe();
    /**
     * @brief Checks if a coordinate is inside the valid diamond playing area.
     * @param r Row index.
     * @param c Column index.
     * @return true if valid, false if outside the diamond.
     */
    bool inside_diamond(int r, int c);
    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to the Move object containing coordinates and symbol.
     * @return true if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override ;
    /**
     * @brief Checks if the specified player has won.
     * @param player Pointer to the player to check.
     * @return true if the player meets the winning condition (forming shapes).
     */
    bool is_win(Player<char>* player) override ;
    /**
     * @brief Checks if the specified player has lost.
     * @return Always returns false for this game variant.
     */
    bool is_lose(Player<char>* player) override ;
    /**
     * @brief Checks if the game is a draw.
     * @return true if the board is full and no winner, false otherwise.
     */
    bool is_draw(Player<char>* player) override ;
    /**
     * @brief Checks if the game is over (win or draw).
     * @return true if the game has ended.
     */
    bool game_is_over(Player<char>* player) override ;
    /**
     * @brief Gets the content of a specific cell.
     * @param r Row index.
     * @param c Column index.
     * @return The character at the cell ('X', 'O', or 0).
     */
    char get_cell(int r, int c);
    /**
     * @brief Sets the content of a specific cell manually.
     * @param r Row index.
     * @param c Column index.
     * @param symbol The symbol to place.
     */
    void set_cell(int r, int c, char symbol);
};
/**
 * @class DiamondTicTacToeUI
 * @brief User Interface for the Diamond Tic-Tac-Toe game.
 * * Handles input/output specific to this game.
 */
class DiamondTicTacToeUI : public UI<char> {
public:
    DiamondTicTacToeUI();
    /**
     * @brief Sets up the players for the game (Human vs Human, Human vs AI, etc.).
     * @return Array of pointers to the two created players.
     */
    Player<char>** setup_players() override;
    /**
     * @brief Prompts the user or AI for a move.
     * @param player Pointer to the player whose turn it is.
     * @return Pointer to the Move object created.
     */
    Move<char>* get_move(Player<char>* player) override;
    /**
     * @brief Factory method to create a player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};
/**
 * @class DiamondAI
 * @brief AI Player logic for Diamond Tic-Tac-Toe.
 * * Uses Minimax algorithm to decide the best move.
 */
class DiamondAI : public Player<char> {
public:
    DiamondAI(string name, char symbol);
    Move<char>* get_move_ai();
    /**
     * @brief Override to integrate with the generic framework.
     */
    Move<char>* get_move(Player<char>* p);

private:
    /**
     * @brief Minimax algorithm implementation to evaluate board states.
     * @param board The current game board.
     * @param depth Current depth in the recursion tree.
     * @param isMaximizing true if it's the AI's turn (maximize score).
     * @return The score of the board state.
     */
    int minimax(DiamondTicTacToe* board, int depth, bool isMaximizing);
};
#endif //DIAMONDTICTACTOE_H
