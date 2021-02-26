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
        GLuint* vertexDistribution;
        glm::mat4 transformMatrix;

        Shader shader;
        Helper::RectCoordinates currentCoord;

    public:
        GLObject(glm::vec2 initPosition, std::string textureSource);
        ~GLObject();

        Helper::RectCoordinates getCurrentCoord();
        void initObject(glm::mat4* projection);
        void draw();
};

#endif