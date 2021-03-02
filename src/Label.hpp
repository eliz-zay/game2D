#ifndef LABEL
#define LABEL

#include <glm/glm.hpp>

#include <src/GLObject.hpp>
#include <src/Shader.hpp>

class Label {
    private:
        std::string text;
        std::string fontSource;
        int size;
        glm::vec4 color;

    protected:
        GLfloat* texturePosition;
        glm::mat4 transformMatrix;

        Shader shader;

    public:
        Label(glm::vec2 position, std::string text, std::string fontSource, int size, glm::vec4 color);

        void draw();
};

#endif