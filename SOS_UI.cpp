#include "SOS_UI.h"
#include <iostream>

SOS_UI::SOS_UI()
    : UI("Welcome to SOS Game!", 3) {}

Move<char>* SOS_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;

    cout << player->get_name() << " enter row and column: ";
    cin >> x >> y;

    cout << "Enter letter (S or U): ";
    cin >> letter;

    letter = toupper(letter);

    return new Move<char>(x, y, letter);
}

Player<char>* SOS_UI::create_player(string& name, char symbol, PlayerType type) {
    // player symbol = S or U assigned manually by game file
    return new Player<char>(name, symbol, type);
}

