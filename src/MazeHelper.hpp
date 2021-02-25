#ifndef MAZE_HELPER
#define MAZE_HELPER

#include <src/GLObject.cpp>

namespace MazeHelper {
    std::vector<std::vector<char> > parseMazeData();
    std::vector<GLObject*> mazeDataToGLObjects(
        std::vector<std::vector<char> > mazeData, 
        std::map<std::string, std::string> textureSources
    );
    std::map<std::string, std::string> getTextureSources();
}

#endif