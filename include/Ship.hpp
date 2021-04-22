#ifndef Ship_struct_82349815
#define Ship_struct_82349815

#include <vector>
#include <utility>

namespace Battleship{
    struct Ship {
        int health;
        std::vector<std::pair<int,int>> body;
    };
}

#endif
