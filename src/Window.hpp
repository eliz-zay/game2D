#ifndef WINDOW
#define WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>

class Window {
    GLFWwindow* window;
public:
    ~Window();

    GLFWwindow* getWindow();
    
    void initWindow(int width, int height);
    void clearWindow();
    bool shouldBeOpened();
    void refreshWindow();
};

#endif