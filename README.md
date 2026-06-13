# CS_Oop_ASS3_BoardGame - Multi-Game Board Gaming Framework

![C++](https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square)
![HTML](https://img.shields.io/badge/HTML-87.3%25-orange?style=flat-square)
![CMake](https://img.shields.io/badge/CMake-Build-brightgreen?style=flat-square)
![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=flat-square)

## Project Overview

This is a comprehensive Object-Oriented Programming (OOP) assignment showcasing a **multi-game board gaming framework** implemented in C++. The project demonstrates advanced OOP principles through the implementation of 13+ playable board game variants, including Tic-Tac-Toe in multiple formats, Connect 4, SUS, and more. Each game implements a flexible template-based architecture supporting both human and AI players with an interactive console-based user interface.

---

## Features

✨ **13+ Playable Games**
- Standard Tic-Tac-Toe variants with different rules and board sizes
- Connect 4 - Classic four-in-a-row game
- SUS Game - Strategic symbol-based gameplay
- Advanced game modes with obstacles, memory, and unlimited boards

🎮 **Game Variants**
- **4x4 Tic-Tac-Toe** - Larger board with 4-in-a-row win condition
- **5x5 Tic-Tac-Toe** - Extended gameplay on 5x5 board
- **Pyramid Tic-Tac-Toe** - Diamond-shaped board layout
- **Diamond Tic-Tac-Toe** - Alternative board geometry
- **Word Tic-Tac-Toe** - Alphabet-based gameplay
- **Numerical Tic-Tac-Toe** - Number-based strategy game
- **Obstacles Tic-Tac-Toe** - Board with blocked positions
- **Infinity Tic-Tac-Toe** - Unlimited board expansion
- **Ultimate Tic-Tac-Toe** - Complex 3x3 grid of boards
- **Memory Tic-Tac-Toe** - Memory-based tile game
- **Misere Tic-Tac-Toe** - Reverse win condition
- **Connect 4** - Drop-piece strategy game
- **SUS Game** - Symbol allocation game

👥 **Player Support**
- Human vs Human gameplay
- Human vs Computer (AI) gameplay
- Computer vs Computer automation
- Intelligent AI decision-making for select games

🏗️ **Architecture**
- Template-based generic game framework
- Polymorphic board and player classes
- Extensible UI system for custom game interfaces
- Modular game manager for game flow control
- Strategy pattern for AI players

---

## Technologies Used

| Category | Technology |
|----------|-----------|
| **Language** | C++ (C++20 Standard) |
| **Build System** | CMake 3.31+ |
| **UI** | Console-based (Standard I/O) |
| **Data Structures** | Vectors, 2D Arrays, Templates |
| **IDE Support** | CLion (.idea), Visual Studio (.vs) |
| **Documentation** | PDF Game Manual |

---

## Project Structure

```
CS_Oop_ASS3_boardgame/
├── Core Framework
│   ├── BoardGame_Classes.h      # Base templates (Board, Player, Move, GameManager, UI)
│   └── XO_Classes.h             # Tic-Tac-Toe specific classes
│
├── Game Implementations
│   ├── SUS.h / SUS.cpp          # SUS Game with AI player
│   ├── Connect4.h / Connect4.cpp # Connect 4 game
│   ├── FiveByFive.h / FiveByFive.cpp              # 5x5 Tic-Tac-Toe
│   ├── Word_TicTacToe.h / Word_TicTacToe.cpp      # Word-based variant
│   ├── miser.h / miser.cpp      # Misere (reverse) Tic-Tac-Toe
│   ├── DiamondTicTacToe.h / DiamondTicTacToe.cpp  # Diamond board layout
│   ├── fourxfourTicTacToe.h / fourxfourTicTacToe.cpp  # 4x4 variant
│   ├── pyramidTicTacToe.h / pyramidTicTacToe.cpp      # Pyramid board
│   ├── NUMERICALTICTACTOE.h / NUMERICALTICTACTOE.cpp  # Number-based game
│   ├── Obstacles_XO.h / Obstacles_XO.cpp              # With obstacles
│   ├── Infinity_XO.h / Infinity_XO.cpp                # Unlimited expansion
│   ├── Memory_XO.h / Memory_XO.cpp                    # Memory tiles
│   ├── Ultimate_XO.h / Ultimate_XO.cpp                # 3x3 board grid
│   └── XO_Board.h                                     # Basic XO board
│
├── Entry Point
│   └── main.cpp                 # Main menu and game launcher
│
├── Build Configuration
│   ├── CMakeLists.txt           # CMake build configuration
│   ├── .gitattributes           # Git settings
│   └── main.exe                 # Compiled executable
│
├── IDE Configurations
│   ├── .idea/                   # CLion IDE settings
│   ├── .vs/                     # Visual Studio settings
│   └── cmake-build-debug/       # CMake debug build output
│
├── Documentation
│   ├── Gameboard Doc..pdf       # Complete game manual
│   └── README.md                # This file
│
└── Web Interface (Future)
    └── html/                    # Placeholder for web UI
```

### Key Files Description

| File | Purpose |
|------|---------|
| **BoardGame_Classes.h** | Generic base classes for any board game (Board, Player, Move, GameManager, UI) |
| **main.cpp** | Menu system and game selection launcher with 13 game options |
| **[GameName].h/.cpp** | Individual game implementations with specific rules and AI logic |
| **CMakeLists.txt** | Build configuration using CMake for cross-platform compilation |
| **Gameboard Doc..pdf** | Complete documentation of game rules and mechanics |

---

## Installation

### Prerequisites

- **C++ Compiler** with C++20 support (GCC 10+, Clang 10+, MSVC 2019+)
- **CMake** version 3.31 or higher
- **Git** for cloning the repository
- Terminal/Command Prompt access

### Clone the Repository

```bash
git clone https://github.com/sondososama70/CS_Oop_ASS3_boardgame.git
cd CS_Oop_ASS3_boardgame
```

### Build with CMake

**On Linux/macOS:**
```bash
mkdir build
cd build
cmake ..
make
```

**On Windows (Visual Studio):**
```bash
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..
cmake --build . --config Release
```

**On Windows (MinGW):**
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

### Run the Compiled Executable

**Linux/macOS:**
```bash
./CS_ASSIGNMENT2_SOUND
# or from project root
./build/CS_ASSIGNMENT2_SOUND
```

**Windows:**
```bash
CS_ASSIGNMENT2_SOUND.exe
# or from the build directory
.\build\Release\CS_ASSIGNMENT2_SOUND.exe
```

---

## Usage

### Starting the Application

Run the executable to display the main menu:

```
===== MAIN MENU =====
1. SUS Game
2. Four in a row Game
3. 5x5 Tic-Tac-Toe Game
4. Word Tic-Tac-Toe Game
5. Misere Tic-Tac-Toe Game
6. Diamond Tic-Tac-Toe Game
7. 4x4 Tic-Tac-Toe Game
8. Pyramid Tic-Tac-Toe Game
9. Numerical Tic-Tac-Toe Game
10. Obstacles Tic-Tac-Toe Game
11. Infinity Tic-Tac-Toe Game
12. Ultimate Tic Tac Toe Game
13. Memory Tic-Tac-Toe Game
14. Exit
Choose (1-14):
```

### Game Setup Example

**Playing 5x5 Tic-Tac-Toe:**

```
Choose (1-14): 3

Enter Player 1 name (X): Alice
Choose Player 1 type:
1. Human
2. Computer
Choose (1 or 2): 1

Enter Player 2 name (O): Bob
Choose Player 2 type:
1. Human
2. Computer
Choose (1 or 2): 1

    0   1   2   3   4
   ------------------
 0 |   |   |   |   |   |
   ------------------
 1 |   |   |   |   |   |
   ------------------
 2 |   |   |   |   |   |
   ------------------
 3 |   |   |   |   |   |
   ------------------
 4 |   |   |   |   |   |
   ------------------

Enter move for Alice (X) - row col: 2 2
```

### Game Flow

1. **Select a game** from the menu
2. **Enter player names** and choose player types (Human/Computer)
3. **Make moves** by entering coordinates (row column)
4. **View game results** when someone wins, loses, or draws
5. **Return to menu** to play another game

### Sample Output

```
Your Current Board:
    0   1   2
   ---------
 0 | X |   |   |
   ---------
 1 |   | X |   |
   ---------
 2 |   |   | X |
   ---------

Alice wins!
```

---

## Configuration

### Build Options in CMakeLists.txt

```cmake
set(CMAKE_CXX_STANDARD 20)    # C++ standard version
```

### Game Customization

Each game class can be customized by modifying:
- Board dimensions (rows/columns)
- Win conditions
- AI difficulty levels
- Symbol definitions

**Example - Modify 5x5 board size:**
Edit `FiveByFive.h`:
```cpp
// Change dimensions
const int ROWS = 5;      // Modify to desired size
const int COLUMNS = 5;   // Modify to desired size
```

### Environment Variables

No specific environment variables required. All configuration is embedded in source code.

---

## Architecture Overview

### System Design

```
┌──────────────────────────────────────────────────────┐
│                    main.cpp                          │
│              (Menu & Game Launcher)                 │
└──────────────┬───────────────────────────────────────┘
               │
       ┌───────┴────────┐
       │                │
    Game 1           Game 2
    (SUS)            (Connect4)
       │                │
       └────────┬───────┘
                │
    ┌───────────┴──────────────┐
    │   BoardGame_Classes.h    │
    │  (Core Framework)        │
    ├──────────────────────────┤
    │ • Board<T> (Abstract)    │
    │ • Player<T>              │
    │ • Move<T>                │
    │ • GameManager<T>         │
    │ • UI<T> (Abstract)       │
    └──────────────────────────┘
```

### Component Interaction

1. **Board Class** - Manages game state and move validation
2. **Player Class** - Represents human or AI player
3. **Move Class** - Encapsulates position and symbol
4. **GameManager** - Controls game flow and turn alternation
5. **UI Class** - Handles display and input
6. **AI Players** - Specialized Player subclasses with strategy

### Template-Based Design

```cpp
// Generic game implementation
template <typename T>
class Board { /* board logic */ };

// Specialized for each game
class FiveByFive : public Board<char> { /* ... */ };
class NUMERICALTICTACTOE : public Board<int> { /* ... */ };
```

---

## Development

### Code Standards

- **Naming Convention:** camelCase for variables, PascalCase for classes
- **Documentation:** Doxygen-style comments for all classes and methods
- **Header Guards:** Include guards to prevent multiple inclusions
- **Memory Management:** Smart use of `new`/`delete` with proper cleanup
- **Inheritance:** Extensive use of virtual functions for polymorphism

### Adding a New Game

1. Create header file `YourGame.h` inheriting from `Board<T>`
2. Implement required methods:
   - `update_board()`
   - `is_win()`, `is_lose()`, `is_draw()`
   - `game_is_over()`
3. Create `YourGame_UI` inheriting from `UI<T>`
4. Add includes to `main.cpp`
5. Update `CMakeLists.txt`
6. Add menu option in `displayMainMenu()`

### Testing Instructions

**Test Basic Game Flow:**
```bash
# Compile
cmake --build . --config Debug

# Run
./CS_ASSIGNMENT2_SOUND

# Select game 1 (SUS)
# Enter player names
# Play a game to completion
```

**Test AI Players:**
```
Choose Player 1 type: 2 (Computer)
Choose Player 2 type: 2 (Computer)
# Watch AI play against itself
```

**Test Invalid Inputs:**
```
Enter move: 10 10  # Out of bounds (should reject)
Enter move: -1 0   # Negative index (should reject)
```

---

## Future Improvements

### Roadmap

- [ ] **GUI Implementation** - Migrate from console to Qt/SDL graphical interface
- [ ] **Network Multiplayer** - Online gameplay with remote players
- [ ] **Advanced AI** - Implement Minimax with Alpha-Beta pruning
- [ ] **Game Statistics** - Track wins, losses, and player ratings
- [ ] **Persistence** - Save/load game state to files
- [ ] **Web Version** - Convert to WebAssembly for browser play
- [ ] **Mobile App** - Cross-platform mobile game client
- [ ] **Bot Tournament System** - Automated AI vs AI competitions
- [ ] **Difficulty Levels** - Adjustable AI challenge levels
- [ ] **Replay System** - Record and replay game moves

### Enhancement Ideas

1. **Performance Optimization**
   - Implement bitboard representation for faster move validation
   - Cache game state hashes for AI evaluation

2. **AI Improvements**
   - Minimax algorithm with alpha-beta pruning
   - Machine learning-based player
   - Neural network training for complex games

3. **User Experience**
   - Undo/Redo functionality
   - Hint system for humans playing against AI
   - Game statistics and leaderboards

4. **Code Quality**
   - Unit test suite with Google Test framework
   - Integration tests for all game variants
   - Performance benchmarks

---

## Documentation References

- **Game Manual:** [Gameboard Doc..pdf](https://github.com/sondososama70/CS_Oop_ASS3_boardgame/blob/main/Gameboard%20Doc..pdf) - Complete rules for all games
- **C++ Standard Library:** [cppreference.com](https://en.cppreference.com/)
- **CMake Documentation:** [cmake.org](https://cmake.org/documentation/)
- **OOP Principles:** Design Patterns, SOLID Principles

---

## Project Statistics

- **Total Games:** 13+ playable variants
- **Core Classes:** 5 (Board, Player, Move, GameManager, UI)
- **Implementation Classes:** 20+ specialized game implementations
- **Lines of Code:** ~3,500+ across all files
- **Build System:** CMake 3.31+
- **Memory Management:** Manual with proper cleanup
