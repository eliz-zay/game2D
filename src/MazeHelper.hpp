#ifndef MAZE_HELPER
#define MAZE_HELPER

#include <src/BaseTile.hpp>
#include <src/TrapTile.hpp>

namespace MazeHelper {
    std::vector<std::vector<char> > parseMazeData();
    void mazeDataToGLObjects(
        std::vector<std::vector<char> > mazeData, 
        std::map<std::string, std::string> textureSources,
        std::vector<BaseTile*>* baseTiles,
        std::vector<TrapTile*>* trapTiles
    );
    std::map<std::string, std::string> getTextureSources();
}

#endif