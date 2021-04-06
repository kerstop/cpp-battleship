#include "Game.h"
#include <iostream>

using namespace Battleship;

int main () {

//initialize game

    Game game(6, 6);
    
//main game loop

    bool playing {true};
    while(playing){
        while(game.canMakeGuess()){
            
            std::cout << "Ships: " << game.getNumberOfShips() << std::endl;
            std::cout << "Guesses: " << game.getNumberOfGuesses() << std::endl;
            game.printBoard();
            std::cout << "Where would you like to fire?\n";
            std::cout << "x cordinate: ";
            int xCord{0};
            std::cin >> xCord;
            int yCord{0};
            std::cout << "y cordinate: ";
            std::cin >> yCord;
            game.makeGuess(xCord, yCord);

            std::cout << std::endl;

        }
        playing = false;
    }

    return 0;
}
