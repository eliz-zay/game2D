#include <iostream>

#define WINDOW_WIDTH 360
#define WINDOW_HEIGHT 360

#include <src/Window.cpp>
#include <src/Shader.cpp>
#include <src/View.cpp>
#include <src/GLObject.cpp>
#include <src/MazeHelper.cpp>

int main() {
    View view(WINDOW_WIDTH, WINDOW_HEIGHT);

	Window window;
    window.initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	std::vector<std::vector<char> > mazeData = MazeHelper::parseMazeData();
	std::map<std::string, std::string> textureSources = MazeHelper::getTextureSources();
	std::vector<GLObject*> tiles = MazeHelper::mazeDataToGLObjects(mazeData, textureSources);

	for (auto tile: tiles) {
		tile->initObject(view.getProjection());
	}

	GLObject sprite(glm::vec2(10.f, 20.f), "resources/frog.png");
	sprite.initObject(view.getProjection());

	do {
		window.clearWindow();
		for (auto tile: tiles) {
			tile->draw();
		}
		sprite.move(window.getWindow());
		sprite.draw();
		window.refreshWindow();
	} while (window.shouldBeOpened());

	return 0;
}