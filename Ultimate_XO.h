/** @file Ultimate_XO.h
 * @brief Defines the classes for the Ultimate Tic-Tac-Toe game.
 *
 * This file contains the declarations for the specialized move, board,
 * player, UI, and game manager classes required to implement the
 * complex rules of Ultimate Tic-Tac-Toe.
 */
#ifndef ULTIMATE_XO_H
#define ULTIMATE_XO_H

#include "BoardGame_classes.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

/**
 * @class UltimateMove
 * @brief Represents a move in the Ultimate Tic-Tac-Toe game.
 *
 * This move class extends \ref Move<char> to include four coordinates:
 * the row and column of the main 3x3 board (\c main_row, \c main_col)
 * and the row and column within the chosen sub-board (\c sub_row, \c sub_col).
 *
 * @see Move
 */
class UltimateMove : public Move<char> {
private:
    /** @brief The row index (0-2) of the chosen sub-board on the main board. */
    int main_row;
    /** @brief The column index (0-2) of the chosen sub-board on the main board. */
    int main_col;
    /** @brief The row index (0-2) within the chosen sub-board. */
    int sub_row;
    /** @brief The column index (0-2) within the chosen sub-board. */
    int sub_col;

public:
    /**
     * @brief Constructs a new UltimateMove object.
     *
     * @param main_r The main board row.
     * @param main_c The main board column.
     * @param sub_r The sub-board row.
     * @param sub_c The sub-board column.
     * @param symbol The player's symbol ('X' or 'O').
     */
    UltimateMove(int main_r, int main_c, int sub_r, int sub_c, char symbol)
        : Move<char>(-1, -1, symbol), main_row(main_r), main_col(main_c),
          sub_row(sub_r), sub_col(sub_c) {}

    /**
     * @brief Gets the main board row index.
     * @return The main board row.
     */
    int get_main_row() const { return main_row; }
    /**
     * @brief Gets the main board column index.
     * @return The main board column.
     */
    int get_main_col() const { return main_col; }
    /**
     * @brief Gets the sub-board row index.
     * @return The sub-board row.
     */
    int get_sub_row() const { return sub_row; }
    /**
     * @brief Gets the sub-board column index.
     * @return The sub-board column.
     */
    int get_sub_col() const { return sub_col; }
};

/**
 * @class UltimateBoard
 * @brief Implements the board logic for Ultimate Tic-Tac-Toe.
 *
 * This class manages the 3x3 grid of 3x3 sub-boards and tracks the winner
 * of each sub-board on a separate main board. It enforces the rule
 * that the location of the previous player's move dictates the next
 * sub-board where the current player must play.
 *
 * @see Board
 */
class UltimateBoard : public Board<char> {
private:
    /** @brief The 4D vector representing the 3x3 grid of 3x3 sub-boards.
     * (main_row, main_col, sub_row, sub_col) */
    vector<vector<vector<vector<char>>>> ultimate_board;
    /** @brief The 3x3 board tracking the winners of each sub-board. */
    vector<vector<char>> main_board;
    /** @brief The row index of the last sub-board played. */
    int last_main_row;
    /** @brief The column index of the last sub-board played. */
    int last_main_col;
    /** @brief Flag indicating if the current move is the first move of the game. */
    bool first_move;
    /** @brief Counter for the total number of moves played. */
    int move_count;

public:
    /**
     * @brief Constructs a new UltimateBoard object.
     *
     * Initializes all boards (ultimate_board and main_board) to empty state ('.').
     */
    UltimateBoard();
    /** @brief Destructor. */
    ~UltimateBoard() override {}

    /**
     * @brief Updates the ultimate board with a player's move.
     *
     * @param move A pointer to the \ref Move<char> object, expected to be an \ref UltimateMove.
     * @return \c true if the move was valid and the board was updated, \c false otherwise.
     */
    bool update_board(Move<char>* move) override;
    /**
     * @brief Checks if the specified player has won the overall game.
     *
     * A player wins by winning 3 sub-boards in a row, column, or diagonal on the \c main_board.
     * @param player A pointer to the \ref Player<char> being checked.
     * @return \c true if the player has won, \c false otherwise.
     */
    bool is_win(Player<char>* player) override;
    /**
     * @brief Checks if the specified player has lost the overall game.
     * @param player A pointer to the \ref Player<char> being checked.
     * @return \c true if the player has lost, \c false otherwise.
     */
    bool is_lose(Player<char>* player) override;
    /**
     * @brief Checks if the game has ended in a draw.
     *
     * A draw occurs if the main board is full without a winner.
     * @param player A pointer to the current \ref Player<char>.
     * @return \c true if the game is a draw, \c false otherwise.
     */
    bool is_draw(Player<char>* player) override;
    /**
     * @brief Checks if the overall game is over (win, lose, or draw).
     * @param player A pointer to the current \ref Player<char>.
     * @return \c true if the game is over, \c false otherwise.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Gets the current state of the main board (tracking sub-board winners).
     * @return The 3x3 main board matrix.
     */
    vector<vector<char>> get_main_board() const { return main_board; }
    /**
     * @brief Gets the full 4D structure of the ultimate board.
     * @return The 4D ultimate board matrix.
     */
    vector<vector<vector<vector<char>>>> get_ultimate_board() const { return ultimate_board; }
    /**
     * @brief Determines the required main board coordinates for the next move.
     *
     * Based on the \c sub_row and \c sub_col of the previous move.
     * @return A pair of integers (\c main_row, \c main_col) for the next required board.
     */
    pair<int, int> get_next_main_board() const;
    /**
     * @brief Checks if a specific sub-board is completely full.
     * @param main_r The main board row index.
     * @param main_c The main board column index.
     * @return \c true if the sub-board is full, \c false otherwise.
     */
    bool is_sub_board_full(int main_r, int main_c) const;
    /**
     * @brief Checks if a specific sub-board has been won by the given symbol.
     * @param main_r The main board row index.
     * @param main_c The main board column index.
     * @param symbol The symbol ('X' or 'O') to check for.
     * @return \c true if the sub-board is won by the symbol, \c false otherwise.
     */
    bool is_sub_board_won(int main_r, int main_c, char symbol) const;
    /**
     * @brief Checks the winner of a specific sub-board.
     * @param main_r The main board row index.
     * @param main_c The main board column index.
     * @return The winning symbol ('X' or 'O'), or '.' if no winner yet.
     */
    char check_sub_winner(int main_r, int main_c) const;
    /**
     * @brief Updates the \c main_board by checking for new winners in all sub-boards.
     */
    void update_main_board();
    /** @brief Displays the current state of the ultimate board to the console. */
    void display_ultimate_board() const;
    /**
     * @brief Gets the total number of moves played so far.
     * @return The total move count.
     */
    int get_move_count() const { return move_count; }

private:
    /**
     * @brief Helper function to check for a Tic-Tac-Toe win condition on any 3x3 board.
     * @param board The 3x3 board matrix to check.
     * @param symbol The symbol to check for ('X' or 'O').
     * @return \c true if the symbol has won on this board, \c false otherwise.
     */
    bool check_win_condition(const vector<vector<char>>& board, char symbol) const;
    /**
     * @brief Helper function to check if a 3x3 board is full.
     * @param board The 3x3 board matrix to check.
     * @return \c true if the board is full, \c false otherwise.
     */
    bool is_board_full(const vector<vector<char>>& board) const;
};

/**
 * @class UltimatePlayer
 * @brief Represents a general player for Ultimate Tic-Tac-Toe.
 *
 * Inherits from \ref Player<char>.
 *
 * @see Player
 */
class UltimatePlayer : public Player<char> {
public:
    /**
     * @brief Constructs a new UltimatePlayer object.
     * @param name The player's name.
     * @param symbol The player's symbol ('X' or 'O').
     * @param type The type of the player (\ref PlayerType::HUMAN or \ref PlayerType::COMPUTER).
     */
    UltimatePlayer(string name, char symbol, PlayerType type)
        : Player<char>(name, symbol, type) {}

    /** @brief Destructor. */
    ~UltimatePlayer() override {}
};

/**
 * @class UltimateComputerPlayer
 * @brief Represents an AI/Computer player for Ultimate Tic-Tac-Toe.
 *
 * Inherits from \ref UltimatePlayer.
 *
 * @see UltimatePlayer
 */
class UltimateComputerPlayer : public UltimatePlayer {
public:
    /**
     * @brief Constructs a new UltimateComputerPlayer object.
     * @param name The computer's name.
     * @param symbol The computer's symbol ('X' or 'O').
     */
    UltimateComputerPlayer(string name, char symbol)
        : UltimatePlayer(name, symbol, PlayerType::COMPUTER) {}

    /** @brief Destructor. */
    ~UltimateComputerPlayer() override {}
};

/**
 * @class Ultimate_UI
 * @brief Implements the User Interface logic for Ultimate Tic-Tac-Toe.
 *
 * Handles player setup, input gathering for moves, and displaying the complex board state.
 *
 * @see UI
 */
class Ultimate_UI : public UI<char> {
private:
    /** @brief Pointer to the active \ref UltimateBoard. */
    UltimateBoard* ultimate_board;

public:
    /**
     * @brief Constructs a new Ultimate_UI object.
     * @param board A pointer to the \ref UltimateBoard instance being used.
     */
    Ultimate_UI(UltimateBoard* board);
    /** @brief Destructor. */
    ~Ultimate_UI() override {}

    /**
     * @brief Gets a move from the current player (human or computer).
     *
     * Dispatches to \ref get_human_move() or \ref get_computer_move().
     * @param player A pointer to the current \ref Player<char>.
     * @return A pointer to the created \ref Move<char> (specifically \ref UltimateMove).
     */
    Move<char>* get_move(Player<char>* player) override;
    /**
     * @brief Sets up and returns pointers to Player 1 and Player 2.
     *
     * Handles human vs. human, human vs. computer, or computer vs. computer setup.
     * @return An array of two \ref Player<char>* pointers.
     */
    Player<char>** setup_players() override;
    /**
     * @brief Factory method to create an \ref UltimatePlayer or \ref UltimateComputerPlayer.
     * @param name The player's name.
     * @param symbol The player's symbol.
     * @param type The type of the player.
     * @return A pointer to the newly created player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    /**
     * @brief Displays a simple 3x3 board matrix (used for sub-boards or the main board).
     * @param matrix The 3x3 vector matrix to display.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const;
    /** @brief Displays the entire ultimate board game state. */
    void display_ultimate_game() const;

private:
    /**
     * @brief Handles input from a human player to get the four required coordinates.
     * @param player A pointer to the human player.
     * @return A pointer to the \ref UltimateMove.
     */
    Move<char>* get_human_move(Player<char>* player);
    /**
     * @brief Calculates a move for the computer player.
     * @param player A pointer to the computer player.
     * @return A pointer to the \ref UltimateMove.
     */
    Move<char>* get_computer_move(Player<char>* player);
    /**
     * @brief Finds all currently valid moves for a player based on the board state.
     * @param player A pointer to the current player.
     * @return A vector of valid \ref UltimateMove objects.
     */
    vector<UltimateMove> get_valid_moves(Player<char>* player) const;
};

/**
 * @class UltimateGameManager
 * @brief Manages the flow of the Ultimate Tic-Tac-Toe game.
 *
 * This class orchestrates the game loop, alternating turns, checking for game
 * termination conditions, and communicating with the UI.
 */
class UltimateGameManager {
private:
    /** @brief Pointer to the game board. */
    UltimateBoard* boardPtr;
    /** @brief Pointer to Player 1. */
    Player<char>* player1;
    /** @brief Pointer to Player 2. */
    Player<char>* player2;
    /** @brief Pointer to the UI handler. */
    Ultimate_UI* ui;

public:
    /**
     * @brief Constructs a new UltimateGameManager object.
     * @param board Pointer to the game board.
     * @param p1 Pointer to Player 1.
     * @param p2 Pointer to Player 2.
     * @param u Pointer to the UI.
     */
    UltimateGameManager(UltimateBoard* board, Player<char>* p1, Player<char>* p2, Ultimate_UI* u);
    /** @brief Executes the main game loop until the game is over. */
    void run();
};

#endif   //Ultimate_XO_h