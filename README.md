# Tic-Tac-Toe

A small two-player Tic-Tac-Toe game written in modern C++ (C++17), playable in the terminal.

The game logic is separated from the I/O loop, so the board rules are covered by
standalone unit tests.

## Project layout

```
.
├── CMakeLists.txt       # Build configuration
├── src/
│   ├── Board.h / .cpp   # Board state, move rules, win/draw detection
│   ├── Game.h / .cpp    # Interactive two-player game loop
│   └── main.cpp         # Entry point
└── tests/
    └── test_board.cpp   # Unit tests for the board logic
```

## Build

Requires CMake 3.16+ and a C++17 compiler.

```bash
cmake -S . -B build
cmake --build build
```

## Play

```bash
./build/tic_tac_toe
```

Players take turns entering a cell number (1–9). Empty cells are shown as their
number so you always know where you can move:

```
1 | 2 | 3
---------
4 | 5 | 6
---------
7 | 8 | 9
```

Enter `q` at any prompt to quit.

## Run the tests

```bash
cd build && ctest --output-on-failure
```

## License

MIT — see [LICENSE](LICENSE).
