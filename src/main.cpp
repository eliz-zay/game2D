#include <iostream>
#include <exception>

#include <src/Game.cpp>

int main() {
    try {
        Game::setResolution(640, 640);

        Game::addScene("level_2", new Scene("level_2", "resources/maze/maze_level_2.txt", glm::vec2(0.f, 80.f)));
        Game::addScene("intro", new Scene("intro", "resources/fonts/arial.ttf", glm::vec2(50.f, 50.f), "fuck", 80, glm::vec4(0, 0, 1, 1)));

        Game::setActiveScene("intro");

        Game::play();

        Game::end();

        return 0;
        
    } catch (std::exception& exc) {
      std::cerr << exc.what() << std::endl;
      return -1;
    }
}