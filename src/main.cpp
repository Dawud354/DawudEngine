#include <iostream>

#include "Application.h"



int main() {

    const auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    Application game;
    game.run();


    return 0;
}
