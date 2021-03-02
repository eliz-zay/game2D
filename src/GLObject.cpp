#pragma once

#include <stdio.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <src/GLObject.hpp>

#include <src/Helper.cpp>
#include <src/Shader.cpp>
#include <src/View.cpp>

GLObject::GLObject(glm::vec2 initPosition, std::string textureSource, std::string vertexShader, std::string fragShader): 
    shader(vertexShader, fragShader)
{
    Helper::TextureData textureData = Helper::parseTexture(textureSource);
    GLfloat* vertices = new GLfloat [18] {
        initPosition.x, initPosition.y, 0.f,
        initPosition.x + textureData.width, initPosition.y, 0.f,
        initPosition.x + textureData.width, initPosition.y + textureData.height, 0.f,

        initPosition.x + textureData.width, initPosition.y + textureData.height, 0.f,
        initPosition.x, initPosition.y + textureData.height, 0.f,
        initPosition.x, initPosition.y, 0.f
    };

    this->texturePosition = new GLfloat [12] {
        0.f, 0.f,
        1.f, 0.f,
		1.f, 1.f,

        1.f, 1.f,
		0.f, 1.f,
        0.f, 0.f
    };

    this->transformMatrix = glm::mat4(1.f);

    this->currentCoord = Helper::RectCoordinates({
        initPosition.x, initPosition.y, 
        initPosition.x + textureData.width, initPosition.y + textureData.height
    });

    this->shader.initBuffers(vertices, this->texturePosition, textureData);
    this->shader.setUniform<glm::mat4*>("projection", View::getProjection(), EnumUniformType::GLM_MAT4);
    this->shader.setUniform<glm::mat4*>("transform", &(this->transformMatrix), EnumUniformType::GLM_MAT4);

    stbi_image_free(textureData.data);
    delete[] vertices;
}

GLObject::~GLObject() {
    delete[] this->texturePosition;
}

Helper::RectCoordinates GLObject::getCurrentCoord() {
    return this->currentCoord;
}

void GLObject::draw() {
    this->shader.runShader();
}