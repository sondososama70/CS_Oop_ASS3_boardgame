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

/**
 * @brief Check whether a word exists in the loaded dictionary.
 * @param word Candidate uppercase word to validate.
 * @return true if present in dictionary.
 */
bool is_valid_word(const string& word) {
    if (!dictionary_loaded) {
        load_dictionary();
    }
    return dictionary.count(word);
}

/**
 * @class Word_TicTacToe
 * @brief 3x3 letter-placement board which wins if any full line forms a valid dictionary word.
 */

/**
 * @brief Construct a new Word_TicTacToe board and initialize blank cells.
 */
Word_TicTacToe::Word_TicTacToe() : Board(3 , 3){
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_symbol;
        }
    }
    load_dictionary();
}

/**
 * @brief Place a letter at (x,y) if within bounds and empty.
 * @param move Pointer to Move<char> containing coordinates and the letter.
 * @return true on successful placement.
 */
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

/**
 * @brief Check whether a completed line string is a valid dictionary word.
 * @param line String of exactly 3 characters.
 * @return true if the word exists in the dictionary.
 */
bool check_line(const string& line) {
    // A line must be complete
    if (line.find('.') != string::npos) {
        return false; // Not complete
    }

    // Check if it is a valid word from the dictionary
    return is_valid_word(line);
}

/**
 * @brief Determine if there exists any winning line (row, column, main or anti-diagonal)
 * that forms a valid 3-letter word.
 * @param player Player pointer (unused as words can use letters from both players).
 * @return true if any winning word is present.
 */
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

/**
 * @brief No explicit lose condition for Word_TicTacToe.
 */
bool Word_TicTacToe::is_lose(Player<char> *player) {
    return false;
}

/**
 * @brief Draw when board full and no valid word lines.
 */
bool Word_TicTacToe::is_draw(Player<char> *player) {
    if (n_moves == rows * columns && !is_win(player)) {
        return true;
    }
    return false;
}

/**
 * @brief Game over when a valid word exists or board is full without such a word.
 */
bool Word_TicTacToe::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}

// UI Implementation

/**
 * @class Word_TicTacToe_UI
 * @brief UI for Word TicTacToe: prompts for row/column/letter and creates players.
 */

/**
 * @brief Construct UI instance.
 */
Word_TicTacToe_UI::Word_TicTacToe_UI() : UI<char>("Welcome to Word TicTacToe" , 3) {}

Word_TicTacToe_UI::~Word_TicTacToe_UI() {}

/**
 * @brief Create a player (human or computer) for the game.
 * @param name Player name.
 * @param symbol Character symbol associated with player (not used as letter restriction).
 * @param type PlayerType enum.
 * @return allocated Player<char>* instance.
 */
Player<char>* Word_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << "\n";
    return new Player<char>(name, symbol, type);
}

/**
 * @brief Solicit a move: for human ask row/column/letter with validation; for computer choose random cell and letter.
 * @param player Player making the move.
 * @return allocated Move<char>* with chosen placement.
 */
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