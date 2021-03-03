#pragma once

#include <src/Game.hpp>

#include <src/Window.cpp>
#include <src/View.cpp>
#include <src/Scene.cpp>

Scene* Game::activeScene = nullptr;
std::map<std::string, Scene*> Game::scenes = {};

void Game::play() {
    do {
        Window::clearWindow();
        Game::activeScene->draw();
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

void Game::addScene(std::string name, Scene* scene) {
    Game::scenes.insert({name, scene});
}

void Game::setActiveScene(std::string name) {
    Game::activeScene = Game::scenes[name];
}