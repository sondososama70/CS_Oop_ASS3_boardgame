#include "Ultimate_XO.h"
#include <iostream>
#include <random>
#include <ctime>
#include <vector>

using namespace std;

UltimateBoard::UltimateBoard()
    : Board<char>(9, 9), last_main_row(-1), last_main_col(-1), first_move(true), move_count(0) {

    ultimate_board.resize(3, vector<vector<vector<char>>>(3,
        vector<vector<char>>(3, vector<char>(3, '.'))));

    main_board.resize(3, vector<char>(3, '.'));
}

bool UltimateBoard::update_board(Move<char>* move) {
    UltimateMove* ultimate_move = static_cast<UltimateMove*>(move);
    if (!ultimate_move) return false;

    int main_r = ultimate_move->get_main_row();
    int main_c = ultimate_move->get_main_col();
    int sub_r = ultimate_move->get_sub_row();
    int sub_c = ultimate_move->get_sub_col();
    char symbol = ultimate_move->get_symbol();

    if (main_r < 0 || main_r >= 3 || main_c < 0 || main_c >= 3 ||
        sub_r < 0 || sub_r >= 3 || sub_c < 0 || sub_c >= 3) {
        return false;
    }

    if (ultimate_board[main_r][main_c][sub_r][sub_c] != '.') {
        return false;
    }

    if (!first_move) {

        if (last_main_row != -1 && last_main_col != -1) {
            if (is_sub_board_full(last_main_row, last_main_col) ||
                is_sub_board_won(last_main_row, last_main_col, 'X') ||
                is_sub_board_won(last_main_row, last_main_col, 'O')) {
            } else {
            }
        }
    }

    ultimate_board[main_r][main_c][sub_r][sub_c] = symbol;
    move_count++;
    first_move = false;

    last_main_row = sub_r;
    last_main_col = sub_c;

    update_main_board();

    return true;
}

bool UltimateBoard::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    return check_win_condition(main_board, symbol);
}

bool UltimateBoard::is_lose(Player<char>* player) {
    char symbol = player->get_symbol();
    char opponent_symbol = (symbol == 'X') ? 'O' : 'X';
    return check_win_condition(main_board, opponent_symbol);
}

bool UltimateBoard::is_draw(Player<char>* player) {
    if (!is_board_full(main_board)) return false;

    char symbol = player->get_symbol();
    char opponent_symbol = (symbol == 'X') ? 'O' : 'X';

    return !check_win_condition(main_board, symbol) &&
           !check_win_condition(main_board, opponent_symbol);
}

bool UltimateBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

pair<int, int> UltimateBoard::get_next_main_board() const {
    return make_pair(last_main_row, last_main_col);
}

bool UltimateBoard::is_sub_board_full(int main_r, int main_c) const {
    const auto& sub_board = ultimate_board[main_r][main_c];
    return is_board_full(sub_board);
}

bool UltimateBoard::is_sub_board_won(int main_r, int main_c, char symbol) const {
    return check_win_condition(ultimate_board[main_r][main_c], symbol);
}

char UltimateBoard::check_sub_winner(int main_r, int main_c) const {
    const auto& sub_board = ultimate_board[main_r][main_c];

    if (check_win_condition(sub_board, 'X')) return 'X';
    if (check_win_condition(sub_board, 'O')) return 'O';
    if (is_board_full(sub_board)) return 'D';
    return '.';
}

void UltimateBoard::update_main_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (main_board[i][j] == '.') {
                char winner = check_sub_winner(i, j);
                if (winner != '.' && winner != 'D') {
                    main_board[i][j] = winner;
                }
            }
        }
    }
}

void UltimateBoard::display_ultimate_board() const {
    cout << "\nUltimate Tic Tac Toe Board:\n\n";

    for (int main_row = 0; main_row < 3; main_row++) {
        for (int sub_row = 0; sub_row < 3; sub_row++) {
            cout << " ";
            for (int main_col = 0; main_col < 3; main_col++) {
                for (int sub_col = 0; sub_col < 3; sub_col++) {
                    char cell = ultimate_board[main_row][main_col][sub_row][sub_col];
                    char winner = check_sub_winner(main_row, main_col);
                    if (winner == 'X' || winner == 'O') {
                        cout << " " << winner;
                    } else {
                        cout << " " << cell;
                    }
                    if (sub_col < 2) cout << " |";
                }
                if (main_col < 2) cout << " ||";
            }
            cout << endl;

            if (sub_row < 2) {
                cout << " ";
                for (int main_col = 0; main_col < 3; main_col++) {
                    cout << "--- --- ---";
                    if (main_col < 2) cout << "||";
                }
                cout << endl;
            }
        }

        if (main_row < 2) {
            cout << string(35, '=') << endl;
        }
    }

    cout << "\nMain Board Status:\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << " " << main_board[i][j];
            if (j < 2) cout << " |";
        }
        cout << endl;
        if (i < 2) cout << " ---+---+---" << endl;
    }
    cout << endl;
}

bool UltimateBoard::check_win_condition(const vector<vector<char>>& board, char symbol) const {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return true;
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol)
            return true;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return true;

    return false;
}

bool UltimateBoard::is_board_full(const vector<vector<char>>& board) const {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == '.') return false;
        }
    }
    return true;
}

Ultimate_UI::Ultimate_UI(UltimateBoard* board)
    : UI<char>("Welcome to Ultimate Tic Tac Toe!", 1), ultimate_board(board) {}

Move<char>* Ultimate_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        return get_human_move(player);
    } else {
        return get_computer_move(player);
    }
}

Move<char>* Ultimate_UI::get_human_move(Player<char>* player) {
    int main_r, main_c, sub_r, sub_c;
    char symbol = player->get_symbol();

    cout << "\n" << player->get_name() << "'s turn (" << symbol << ")\n";

    while (true) {
        cout << "Enter main board row and column (0-2): ";
        cin >> main_r >> main_c;

        cout << "Enter sub-board row and column (0-2): ";
        cin >> sub_r >> sub_c;

        UltimateMove* move = new UltimateMove(main_r, main_c, sub_r, sub_c, symbol);

        if (ultimate_board->update_board(move)) {
            return move;
        } else {
            delete move;
            cout << "Invalid move! Try again.\n";
        }
    }
}

Move<char>* Ultimate_UI::get_computer_move(Player<char>* player) {
    cout << "\nComputer (" << player->get_symbol() << ") is thinking...\n";

    vector<UltimateMove> valid_moves = get_valid_moves(player);

    if (valid_moves.empty()) {
        cout << "Computer has no valid moves!\n";
        return nullptr;
    }

    srand(time(0));
    int random_index = rand() % valid_moves.size();
    UltimateMove selected_move = valid_moves[random_index];

    cout << "Computer plays: Main[" << selected_move.get_main_row() << ","
         << selected_move.get_main_col() << "] Sub[" << selected_move.get_sub_row()
         << "," << selected_move.get_sub_col() << "]\n";

    UltimateMove* computer_move = new UltimateMove(
        selected_move.get_main_row(),
        selected_move.get_main_col(),
        selected_move.get_sub_row(),
        selected_move.get_sub_col(),
        player->get_symbol()
    );

    bool move_applied = ultimate_board->update_board(computer_move);

    if (!move_applied) {
        cout << "Computer move failed! Trying again...\n";
        delete computer_move;
        return get_computer_move(player);
    }

    return computer_move;
}

vector<UltimateMove> Ultimate_UI::get_valid_moves(Player<char>* player) const {
    vector<UltimateMove> valid_moves;
    char symbol = player->get_symbol();

    auto next_board = ultimate_board->get_next_main_board();
    int suggested_main_r = next_board.first;
    int suggested_main_c = next_board.second;

    for (int main_r = 0; main_r < 3; main_r++) {
        for (int main_c = 0; main_c < 3; main_c++) {
            if (ultimate_board->is_sub_board_full(main_r, main_c) ||
                ultimate_board->is_sub_board_won(main_r, main_c, 'X') ||
                ultimate_board->is_sub_board_won(main_r, main_c, 'O')) {
                continue;
            }

            for (int sub_r = 0; sub_r < 3; sub_r++) {
                for (int sub_c = 0; sub_c < 3; sub_c++) {
                    auto ultimate_board_matrix = ultimate_board->get_ultimate_board();
                    if (ultimate_board_matrix[main_r][main_c][sub_r][sub_c] == '.') {
                        valid_moves.push_back(UltimateMove(main_r, main_c, sub_r, sub_c, symbol));
                    }
                }
            }
        }
    }

    return valid_moves;
}

Player<char>** Ultimate_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    if (type == PlayerType::COMPUTER) {
        return new UltimateComputerPlayer(name, symbol);
    } else {
        return new UltimatePlayer(name, symbol, type);
    }
}

void Ultimate_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    ultimate_board->display_ultimate_board();
}

void Ultimate_UI::display_ultimate_game() const {
    ultimate_board->display_ultimate_board();
}


UltimateGameManager::UltimateGameManager(UltimateBoard* board, Player<char>* p1, Player<char>* p2, Ultimate_UI* u)
    : boardPtr(board), player1(p1), player2(p2), ui(u) {

    player1->set_board_ptr(board);
    player2->set_board_ptr(board);
}

void UltimateGameManager::run() {
    ui->display_ultimate_game();

    Player<char>* currentPlayer = player1;
    int currentIndex = 0;

    while (true) {
        currentPlayer = (currentIndex == 0) ? player1 : player2;
        Move<char>* move = ui->get_move(currentPlayer);

        if (!move) {
            cout << "No valid moves available for " << currentPlayer->get_name() << "!\n";
            currentIndex = 1 - currentIndex;
            continue;
        }
        ui->display_ultimate_game();

        if (boardPtr->is_win(currentPlayer)) {
            ui->display_message(currentPlayer->get_name() + " wins the Ultimate Tic Tac Toe!");
            delete move;
            return;
        }
        if (boardPtr->is_lose(currentPlayer)) {
            Player<char>* winner = (currentIndex == 0) ? player2 : player1;
            ui->display_message(winner->get_name() + " wins the Ultimate Tic Tac Toe!");
            delete move;
            return;
        }
        if (boardPtr->is_draw(currentPlayer)) {
            ui->display_message("The Ultimate Tic Tac Toe game is a draw!");
            delete move;
            return;
        }

        delete move;
        currentIndex = 1 - currentIndex;
    }
}