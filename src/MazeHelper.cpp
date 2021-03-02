#pragma once

#include <fstream>
#include <vector>
#include <exception>

#include <glm/glm.hpp>

#include <src/MazeHelper.hpp>

#include <src/Helper.cpp>
#include <src/BaseTile.cpp>
#include <src/TrapTile.cpp>

std::vector<std::vector<char> > MazeHelper::parseMazeData(std::string mazeFile) {
    std::vector<std::vector<char> > mazeData;
    std::string line;
    std::ifstream file;

    file.open(mazeFile.c_str());
    if (!file.is_open()) {
        std::cout << "Helper: Could not open file" << std::endl;
        throw std::invalid_argument("MazeHelper: Could not open file");
    }

    while (std::getline(file, line)) {
        mazeData.push_back(std::vector<char>(line.begin(), line.end()));
    }

    file.close();
    return mazeData;
}

void MazeHelper::mazeDataToGLObjects(
    std::vector<std::vector<char> > mazeData,
    std::vector<BaseTile*>* baseTiles,
    std::vector<TrapTile*>* trapTiles
) {
    std::map<std::string, std::string> textureSources = MazeHelper::getTextureSources();
    // Here all tiles have the same size
    Helper::TextureData textureData = Helper::parseTexture(textureSources["floor"]);

    for (int i = 0; i < mazeData.size(); i++) {
        for (int j = 0; j < mazeData[i].size(); j++) {
            switch (mazeData[i][j]) {
                case ('.'): {
                    (*baseTiles).push_back(
                        new BaseTile(
                            glm::vec2(j * textureData.width * 1.f, i * textureData.height * 1.f), 
                            textureSources["floor"], 
                            false
                        )
                    );
                    break; 
                }
                case ('#'): {
                    (*baseTiles).push_back(
                        new BaseTile(
                            glm::vec2(j * textureData.width * 1.f, i * textureData.height * 1.f), 
                            textureSources["wall"], 
                            true
                        )
                    ); 
                    break;
                }
                case ('T'): {
                    (*trapTiles).push_back(
                        new TrapTile(
                            glm::vec2(j * textureData.width * 1.f, i * textureData.height * 1.f),
                            textureSources["trap"],
                            textureSources["floor"]
                        )
                    );
                    break;
                }
                case ('D'): {
                    (*baseTiles).push_back(
                        new BaseTile(
                            glm::vec2(j * textureData.width * 1.f, i * textureData.height * 1.f),
                            textureSources["door"],
                            false
                        )
                    );
                    break;
                }
            }
        }
    }
}

std::map<std::string, std::string> MazeHelper::getTextureSources() {
    std::map<std::string, std::string> textureSources;
    textureSources.insert({"floor", "resources/floor/floor.jpg"});
	textureSources.insert({"wall", "resources/walls/wall.jpg"});
    textureSources.insert({"door", "resources/doors/portal.jpg"});
    textureSources.insert({"trap", "resources/other/chemicals.png"});

    return textureSources;
}