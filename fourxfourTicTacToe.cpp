//
// Created by HP on 11/26/2025.
//

#include "fourxfourTicTacToe.h"

using namespace std;

FourxFour_Board::FourxFour_Board() : Board(4, 4) {
    init_start_positions();
}
void FourxFour_Board :: init_start_positions() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = blank_symbol;
        }
    }

    board[0][0] = 'O';
    board[0][1] = 'X';
    board[0][2] = 'O';
    board[0][3] = 'X';
    board[3][0] = 'X';
    board[3][1] = 'O';
    board[3][2] = 'X';
    board[3][3] = 'O';
}
FourxFour_Board::~FourxFour_Board() { }

bool FourxFour_Board::in_bounds(int r, int c) const {
    if (r >=0 && r <= 3 && c >= 0 && c <= 3) {
        return true;
    }
    return false;
}

bool FourxFour_Board::is_adjacent(int r, int c, int newr, int newc) const {
    if (abs(r - newr)+ abs(c-newc)==1) {
        return true;
    }
    return false;
}

bool FourxFour_Board::update_board(Move<char> *move) {
    FourxFour_Move* mv = static_cast<FourxFour_Move*>(move);

    int oldX=mv->get_x();
    int oldY=mv->get_y();
    int newX=mv->getNewX();
    int newY=mv->getNewY();
    char mark =mv->get_symbol();

    if (in_bounds(newX,newY)) {
        if (is_adjacent(oldX,oldY,newX,newY)) {
            n_moves++;
            board[newX][newY] = mark;
            board[oldX][oldY] = blank_symbol;
        }
        else if (mark == 0) {
            board[newX][newY] = blank_symbol;
        }
        return true;
    }
    return false;
}

bool FourxFour_Board::is_win(Player<char> *player) {
    const char sym =player->get_symbol();
    // auto all_equal = [&](char a, char b, char c) {
    //     return a == b && b == c && a != blank_symbol;
    // };
    // for (int i = 0; i <3; ++i) {
    //     if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
    //         (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
    //         return true;
    // }
    // for (int i = 1; i <rows; ++i) {
    //     if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
    //         (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
    //         return true;
    // }
    // for (int i = 1; i <rows; ++i) {
    //     if ((all_equal(board[i][1], board[i][2], board[i][3]) && board[i][1] == sym) ||
    //         (all_equal(board[1][i], board[2][i], board[3][i]) && board[1][i] == sym))
    //         return true;
    // }
    // if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
    //     (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
    //         return true;
    //
    // if ((all_equal(board[0][1], board[1][2], board[2][3]) && board[1][2] == sym) ||
    //     (all_equal(board[0][3], board[1][2], board[2][1]) && board[1][2 ] == sym))
    //     return true;
    //
    // if ((all_equal(board[1][0], board[2][1], board[3][2]) && board[2][1] == sym) ||
    //     (all_equal(board[1][2], board[2][1], board[3][0]) && board[2][1] == sym))
    //     return true;
    //
    // if ((all_equal(board[1][1], board[2][2], board[3][3]) && board[2][2] == sym) ||
    //     (all_equal(board[1][3], board[2][2], board[3][1]) && board[2][2] == sym))
    //     return true;
    //
    //
    //
    // return false;

    return checking_win(sym);

}

bool FourxFour_Board::is_draw(Player<char> *player) {
    return (n_moves==16 && !is_win(player));
}

bool FourxFour_Board::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}

vector<pair<int, int>> FourxFour_Board::get_adjacent(int row, int col) {
    vector<pair<int,int>> moves;
    int TestR[] = {-1, 1, 0, 0};
    int TestC[] = {0, 0, -1, 1};
    for(int i = 0; i < 4; i++) {
        int newr = row + TestR[i];
        int newc = col + TestC[i];
        if(in_bounds(newr,newc) && board[newr][newc] == blank_symbol) {
            moves.push_back({newr, newc});
        }

    }
    return moves;
}

bool FourxFour_Board::checking_win( char player) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 2; j++) {
            if(board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player)
                return true;
            if(board[j][i] == player && board[j+1][i] == player && board[j+2][i] == player)
                return true;
        }
    }
    int diagonals[4][3][2] = {
        {{0,0},{1,1},{2,2}}, {{0,1},{1,2},{2,3}},
        {{1,0},{2,1},{3,2}}, {{1,1},{2,2},{3,3}}
    };
    for(auto& d : diagonals) {
        if(board[d[0][0]][d[0][1]] == player &&
           board[d[1][0]][d[1][1]] == player &&
           board[d[2][0]][d[2][1]] == player)
            return true;
    }
    return false;
}

int FourxFour_Board::evaluate1(char ai_symbol, char human_symbol) {
    if (checking_win(ai_symbol)) return 1000;
    if (checking_win(human_symbol)) return -1000;
    return 0;
}
//
// FourxFour_Move* FourxFour_Board::AImove(char ai, char player2) {
//     vector<pair<pair<int,int>, pair<int,int>>> possible_moves;
//     pair<int,int> old,neww;
//     for(int i = 0; i < 4; i++)
//         for(int j = 0; j < 4; j++)
//             if(board[i][j] == ai) {
//                 for(auto m : get_adjacent(i,j))
//                     possible_moves.push_back({{i,j}, m});
//             }
//     for(auto m : possible_moves) {
//         board[m.second.first][m.second.second] = ai;
//         board[m.first.first][m.first.second] = ' ';
//         if(checking_win( ai)) {
//             old = m.first;
//             neww = m.second;
//             return new FourxFour_Move(old.first, old.second,
//                                       neww.first, neww.second, ai);
//         }
//         board[m.first.first][m.first.second] = ai;
//         board[m.second.first][m.second.second] = ' ';
//     }
//     for(auto m : possible_moves) {
//         board[m.second.first][m.second.second] = ai;
//         board[m.first.first][m.first.second] = ' ';
//         for(int r = 0; r < 4; r++)
//             for(int c = 0; c < 4; c++)
//                 if(board[r][c] == player2) {
//                     for(auto pm : get_adjacent(r,c)) {
//                         board[pm.first][pm.second] = player2;
//                         board[r][c] = ' ';
//                         if(checking_win( player2)) {
//                             old = m.first;
//                             neww = m.second;
//                             board[pm.first][pm.second] = ' ';
//                             board[r][c] = player2;
//                             return new FourxFour_Move(old.first, old.second,
//                                                       neww.first, neww.second, ai);
//                         }
//                         board[pm.first][pm.second] = ' ';
//                         board[r][c] = player2;
//                     }
//                 }
//         board[m.first.first][m.first.second] = ai;
//         board[m.second.first][m.second.second] = ' ';
//     }
//     auto move = possible_moves[0];
//     board[move.second.first][move.second.second] = ai;
//     board[move.first.first][move.first.second] = ' ';
//     return new FourxFour_Move(move.first.first, move.first.second,
//                              move.second.first, move.second.second, ai);
//
// }
//

//
// int FourxFour_Board::minimax(char ai_symbol, char human_symbol, bool isMaximizingPlayer) {
//     // 1. حالات التوقف (Base Cases)
//     int score = evaluate(ai_symbol, human_symbol);
//     if (score != 0) return score;
//
//     // إذا كانت اللوحة ممتلئة ولا يوجد فائز (لا تنطبق على هذه اللعبة لكن كإجراء)
//     if (get_all_valid_moves(ai_symbol).empty() && get_all_valid_moves(human_symbol).empty()) return 0;
//
//     char current_sym = isMaximizingPlayer ? ai_symbol : human_symbol;
//     vector<FourxFour_Move*> possible_moves = get_all_valid_moves(current_sym);
//
//     if (isMaximizingPlayer) {
//         int best = -100000;
//         for (FourxFour_Move* move : possible_moves) {
//
//             // 2. تطبيق الحركة (Apply Move) - هذه هي خطوة الـ update_board
//             update_board(move);
//
//             // 3. التكرار (Recursion) - الذهاب للعمق التالي
//             best = max(best, minimax(ai_symbol, human_symbol, false));
//
//             // 4. التراجع (Backtracking)
//             // لإلغاء الحركة، نعكسها: نقل الرمز من الخلية الجديدة إلى القديمة
//             board[move->get_y()][move->getNewY()] = blank_symbol; // تفريغ الخلية الجديدة
//             board[move->get_x()][move->get_y()] = current_sym;     // إعادة القطعة للخلية القديمة
//
//             delete move; // مهم: حذف كائن الحركة بعد استخدامه
//         }
//         return best;
//     }
//     else { // Minimizing Player
//         int best = 100000;
//         for (FourxFour_Move* move : possible_moves) {
//
//             update_board(move);
//             best = min(best, minimax(ai_symbol, human_symbol, true));
//
//             // التراجع (Backtracking)
//             board[move->getNewX()][move->getNewY()] = blank_symbol;
//             board[move->get_x()][move->get_y()] = current_sym;
//
//             delete move;
//         }
//         return best;
//     }
// }
//
//
// FourxFour_Move* FourxFour_Board::best_move(char ai, char human) {
//     int bestVal = -100000;
//     FourxFour_Move* final_best_move = nullptr;
//
//     vector<FourxFour_Move*> possible_moves = get_all_valid_moves(ai);
//
//     if (possible_moves.empty()) return nullptr;
//
//     for (FourxFour_Move* move : possible_moves) {
//
//         // 1. تطبيق الحركة التجريبية
//         update_board(move);
//
//         // 2. حساب قيمة الحركة (الخصم سيلعب أولاً في التكرار)
//         int moveVal = minimax(ai, human, false);
//
//         // 3. التراجع
//         board[move->getNewX()][move->getNewY()] = blank_symbol;
//         board[move->get_x()][move->get_y()] = ai;
//
//         // 4. اختيار الحركة الأفضل
//         if (moveVal > bestVal) {
//             bestVal = moveVal;
//             if (final_best_move) delete final_best_move; // حذف الحركة القديمة إذا وجدت
//             final_best_move = move; // تخزين كائن الحركة الأفضل
//         } else {
//             delete move; // حذف الحركة غير الأفضل
//         }
//     }
//     return final_best_move;
// }



// التصريح الجديد في .h سيكون:
// int minimax(char ai_symbol, char human_symbol, bool isMaximizingPlayer, int alpha, int beta, int depth);

// التعديل على الكود في .cpp

// 🎯 تعريف العمق الأقصى (يمكنك تغييره لاحقًا)
const int MAX_DEPTH = 3;
// العمق 3 يعني أن الكمبيوتر يفكر 3 حركات للأمام (حركة الكمبيوتر، رد البشري، حركة الكمبيوتر الثانية)

int FourxFour_Board::minimax(char ai, char human, bool isMaximizingPlayer, int alpha, int beta, int depth) {
    int score = evaluate1(ai, human);
    if (score != 0) return score;
    if (depth == MAX_DEPTH) {
        return evaluation2(ai, human);
    }

    char current_sym = isMaximizingPlayer ? ai : human;
    vector<FourxFour_Move*> possible_moves = get_all_valid_moves(current_sym);

    if (possible_moves.empty()) {
        return 0;
    }

    int best_score = isMaximizingPlayer ? -100000 : 100000;

    for (size_t i = 0; i < possible_moves.size(); ++i) {
        FourxFour_Move* move = possible_moves[i];
        update_board(move);
        int current_score = minimax(ai, human, !isMaximizingPlayer, alpha, beta, depth + 1);
        board[move->getNewX()][move->getNewY()] = blank_symbol;
        board[move->get_x()][move->get_y()] = current_sym;
        if (isMaximizingPlayer) {
            best_score = max(best_score, current_score);
            alpha = max(alpha, best_score);
        } else {
            best_score = min(best_score, current_score);
            beta = min(beta, best_score);
        }
        delete move;
        if (beta <= alpha) {
            for (size_t j = i + 1; j < possible_moves.size(); ++j) {
                delete possible_moves[j];
            }
            return best_score;
        }
    }

    return best_score;
}

int FourxFour_Board::count_alignment(char symbol, int length) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - (length - 1); j++) {
            bool matches = true;
            for (int k = 0; k < length; k++) {
                if (board[i][j + k] != symbol) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                count++;
            }
        }
    }
    return count;
}

int FourxFour_Board::evaluation2(char ai, char human) {
    int value = 0;
    if (checking_win(ai)) value += 1000;
    value += count_alignment(ai, 2) * 10;
    value -= count_alignment(human, 2) * 10;
    return value;
}


//
// FourxFour_Move* FourxFour_Board::AImove(char ai, char player2) {
//     vector<pair<pair<int,int>, pair<int,int>>> possible_moves;
//
//     // جمع كل الحركات الممكنة
//     for(int i = 0; i < 4; i++)
//         for(int j = 0; j < 4; j++)
//             if(board[i][j] == ai) {
//                 for(auto m : get_adjacent(i,j))
//                     possible_moves.push_back({{i,j}, m});
//             }
//
//     // 1- لو ممكن نكسب مباشرة
//     for(auto m : possible_moves) {
//         // تعديل مؤقت للـ board
//         board[m.second.first][m.second.second] = ai;
//         board[m.first.first][m.first.second] = blank_symbol;
//         if(checking_win(ai)) {
//             // إعادة board زي ما كان
//             board[m.first.first][m.first.second] = ai;
//             board[m.second.first][m.second.second] = blank_symbol;
//             return new FourxFour_Move(m.first.first, m.first.second,
//                                       m.second.first, m.second.second, ai);
//         }
//         board[m.first.first][m.first.second] = ai;
//         board[m.second.first][m.second.second] = blank_symbol;
//     }
//
//     // 2- منع الخصم من الفوز
//     for(auto m : possible_moves) {
//         board[m.second.first][m.second.second] = ai;
//         board[m.first.first][m.first.second] = blank_symbol;
//         for(int r = 0; r < 4; r++)
//             for(int c = 0; c < 4; c++)
//                 if(board[r][c] == player2) {
//                     for(auto pm : get_adjacent(r,c)) {
//                         board[pm.first][pm.second] = player2;
//                         board[r][c] = blank_symbol;
//                         if(checking_win(player2)) {
//                             // إعادة board زي ما كان
//                             board[pm.first][pm.second] = blank_symbol;
//                             board[r][c] = player2;
//                             board[m.first.first][m.first.second] = ai;
//                             board[m.second.first][m.second.second] = blank_symbol;
//                             return new FourxFour_Move(m.first.first, m.first.second,
//                                                       m.second.first, m.second.second, ai);
//                         }
//                         board[pm.first][pm.second] = blank_symbol;
//                         board[r][c] = player2;
//                     }
//                 }
//         board[m.first.first][m.first.second] = ai;
//         board[m.second.first][m.second.second] = blank_symbol;
//     }
//
//     // 3- أي حركة fallback
//     if(!possible_moves.empty()) {
//         auto m = possible_moves[0];
//         return new FourxFour_Move(m.first.first, m.first.second,
//                                   m.second.first, m.second.second, ai);
//     }
//
//     return nullptr;
// }
//


FourxFour_Move* FourxFour_Board::best_move(char ai, char human) {
    int bestVal = -100000;
    FourxFour_Move* final_best_move = nullptr;
    int alpha = -100000;
    int beta = 100000;
    // 🎯 العمق الابتدائي هو 0
    const int START_DEPTH = 0;

    vector<FourxFour_Move*> possible_moves = get_all_valid_moves(ai);
    if (possible_moves.empty()) return nullptr;

    vector<FourxFour_Move*> moves_to_delete;

    for (FourxFour_Move* move : possible_moves) {

        update_board(move);

        // الاستدعاء الآن يشمل العمق 1 (START_DEPTH + 1)
        int moveVal = minimax(ai, human, false, alpha, beta, START_DEPTH + 1);

        // التراجع (Backtracking)
        board[move->getNewX()][move->getNewY()] = blank_symbol;
        board[move->get_x()][move->get_y()] = ai;

        // ... (منطق اختيار الحركة الأفضل وإدارة الذاكرة) ...
        if (moveVal > bestVal) {
            bestVal = moveVal;
            if (final_best_move) {
                moves_to_delete.push_back(final_best_move);
            }
            final_best_move = move;
        } else {
            moves_to_delete.push_back(move);
        }

        alpha = max(alpha, bestVal);
    }

    for (auto move : moves_to_delete) {
        delete move;
    }

    return final_best_move;
}



vector<FourxFour_Move*> FourxFour_Board::get_all_valid_moves(char player_symbol) {
    vector<FourxFour_Move*> moves;

    // المرور على كل الخلايا
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {

            // 1. إذا كانت الخلية تحتوي على قطعة اللاعب الحالي
            if (board[r][c] == player_symbol) {

                // 2. الحصول على الأماكن المجاورة الفارغة (استخدام get_adjacent الموجودة)
                vector<pair<int, int>> adj_empty_cells = get_adjacent(r, c);

                // 3. إنشاء كائن حركة لكل خلية مجاورة
                for (auto& dest : adj_empty_cells) {
                    // الحركة هي: من (r, c) إلى (dest.first, dest.second)
                    moves.push_back(new FourxFour_Move(r, c, dest.first, dest.second, player_symbol));
                }
            }
        }
    }
    return moves;
}

//end of board implementation


FourxFour_UI::FourxFour_UI() : UI<char>("Welcome , The Game has started",3) {}
FourxFour_UI::~FourxFour_UI() { }
Player<char> *FourxFour_UI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);

}
//
// vector<pair<int, int> > FourxFour_UI::get_adjacent(int row, int col, vector<vector<char> > &board) {
//     vector<pair<int,int>> moves;
//     int TestR[] = {-1, 1, 0, 0};
//     int TestC[] = {0, 0, -1, 1};
//     for(int i = 0; i < 4; i++) {
//         int newr = row + TestR[i];
//         int newc = col + TestC[i];
//         if(newr >= 0 && newr < 4 && newc >= 0 && newc < 4 && board[newr][newc] == ' ')
//             moves.push_back({newr, newc});
//         return moves;
//     }
// }
//
// bool FourxFour_UI::checking_win(vector<vector<char>>& board, char player) {
//     for(int i = 0; i < 4; i++) {
//         for(int j = 0; j < 2; j++) {
//             if(board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player)
//                 return true;
//             if(board[j][i] == player && board[j+1][i] == player && board[j+2][i] == player)
//                 return true;
//         }
//     }
//     int diagonals[4][3][2] = {
//         {{0,0},{1,1},{2,2}}, {{0,1},{1,2},{2,3}},
//         {{1,0},{2,1},{3,2}}, {{1,1},{2,2},{3,3}}
//     };
//     for(auto& d : diagonals) {
//         if(board[d[0][0]][d[0][1]] == player &&
//            board[d[1][0]][d[1][1]] == player &&
//            board[d[2][0]][d[2][1]] == player)
//             return true;
//     }
//     return false;
// }
//
// void FourxFour_UI::AImove(vector<vector<char>> &board, char ai, char player2) {
//     vector<pair<pair<int,int>, pair<int,int>>> possible_moves;
//     for(int i = 0; i < 4; i++)
//         for(int j = 0; j < 4; j++)
//             if(board[i][j] == ai) {
//                 for(auto m : get_adjacent(i,j,board))
//                     possible_moves.push_back({{i,j}, m});
//             }
//     for(auto m : possible_moves) {
//         board[m.second.first][m.second.second] = ai;
//         board[m.first.first][m.first.second] = ' ';
//         if(checking_win(board, ai)) return;
//         board[m.first.first][m.first.second] = ai;
//         board[m.second.first][m.second.second] = ' ';
//     }
//     for(auto m : possible_moves) {
//         board[m.second.first][m.second.second] = ai;
//         board[m.first.first][m.first.second] = ' ';
//         for(int r = 0; r < 4; r++)
//             for(int c = 0; c < 4; c++)
//                 if(board[r][c] == player2) {
//                     for(auto pm : get_adjacent(r,c,board)) {
//                         board[pm.first][pm.second] = player2;
//                         board[r][c] = ' ';
//                         if(checking_win(board, player2)) {
//                             board[r][c] = player2;
//                             board[m.second.first][m.second.second] = ai;
//                             board[m.first.first][m.first.second] = ' ';
//                             return;
//                         }
//                         board[pm.first][pm.second] = ' ';
//                         board[r][c] = player2;
//                     }
//                 }
//         board[m.first.first][m.first.second] = ai;
//         board[m.second.first][m.second.second] = ' ';
//     }
//     if(!possible_moves.empty()) {
//         auto move = possible_moves[0];
//         board[move.second.first][move.second.second] = ai;
//         board[move.first.first][move.first.second] = ' ';
//     }
// }
//
//
//

Move<char>* FourxFour_UI::get_move(Player<char>* player) {
    int oldX, oldY, newX, newY;


    FourxFour_Board* boardd = dynamic_cast<FourxFour_Board*>(player->get_board_ptr());
    if (!boardd) {
        cout << "Error: board pointer is not FourxFour_Board!" << endl;
        return nullptr;
    }

    if (player->get_type() == PlayerType::HUMAN) {
        bool valid = false;
        while (!valid) {

            cout << "\nEnter the token to move (oldX oldY): ";
            cin >> oldX >> oldY;
            cout << "Enter the destination (newX newY): ";
            cin >> newX >> newY;

            if (!boardd->in_bounds(oldX, oldY) || !boardd->in_bounds(newX, newY)) {
                cout << "Out of bounds! Try again.\n";
                continue;
            }

            if (!boardd->is_adjacent(oldX, oldY, newX, newY)) {
                cout << "Move not adjacent! Try again.\n";
                continue;
            }

            if (boardd->get_board_matrix()[oldX][oldY] != player->get_symbol() ) {
                cout << "Not your token at the selected cell! Try again.\n";
                continue;
            }

            if (boardd->get_board_matrix()[newX][newY] != '.') {
                cout << "Destination cell is not empty! Try again.\n";
                continue;
            }

            valid = true;
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // bool valid = false;
    //     while (!valid) {
    //         oldX = rand() % board->get_rows();
    //         oldY = rand() % board->get_columns();
    //         newX = rand() % board->get_rows();
    //         newY = rand() % board->get_columns();
    //
    //         if (board->get_board_matrix()[oldX][oldY] != player->get_symbol())
    //             continue;
    //
    //         if (!board->is_adjacent(oldX, oldY, newX, newY))
    //             continue;
    //
    //         if (board->get_board_matrix()[newX][newY] != '.')
    //             continue;
    //
    //         valid = true;
    //     }
    //     cout << "Computer moves from (" << oldX << "," << oldY << ") to ("
    //          << newX << "," << newY << ")\n";


        // boardd->get_adjacent(oldX,oldY);
        // char sym =player->get_symbol();
        // boardd->checking_win(sym);
        // char ai=player->get_symbol();
        // char player2 =(ai=='X')? 'O':'X';
        // // boardd->AImove(ai,player2);
        // return boardd->AImove(ai, player2);

        char ai=player->get_symbol();
        char player2 =(ai=='X')? 'O':'X';
        return boardd->best_move(ai, player2);

    }

    return new FourxFour_Move(oldX, oldY, newX, newY, player->get_symbol());
}

// end of UI implementation