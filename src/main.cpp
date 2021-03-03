#include <iostream>
#include <exception>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#include <src/Window.cpp>
#include <src/View.cpp>
#include <src/Sprite.cpp>
#include <src/BaseTile.cpp>
#include <src/TrapTile.cpp>
#include <src/MazeHelper.cpp>
#include <src/Label.cpp>
#include <src/Scene.cpp>

int main() {
    try {
        View::setResolution(WINDOW_WIDTH, WINDOW_HEIGHT);
		Window::initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

        Scene level1("level_1", "resources/maze/maze_level_2.txt", glm::vec2(0.f, 80.f));
        Scene fuckLabel("intro", "resources/fonts/arial.ttf", glm::vec2(50.f, 50.f), "fuck", 80, glm::vec4(0, 0, 1, 1));

        do {
            Window::clearWindow();
            fuckLabel.draw();
            Window::refreshWindow();
        } while (Window::shouldBeOpened());

		Window::closeWindow();

        return 0;

	} catch (std::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return -1;
    }
}