#include "Game.hpp"
#include "Tile.hpp"
#include <vector>
#include <iostream>

using namespace Battleship;



void Game::construct(int width, int height, int ships, int guesses){
    
    Tile templateTile{false, nullptr};
    std::vector<Tile> templateRow;
    
    templateRow.assign(width, templateTile);
    board.assign(height, templateRow);

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
            Tile *tile = &board[x][y];
            
            if(tile->guessed){

                if(tile->ship){
                    std::cout << "X ";
                } 
                else {
                    std::cout << "# ";
                }

            } else {
                std::cout << "? ";
            }
        }
        std::cout << "\n";
    }
}

void Game::placeShips(int shipsToPlace){

    //make sure that the extra ships can fit
    if( numberOfShips + shipsToPlace < boardHeight * boardWidth){
        std::srand(time(nullptr));
        
        while( shipsToPlace > 0 ) {
            int x = std::rand() % boardWidth;
            int y = std::rand() % boardHeight;
            if (!board[x][y].ship)
            {
                board[x][y].ship = true;
                shipsToPlace--;
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

int Game::getBoardHeight(){
    return boardHeight;
}

int Game::getBoardWidth(){
    return boardWidth;
}

int Game::makeGuess(int x, int y){

    Tile *tile = &board[x-1][y-1];
    
    if(tile->guessed){
        std::cout << "You already guessed that spot\n";
        return -1;
    }

    if(tile->ship){
        std::cout << "Hit!\n";
        tile->guessed = true;
        numberOfGuesses--;
        return 1;
    } else {
        std::cout << "Miss\n";
        tile->guessed = true;
        numberOfGuesses--;
        return 0;
    }
}

bool Game::canMakeGuess(){
    return numberOfGuesses > 0;
}
