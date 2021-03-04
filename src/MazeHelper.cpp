#pragma once

#include <fstream>
#include <vector>
#include <exception>

#include <glm/glm.hpp>

#include <src/MazeHelper.hpp>

#include <src/ImageTexture.cpp>
#include <src/BaseTile.cpp>
#include <src/TrapTile.cpp>
#include <src/DoorTile.cpp>

std::vector<std::vector<char> > MazeHelper::parseMazeData(std::string mazeFile) {
    std::vector<std::vector<char> > mazeData;
    std::string line;
    std::ifstream file;

    file.open(mazeFile.c_str());
    if (!file.is_open()) {
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
    std::vector<TrapTile*>* trapTiles,
    std::vector<DoorTile*>* doorTiles
) {
    std::map<std::string, std::string> textureSources = MazeHelper::getTextureSources();
    // Here all tiles have the same size
    ImageTexture texture(textureSources["floor"]);

    int width = texture.getWidth();
    int height = texture.getHeight();

    for (int i = 0; i < mazeData.size(); i++) {
        for (int j = 0; j < mazeData[i].size(); j++) {
            switch (mazeData[i][j]) {
                case ('.'): {
                    (*baseTiles).push_back(
                        new BaseTile(
                            glm::vec2(j * width * 1.f, i * height * 1.f), 
                            textureSources["floor"], 
                            false
                        )
                    );
                    break; 
                }
                case ('#'): {
                    (*baseTiles).push_back(
                        new BaseTile(
                            glm::vec2(j * width * 1.f, i * height * 1.f), 
                            textureSources["wall"], 
                            true
                        )
                    ); 
                    break;
                }
                case ('T'): {
                    (*trapTiles).push_back(
                        new TrapTile(
                            glm::vec2(j * width * 1.f, i * height * 1.f),
                            textureSources["trap"],
                            textureSources["floor"]
                        )
                    );
                    break;
                }
                case ('D'): {
                    (*doorTiles).push_back(
                        new DoorTile(
                            glm::vec2(j * width * 1.f, i * height * 1.f),
                            textureSources["door"]
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