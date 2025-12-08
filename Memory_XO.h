#ifndef MEMORY_XO_H
#define MEMORY_XO_H
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Memory_XO
 * @brief A variation where symbols are hidden, testing memory.
 */
class Memory_XO : public Board<char> {
private:
    char blank_symbol = '.';
    char hiddenboard[3][3]; ///< Stores the actual values hidden from view.

public:
    Memory_XO();

    /**
     * @brief Updates the hidden board and manages the temporary reveal logic.
     */
    bool update_board(Move<char> *move) override;

    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class Memory_XO_UI
 * @brief UI handling for Memory XO.
 */
class Memory_XO_UI : public UI<char> {
public:
    Memory_XO_UI();
    Player<char>** setup_players() override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif //MEMORY_XO_H