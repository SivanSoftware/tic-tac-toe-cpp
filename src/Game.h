#pragma once

#include <iosfwd>

#include "Board.h"

namespace ttt {

// Who controls each side.
enum class Mode {
    TwoPlayers, // both sides are human
    VsComputer, // one side is the minimax AI
};

// Drives a game loop over the given input/output streams.
// Separating the streams from std::cin/std::cout keeps the loop testable.
class Game {
public:
    Game(std::istream& in, std::ostream& out);

    // Asks the player for a mode (and symbol, when playing the computer),
    // then runs the game. Returns the final status.
    Status run();

    // Runs a game with an explicit configuration, skipping the menu.
    // `aiPlayer` is ignored in TwoPlayers mode.
    Status run(Mode mode, Cell aiPlayer);

private:
    // Prompts the current human player until a legal move is entered.
    // Returns false on end-of-input or quit.
    bool readMove(Cell player, int& pos);

    // Reads the menu choices from the input stream.
    Mode chooseMode();
    Cell chooseHumanSymbol();

    Board board_;
    std::istream& in_;
    std::ostream& out_;
};

} // namespace ttt
