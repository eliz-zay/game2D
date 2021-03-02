#pragma once

#include <src/BaseObject.hpp>

BaseObject::BaseObject(glm::vec2 initPosition, std::string vertexShader, std::string fragShader):
    shader(vertexShader, fragShader)
{
    this->texturePosition = new GLfloat [12] {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    this->shader.setUniform<glm::mat4*>("projection", View::getProjection(), EnumUniformType::GLM_MAT4);
}

BaseObject::~BaseObject() {
    delete[] this->texturePosition;
}