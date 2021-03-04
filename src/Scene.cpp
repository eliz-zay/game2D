#pragma once

#include <vector>

#include <src/Scene.hpp>

#include <src/Sprite.cpp>
#include <src/BaseTile.cpp>
#include <src/TrapTile.cpp>
#include <src/DoorTile.cpp>
#include <src/Label.cpp>
#include <src/MazeHelper.cpp>

Scene::Scene(std::string name, std::string mazeSource, glm::vec2 initPosition) {
    this->name = name;

    std::vector<std::vector<char> > mazeData = MazeHelper::parseMazeData(mazeSource);
    MazeHelper::mazeDataToGLObjects(mazeData, &this->baseTiles, &this->trapTiles, &this->doorTiles);

    this->baseObjects.push_back(new Sprite(initPosition, "resources/sprites/main_hero.png", this->baseTiles));
}

Scene::Scene(std::string name, std::string fontSource, glm::vec2 initPosition, std::string labelText, int size, glm::vec4 color) {
    this->name = name;
    this->baseObjects.push_back(new Label(initPosition, labelText, fontSource, size, color));
}

void Scene::draw(double deltaTime) {
    for (auto obj: this->baseObjects) {
        obj->move(deltaTime);
    }
    for (auto tile: this->baseTiles) {
        tile->draw();
    }
    for (auto tile: this->doorTiles) {
        tile->draw(dynamic_cast<Sprite*>(this->baseObjects[0]));
    }
    for (auto tile: this->trapTiles) {
        tile->draw(dynamic_cast<Sprite*>(this->baseObjects[0]));
    }
    for (auto obj: this->baseObjects) {
        obj->draw();
    }
}