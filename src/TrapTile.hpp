#ifndef TRAP_TILE
#define TRAP_TILE

#include <src/Tile.hpp>
#include <src/BaseTile.hpp>
#include <src/Sprite.hpp>

class Sprite;

class TrapTile: public Tile {
        BaseTile altTile;

    public:
        TrapTile(glm::vec2 initPosition, std::string textureSource, std::string altTextureSource);

        virtual void initObject(glm::mat4* projection);
        virtual void draw(Sprite* mainHero);
};

#endif