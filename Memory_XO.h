// #ifndef MEMORY_XO_H
// #define MEMORY_XO_H
// #include "BoardGame_Classes.h"
// using namespace std;
//
// class Memory_XO : public Board<char> {
// private:
//     char blank_symbol = '.';
// public:
//      Memory_XO();
//     bool update_board(Move<char> *move);
//     bool is_win(Player<char>* player);
//     bool is_lose(Player<char>*);
//     bool is_draw(Player<char>* player);
//     bool game_is_over(Player<char>* player);
// };
//
// class  Memory_XO_UI : public UI<char> {
// public:
//     Memory_XO_UI();
//     ~Memory_XO_UI();
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override;
//     Move<char>* get_move(Player<char>* player) override;
// };
//
// #endif //MEMORY_XO_H