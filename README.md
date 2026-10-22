# Tic-Tac-Toe

A small Tic-Tac-Toe game written in modern C++ (C++17), playable in the terminal.
Play against a friend, or against an unbeatable computer opponent.

The game logic is separated from the I/O loop, so the board rules and the AI are
covered by standalone unit tests.

## Game modes

At startup you choose:

1. **Two players** — both sides are human.
2. **Play against the computer** — you pick X or O, and the computer plays the
   other side using a [minimax](https://en.wikipedia.org/wiki/Minimax) search.
   It plays perfectly, so the best you can do is a draw.

## Project layout

```
.
├── CMakeLists.txt       # Build configuration
├── src/
│   ├── Board.h / .cpp   # Board state, move rules, win/draw detection
│   ├── Ai.h / .cpp      # Minimax computer opponent
│   ├── Game.h / .cpp    # Interactive game loop (2-player and vs-computer)
│   └── main.cpp         # Entry point
└── tests/
    ├── test_board.cpp   # Unit tests for the board logic
    └── test_ai.cpp      # Unit tests for the AI (incl. an unbeatability proof)
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
