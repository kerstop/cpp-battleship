#include "Game.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include <vector>
#include <iostream>

using namespace Battleship;

Game::Game(int width, int height) {

    playerOne = Board(width, height);
    playerTwo = Board(width, height);

}
