#pragma once

#include "Board.h"

namespace ttt {

// Computer opponent. Uses minimax to play perfectly, so the best a human
// can hope for is a draw.
class Ai {
public:
    // Returns the best cell (1..9) for `player` to move on the given board.
    // Precondition: the board has at least one empty cell and is Ongoing.
    static int bestMove(const Board& board, Cell player);
};

} // namespace ttt
