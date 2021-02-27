#ifndef BASE_TILE
#define BASE_TILE

#include <src/Tile.hpp>

class BaseTile: public Tile {
        bool wall;  
        
    public:
        BaseTile(glm::vec2 initPosition, std::string textureSource, bool wall);

        bool isWall();
};

#endif