// #pragma once
// #include "BoardGame_Classes.h"
//
// class X_O_Board : public Board<char> {
// public:
//     X_O_Board() : Board(3, 3) {
//         for (auto& row : board)
//             for (auto& cell : row)
//                 cell = '-';
//     }
//
//     bool update_board(Move<char>* move) override {
//         int x = move->get_x();
//         int y = move->get_y();
//         if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
//         if (board[x][y] != '-') return false;
//
//         board[x][y] = move->get_symbol();
//         n_moves++;
//         return true;
//     }
//
//     bool is_win(Player<char>* player) override {
//         char s = player->get_symbol();
//         // Rows
//         for (int i = 0; i < 3; i++)
//             if (board[i][0] == s && board[i][1] == s && board[i][2] == s)
//                 return true;
//         // Cols
//         for (int j = 0; j < 3; j++)
//             if (board[0][j] == s && board[1][j] == s && board[2][j] == s)
//                 return true;
//         // Diagonals
//         if (board[0][0] == s && board[1][1] == s && board[2][2] == s)
//             return true;
//         if (board[0][2] == s && board[1][1] == s && board[2][0] == s)
//             return true;
//         return false;
//     }
//
//     bool is_lose(Player<char>* player) override {
//         return false; // مش مستخدمة هنا
//     }
//
//     bool is_draw(Player<char>* player) override {
//         return n_moves == 9 && !is_win(player);
//     }
//
//     bool game_is_over(Player<char>* player) override {
//         return is_win(player) || is_draw(player);
//     }
// };
// #pragma once
// #include "BoardGame_Classes.h"
// #include <set>
// #include <iostream>
// using namespace std;
//
// class Numerical_Board : public Board<int> {
//     set<int> used_numbers; // لتخزين الأرقام اللي اتلعبت
// public:
//     Numerical_Board() : Board(3, 3) {
//         for (auto& row : board)
//             for (auto& cell : row)
//                 cell = 0; // الصفر معناها خانة فاضية
//     }
//
//     bool update_board(Move<int>* move) override {
//         int x = move->get_x();
//         int y = move->get_y();
//         int num = move->get_symbol();
//
//         // تحقق من حدود البورد
//         if (x < 0 || x >= 3 || y < 0 || y >= 3) {
//             cout << "❌ Invalid cell!\n";
//             return false;
//         }
//
//         // الخانة فاضية؟
//         if (board[x][y] != 0) {
//             cout << "❌ Cell already used!\n";
//             return false;
//         }
//
//         // الرقم في المدى الصحيح؟
//         if (num < 1 || num > 9) {
//             cout << "❌ Number must be between 1 and 9!\n";
//             return false;
//         }
//
//         // الرقم اتلعب قبل كده؟
//         if (used_numbers.count(num)) {
//             cout << "❌ Number already played!\n";
//             return false;
//         }
//
//         // التحقق من الدور: Player 1 odd, Player 2 even
//         bool isOdd = (num % 2 != 0);
//         bool firstPlayerTurn = (n_moves % 2 == 0);
//
//         if (firstPlayerTurn && !isOdd) {
//             cout << "❌ Player 1 must play odd numbers!\n";
//             return false;
//         }
//         if (!firstPlayerTurn && isOdd) {
//             cout << "❌ Player 2 must play even numbers!\n";
//             return false;
//         }
//
//         // كل شيء تمام ✅
//         board[x][y] = num;
//         used_numbers.insert(num);
//         n_moves++;
//         return true;
//     }
//
//     // فحص لو في صف / عمود / قطر مجموعهم = 15
//     bool check_sum_15() {
//         // صفوف
//         for (int i = 0; i < 3; i++)
//             if (board[i][0] && board[i][1] && board[i][2] &&
//                 board[i][0] + board[i][1] + board[i][2] == 15)
//                 return true;
//
//         // أعمدة
//         for (int j = 0; j < 3; j++)
//             if (board[0][j] && board[1][j] && board[2][j] &&
//                 board[0][j] + board[1][j] + board[2][j] == 15)
//                 return true;
//
//         // أقطار
//         if (board[0][0] && board[1][1] && board[2][2] &&
//             board[0][0] + board[1][1] + board[2][2] == 15)
//             return true;
//
//         if (board[0][2] && board[1][1] && board[2][0] &&
//             board[0][2] + board[1][1] + board[2][0] == 15)
//             return true;
//
//         return false;
//     }
//
//     bool is_win(Player<int>* player) override {
//         return check_sum_15();
//     }
//
//     bool is_lose(Player<int>* player) override { return false; }
//
//     bool is_draw(Player<int>* player) override {
//         return n_moves == 9 && !check_sum_15();
//     }
//
//     bool game_is_over(Player<int>* player) override {
//         return is_win(player) || is_draw(player);
//     }
// };
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
        cout << "Board:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) cout << ". ";
                else cout << board[i][j] << " ";
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
            cout << "Invalid cell!" << endl;
            return false;
        }

        if (board[x][y] != 0) {
            cout << " Cell already used!" << endl;
            return false;
        }

        if (num < 1 || num > 9) {
            cout << " Number must be between 1 and 9! " << endl;
            return false;
        }

        if (used_numbers.count(num)) {
            cout << " Number already played! " << endl;
            return false;
        }

        bool isOdd = (num % 2 != 0);
        bool firstPlayerTurn = (n_moves % 2 == 0);

        if (firstPlayerTurn && !isOdd) {
            cout << " Player 1 must play odd numbers! " << endl;
            return false;
        }
        if (!firstPlayerTurn && isOdd) {
            cout << " Player 2 must play even numbers! " << endl;
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
            if (board[i][0] && board[i][1] && board[i][2] &&
                board[i][0] + board[i][1] + board[i][2] == 15)
                return true;

        for (int j = 0; j < 3; j++)
            if (board[0][j] && board[1][j] && board[2][j] &&
                board[0][j] + board[1][j] + board[2][j] == 15)
                return true;

        if (board[0][0] && board[1][1] && board[2][2] &&
            board[0][0] + board[1][1] + board[2][2] == 15)
            return true;

        if (board[0][2] && board[1][1] && board[2][0] &&
            board[0][2] + board[1][1] + board[2][0] == 15)
            return true;

        return false;
    }

    bool is_win(Player<int>* player) override {
        return check_sum_15();
    }

    bool is_lose(Player<int>* player) override { return false; }

    bool is_draw(Player<int>* player) override {
        return n_moves == 9 && !check_sum_15();
    }

    bool game_is_over(Player<int>* player) override {
        return is_win(player) || is_draw(player);
    }
};
