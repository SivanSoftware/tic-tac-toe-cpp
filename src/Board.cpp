#include "Board.h"

namespace ttt {

namespace {
char glyph(Cell c) {
    switch (c) {
        case Cell::X: return 'X';
        case Cell::O: return 'O';
        default:      return ' ';
    }
}

// All eight winning lines, as 0-based cell indices.
constexpr int kLines[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
    {0, 4, 8}, {2, 4, 6},            // diagonals
};
} // namespace

Board::Board() {
    cells_.fill(Cell::Empty);
}

bool Board::place(int pos, Cell player) {
    if (pos < 1 || pos > 9) return false;
    if (player == Cell::Empty) return false;
    int idx = pos - 1;
    if (cells_[idx] != Cell::Empty) return false;
    cells_[idx] = player;
    return true;
}

Cell Board::at(int pos) const {
    if (pos < 1 || pos > 9) return Cell::Empty;
    return cells_[pos - 1];
}

Status Board::status() const {
    for (const auto& line : kLines) {
        Cell a = cells_[line[0]];
        if (a != Cell::Empty && a == cells_[line[1]] && a == cells_[line[2]]) {
            return a == Cell::X ? Status::XWins : Status::OWins;
        }
    }
    return isFull() ? Status::Draw : Status::Ongoing;
}

bool Board::isFull() const {
    for (Cell c : cells_) {
        if (c == Cell::Empty) return false;
    }
    return true;
}

std::string Board::render() const {
    // Empty cells show their number so the player knows where to move.
    std::string out;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            int idx = row * 3 + col;
            if (cells_[idx] == Cell::Empty) {
                out += std::to_string(idx + 1);
            } else {
                out += glyph(cells_[idx]);
            }
            if (col < 2) out += " | ";
        }
        out += '\n';
        if (row < 2) out += "---------\n";
    }
    return out;
}

} // namespace ttt
