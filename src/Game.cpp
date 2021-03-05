#pragma once

#include <src/Game.hpp>

#include <src/Window.cpp>
#include <src/View.cpp>
#include <src/Scene.cpp>

std::tuple<std::string, Scene*, int> Game::activeScene = {};
std::map<std::string, Scene*> Game::scenes = {};
std::map<int, std::string> Game::levelNames = {};

void Game::update(SceneChange sceneChange) {
    GLFWwindow* window = Window::getWindow();

    std::string name = std::get<0>(Game::activeScene);
    int nextLevel = std::get<2>(Game::activeScene) + 1;

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && name == "Intro") {
        Game::setActiveScene("Level_1", 1);
    }

    if (sceneChange == SceneChange::NEXT_LEVEL && (!Game::levelNames[nextLevel].empty())) {
        Game::setActiveScene(Game::levelNames[nextLevel], nextLevel);
    } else if (sceneChange == SceneChange::NEXT_LEVEL || sceneChange == SceneChange::WIN) {
        Game::setActiveScene("Win");
    } else if (sceneChange == SceneChange::DEATH) {
        Game::setActiveScene("Death");
    }
}

void Game::play() {
    double lastTime = 0.;
    double lastTimeFPS = 0.;
    double currentTime, deltaTime;
    int frames = 0;
    do {
        currentTime = Window::getTime();
        deltaTime = 1000 * (currentTime - lastTime);
        lastTime = currentTime;
        frames++;
        if (currentTime - lastTimeFPS >= 1.) {
            std::cout << double(frames)<< std::endl;
            frames = 0;
            lastTimeFPS += 1.;
        }


        Window::clearWindow();
        Game::update();
        std::get<1>(Game::activeScene)->draw(deltaTime);
        Window::refreshWindow();
    } while (Window::shouldBeOpened());
}

void Game::end() {
    Window::closeWindow();
}

void Game::setResolution(int width, int height) {
    View::setResolution(width, height);
    Window::initWindow(width, height);
}

void Game::addScene(std::string name, int level, Scene* scene) {
    Game::scenes.insert({name, scene});
    if (level) {
        Game::levelNames.insert({level, name});
    }
}

void Game::setActiveScene(std::string name, int level) {
    Game::activeScene = {name, Game::scenes[name], level};
    Game::scenes[name]->activate();
}