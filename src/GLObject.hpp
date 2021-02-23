#ifndef GL_OBJECT
#define GL_OBJECT

#include <OpenGL/glu.h>

#include <glm/glm.hpp>

#include "Shader.cpp"

class GLObject {
    GLfloat* vertices;
    GLfloat* texturePosition;
    GLuint* vertexDistribution;
    glm::mat4 transformMatrix;

    Shader shader;
public:
    GLObject(int width, int height, glm::vec2 initPosition);
    ~GLObject();

    void initObject(glm::mat4 projection, std::string textureSource);
    void draw();
};

#endif