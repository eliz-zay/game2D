#pragma once

#include <vector>

#include <src/Scene.hpp>

#include <src/Sprite.cpp>
#include <src/BaseTile.cpp>
#include <src/TrapTile.cpp>
#include <src/MazeHelper.cpp>
#include <src/Label.cpp>

Scene::Scene(std::string name, std::string mazeSource, glm::vec2 initPosition) {
    this->name = name;

    std::vector<std::vector<char> > mazeData = MazeHelper::parseMazeData("resources/maze/maze_level_2.txt");
    MazeHelper::mazeDataToGLObjects(mazeData, &this->baseTiles, &this->trapTiles);

    this->baseObjects.push_back(new Sprite(initPosition, "resources/sprites/main_hero.png", this->baseTiles, this->trapTiles));
}

Scene::Scene(std::string name, std::string fontSource, glm::vec2 initPosition, std::string labelText, int size, glm::vec4 color) {
    this->name = name;

    this->baseObjects.push_back(new Label(initPosition, labelText, fontSource, size, color));
}

void Scene::draw() {
    for (auto obj: this->baseObjects) {
        obj->move();
    }
    for (auto tile: this->baseTiles) {
        tile->draw();
    }
    for (auto tile: this->trapTiles) {
        tile->draw(dynamic_cast<Sprite*>(this->baseObjects[0]));
    }
    for (auto obj: this->baseObjects) {
        obj->draw();
    }
}