#ifndef Ship_struct_82349815
#define Ship_struct_82349815

#include <vector>
#include <utility>

namespace Battleship{
    struct Ship {
        std::vector<std::pair<int,int>> body;
        int health;
    };
}

#endif
