#pragma once

#include <iosfwd>

#include "Board.h"

namespace ttt {

// Drives a two-player game loop over the given input/output streams.
// Separating the streams from std::cin/std::cout keeps the loop testable.
class Game {
public:
    Game(std::istream& in, std::ostream& out);

    // Runs the game to completion. Returns the final status.
    Status run();

private:
    // Prompts the current player until a legal move is entered.
    // Returns false on end-of-input (player quit).
    bool readMove(Cell player, int& pos);

    Board board_;
    std::istream& in_;
    std::ostream& out_;
};

} // namespace ttt
