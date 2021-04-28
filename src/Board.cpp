#include "Board.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace Battleship;

Board::Board(){

    Board(8,8);

}

Board::Board(int width, int height){

    Tile templateTile{false, nullptr};
    std::vector<Tile> templateRow;
    
    templateRow.assign(width, templateTile);
    board.assign(height, templateRow);

    boardWidth = width;
    boardHeight = height;

}

std::string Board::getBoardString(){
    
    std::string constructor{""};
    
    //scale across the top
    constructor += "+ ";
    for(int n{0}; n < boardWidth; n++){
        constructor += std::to_string(n+1) + " ";
    }
    constructor += "\n";

    //get the body of the board
    for(int y{0}; y < boardHeight; y++){
        constructor += std::to_string(y+1) + " ";
        for(int x{0}; x < boardWidth; x++){
            Tile *tile = &board[x][y];
            
            //choose which character to print
            if(tile->guessed){

                if(tile->ship){
                    constructor += "X ";
                } 
                else {
                    constructor += "# ";
                }

            } else {
                constructor += "? ";
            }
        }
        constructor += "\n";
    }

    return constructor;
}

void Board::placeShip(int x, int y, int length, bool vertical) throw(ShipPlacementError){
    
    //check if given values are within the board
    if(vertical && y + length > boardHeight ) {
        throw(ShipPlacementError::ShipOutOfBounds);
    }
    else if(!vertical && x + length > boardWidth){
        throw(ShipPlacementError::ShipOutOfBounds);
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
            throw(ShipPlacementError::SpaceAlreadyOccupied);
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
}

void Board::placeShipsAtRandom(int shipsToPlace, int shipLength){

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
        catch(ShipPlacementError e){
            std::cerr << "Ship placement exception\n";
            
            if(e == ShipPlacementError::SpaceAlreadyOccupied){
                errorCounter++;
            }
            
            if(errorCounter > 1000){
                std::cerr << "Board::placeShipsAtRandom was unable to find" << 
                " an available spot for ship of length " << shipLength <<
                "\nAborting ship placement\n";
                return;
            }
        }
    }
};

int Board::getNumberOfActiveShips(){
    int total{0};
    for(const auto &i: ships ){
        if(i.health > 0){
            total++;
        }
    }
    return total;
}

int Board::getBoardHeight(){
    return boardHeight;
}

int Board::getBoardWidth(){
    return boardWidth;
}

Board::GuessResult Board::makeGuess(int x, int y){

    Tile *tile = &board[x-1][y-1];
    
    if(tile->guessed){
        return GuessResult::SpaceAreadyGuessed;
    }

    if(tile->ship){
        tile->guessed = true;
        tile->ship->health--;

        if(tile->ship->health == 0){
            return GuessResult::BattleshipSunk;
        }

        return GuessResult::Hit;

    } else {
        tile->guessed = true;
        return GuessResult::Miss;
    }
}