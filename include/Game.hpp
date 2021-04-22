#ifndef battleship_project_462
#define battleship_project_462

#include <vector>
#include "Tile.hpp"
#include <exception>

namespace Battleship{

    class Game {
    private:
        
        std::vector<std::vector<Tile>> board;
        std::vector<Ship> ships;
        int numberOfShips;
        int boardHeight;
        int boardWidth;
        int numberOfGuesses;

    public:

        Game(int x, int y);

        int getNumberOfGuesses();
        int getNumberOfShips();
        int getBoardWidth();
        int getBoardHeight();
        bool canMakeGuess();

        void printBoard();

        void placeShip(int x, int y, int length, bool vertical) throw(int);
        void placeShipsAtRandom(int n, int length);
        int makeGuess(int x, int y);

    };
}


#endif