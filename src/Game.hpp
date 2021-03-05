#ifndef GAME
#define GAME

#include <src/Window.hpp>
#include <src/View.hpp>
#include <src/Scene.hpp>

enum SceneChange {
    NEXT_LEVEL,
    DEATH,
    WIN,
    NONE
};

class Game {
    private:
        static std::tuple<std::string, Scene*, int, int> activeScene;
        static std::map<std::string, Scene*> scenes;
        static std::map<int, std::string> levelScenes;
        static std::map<int, std::string> levelIntros;

        Game();

    public:
        static void update(SceneChange sceneChange = SceneChange::NONE);
        static void play();
        static void end();

        static void setResolution(int width, int height);
        static void addScene(std::string name, int level, int levelIntro, Scene* scene);
        static void setActiveScene(std::string name, int level = 0, int levelIntro = 0);
};

#endif