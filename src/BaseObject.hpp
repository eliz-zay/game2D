#ifndef BASE_OBJECT
#define BASE_OBJECT

#include <glm/glm.hpp>

#include <src/Shader.hpp>

class BaseObject {
    protected:
        GLfloat* vertices;
        GLfloat* texturePosition;

        Shader shader;

    public:
        BaseObject(std::string vertexShader, std::string fragShader);
        ~BaseObject();

        virtual void move(double deltaTime);
        virtual void draw() = 0;
};

#endif