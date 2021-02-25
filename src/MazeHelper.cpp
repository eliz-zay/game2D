#pragma once

#include <fstream>
#include <vector>
#include <exception>

#include <glm/glm.hpp>

#include "MazeHelper.hpp"

#include "Helper.cpp"

std::vector<std::vector<char> > MazeHelper::parseMazeData() {
    std::vector<std::vector<char> > mazeData;
    std::string line;
    std::ifstream file;

    file.open("resources/maze.txt");
    if (!file.is_open()) {
        std::cout << "Helper: Could not open file" << std::endl;
        // TODO: throw exception
    }

    while (std::getline(file, line)) {
        mazeData.push_back(std::vector<char>(line.begin(), line.end()));
    }

    file.close();
    return mazeData;
}

std::vector<GLObject*> MazeHelper::mazeDataToGLObjects(
    std::vector<std::vector<char> > mazeData,
    std::map<std::string, std::string> textureSources
) {
    // Here all tiles have the same size
    Helper::TextureData textureData = Helper::parseTexture(textureSources["floor"]);

    std::vector<GLObject*> objects;
    for (int i = 0; i < mazeData.size(); i++) {
        for (int j = 0; j < mazeData[i].size(); j++) {
            switch (mazeData[i][j]) {
                case ('.'): {
                    objects.push_back(new GLObject(glm::vec2(j * textureData.width * 1.f, i * textureData.height * 1.f), textureSources["floor"])); 
                    break; 
                }
                case ('#'): {
                    objects.push_back(new GLObject(glm::vec2(j * textureData.width * 1.f, i * textureData.height * 1.f), textureSources["wall"])); 
                    break;
                }
            }
        }
    }

    return objects;
}

std::map<std::string, std::string> MazeHelper::getTextureSources() {
    std::map<std::string, std::string> textureSources;
    textureSources.insert({"floor", "resources/floor/center_1.png"});
	textureSources.insert({"wall", "resources/walls/wall_1.png"});

    return textureSources;
}