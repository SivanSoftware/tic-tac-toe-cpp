#include "Game.h"

#include <istream>
#include <limits>
#include <ostream>
#include <string>

namespace ttt {

namespace {
char glyph(Cell player) { return player == Cell::X ? 'X' : 'O'; }
} // namespace

Game::Game(std::istream& in, std::ostream& out) : in_(in), out_(out) {}

bool Game::readMove(Cell player, int& pos) {
    while (true) {
        out_ << "Player " << glyph(player) << ", choose a cell (1-9, or q to quit): ";
        std::string token;
        if (!(in_ >> token)) return false; // end-of-input

        if (token == "q" || token == "Q") return false;

        try {
            pos = std::stoi(token);
        } catch (...) {
            out_ << "  Not a number. Try again.\n";
            continue;
        }

        if (pos < 1 || pos > 9) {
            out_ << "  Out of range. Pick 1-9.\n";
            continue;
        }
        if (board_.at(pos) != Cell::Empty) {
            out_ << "  That cell is taken. Try again.\n";
            continue;
        }
        return true;
    }
}

Status Game::run() {
    Cell current = Cell::X;
    out_ << "Tic-Tac-Toe\n\n" << board_.render() << '\n';

    while (board_.status() == Status::Ongoing) {
        int pos = 0;
        if (!readMove(current, pos)) {
            out_ << "\nGame aborted.\n";
            return board_.status();
        }

        board_.place(pos, current);
        out_ << '\n' << board_.render() << '\n';

        current = (current == Cell::X) ? Cell::O : Cell::X;
    }

    switch (board_.status()) {
        case Status::XWins: out_ << "Player X wins!\n"; break;
        case Status::OWins: out_ << "Player O wins!\n"; break;
        case Status::Draw:  out_ << "It's a draw.\n";   break;
        default: break;
    }
    return board_.status();
}

} // namespace ttt
