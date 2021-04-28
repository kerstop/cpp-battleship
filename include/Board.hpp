#ifndef Board_Class_82349815
#define Board_Class_82349815

#include "Ship.hpp"
#include <vector>
#include <list>
#include <string>

namespace Battleship{

    class Board{
        
        public: 
        struct Tile;
        private:
        
        std::vector<std::vector<Tile>> board;
        int boardWidth;
        int boardHeight;
        std::list<Ship> ships;
        
    public:

        enum GuessResult{
            SpaceAreadyGuessed,
            Hit,
            Miss,
            BattleshipSunk,
        };

        enum ShipPlacementError{
            SpaceAlreadyOccupied,
            ShipOutOfBounds,
        };

        Board();
        Board(int width, int heigt);

        GuessResult makeGuess(int x, int y);

        void placeShip(int x, int y, int length, bool vertical) throw(ShipPlacementError);
        void placeShipsAtRandom(int number, int length);

        std::string getBoardString();
        int getNumberOfActiveShips();
        int getBoardWidth();
        int getBoardHeight();

        struct Tile{
            bool guessed;
            Ship *ship;
        };

        

    };
}


#endif
