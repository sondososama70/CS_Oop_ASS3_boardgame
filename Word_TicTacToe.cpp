#include "Word_TicTacToe.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cctype>
using namespace std;

// Static member to hold the dictionary words
static unordered_set<string> dictionary;
static bool dictionary_loaded = false;

//Function to load the dictionary from the file
void load_dictionary() {
    if (dictionary_loaded) {
        return;
    };

    ifstream file("dic.txt");
    if (!file.is_open()) {
        cout << "Could not open dic.txt\n";
        return;
    }

    string word;
    while (file >> word) {
        //Make sure the word is 3 characters
        if (word.length() == 3) {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            dictionary.insert(word);
        }
    }
    file.close();
    dictionary_loaded = true;
    cout << "Dictionary loaded with " << dictionary.size() << " words.\n";
}

//Function to check if a word is valid
bool is_valid_word(const string& word) {
    if (!dictionary_loaded) {
        load_dictionary();
    }
    return dictionary.count(word);
}

Word_TicTacToe::Word_TicTacToe() : Board(3 , 3){
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
    //Load the dictionary when the board is created
    load_dictionary();
}

bool Word_TicTacToe::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

//Checks if the line forms a valid word using letters from BOTH players
bool check_line(const string& line) {
    // A line must be complete
    if (line.find('.') != string::npos) {
        return false; // Not complete
    }

    // Check if it is a valid word from the dictionary
    return is_valid_word(line);
}

bool Word_TicTacToe::is_win(Player<char>* player) {
    //Check rows
    for (int i = 0; i < rows; ++i) {
        string row_str = "";
        for (int j = 0; j < columns; ++j) {
            row_str += board[i][j];
        }
        if (check_line(row_str)) {
            cout << "WINNING WORD FOUND in row " << i << ": " << row_str << endl;
            return true;
        }
    }

    //Check columns
    for (int j = 0; j < columns; ++j) {
        string col_str = "";
        for (int i = 0; i < rows; ++i) {
            col_str += board[i][j];
        }
        if (check_line(col_str)) {
            cout << "WINNING WORD FOUND in column " << j << ": " << col_str << endl;
            return true;
        }
    }

    //Check main diagonal (Top-Left to Bottom-Right)
    string diag1_str = "";
    for (int i = 0; i < rows; ++i) {
        diag1_str += board[i][i];
    }
    if (check_line(diag1_str)) {
        cout << "WINNING WORD FOUND in main diagonal: " << diag1_str << endl;
        return true;
    }

    //Check anti-diagonal (Top-Right to Bottom-Left)
    string diag2_str = "";
    for (int i = 0; i < rows; ++i) {
        diag2_str += board[i][columns - 1 - i];
    }
    if (check_line(diag2_str)) {
        cout << "WINNING WORD FOUND in anti-diagonal: " << diag2_str << endl;
        return true;
    }
    return false;
}

bool Word_TicTacToe::is_lose(Player<char> *player) {
    return false;
}

bool Word_TicTacToe::is_draw(Player<char> *player) {
    if (n_moves == rows * columns && !is_win(player)) {
        return true;
    }
    return false;
}

bool Word_TicTacToe::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}

// UI Implementation
Word_TicTacToe_UI::Word_TicTacToe_UI() : UI<char>("Welcome to Word TicTacToe" , 3) {}

Word_TicTacToe_UI::~Word_TicTacToe_UI() {}

Player<char>* Word_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Word_TicTacToe_UI::get_move(Player<char>* player) {
    int row, column;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column: ";
        cin >> row >> column;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Simple random move for computer player
        row = rand() % player->get_board_ptr()->get_rows();
        column = rand() % player->get_board_ptr()->get_columns();
        cout << "Computer " << player->get_name() << " chooses: (" << row << ", " << column << ")\n";
    }
    return new Move<char>(row , column , player->get_symbol());
}








// #include "Word_TicTacToe.h"
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <unordered_set>
// #include <algorithm> //For std::transform
// using namespace std;
//
// // Static member to hold the dictionary words
// static unordered_set<string> dictionary;
// static bool dictionary_loaded = false;
//
// //Function to load the dictionary from the file
// void load_dictionary() {
//     if (dictionary_loaded) {
//         return;
//     };
//
//     // Use a try-catch block for file operations if available, otherwise just check open
//     ifstream file("dic.txt");
//     if (!file.is_open()) {
//         cout << "Could not open dic.txt\n";
//         return;
//     }
//
//     string word;
//
//     while (file >> word) {
//         //Make sure the word is 3 characters
//         if (word.length() == 3) {
//             transform(word.begin(), word.end(), word.begin(), ::toupper);
//             dictionary.insert(word);
//         }
//     }
//     file.close();
//     dictionary_loaded = true;
//     cout << "Dictionary loaded with " << dictionary.size() << " words.\n";
// }
//
// //Function to check if a word is valid
// bool is_valid_word(const string& word) {
//     if (!dictionary_loaded) {
//         load_dictionary();
//     }
//     return dictionary.count(word);
// }
//
// Word_TicTacToe::Word_TicTacToe() : Board(3 , 3){
//     for (auto& row : board) {
//         for (auto& cell : row) {
//             cell = blank_symbol;
//         }
//     }
//     //Load the dictionary when the board is created
//     load_dictionary();
// }
//
// bool Word_TicTacToe::update_board(Move<char>* move) {
//     int x = move->get_x();
//     int y = move->get_y();
//     char mark = move->get_symbol();
//
//     if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
//         (board[x][y] == blank_symbol || mark == 0)) {
//
//         if (mark == 0) {
//             n_moves--;
//             board[x][y] = blank_symbol;
//         }
//         else {
//             n_moves++;
//             board[x][y] = toupper(mark);
//         }
//         return true;
//     }
//     return false;
// }
//
// //Function to check row, column or diagonal for a win
// bool check_line(const string& line) {
//     // A line must be complete and form a valid 3-letter word
//     if (line.find('.') != string::npos) {
//         return false; // Not complete
//     }
//     return is_valid_word(line);
// }
//
// bool Word_TicTacToe::is_win(Player<char>* player) {
//
//     //Check rows
//     for (int i = 0; i < rows; ++i) {
//         string row_str = " ";
//         for (int j = 0; j < columns; ++j) {
//             row_str += board[i][j];
//         }
//         if (check_line(row_str)) {
//             return true;
//         }
//     }
//
//     //Check columns
//     for (int j = 0; j < columns; ++j) {
//         string col_str = " ";
//         for (int i = 0; i < rows; ++i) {
//             col_str += board[i][j];
//         }
//         if (check_line(col_str)) {
//             return true;
//         }
//     }
//
//     //Check main diagonal (Top-Left to Bottom-Right)
//     string diag1_str = " ";
//     for (int i = 0; i < rows; ++i) {
//         diag1_str += board[i][i];
//     }
//     if (check_line(diag1_str)) {
//         return true;
//     }
//
//     //Check anti-diagonal (Top-Right to Bottom-Left)
//     string diag2_str = " ";
//     for (int i = 0; i < rows; ++i) {
//         diag2_str += board[i][columns - 1 - i];
//     }
//     if (check_line(diag2_str)) {
//         return true;
//     }
//     return false;
// }
//
// bool Word_TicTacToe::is_lose(Player<char> *player) {
//     return false;
// }
//
// bool Word_TicTacToe::is_draw(Player<char> *player) {
//     if (n_moves == rows * columns && !is_win(player)) {
//         return true;
//     }
//     return false;
// }
//
// bool Word_TicTacToe::game_is_over(Player<char> *player) {
//     return is_win(player) || is_draw(player);
// }
//
// // UI Implementation
// Word_TicTacToe_UI::Word_TicTacToe_UI() : UI<char>("Welcome to Word TicTacToe" , 3) {}
//
// Word_TicTacToe_UI::~Word_TicTacToe_UI() {}
//
// Player<char>* Word_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
//     return new Player<char>(name, symbol, type);
// }
//
// Move<char>* Word_TicTacToe_UI::get_move(Player<char>* player) {
//     int row, column;
//
//     if (player->get_type() == PlayerType::HUMAN) {
//         cout << player->get_name() << " (" << player->get_symbol() << ") enter row and column: ";
//         cin >> row >> column;
//     }
//     else if (player->get_type() == PlayerType::COMPUTER) {
//         // Simple random move for computer player
//         row = rand() % player->get_board_ptr()->get_rows();
//         column = rand() % player->get_board_ptr()->get_columns();
//         cout << "Computer " << player->get_name() << " chooses: (" << row << ", " << column << ")\n";
//     }
//     return new Move<char>(row , column , player->get_symbol());
// }