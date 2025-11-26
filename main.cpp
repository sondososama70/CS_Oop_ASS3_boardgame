#include <iostream>
#include "BoardGame_Classes.h"
#include "SUS.h"
#include "miser.h"
#include "NUMERICALTICTACTOE.h"
#include "fourxfourTicTacToe.h"
#include "FiveByFive.h"

using namespace std;
template <typename T>

void startGame(Board<T>* board, UI<T>* ui) {
    Player<T>** players = ui->setup_players();
    GameManager<T> game(board, players, ui);
    game.run();
    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1. SUS Game\n";
    cout << "2. Four in a row Game\n";
    cout << "3. 5x5 Tic-Tac-Toe Game\n";
    cout << "4. Word Tic-Tac-Toe Game\n";
    cout << "5. Misere Tic-Tac-Toe Game\n";
    cout << "6. Diamond Tic-Tac-Toe Game\n";
    cout << "7. 4x4 Tic-Tac-Toe Game\n";
    cout << "8. Pyramid Tic-Tac-Toe Game\n";
    cout << "9. Numerical Tic-Tac-Toe Game\n";
    cout << "10. Obstacles Tic-Tac-Toe Game\n";
    cout << "11. Infinity Tic-Tac-Toe Game\n";
    cout << "12. Ultimate Tic Tac Toe Game\n";
    cout << "13.Memory Tic-Tac-Toe Game\n";
    cout << "14. Exit\n";
    cout << "Choose (1-14): ";
}

bool confirmExit() {
    char c;
    cout << "Are you sure you want to exit? (y/n): ";
    cin >> c;
    return (c == 'y' || c == 'Y');
}

int getMenuChoice() {
    int choice;
    cin >> choice;
    return choice;
}

// ===================== PLAY SUS GAME =====================
void playSUSGame() {
    cout << "\n=== SUS GAME ===\n";

    SUS board;
    SUS_UI ui;

    string name1, name2;
    char sym1, sym2;

    cout << "Enter Player 1 name: ";
    cin >> name1;

    cout << "Choose symbol for Player 1 (S or U): ";
    cin >> sym1;

    // Validate
    while (sym1 != 'S' && sym1 != 'U' && sym1 != 's' && sym1 != 'u') {
        cout << "Invalid! Choose S or U: ";
        cin >> sym1;
    }
    sym1 = toupper(sym1);

    // Player 2 automatically gets the other symbol
    sym2 = (sym1 == 'S' ? 'U' : 'S');

    cout << "Enter Player 2 name: ";
    cin >> name2;

    cout << name2 << " will use symbol: " << sym2 << "\n\n";

    Player<char>* p1 = ui.create_player(name1, sym1, PlayerType::HUMAN);
    Player<char>* p2 = ui.create_player(name2, sym2, PlayerType::HUMAN);

    Player<char>* players[2];

    // Player with S always starts first
    if (sym1 == 'S') {
        players[0] = p1;
        players[1] = p2;
    } else {
        players[0] = p2;
        players[1] = p1;
    }

    GameManager<char> game(&board, players, &ui);
    game.run();

    cout << "\n=== GAME OVER ===\n";

    delete p1;
    delete p2;
}

// ===================== PLAY 5x5 TIC-TAC-TOE GAME =====================
void playFiveByFiveGame() {
    FiveByFive board;
    FiveByFive_UI ui;

    string name1, name2;
    cout << "Enter Player 1 name (X): ";
    cin >> name1;
    cout << "Enter Player 2 name (O): ";
    cin >> name2;

    Player<char>* p1 = ui.create_player(name1, 'X', PlayerType::HUMAN);
    Player<char>* p2 = ui.create_player(name2, 'O', PlayerType::HUMAN);
    Player<char>* players[2] = {p1, p2};

    GameManager<char> game(&board, players, &ui);
    game.run();

    delete p1;
    delete p2;
}

//=====================MAIN======================//
int main() {
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        displayMainMenu();
        choice = getMenuChoice();

        switch (choice) {
             case 1:
                 playSUSGame() ;
                 break;
             case 2:
                 // startGame(new FourInARow_Board(), new FourInARow_UI());
                 break;
             case 3:
                 playFiveByFiveGame();
                 break;
             case 4:
                 // startGame(new Word_Board(), new Word_UI());
                 break;
             case 5:
                 cout << "\nStarting Misere Tic Tac Toe...\n";
                 startGame(new miser(), new MiserUI());
                 break;
             case 6:
                 // startGame(new Diamond_Board(), new Diamond_UI());
                 break;
             case 7:
                 startGame(new FourxFour_Board(), new FourxFour_UI());
                 break;
             case 8:
                 // startGame(new Pyramid_Board(), new Pyramid_UI());
                 break;
             case 9:
                 cout << "\nStarting Numerical Tic Tac Toe...\n";
                 startGame(new NumericalBoard(), new NumericalUI());
                 break;
             case 10:
                 // startGame(new Obstacles_Board(), new Obstacles_UI());
                 break;
             case 11:
                 // startGame(new Infinity_Board(), new Infinity_UI());
                 break;
             case 12:
                 // Bonus Game 1
                 break;
             case 13:
                 // Bonus Game 2
                 break;
             case 14:
                 cout << "\nGoodbye, Thanks for playing.\n";
                 exitProgram = true;
                 break;
             default:
                 cout << "\nInvalid choice! Please choose a number between 1 and 14.\n";
                 break;
        }
    }
    return 0;
};





















//
//
//
//
// #include <iostream>
// #include <limits>
// #include "BoardGame_Classes.h"
//
// // تضمين ملفات الألعاب الخاصة بك
// #include "SUS.h"
// #include "NUMERICALTICTACTOE.h"
// #include "miser.h"
// // #include "FourInARow.h" ... وتضيف باقي الملفات هنا
//
// using namespace std;
//
// // =============================================================
// //  1. The Generic Game Starter (من الكود الأول - عبقري ومختصر)
// // =============================================================
// template <typename T>
// void startGame(Board<T>* board, UI<T>* ui) {
//     // هذه الدالة تقوم بكل شيء: تجهيز اللاعبين، تشغيل اللعبة، وتنظيف الذاكرة
//     Player<T>** players = ui->setup_players();
//     GameManager<T> game(board, players, ui);
//     game.run();
//
//     // تنظيف الذاكرة (Memory Management)
//     delete board;
//     delete ui;
//     delete players[0];
//     delete players[1];
//     delete[] players;
// }
//
// // =============================================================
// //  2. UI Helper Functions (من الكود الثاني - للتنظيم)
// // =============================================================
// void displayMainMenu() {
//     cout << "\n===========================================" << endl;
//     cout << "       WELCOME TO GAME STATION        " << endl;
//     cout << "===========================================" << endl;
//     cout << "1. Play SUS Tic Tac Toe" << endl;
//     cout << "2. Play Four-in-a-row Tic Tac Toe" << endl;
//     cout << "3. Play 5 x 5 Tic Tac Toe" << endl;
//     cout << "4. Play Word Tic Tac Toe" << endl;
//     cout << "5. Play Misere Tic Tac Toe" << endl;
//     cout << "6. Play Diamond Tic-Tac-Toe" << endl;
//     cout << "7. Play 4 x 4 Tic-Tac-Toe" << endl;
//     cout << "8. Play Pyramid Tic-Tac-Toe" << endl;
//     cout << "9. Play Numerical Tic Tac Toe" << endl;
//     cout << "10. Obstacles Tic-Tac-Toe" << endl;
//     cout << "11. Infinity Tic-Tac-Toe" << endl;
//     cout << "12. Ultimate Tic Tac Toe (Bonus)" << endl;
//     cout << "13. Memory Tic-Tac-Toe (Bonus)" << endl;
//     cout << "14. Exit" << endl;
//     cout << "===========================================" << endl;
//     cout << "Enter your choice (1-14): ";
// }
//
// // =============================================================
// //  3. MAIN FUNCTION
// // =============================================================
// int main() {
//     int choice = 0;
//     bool exitProgram = false;
//
//     while (!exitProgram) {
//         displayMainMenu();
//
//         // حماية الإدخال (Input Validation) من الكود الأول
//         if (!(cin >> choice)) {
//             cout << "\nInvalid input! Please enter a number.\n";
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             continue;
//         }
//
//         switch (choice) {
//             case 1:
//                 cout << "\nStarting SUS Tic Tac Toe...\n";
//                 // تأكد أنك تستخدم أسماء الكلاسات الصحيحة الموجودة عندك
//                 // startGame(new SUS_Board(), new SUS_UI());
//                 break;
//             case 2:
//                 // startGame(new FourInARow_Board(), new FourInARow_UI());
//                 break;
//             case 3:
//                 // startGame(new FiveByFive_Board(), new FiveByFive_UI());
//                 break;
//             case 4:
//                 // startGame(new Word_Board(), new Word_UI());
//                 break;
//             case 5:
//                 cout << "\nStarting Misere Tic Tac Toe...\n";
//                 startGame(new miser(), new MiserUI()); // مثال صحيح
//                 break;
//             case 6:
//                 // startGame(new Diamond_Board(), new Diamond_UI());
//                 break;
//             case 7:
//                 // startGame(new FourByFour_Board(), new FourByFour_UI());
//                 break;
//             case 8:
//                 // startGame(new Pyramid_Board(), new Pyramid_UI());
//                 break;
//             case 9:
//                 cout << "\nStarting Numerical Tic Tac Toe...\n";
//                 startGame(new NumericalBoard(), new NumericalUI()); // مثال صحيح
//                 break;
//             case 10:
//                 // startGame(new Obstacles_Board(), new Obstacles_UI());
//                 break;
//             case 11:
//                 // startGame(new Infinity_Board(), new Infinity_UI());
//                 break;
//             case 12:
//                 // Bonus Game 1
//                 break;
//             case 13:
//                 // Bonus Game 2
//                 break;
//             case 14:
//                 cout << "\nGoodbye! Thanks for playing.\n";
//                 exitProgram = true;
//                 break;
//             default:
//                 cout << "\nInvalid choice! Please choose a number between 1 and 14.\n";
//                 break;
//         }
//     }
//
//     return 0;
// }