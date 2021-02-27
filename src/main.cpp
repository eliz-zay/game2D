#include <iostream>
#include <exception>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#include <src/Window.cpp>
#include <src/Shader.cpp>
#include <src/View.cpp>
#include <src/Sprite.cpp>
#include <src/BaseTile.cpp>
#include <src/TrapTile.cpp>
#include <src/MazeHelper.cpp>

int main() {
	try {
		View view(WINDOW_WIDTH, WINDOW_HEIGHT);

		Window window;
		window.initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

		std::vector<std::vector<char> > mazeData = MazeHelper::parseMazeData();
		std::map<std::string, std::string> textureSources = MazeHelper::getTextureSources();
		std::vector<BaseTile*> baseTiles;
		std::vector<TrapTile*> trapTiles;
		MazeHelper::mazeDataToGLObjects(mazeData, textureSources, &baseTiles, &trapTiles);

		for (auto tile: baseTiles) {
			tile->initObject(view.getProjection());
		}
		for (auto tile: trapTiles) {
			tile->initObject(view.getProjection());
		}

		Sprite sprite(glm::vec2(0.f, 80.f), "resources/main_hero.png", baseTiles, trapTiles);
		sprite.initObject(view.getProjection());

		do {
			window.clearWindow();
			sprite.move(window.getWindow());
			for (auto tile: baseTiles) {
				tile->draw();
			}
			for (auto tile: trapTiles) {
				tile->draw(&sprite);
			}
			sprite.draw();
			window.refreshWindow();
		} while (window.shouldBeOpened());

		return 0;

	} catch (std::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return -1;
	}
}