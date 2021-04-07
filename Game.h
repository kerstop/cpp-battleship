#ifndef battleship_project_462
#define battleship_project_462

#include <vector>

namespace Battleship{

    class Game {
    private:
        
        void construct(int x, int y, int numberOfShips, int numberOfGuesses);
        std::vector<std::vector<int>> board;
        int numberOfShips;
        int boardHeight;
        int boardWidth;
        int numberOfGuesses;

    public:

        Game(int x, int y);
        Game(int x, int y, int numberOfShips);

        int getNumberOfGuesses();
        int getNumberOfShips();

        void printBoard();
        void placeShips(int n);
        int makeGuess(int x, int y);
        bool canMakeGuess();

    };
}


#endif