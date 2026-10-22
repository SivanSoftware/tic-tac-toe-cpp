// Tests for the minimax computer opponent.
#include <cstdio>
#include <cstdlib>

#include "Ai.h"
#include "Board.h"

using namespace ttt;

static int g_failures = 0;

#define CHECK(cond)                                                      \
    do {                                                                 \
        if (!(cond)) {                                                   \
            std::printf("FAIL %s:%d  %s\n", __FILE__, __LINE__, #cond);  \
            ++g_failures;                                                \
        }                                                                \
    } while (0)

static Cell other(Cell c) { return c == Cell::X ? Cell::O : Cell::X; }

static void test_takes_winning_move() {
    Board b;
    b.place(1, Cell::X);
    b.place(2, Cell::X);
    // X can win at 3.
    CHECK(Ai::bestMove(b, Cell::X) == 3);
}

static void test_blocks_opponent() {
    Board b;
    b.place(1, Cell::X);
    b.place(2, Cell::X);
    // X threatens 3; O to move must block at 3.
    CHECK(Ai::bestMove(b, Cell::O) == 3);
}

// Recursively verifies the AI never loses from `board`, whatever the opponent
// does. When it is the AI's turn it plays its chosen move; when it is the
// opponent's turn, every legal reply is explored.
static void assertNeverLoses(Board board, Cell ai, Cell toMove) {
    Status s = board.status();
    if (s != Status::Ongoing) {
        Status aiLose = ai == Cell::X ? Status::OWins : Status::XWins;
        CHECK(s != aiLose);
        return;
    }

    if (toMove == ai) {
        int pos = Ai::bestMove(board, ai);
        board.place(pos, ai);
        assertNeverLoses(board, ai, other(ai));
    } else {
        for (int pos = 1; pos <= 9; ++pos) {
            if (board.at(pos) != Cell::Empty) continue;
            Board next = board;
            next.place(pos, toMove);
            assertNeverLoses(next, ai, ai);
        }
    }
}

static void test_unbeatable_as_first_player() {
    assertNeverLoses(Board{}, Cell::X, Cell::X);
}

static void test_unbeatable_as_second_player() {
    assertNeverLoses(Board{}, Cell::O, Cell::X);
}

static void test_ai_vs_ai_is_draw() {
    Board b;
    Cell toMove = Cell::X;
    while (b.status() == Status::Ongoing) {
        b.place(Ai::bestMove(b, toMove), toMove);
        toMove = other(toMove);
    }
    CHECK(b.status() == Status::Draw);
}

int main() {
    test_takes_winning_move();
    test_blocks_opponent();
    test_unbeatable_as_first_player();
    test_unbeatable_as_second_player();
    test_ai_vs_ai_is_draw();

    if (g_failures == 0) {
        std::printf("All AI tests passed.\n");
        return 0;
    }
    std::printf("%d AI test(s) failed.\n", g_failures);
    return EXIT_FAILURE;
}
