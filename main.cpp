// 2048 GAME
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"

int main( int argc, char* argv[] )
{
    srand(time(NULL));   
    G2048 game;
    game.StartGame();
}