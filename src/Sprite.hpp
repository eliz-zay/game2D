#ifndef SPRITE
#define SPRITE

#include <vector>

#include <src/GLObject.hpp>
#include <src/BaseTile.hpp>
#include <src/TrapTile.hpp>

class TrapTile;

class Sprite: public GLObject {
    private:
        std::vector<BaseTile*> baseTiles;
        std::vector<TrapTile*> trapTiles;
        
        bool isCollision(int dx, int dy);
        
    public:
        Sprite(glm::vec2 initPosition, std::string textureSource, std::vector<BaseTile*> baseTiles, std::vector<TrapTile*> trapTiles);

        void move(GLFWwindow* window);
};

#endif