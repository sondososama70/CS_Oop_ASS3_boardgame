// #ifndef ULTIMATE_XO_H
// #define ULTIMATE_XO_H
// #include "BoardGame_Classes.h"
// using namespace std;
//
// class Ultimate_XO : public Board<char> {
// private:
//     char blank_symbol = '.';
// public:
//     Ultimate_XO();
//     bool update_board(Move<char> *move);
//     bool is_win(Player<char>* player);
//     bool is_lose(Player<char>*);
//     bool is_draw(Player<char>* player);
//     bool game_is_over(Player<char>* player);
// };
//
// class Ultimate_XO_UI : public UI<char> {
// public:
//     Ultimate_XO_UI();
//     ~Ultimate_XO_UI();
//
//     Player<char>* create_player(string& name, char symbol, PlayerType type) override;
//     Move<char>* get_move(Player<char>* player) override;
// };
//
// #endif //ULTIMATE_XO_H