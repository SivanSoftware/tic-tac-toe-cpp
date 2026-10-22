#include "Ai.h"

#include <limits>

namespace ttt {

namespace {

Cell other(Cell c) { return c == Cell::X ? Cell::O : Cell::X; }

// Maps a finished board to a score from `aiPlayer`'s point of view.
// `depth` is the number of moves already played in this branch; subtracting it
// makes the AI prefer winning sooner and losing later.
int terminalScore(Status s, Cell aiPlayer, int depth) {
    Status aiWin  = aiPlayer == Cell::X ? Status::XWins : Status::OWins;
    Status aiLose = aiPlayer == Cell::X ? Status::OWins : Status::XWins;
    if (s == aiWin)  return 10 - depth;
    if (s == aiLose) return depth - 10;
    return 0; // draw
}

// Returns the best achievable score for `aiPlayer` when it is `toMove`'s turn.
int minimax(Board board, Cell aiPlayer, Cell toMove, int depth) {
    Status s = board.status();
    if (s != Status::Ongoing) {
        return terminalScore(s, aiPlayer, depth);
    }

    bool maximizing = (toMove == aiPlayer);
    int best = maximizing ? std::numeric_limits<int>::min()
                          : std::numeric_limits<int>::max();

    for (int pos = 1; pos <= 9; ++pos) {
        if (board.at(pos) != Cell::Empty) continue;

        Board next = board;
        next.place(pos, toMove);
        int score = minimax(next, aiPlayer, other(toMove), depth + 1);

        best = maximizing ? (score > best ? score : best)
                          : (score < best ? score : best);
    }
    return best;
}

} // namespace

int Ai::bestMove(const Board& board, Cell player) {
    int bestPos = -1;
    int bestScore = std::numeric_limits<int>::min();

    for (int pos = 1; pos <= 9; ++pos) {
        if (board.at(pos) != Cell::Empty) continue;

        Board next = board;
        next.place(pos, player);
        int score = minimax(next, player, other(player), 1);

        if (score > bestScore) {
            bestScore = score;
            bestPos = pos;
        }
    }
    return bestPos;
}

} // namespace ttt
