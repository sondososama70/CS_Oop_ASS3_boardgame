#pragma once
#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
#include <string>
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * @class miser
 * @brief Implements Misère Tic Tac Toe board logic (inverse X-O).
 *
 * In Misère Tic Tac Toe, a player LOSES if they make 3 of their marks
 * in a row (horizontally, vertically, or diagonally).
 * This class manages the board, moves, losing conditions, and draw states.
 */
class miser : public Board<char> {
public:
    miser() ;
    /**
 * @brief Applies a move to the board if valid.
 * @param move Pointer to Move containing coordinates and symbol.
 * @return True if the move is applied, false if invalid.
 */
    bool update_board(Move<char>* move) override;
    /**
 * @brief Misère Tic Tac Toe has no "win" condition.
 * @return Always false.
 */
    bool is_win(Player<char>* p) override;
    /**
 * @brief Checks whether the board is full and no player has lost.
 * @return True if draw, otherwise false.
 */
    bool is_draw(Player<char>* p) override;
    /**
 * @brief Checks if the player has LOST (made 3 in a row).
 * @return True if losing condition is met.
 */
    bool is_lose(Player<char>* p) override;
    /**
 * @brief Determines whether the game is over.
 * @return True if draw or loss happened.
 */
    bool game_is_over(Player<char>* p) override;

    /**
     * @brief Gets symbol at a board cell.
     */
    char get_cell(int r, int c);
    /**
 * @brief Sets a symbol in a board cell (used by AI).
 */
    void set_cell(int r, int c, char symbol);
};
/**
 * @class MiserUI
 * @brief UI class for handling user interaction for Misère Tic Tac Toe.
 */
class MiserUI : public UI<char> {
public:
    MiserUI();
   /**
 * @brief Creates the two game players (human/computer).
 */
    Player<char>** setup_players() override;
   /**
 * @brief Gets a move from human or computer player.
 */
    Move<char>* get_move(Player<char>* player) override;
   /**
 * @brief Creates a specific Player object (Human or AI).
 */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;


};
/**
 * @class MisereAI
 * @brief Smart computer player using MiniMax algorithm.
 */
class MisereAI : public Player<char> {
public:
   /**
 * @brief Creates a computer player with minimax logic.
 */
    MisereAI(string name, char symbol);
   /**
 * @brief Returns the best move computed by the minimax algorithm.
 */
    Move<char>* get_move(Player<char>* p);
private:
   /**
 * @brief MiniMax recursive evaluation of optimal moves.
 * @param board Current game board.
 * @param depth Recursion depth.
 * @param isMaximizing True if maximizing player turn.
 * @return Score representing the optimality of the move.
 */
    int minimax(miser* board, int depth, bool isMaximizing);
};