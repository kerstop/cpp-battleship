#include "Game.hpp"
#include <iostream>
#include <utility>
#include <string>

using namespace Battleship;
using std::string;

constexpr bool debug = false;

string combineStringsSideBySide(string sOne, string sTwo);

int main () {

//initialize game

    Game game(8,8);
    game.playerOne.placeShipsAtRandom(3,3);
    game.playerTwo.placeShipsAtRandom(3,3);

//main game loop

    
    

    

    
}

string combineStringsSideBySide(string sOne, string sTwo){

    string sOut = "";

    auto oneWalker = sOne.begin();
    auto twoWalker = sTwo.begin();

    while (oneWalker != sOne.end() && twoWalker != sTwo.end()){
        while(oneWalker != sOne.end()){
            if(*oneWalker != '\n'){
                sOut.push_back(*oneWalker);
                oneWalker++;
            }
            else {
                sOut.push_back(' ');
                oneWalker++;
                break;
            }
        }
        while (twoWalker != sTwo.end()){
            
            sOut.push_back(*twoWalker);
            
            if (*twoWalker == '\n'){
                twoWalker++;
                break;
            }
            twoWalker++;
        }
        
    }
    return sOut;

}