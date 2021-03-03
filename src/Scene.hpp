#ifndef SCENE
#define SCENE

#include <glm/glm.hpp>

#include <src/Window.cpp>
#include <src/View.cpp>
#include <src/BaseObject.hpp>
#include <src/MazeHelper.cpp>

class Scene {
    private:
        std::string name;
        std::vector<BaseObject*> baseObjects;
        std::vector<BaseTile*> baseTiles;
        std::vector<TrapTile*> trapTiles;
        std::vector<std::vector<char> > mazeData;
    
    public:
        Scene(std::string name, std::string mazeSource, glm::vec2 initPosition);
        Scene(std::string name, std::string fontSource, glm::vec2 initPosition, std::string labelText, int size, glm::vec4 color);

        void draw();
};

#endif