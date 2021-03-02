#ifndef LABEL
#define LABEL

#include <glm/glm.hpp>

#include <src/BaseObject.hpp>
#include <src/Shader.hpp>

class Label: public BaseObject {
    private:
        std::string text;
        std::string fontSource;
        int size;
        glm::vec4 color;

    public:
        Label(glm::vec2 position, std::string text, std::string fontSource, int size, glm::vec4 color);

        virtual void draw();
};

#endif