#ifndef WINDOW
#define WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>

class Window {
    private:
        static int width, height;
        static GLFWwindow* window;

        Window();
        
    public:
        static void initWindow(int width, int height);
        static void clearWindow();
        static bool shouldBeOpened();
        static void refreshWindow();
        static void closeWindow();

        static GLFWwindow* getWindow();
        static int getWidth();
        static int getHeight();
        static double getTime();
};

#endif