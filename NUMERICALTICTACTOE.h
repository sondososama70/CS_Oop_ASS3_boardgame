#pragma once
#include "BoardGame_Classes.h"
#include <set>
#include <iostream>
using namespace std;

/**
 * @class NumericalBoard
 * @brief Board logic for Numerical Tic-Tac-Toe.
 * * Players use numbers instead of X/O. The goal is to reach a sum of 15.
 */
class NumericalBoard : public Board<int> {
    set<int> used_numbers; ///< Tracks numbers already used on the board.

public:
    /**
     * @brief Constructor initializes a 3x3 board.
     */
    NumericalBoard();

    /**
     * @brief Places a number on the board if valid.
     * @param move Contains the coordinates and the number to place.
     * @return true if valid, false otherwise.
     */
    bool update_board(Move<int>* move) override;

    /**
     * @brief Checks if any line sums to 15.
     * @return true if a winning condition is met.
     */
    bool checkSum();

    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
};

/**
 * @class NumericalUI
 * @brief UI for Numerical Tic-Tac-Toe.
 * * Handles ensuring Player 1 uses odd numbers and Player 2 uses even numbers.
 */
class NumericalUI : public UI<int> {
public:
    NumericalUI();
    Player<int>** setup_players() override;
    Move<int>* get_move(Player<int>* player) override;
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
};
