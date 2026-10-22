#pragma once

#include <array>
#include <string>

namespace ttt {

// A single cell on the board.
enum class Cell { Empty, X, O };

// Result of evaluating the board after a move.
enum class Status { Ongoing, XWins, OWins, Draw };

// A 3x3 tic-tac-toe board. Cells are indexed 1..9, left-to-right, top-to-bottom:
//   1 | 2 | 3
//   4 | 5 | 6
//   7 | 8 | 9
class Board {
public:
    Board();

    // Places `player` at cell `pos` (1..9).
    // Returns false if `pos` is out of range or already occupied.
    bool place(int pos, Cell player);

    // Reads the cell at `pos` (1..9). Returns Cell::Empty for invalid positions.
    Cell at(int pos) const;

    // Evaluates the current board state.
    Status status() const;

    // True when no empty cells remain.
    bool isFull() const;

    // Renders the board as a printable string.
    std::string render() const;

private:
    std::array<Cell, 9> cells_;
};

} // namespace ttt
