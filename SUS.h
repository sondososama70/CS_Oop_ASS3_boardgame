#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"

class SUS : public Board<char> {
private:
    int score_p1;
    int score_p2;

public:
    SUS();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override ;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    int count_SUS();
    int get_score_s() const;
    int get_score_u() const;

    // Display scores
    void display_scores() const;
};


// AI PLAYER


class SUS_AI_Player : public Player<char> {
private:
    SUS* gameBoard;

public:
    SUS_AI_Player(string name, char symbol, PlayerType type)
        : Player<char>(name, symbol, type) {}

    void set_game_board(SUS* board) {
        gameBoard = board;
    }

    Move<char>* get_move() {
        cout << name << " (" << symbol << ") is thinking...\n";

        // Get current board
        vector<vector<char>> board = gameBoard->get_board_matrix();

        // Simple strategy:
        // 1. Try to complete SUS sequence if possible
        // 2. Otherwise, block opponent's potential SUS
        // 3. Otherwise, pick center or corner
        // 4. Otherwise, pick any empty spot

        // Check all empty cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '.') {
                    // Try this move
                    board[i][j] = symbol;
                    if (check_if_creates_sus(board)) {
                        return new Move<char>(i, j, symbol);
                    }
                    board[i][j] = '.'; // Undo
                }
            }
        }

        // Block opponent
        char opponent = (symbol == 'S') ? 'U' : 'S';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '.') {
                    board[i][j] = opponent;
                    if (check_if_creates_sus(board)) {
                        // Block here!
                        return new Move<char>(i, j, symbol);
                    }
                    board[i][j] = '.'; // Undo
                }
            }
        }

        // Pick center if available
        if (board[1][1] == '.') {
            return new Move<char>(1, 1, symbol);
        }

        // Pick corners
        int corners[4][2] = {{0,0}, {0,2}, {2,0}, {2,2}};
        for (int k = 0; k < 4; k++) {
            int i = corners[k][0];
            int j = corners[k][1];
            if (board[i][j] == '.') {
                return new Move<char>(i, j, symbol);
            }
        }

        // Pick first available spot
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '.') {
                    return new Move<char>(i, j, symbol);
                }
            }
        }

        return new Move<char>(0, 0, symbol); // fallback
    }

private:
    bool check_if_creates_sus(const vector<vector<char>>& board) {
        // Check all possible SUS patterns
        for (int i = 0; i < 3; i++) {
            // Check row i
            if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S') {
                return true;
            }
            // Check column i
            if (board[0][i] == 'S' && board[1][i] == 'U' && board[2][i] == 'S') {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S') {
            return true;
        }
        if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S') {
            return true;
        }

        return false;
    }
};

// In SUS.h, update SUS_UI class
class SUS_UI : public UI<char> {
public:
    SUS_UI() : UI("=== SUS Game ===", 3) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override {
        if (type == PlayerType::COMPUTER) {
            return new SUS_AI_Player(name, symbol, type);
        }
        return new Player<char>(name, symbol, type);
    }

    Move<char>* get_move(Player<char>* player) override {
        // If it's a computer player, use AI logic
        SUS_AI_Player* ai_player = dynamic_cast<SUS_AI_Player*>(player);
        if (ai_player) {
            return ai_player->get_move();
        }

        // Human player - get input
        int r, c;
        cout << player->get_name() << " (" << player->get_symbol()
             << ") enter row and column: ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }
};





#endif
