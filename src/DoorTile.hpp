#ifndef DOOR_TILE
#define DOOR_TILE

#include <src/Tile.hpp>
#include <src/Sprite.hpp>

class DoorTile: public Tile {
    private:
        void isOpened(Sprite* mainHero);

    public:
        DoorTile(glm::vec2 initPosition, std::string textureSource);

        virtual void draw(Sprite* mainHero);
};

#endif