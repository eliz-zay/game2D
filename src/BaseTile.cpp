#pragma once

#include <src/BaseTile.hpp>

#include <src/Tile.cpp>

BaseTile::BaseTile(glm::vec2 initPosition, std::string textureSource, bool wall): Tile(initPosition, textureSource) {
    this->wall = wall;
}

bool BaseTile::isWall() {
    return this->wall;
}