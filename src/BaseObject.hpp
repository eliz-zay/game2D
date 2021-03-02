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
        BaseObject(glm::vec2 initPosition, std::string vertexShader, std::string fragShader);
        ~BaseObject();

        virtual void draw() = 0;
};

#endif