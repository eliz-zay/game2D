#pragma once

#include <src/Sprite.hpp>

#include <src/BaseTile.cpp>
#include <src/TrapTile.cpp>

Sprite::Sprite(glm::vec2 initPosition, std::string textureSource, std::vector<BaseTile*> baseTiles, std::vector<TrapTile*> trapTiles):
    GLObject(initPosition, textureSource)
{
    this->baseTiles = baseTiles;
    this->trapTiles = trapTiles;
}

void Sprite::move(GLFWwindow* window) {
    const GLfloat EPS = 0.0001;
    float speed = 3.0f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && this->currentCoord.y0 > 0 && !this->isCollision(0, -speed)) {
        this->transformMatrix = glm::translate(this->transformMatrix, glm::vec3(0.f, -speed * 1.f, 0.f));
        this->currentCoord.y0 -= speed * 1.f;
        this->currentCoord.y1 -= speed * 1.f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && this->currentCoord.y1 < WINDOW_HEIGHT && !this->isCollision(0, speed)) {
        this->transformMatrix = glm::translate(this->transformMatrix, glm::vec3(0.f, speed * 1.f, 0.f));
        this->currentCoord.y0 += speed * 1.f;
        this->currentCoord.y1 += speed * 1.f;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && this->currentCoord.x1 < WINDOW_WIDTH && !this->isCollision(speed, 0)) {
        this->transformMatrix = glm::translate(this->transformMatrix, glm::vec3(speed * 1.f, 0.f, 0.f));
        this->currentCoord.x0 += speed * 1.f;
        this->currentCoord.x1 += speed * 1.f;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && this->currentCoord.x0 > 0 && !this->isCollision(-speed, 0)) {
        this->transformMatrix = glm::translate(this->transformMatrix, glm::vec3(-speed * 1.f, 0.f, 0.f));
        this->currentCoord.x0 -= speed * 1.f;
        this->currentCoord.x1 -= speed * 1.f;
    }
}

bool Sprite::isCollision(int dx, int dy) {
    Helper::RectCoordinates newCoord({
        this->currentCoord.x0 + dx, this->currentCoord.y0 + dy,
        this->currentCoord.x1 + dx, this->currentCoord.y1 + dy
    });
    for (auto pTile: this->baseTiles) {
        if (pTile->isWall()) {
            Helper::RectCoordinates wallCoord = pTile->getCurrentCoord();
            if (
                newCoord.x0 < wallCoord.x1 &&
                newCoord.x1 > wallCoord.x0 &&
                newCoord.y1 > wallCoord.y0 &&
                newCoord.y0 < wallCoord.y1 
            ) {
                return true;
            }
        }
    }

    return false;
}