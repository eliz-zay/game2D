#pragma once

#include <src/TrapTile.hpp>

#include <src/Tile.cpp>
#include <src/BaseTile.cpp>
#include <src/Sprite.cpp>

TrapTile::TrapTile(glm::vec2 initPosition, std::string textureSource, std::string altTextureSource):
    Tile(initPosition, textureSource),
    altTile(initPosition, altTextureSource, false)
{
}

void TrapTile::draw(Sprite* mainHero) {
    GLfloat x1 = (this->currentCoord.x1 + this->currentCoord.x0) / 2;
    GLfloat y1 = (this->currentCoord.y1 + this->currentCoord.y0) / 2;
    GLfloat x2 = (mainHero->getCurrentCoord().x1 + mainHero->getCurrentCoord().x0) / 2;
    GLfloat y2 = (mainHero->getCurrentCoord().y1 + mainHero->getCurrentCoord().y0) / 2;

    if (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) <= 70) {
        this->shader.runShader();
    } else {
        this->altTile.draw();
    }
}