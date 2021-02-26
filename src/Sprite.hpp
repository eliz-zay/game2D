#ifndef SPRITE
#define SPRITE

#include <vector>

#include <src/GLObject.hpp>
#include <src/Tile.hpp>

class Sprite: public GLObject {
        std::vector<Tile*> tiles;
        
        bool isCollision(int dx, int dy);
        
    public:
        Sprite(glm::vec2 initPosition, std::string textureSource, std::vector<Tile*> tiles);

        void move(GLFWwindow* window);
};

#endif