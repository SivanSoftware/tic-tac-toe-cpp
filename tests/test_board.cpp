// Minimal assertion-based tests for the board logic — no external framework.
#include <cstdio>
#include <cstdlib>

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

static void test_empty_board() {
    Board b;
    CHECK(b.status() == Status::Ongoing);
    CHECK(!b.isFull());
    CHECK(b.at(1) == Cell::Empty);
}

static void test_place_rules() {
    Board b;
    CHECK(b.place(1, Cell::X));
    CHECK(b.at(1) == Cell::X);
    CHECK(!b.place(1, Cell::O));  // occupied
    CHECK(!b.place(0, Cell::X));  // out of range
    CHECK(!b.place(10, Cell::X)); // out of range
    CHECK(!b.place(2, Cell::Empty)); // Empty is not a player
}

static void test_row_win() {
    Board b;
    b.place(1, Cell::X);
    b.place(2, Cell::X);
    b.place(3, Cell::X);
    CHECK(b.status() == Status::XWins);
}

static void test_diagonal_win() {
    Board b;
    b.place(3, Cell::O);
    b.place(5, Cell::O);
    b.place(7, Cell::O);
    CHECK(b.status() == Status::OWins);
}

static void test_draw() {
    Board b;
    // X O X / X O O / O X X  -> full, no line
    b.place(1, Cell::X); b.place(2, Cell::O); b.place(3, Cell::X);
    b.place(4, Cell::X); b.place(5, Cell::O); b.place(6, Cell::O);
    b.place(7, Cell::O); b.place(8, Cell::X); b.place(9, Cell::X);
    CHECK(b.isFull());
    CHECK(b.status() == Status::Draw);
}

int main() {
    test_empty_board();
    test_place_rules();
    test_row_win();
    test_diagonal_win();
    test_draw();

    if (g_failures == 0) {
        std::printf("All tests passed.\n");
        return 0;
    }
    std::printf("%d test(s) failed.\n", g_failures);
    return EXIT_FAILURE;
}
