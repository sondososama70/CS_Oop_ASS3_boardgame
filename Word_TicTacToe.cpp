#include "Word_TicTacToe.h"
#include <fstream>
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
    }

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
    load_dictionary();
}

bool Word_TicTacToe::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate coordinates and check if cell is empty
    if (x >= 0 && x < rows && y >= 0 && y < columns &&
        board[x][y] == blank_symbol && mark != 0) {

        n_moves++;
        board[x][y] = mark;
        return true;
        }
    return false;
}

//Check if the line forms a valid word using letters from both players
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
            return true;
        }
    }

    //Check main diagonal (Top-Left to Bottom-Right)
    string diag1_str = "";
    for (int i = 0; i < rows; ++i) {
        diag1_str += board[i][i];
    }
    if (check_line(diag1_str)) {
        return true;
    }

    //Check anti-diagonal (Top-Right to Bottom-Left)
    string diag2_str = "";
    for (int i = 0; i < rows; ++i) {
        diag2_str += board[i][columns - 1 - i];
    }
    if (check_line(diag2_str)) {
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
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << "\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Word_TicTacToe_UI::get_move(Player<char>* player) {
    int row, column;
    char letter;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << ", enter row , column and letter: ";
        cin >> row >> column >> letter;

        // Input validation for coordinates
        while (row < 0 || row > 2 || column < 0 || column > 2) {
            cout << "Invalid row and column. Enter row and column (0-2): ";
            cin >> row >> column;
        }

        while (!isalpha(letter)) {
            cout << "Please enter a letter (A-Z): ";
            cin >> letter;
        }
        letter = toupper(letter);
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        //Simple random move for computer player
        row = rand() % player->get_board_ptr()->get_rows();
        column = rand() % player->get_board_ptr()->get_columns();

        // Random letter
        letter = 'A' + rand() % 26;
        cout << "Computer " << player->get_name() << " chooses: (" << row << ", " << column << ") with letter '" << letter << "'\n";
    }
    return new Move<char>(row, column, letter);
}