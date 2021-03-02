#ifndef SHADER
#define SHADER

#include <map>
#include <any>

#include <GL/glew.h>
#include <OpenGL/glu.h>

#include "Helper.cpp"

enum EnumUniformType {
    GLM_MAT4,
    GLM_VEC4
};

class Shader {
    private:
        GLuint programID;
        GLuint vao, vboPosition, vboTexture, ebo;
        GLuint texture;
        std::map<const char*, std::tuple<GLuint, EnumUniformType, std::any>> uniform;

    public:
        Shader(std::string vertexShader, std::string fragmentShader);
        ~Shader();

        template <typename T> void setUniform(const char* name, T value, EnumUniformType valueType);
        void initBuffers(GLfloat* vertices, GLfloat* texturePosition, Helper::TextureData textureData);
        void initBuffers2(GLfloat* vertices, GLfloat* texturePosition, int size);
        void runShader();
        void runShader2(std::string text);
};

#endif