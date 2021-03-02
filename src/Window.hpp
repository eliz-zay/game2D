#ifndef WINDOW
#define WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>

class Window {
    private:
        static GLFWwindow* window;

        Window();
        
    public:
        static GLFWwindow* getWindow();
        
        static void initWindow(int width, int height);
        static void clearWindow();
        static bool shouldBeOpened();
        static void refreshWindow();
        static void closeWindow();
};

#endif