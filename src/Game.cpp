#include "Game.hpp"
#include "Tile.hpp"
#include <vector>
#include <iostream>

using namespace Battleship;

Game::Game(int width, int height) {


    Tile templateTile{false, nullptr};
    std::vector<Tile> templateRow;
    
    templateRow.assign(width, templateTile);
    board.assign(height, templateRow);

    boardWidth = width;
    boardHeight = height;
    numberOfShips = 0;
    numberOfGuesses = (width * height) * 0.8;

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
            
            //choose which character to print
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

void Game::printBoardDebug(){
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
            
            //choose which character to print
            if(tile->guessed){

                if(tile->ship){
                    std::cout << "X ";
                } 
                else {
                    std::cout << "# ";
                }

            } else {
                if(tile->ship){
                    std::cout << "^ ";
                }
                else {
                    std::cout << "? ";
                }
            }
        }
        std::cout << "\n";
    }
}

void Game::placeShip(int x, int y, int length, bool vertical) throw(int){
    
    //check if given values are within the board
    if(vertical && y + length > boardHeight ) {
        throw(1);
    }
    else if(!vertical && x + length > boardWidth){
        throw(1);
    }

    //check if spot overlaps with another ship
    Tile **potentialSpot = new Tile *[length];
    for(int i = 0; i < length; i ++){
        //if the ship should be placed vertically increment vertically
        if(vertical && !board[x][y+i].ship){
            potentialSpot[i] = &board[x][y+i];
        }
        //if the ship should be placed horizantally increment horizantally
        else if ( !vertical && !board[x+i][y].ship){
            potentialSpot[i] = &board[x+i][y];
        }
        //otherwise a ship was detected, clean up and exit
        else {
            delete[] potentialSpot;
            throw(1);
        }
    }

    //if neither then place ships on the board
    ships.push_back(Ship{length});
    Ship *currentShip = &ships.back();
    for(int i = 0; i < length; i ++){
        //if the ship should be placed vertically increment vertically
        int currentXPos;
        int currentYPos;
        if(vertical){
            currentXPos = x;
            currentYPos = y+i;
        }

        //if the ship should be placed horizantally increment horizantally
        else if (!vertical){
            currentXPos = x+i;
            currentYPos = y;
        }

        //tell ship struct where it's body parts are
        currentShip->body.push_back(std::pair<int,int>(currentXPos,currentYPos));
        //Put pointers to the ship on the tiles it occupies
        board[currentXPos][currentYPos].ship = currentShip;

    }
    //increment the number of ships in the game
    numberOfShips++;
}

void Game::placeShipsAtRandom(int shipsToPlace, int shipLength){

    std::srand(time(nullptr));

    int errorCounter{0};
    while( shipsToPlace > 0 ) {
        // pick random spot and direction
        int x = std::rand() % boardWidth;
        int y = std::rand() % boardHeight;
        bool vertical = std::rand() % 2 == 0;
        
        try {
            placeShip(x, y, shipLength, vertical);
            shipsToPlace--;
        }
        catch(int e){
            std::cerr << "Ship placement exception\n";
            errorCounter++;
            if(errorCounter > 1000){
                std::cerr << "Game::placeShipsAtRandom was unable to find" << 
                " an available spot for ship of length " << shipLength <<
                "\nAborting ship placement\n";
                return;
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
