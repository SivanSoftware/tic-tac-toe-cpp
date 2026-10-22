#include "Game.h"

#include <istream>
#include <ostream>
#include <string>

#include "Ai.h"

namespace ttt {

namespace {
char glyph(Cell player) { return player == Cell::X ? 'X' : 'O'; }
Cell other(Cell c) { return c == Cell::X ? Cell::O : Cell::X; }
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

Mode Game::chooseMode() {
    while (true) {
        out_ << "Choose mode:\n"
                "  1) Two players\n"
                "  2) Play against the computer\n"
                "Enter 1 or 2: ";
        std::string token;
        if (!(in_ >> token)) return Mode::TwoPlayers; // default on EOF
        if (token == "1") return Mode::TwoPlayers;
        if (token == "2") return Mode::VsComputer;
        out_ << "  Please enter 1 or 2.\n";
    }
}

Cell Game::chooseHumanSymbol() {
    while (true) {
        out_ << "Do you want to be X or O? (X moves first) ";
        std::string token;
        if (!(in_ >> token)) return Cell::X; // default on EOF
        if (token == "x" || token == "X") return Cell::X;
        if (token == "o" || token == "O") return Cell::O;
        out_ << "  Please enter X or O.\n";
    }
}

Status Game::run() {
    Mode mode = chooseMode();
    Cell human = (mode == Mode::VsComputer) ? chooseHumanSymbol() : Cell::X;
    // In VsComputer mode the AI plays the other symbol.
    Cell aiPlayer = other(human);
    return run(mode, aiPlayer);
}

Status Game::run(Mode mode, Cell aiPlayer) {
    Cell current = Cell::X;
    out_ << "\nTic-Tac-Toe\n\n" << board_.render() << '\n';

    while (board_.status() == Status::Ongoing) {
        bool aiTurn = (mode == Mode::VsComputer) && (current == aiPlayer);

        int pos = 0;
        if (aiTurn) {
            pos = Ai::bestMove(board_, current);
            out_ << "Computer (" << glyph(current) << ") plays " << pos << ".\n";
        } else if (!readMove(current, pos)) {
            out_ << "\nGame aborted.\n";
            return board_.status();
        }

        board_.place(pos, current);
        out_ << '\n' << board_.render() << '\n';

        current = other(current);
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
