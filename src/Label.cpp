#pragma once

#include <exception>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <src/Label.hpp>

#include <src/Shader.cpp>

Label::Label(glm::vec2 position, std::string text, std::string fontSource, int size, glm::vec4 color):
    shader("src/textVertexShader.glsl", "src/textFragmentShader.glsl")
{
    this->text = text;
    this->fontSource = fontSource;
    this->size = size;
    this->color = color;

    this->texturePosition = new GLfloat [12] {
        0.0f, 1.0f,            
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    float x = position.x;
    float y = position.y;
    
    GLfloat* vertices = new GLfloat[text.size() * 18];

    TextLib::initFont(fontSource, this->size);
    for (int i = 0; i < text.size(); i++) {
        Character* ch = TextLib::getChar(text[i]);

        float xpos = x;
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

    this->transformMatrix = glm::mat4(1.f);

    this->shader.initBuffers2(vertices, this->texturePosition, text.size());
    this->shader.setUniform<glm::mat4*>("projection", View::getProjection(), EnumUniformType::GLM_MAT4);
    this->shader.setUniform<glm::vec4*>("textColor", &(this->color), EnumUniformType::GLM_VEC4);
}

void Label::draw() {
    this->shader.runShader2(this->text);
}