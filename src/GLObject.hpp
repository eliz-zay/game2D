#ifndef GL_OBJECT
#define GL_OBJECT

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>

#include <glm/glm.hpp>

#include <src/Helper.hpp>
#include <src/Shader.hpp>

class GLObject {
    protected:
        GLfloat* texturePosition;
        glm::mat4 transformMatrix;

        Shader shader;
        Helper::RectCoordinates currentCoord;

    public:
        GLObject(glm::vec2 initPosition, std::string textureSource, std::string vertexShader, std::string fragShader);
        ~GLObject();

        Helper::RectCoordinates getCurrentCoord();
        virtual void draw();
};

#endif