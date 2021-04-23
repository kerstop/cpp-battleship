#include "Game.hpp"
#include <iostream>
#include <utility>

using namespace Battleship;

constexpr bool debug = false;

std::pair<int,int> getGuess(Game*);

int main () {

//initialize game

    Game game(6, 6);
    game.placeShipsAtRandom(3, 3);
    
//main game loop

    bool playing {true};
    while(playing){
        // main game loop
        while(game.canMakeGuess() && game.getNumberOfShips() > 0){
            
            // printing out game information
            std::cout << "Ships: " << game.getNumberOfShips() << std::endl;
            std::cout << "Guesses: " << game.getNumberOfGuesses() << std::endl;
            if(debug){
                game.printBoardDebug();
            }
            else {
                game.printBoard();
            }

            // ask player where to shoot
            std::cout << "Where would you like to fire?\n";
            
            auto guess = getGuess(&game);

            game.makeGuess(guess.first, guess.second);

            std::cout << std::endl;

        }//main game loop ends
        if(game.getNumberOfShips() == 0){
            std::cout << "Congragulations you win!\n";
        }
        else if(game.getNumberOfGuesses() == 0){
            std::cout << "Sorry, you lost\n";
        }
        playing = false;
    }

    return 0;
}

std::pair<int,int> getGuess(Game *game){
    int xCord{0};
    // while xCord is outside of the game bounds
    while(xCord <= 0 || xCord > game->getBoardWidth()){
        std::cout << "x cordinate: ";
        std::cin >> xCord;
        if (xCord <= 0 || xCord > game->getBoardWidth()){
            std::cout << "Bad x cordinate, please re-enter.\n";
        }
    }

    int yCord{0};
    while(yCord <= 0 || yCord > game->getBoardHeight()){
        std::cout << "y cordinate: ";
        std::cin >> yCord;
        if(yCord <= 0 || yCord > game->getBoardHeight()){
            std::cout << "Bad y cordinate, please re-enter.\n";
        }
    }

    return std::pair<int,int>(xCord,yCord);
}