#ifndef Tile_struct_82349815
#define Tile_struct_82349815

#include "Ship.hpp"

namespace Battleship{
    struct Tile
    {
        bool guessed;
        Ship *ship;
    };
}


#endif
