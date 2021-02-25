#ifndef SHADER
#define SHADER

#include <map>

#include <GL/glew.h>
#include <OpenGL/glu.h>

#include "Helper.cpp"

class Shader {
    GLuint programID;
    GLuint vao, vboPosition, vboTexture, ebo;
    GLuint texture;
    std::map<const char*, std::tuple<GLuint, glm::mat4*>> uniform;
public:
    Shader(std::string vertexShader, std::string fragmentShader);
    ~Shader();

    void setUniform(const char* name, glm::mat4* value);
    void initBuffers(GLfloat* vertices, GLfloat* texturePosition, Helper::TextureData textureData, GLuint* vertexDistribution);
    void runShader();
};

#endif