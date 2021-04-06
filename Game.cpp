#include "Game.h"
#include <vector>
#include <iostream>

using namespace Battleship;



void Game::construct(int width, int height, int ships, int guesses){
    std::vector<int> row;
    row.assign(width, 0);
    board.assign(height, row);

    boardWidth = width;
    boardHeight = height;

    numberOfShips = 0;
    placeShips(ships);

    numberOfGuesses = guesses;

}

Game::Game(int width, int height) {
    
    int numShips = (width * height) / 8;

    int numGuesses = (width * height) * 0.8;

    construct(width, height, numShips, numGuesses);

}

Game::Game(int width, int height, int number) {
    
    int numGuesses = (width * height) * 0.8;

    construct(width, height, number, numGuesses);

}

void Game::printBoard(){
    //scale across the top
    std::cout << "+ ";
    for(int n{0}; n < boardWidth; n++){
        std::cout << n+1 << " ";
    }
    std::cout << std::endl;

    //print the body of the board
    for(int y{0}; y < boardHeight; y++){
        std::cout << y+1 << " ";
        for(int x{0}; x < boardWidth; x++){
            int tile{board[x][y]};
            switch (tile){

            case 0: //nothing
                std::cout << "? ";
                break;

            case 1: //miss
                std::cout << "# ";
                break;

            case 2: //ship
                std::cout << "? ";
                break;

            case 3: //hit
                std::cout << "X ";
                break;
            
            default:
                std::cout << "! ";
                break;
            }
        }
        std::cout << "\n";
    }
}

void Game::placeShips(int n){
    //make sure that the extra ships can fit
    if( numberOfShips + n < boardHeight * boardWidth){
        std::srand(time(nullptr));
        
        while( n > 0 ) {
            int x = std::rand() % boardWidth;
            int y = std::rand() % boardHeight;
            if (board[x][y] == 0)
            {
                board[x][y] = 2;
                n--;
                numberOfShips++;
            }
            
        }
    }
};

int Game::getNumberOfShips(){
    return numberOfShips;
}

int Game::getNumberOfGuesses(){
    return numberOfGuesses;
}

int Game::makeGuess(int x, int y){
    numberOfGuesses--;
    int *tile = &board[x-1][y-1];
    switch(*tile){
        
        case 0: //empty space
            std::cout << "Miss\n";
            (*tile)++;
            return 0;

        case 1: //missed shot space
            std::cout << "You already guessed that spot?\n";
            numberOfGuesses++;
            return -1;

        case 2: //un-hit ship space
            std::cout << "Hit!\n";
            (*tile)++;
            numberOfShips--;
            return 1;

        case 3: //hit ship
            std::cout << "You already guessed that spot?\n";
            numberOfGuesses++;
            return -1;

        default:
            std::cout << "ERROR\n";
            return -5;
    }
}

bool Game::canMakeGuess(){
    return numberOfGuesses > 0;
}
