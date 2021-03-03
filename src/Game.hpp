#ifndef GAME
#define GAME

#include <src/Window.hpp>
#include <src/View.hpp>
#include <src/Scene.hpp>

class Game {
    private:
        static Scene* activeScene;
        static std::map<std::string, Scene*> scenes;

        Game();

    public:
        static void play();
        static void end();

        static void setResolution(int width, int height);
        static void addScene(std::string name, Scene* scene);
        static void setActiveScene(std::string name);
};

#endif