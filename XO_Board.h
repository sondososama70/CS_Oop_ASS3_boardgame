#pragma once
#include "BoardGame_Classes.h"
#include <set>
#include <iostream>
using namespace std;

class Numerical_Board : public Board<int> {
    set<int> used_numbers;
public:
    Numerical_Board() : Board(3, 3) {
        for (auto& r : board)
            for (auto& c : r)
                c = 0;
    }
    void print_board() {
        cout << "Board: " << endl;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    cout << ". ";
                }
                else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    bool update_board(Move<int>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        int num = move->get_symbol();

        if (x < 0 || x >= 3 || y < 0 || y >= 3) {
            cout << "Invalid cell" << endl;
            return false;
        }
        if (board[x][y] != 0) {
            cout << " Cell already used" << endl;
            return false;
        }
        if (num < 1 || num > 9) {
            cout << " Number must be between 1 and 9 " << endl;
            return false;
        }
        if (used_numbers.count(num)) {
            cout << " Number already played " << endl;
            return false;
        }

        bool isOdd = (num % 2 != 0);
        bool firstPlayerTurn = (n_moves % 2 == 0);

        if (firstPlayerTurn && !isOdd) {
            cout << " Player 1 must play odd numbers " << endl;
            return false;
        }
        if (!firstPlayerTurn && isOdd) {
            cout << " Player 2 must play even numbers " << endl;
            return false;
        }

        board[x][y] = num;
        used_numbers.insert(num);
        n_moves++;

        print_board();
        return true;
    }

    bool check_sum_15() {

        for (int i = 0; i < 3; i++)
            if (board[i][0] && board[i][1] && board[i][2] && board[i][0] + board[i][1] + board[i][2] == 15) {
                return true;
            }
        for (int j = 0; j < 3; j++)
            if (board[0][j] && board[1][j] && board[2][j] && board[0][j] + board[1][j] + board[2][j] == 15) {
                return true;
            }

        if (board[0][0] && board[1][1] && board[2][2] && board[0][0] + board[1][1] + board[2][2] == 15) {
            return true;
        }
        if (board[0][2] && board[1][1] && board[2][0] && board[0][2] + board[1][1] + board[2][0] == 15) {
            return true;
        }
        return false;
    }

    bool is_win(Player<int>* player) override {
        return check_sum_15();
    }

    bool is_lose(Player<int>* player) override {
        return false;
    }

    bool is_draw(Player<int>* player) override {
        return n_moves == 9 && !check_sum_15();
    }

    bool game_is_over(Player<int>* player) override {
        return is_win(player) || is_draw(player);
    }
};
