#ifndef SHADER
#define SHADER

#include <map>
#include <any>

#include <GL/glew.h>
#include <OpenGL/glu.h>

enum EnumUniformType {
    GLM_MAT4,
    GLM_VEC4
};

class Shader {
    private:
        GLuint programID;
        GLuint vao, vboPosition, vboTexture;
        std::map<const char*, std::tuple<GLuint, EnumUniformType, std::any>> uniform;

    public:
        Shader(std::string vertexShader, std::string fragmentShader);
        ~Shader();

        template <typename T> void setUniform(const char* name, T value, EnumUniformType valueType);
        void initBuffers(GLfloat* vertices, GLfloat* texturePosition, int length);
        void setContext();
        void runShader(GLuint texture, int offset);
};

#endif