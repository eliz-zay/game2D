#ifndef TILE
#define TILE

#include "GLObject.hpp"

class Tile: public GLObject {
        bool wall;
        
    public:
        Tile(glm::vec2 initPosition, std::string textureSource, bool wall);

        bool isWall();
};

#endif