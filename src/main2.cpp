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

int main() {
	try {
		View::setResolution(WINDOW_WIDTH, WINDOW_HEIGHT);
		Window::initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

		std::vector<BaseTile*> baseTiles;
		std::vector<TrapTile*> trapTiles;
		std::vector<std::vector<char> > mazeData = MazeHelper::parseMazeData("resources/maze/maze_level_2.txt");
		MazeHelper::mazeDataToGLObjects(mazeData, &baseTiles, &trapTiles);

		Sprite sprite(glm::vec2(0.f, 80.f), "resources/sprites/main_hero.png", baseTiles, trapTiles);

		Label label(glm::vec2(50.f, 50.f), "fuck", "resources/fonts/arial.ttf", 80, glm::vec4(0, 0, 1, 1));

		do {
			Window::clearWindow();
			// label.draw();
			sprite.move();
			for (auto tile: baseTiles) {
				tile->draw();
			}
			for (auto tile: trapTiles) {
				tile->draw(&sprite);
			}
			sprite.draw();
			Window::refreshWindow();
		} while (Window::shouldBeOpened());

		Window::closeWindow();

		return 0;

	} catch (std::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return -1;
	}
}