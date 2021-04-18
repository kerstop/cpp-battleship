#include "Game.h"
#include <iostream>

using namespace Battleship;

int main () {

//initialize game

    Game game(6, 6);
    
//main game loop

    bool playing {true};
    while(playing){
        // main game loop
        while(game.canMakeGuess()){
            
            // printing out game information
            std::cout << "Ships: " << game.getNumberOfShips() << std::endl;
            std::cout << "Guesses: " << game.getNumberOfGuesses() << std::endl;
            game.printBoard();

            // ask player where to shoot
            std::cout << "Where would you like to fire?\n";
            
            int xCord{0};
            // while xCord is outside of the game bounds
            while(xCord <= 0 || xCord > game.getBoardWidth()){
                std::cout << "x cordinate: ";
                std::cin >> xCord;
                if (xCord <= 0 || xCord > game.getBoardWidth()){
                    std::cout << "Bad x cordinate, please re-enter.\n";
                }
            }

            int yCord{0};
            while(yCord <= 0 || yCord > game.getBoardHeight()){
                std::cout << "y cordinate: ";
                std::cin >> yCord;
                if(yCord <= 0 || yCord > game.getBoardHeight()){
                    std::cout << "Bad y cordinate, please re-enter.\n";
                }
            }

            game.makeGuess(xCord, yCord);

            std::cout << std::endl;

        }
        playing = false;
    }

    return 0;
}
