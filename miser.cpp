#include "miser.h"
#include "BoardGame_Classes.h"

miser::miser() : Board<char>(3, 3) {
    n_moves = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = 0;
        }
    }
}

char miser::get_cell(int r, int c) {
    return board[r][c];
}
void miser::set_cell(int r, int c, char symbol) {
    board[r][c] = symbol;
    if (symbol != 0) n_moves++;
    else n_moves--;
}
bool miser::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0) {
        cout << "Invalid cell" << endl;
        return false;
    }
        board[x][y] = move->get_symbol();
        n_moves++;
        return true;
}
bool miser::is_win(Player<char>* p) {
    return false;
}
bool miser::is_lose(Player<char>* p) {
    char symbol = p->get_symbol();
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
    return false;
}
bool miser::is_draw(Player<char>* p) {
    return (n_moves == 9 && !is_lose(p));
}
bool miser::game_is_over(Player<char>* p) {
    return is_lose(p) || is_draw(p);
}
MiserUI::MiserUI() : UI("Welcome to Misere Tic Tac Toe Game!", 3) {
}
Player<char>** MiserUI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> choices = {"Human", "Computer"};

    string name1;
    cout << "Enter name of Player 1 (Symbol X): ";
    cin >> name1;

    PlayerType type1 = get_player_type_choice("Player 1", choices);
    players[0] = create_player(name1, 'X', type1);

    string name2;
    cout << "Enter name of Player 2 (Symbol O): ";
    cin >> name2;
    PlayerType type2 = get_player_type_choice("Player 2", choices);
    players[1] = create_player(name2, 'O', type2);

    return players;
}


Move<char>* MiserUI::get_move(Player<char>* player) {

    if (player->get_type() == PlayerType::COMPUTER) {
        MisereAI* ai = dynamic_cast<MisereAI*>(player);
        if (ai != nullptr) {
            return ai->get_move(player);
        }
    }

    int x, y;
    while(true) {
        cout << player->get_name() << " (" << player->get_symbol() << ")"
             << ", Please enter x and y : ";
        if (cin >> x >> y) {
            return new Move<char>(x, y, player->get_symbol());
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Numbers only.\n";
        }
    }
}

Player<char>* MiserUI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER) {
        return new MisereAI(name, symbol);
    }
    return new Player<char>(name, symbol, type);
}

MisereAI::MisereAI(string name, char symbol) : Player<char>(name, symbol, PlayerType::COMPUTER) {}

int MisereAI::minimax(miser* board, int depth, bool isMaximizing) {

    if (board->is_lose(this)) return -10 + depth;

    char dummyplayer = (symbol == 'X') ? 'O' : 'X';
    Player<char> dummy("dummy", dummyplayer, PlayerType::HUMAN);
    if (board->is_lose(&dummy)) return 10 - depth;

    if (board->is_draw(this)) return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board->get_cell(i, j) == 0) {
                    board->set_cell(i, j, symbol);
                    best = max(best, minimax(board, depth + 1, false));
                    board->set_cell(i, j, 0);
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        char dummyplayer = (symbol == 'X') ? 'O' : 'X';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board->get_cell(i, j) == 0) {
                    board->set_cell(i, j, dummyplayer);
                    best = min(best, minimax(board, depth + 1, true));
                    board->set_cell(i, j, 0);
                }
            }
        }
        return best;
    }
}

Move<char>* MisereAI::get_move(Player<char>* p) {
    miser* board = dynamic_cast<miser*>(boardPtr);

    int bestVal = -1000;
    Move<char>* bestMove = nullptr;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->get_cell(i, j) == 0) {

                board->set_cell(i, j, symbol);
                int moveVal = minimax(board, 0, false);
                board->set_cell(i, j, 0);

                if (moveVal > bestVal) {
                    bestVal = moveVal;

                    delete bestMove;

                    bestMove = new Move<char>(i, j, symbol);
                }
            }
        }
    }
    return bestMove;
}