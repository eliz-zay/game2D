#include <iostream>

#include <src/Window.cpp>
#include <src/Shader.cpp>
#include <src/View.cpp>
#include <src/GLObject.cpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main() {
    View view(WINDOW_WIDTH, WINDOW_HEIGHT);

	Window window;
    window.initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	GLObject object(400, 400, glm::vec2(50.f, 50.f));
    object.initObject(view.getProjection(), "resources/container.jpg");

	do {
		window.clearWindow();
		object.draw();
		window.refreshWindow();
	} while (window.shouldBeOpened());

	return 0;
}