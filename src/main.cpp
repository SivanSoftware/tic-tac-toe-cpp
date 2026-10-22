#include <iostream>

#include "Game.h"

int main() {
    ttt::Game game(std::cin, std::cout);
    game.run();
    return 0;
}
