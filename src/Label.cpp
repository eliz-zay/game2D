#pragma once

#include <exception>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <src/Label.hpp>

#include <src/BaseObject.cpp>
#include <src/Shader.cpp>
#include <src/TextLib.cpp>

Label::Label(std::string fontSource, int size):
    BaseObject("src/textVertexShader.glsl", "src/textFragmentShader.glsl")
{
    this->fontSource = fontSource;
    this->size = size;

    TextLib::initFont(fontSource, this->size);
}

void Label::setText(glm::vec2 position, std::string text, glm::vec4 color) {
    this->text = text;
    this->color = color;

    float x = position.x;
    float y = position.y;
    
    this->vertices = new GLfloat[text.size() * 18];

    for (int i = 0; i < text.size(); i++) {
        Character* ch = TextLib::getChar(text[i]);

        float xpos = x + ch->bearing.x;
        float ypos = y + this->size - ch->bearing.y;

        float w = ch->size.x;
        float h = ch->size.y;

        GLfloat* verticeBuffer = new GLfloat[18] {
             xpos,     ypos + h, 0,          
             xpos,     ypos,     0,
             xpos + w, ypos,     0,

             xpos,     ypos + h, 0,
             xpos + w, ypos,     0,
             xpos + w, ypos + h, 0    
        };

        memcpy(vertices + i * 18, verticeBuffer, 18 * sizeof(GLfloat));

        delete[] verticeBuffer;

        x += (ch->advance >> 6);
    }

    this->shader.initBuffers(vertices, this->texturePosition, text.size());
    this->shader.setUniform<glm::vec4*>("textColor", &(this->color), EnumUniformType::GLM_VEC4);
}

void Label::draw() {
    this->shader.setContext();

    for (int i = 0; i < text.size(); i++) {
        Character* ch = TextLib::getChar(text[i]);
        this->shader.runShader(ch->textureId, i * 6);
    }
}