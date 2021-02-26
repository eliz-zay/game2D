#pragma once

#include <src/Tile.hpp>

#include <src/GLObject.cpp>

Tile::Tile(glm::vec2 initPosition, std::string textureSource, bool wall):
    GLObject(initPosition, textureSource)
{
    this->wall = wall;
}

bool Tile::isWall() {
    return this->wall;
}