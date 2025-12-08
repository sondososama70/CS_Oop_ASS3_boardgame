/**
 * @file Obstacles_XO.h
 * @brief Defines the classes for the Obstacles Tic-Tac-Toe game.
 *
 * This game is played on a larger board (6x6) and introduces obstacles ('#')
 * that are placed periodically, blocking moves. The goal is a standard 3-in-a-row
 * win before the board is too cluttered.
 */
#ifndef OBSTACLES_XO_H
#define OBSTACLES_XO_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

/**
 * @class Obstacles_XO
 * @brief Implements the game logic for Obstacles Tic-Tac-Toe on a 6x6 board.
 *
 * Features a 6x6 board with dynamic obstacles added during the game.
 *
 * @see Board
 */
class Obstacles_XO : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell.
    char obstacle_symbol = '#'; ///< Character used to represent an obstacle.
    vector<pair<int, int>> obstacles; ///< A list of coordinates where obstacles are placed.

public:
    /**
     * @brief Constructor for the Obstacles_XO board.
     * @details Initializes the board to 6x6.
     */
    Obstacles_XO();
    /**
     * @brief Updates the board with a player's move.
     * @details Checks if the target cell is empty or an obstacle.
     * @param move Pointer to the Move object containing coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);
    /**
     * @brief Adds new obstacles to the board.
     * @details Logic for randomly placing new '#' symbols on empty cells.
     */
    void add_obstacles();
    /**
     * @brief Checks if the given player has won the game (standard 3-in-a-row).
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    bool is_win(Player<char> *) override;
    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false.
     */
    bool is_lose(Player<char> *) override;
    /**
     * @brief Checks if the game has ended in a draw.
     * @details A draw is determined by the board filling up without a win.
     * @param player Pointer to the player being checked.
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char> *) override;
    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);
    /**
     * @brief Prints the current state of the board.
     */
    void print_board();
};

/**
 * @class Obstacles_XO_UI
 * @brief User Interface class for Obstacles Tic-Tac-Toe.
 *
 * Handles move input and includes logic for adding obstacles after every round.
 *
 * @see UI
 */
class Obstacles_XO_UI : public UI<char> {
private:
    int round_count = 0; ///< Counter to track the number of full rounds played.

public:
    /**
     * @brief Constructor for Obstacles_XO_UI.
     * @details Initializes the base `UI<char>` class with the welcome message and board size 6.
     */
    Obstacles_XO_UI() : UI<char>("Welcome to Obstacles Tic-Tac-Toe", 6) {}
    /**
     * @brief Destructor for Obstacles_XO_UI.
     */
    ~Obstacles_XO_UI() {}

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
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object.
     */
    virtual Move<char>* get_move(Player<char>* player) override {
        int row, column;
        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column (0-5): ";
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

    /**
     * @brief Executes additional logic after a valid move is processed.
     * @details This function increments the round count and, after every full round (2 moves), adds new obstacles to the board.
     * @param board Pointer to the game board.
     * @param current_player Pointer to the player who just made the move.
     */
    void post_move_processing(Board<char>* board, Player<char>* current_player) {
        round_count++;

        // Add obstacles after every round (2 moves)
        if (round_count % 2 == 0) {
            cout << "\n--- Adding 2 new obstacles ---\n";
            Obstacles_XO* obs_board = dynamic_cast<Obstacles_XO*>(board);
            if (obs_board) {
                obs_board->add_obstacles();
                obs_board->print_board();
            }
        }
    }
};

#endif //OBSTACLES_XO_H




// #ifndef OBSTACLES_XO_H
// #define OBSTACLES_XO_H
//
// #include "BoardGame_Classes.h"
// #include <vector>
// #include <utility>
// using namespace std;
//
// class Obstacles_XO : public Board<char> {
// private:
//     char blank_symbol = '.';
//     char obstacle_symbol = '#';
//     vector<pair<int, int>> obstacles;
//
// public:
//     Obstacles_XO();
//     bool update_board(Move<char>* move);
//     void add_obstacles();
//     bool is_win(Player<char> *) override;
//     bool is_lose(Player<char> *) override;
//     bool is_draw(Player<char> *) override;
//     bool game_is_over(Player<char>* player);
//     void print_board();
// };
//
// class Obstacles_XO_UI : public UI<char> {
// private:
//     int round_count = 0;
//
// public:
//     Obstacles_XO_UI() : UI<char>("Welcome to Obstacles Tic-Tac-Toe", 6) {}
//     ~Obstacles_XO_UI() {}
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override {
//         return new Player<char>(name, symbol, type);
//     }
//
//     virtual Move<char>* get_move(Player<char>* player) override {
//         int row, column;
//         if (player->get_type() == PlayerType::HUMAN) {
//             cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column (0-5): ";
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
//
//     void post_move_processing(Board<char>* board, Player<char>* current_player) {
//         round_count++;
//
//         // Add obstacles after every round
//         if (round_count % 2 == 0) {
//             cout << "\n--- Adding 2 new obstacles ---\n";
//             Obstacles_XO* obs_board = dynamic_cast<Obstacles_XO*>(board);
//             if (obs_board) {
//                 obs_board->add_obstacles();
//                 obs_board->print_board();
//             }
//         }
//     }
// };
//
// #endif //OBSTACLES_XO_H
//
//
