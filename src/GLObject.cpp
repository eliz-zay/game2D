#pragma once

#include <stdio.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <src/GLObject.hpp>

#include <src/BaseObject.cpp>
#include <src/ImageTexture.cpp>
#include <src/Shader.cpp>
#include <src/View.cpp>

GLObject::GLObject(glm::vec2 initPosition, std::string textureSource):
    BaseObject(initPosition, "src/vertexShader.glsl", "src/fragmentShader.glsl"),
    texture(textureSource)
{
    int width = this->texture.getWidth();
    int height = this->texture.getHeight();

    this->vertices = new GLfloat [18] {
        initPosition.x, initPosition.y + height, 0.f,
        initPosition.x, initPosition.y, 0.f,
        initPosition.x + width, initPosition.y, 0.f,

        initPosition.x, initPosition.y + height, 0.f,
        initPosition.x + width, initPosition.y, 0.f,
        initPosition.x + width, initPosition.y + height, 0.f
    };

    this->transformMatrix = glm::mat4(1.f);

    this->currentCoord = Helper::RectCoordinates({
        initPosition.x, initPosition.y, 
        initPosition.x + width, initPosition.y + height
    });

    this->texture.createTexture();
    this->shader.initBuffers(this->vertices, this->texturePosition, 1);
    this->shader.setUniform<glm::mat4*>("transform", &(this->transformMatrix), EnumUniformType::GLM_MAT4);
}

GLObject::~GLObject() {
    delete[] this->vertices;
}

Helper::RectCoordinates GLObject::getCurrentCoord() {
    return this->currentCoord;
}

void GLObject::draw() {
    this->shader.setContext();
    this->shader.runShader(this->texture.getID(), 0);
}