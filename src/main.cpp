#include <iostream>
#include <exception>

#include <src/Game.cpp>

int main() {
    try {
        Game::setResolution(800, 800);

        Game::setTextureSources();
        Game::loadTextures();

        Game::addScene("Intro", 0, 0, new Scene("Intro", "resources/fonts/arial.ttf", glm::vec2(80.f, 70.f), "I would like to play a game.", 40, glm::vec4(1, 0.5, 0.5, 1), "src/textVertexShader.glsl", "src/textFragmentShader.glsl"));
        Game::addScene("Intro_to_1", 0, 1, new Scene("Next_level_1", "resources/fonts/arial.ttf", glm::vec2(80.f, 70.f), "Level 1", 40, glm::vec4(1, 0.5, 0.5, 1), "src/textVertexShader.glsl", "src/textFragmentShader.glsl"));
        Game::addScene("Intro_to_2", 0, 2, new Scene("Next_level_2", "resources/fonts/arial.ttf", glm::vec2(80.f, 70.f), "Level 2", 40, glm::vec4(1, 0.5, 0.5, 1), "src/textVertexShader.glsl", "src/textFragmentShader.glsl"));
        Game::addScene("Intro_to_3", 0, 3, new Scene("Next_level_3", "resources/fonts/arial.ttf", glm::vec2(80.f, 70.f), "Level 3", 40, glm::vec4(1, 0.5, 0.5, 1), "src/textVertexShader.glsl", "src/textFragmentShader.glsl"));
        Game::addScene("Win", 0, 0, new Scene("Win", "resources/fonts/arial.ttf", glm::vec2(80.f, 70.f), "Congrats!", 40, glm::vec4(1, 0.5, 0.5, 1), "src/textVertexShader.glsl", "src/textFragmentShader.glsl"));
        Game::addScene("Death", 0, 0, new Scene("Death", "resources/fonts/arial.ttf", glm::vec2(80.f, 70.f), "Not your lucky day.", 40, glm::vec4(1, 0.5, 0.5, 1), "src/textVertexShader.glsl", "src/textFragmentShader.glsl"));
        Game::addScene("Level_1", 1, 0, new Scene("Level_1", "resources/maze/maze_level_1.txt", "src/vertexShader.glsl", "src/fragmentShader.glsl"));
        Game::addScene("Level_2", 2, 0, new Scene("Level_2", "resources/maze/maze_level_2.txt", "src/vertexShader.glsl", "src/fragmentShader.glsl"));
        Game::addScene("Level_3", 3, 0, new Scene("Level_3", "resources/maze/maze_level_3.txt", "src/vertexShader.glsl", "src/fragmentShader.glsl"));

        Game::setActiveScene("Intro");

        Game::play();

        Game::end();

        return 0;

    } catch (std::exception& exc) {
      std::cerr << exc.what() << std::endl;
      return -1;
    }
}