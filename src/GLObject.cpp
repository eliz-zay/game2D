#pragma once

#include <stdio.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <src/GLObject.hpp>

#include <src/BaseObject.cpp>
#include <src/Helper.cpp>
#include <src/Shader.cpp>
#include <src/View.cpp>

GLObject::GLObject(glm::vec2 initPosition, std::string textureSource):
    BaseObject(initPosition, "src/vertexShader.glsl", "src/fragmentShader.glsl")
{
    Helper::TextureData textureData = Helper::parseTexture(textureSource);

    // TODO: move to another module
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

	GLenum format = textureData.channels == 3 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, textureData.width, textureData.height, 0, format, GL_UNSIGNED_BYTE, textureData.data);
	glGenerateMipmap(GL_TEXTURE_2D);

    this->vertices = new GLfloat [18] {
        initPosition.x, initPosition.y + textureData.height, 0.f,
        initPosition.x, initPosition.y, 0.f,
        initPosition.x + textureData.width, initPosition.y, 0.f,

        initPosition.x, initPosition.y + textureData.height, 0.f,
        initPosition.x + textureData.width, initPosition.y, 0.f,
        initPosition.x + textureData.width, initPosition.y + textureData.height, 0.f
    };

    this->transformMatrix = glm::mat4(1.f);

    this->currentCoord = Helper::RectCoordinates({
        initPosition.x, initPosition.y, 
        initPosition.x + textureData.width, initPosition.y + textureData.height
    });

    this->shader.initBuffers(this->vertices, this->texturePosition, 1);
    this->shader.setUniform<glm::mat4*>("transform", &(this->transformMatrix), EnumUniformType::GLM_MAT4);

    stbi_image_free(textureData.data);
}

GLObject::~GLObject() {
    delete[] this->vertices;
}

Helper::RectCoordinates GLObject::getCurrentCoord() {
    return this->currentCoord;
}

void GLObject::draw() {
    this->shader.setContext();
    this->shader.runShader(this->texture, 0);
}