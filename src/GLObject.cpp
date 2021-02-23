#pragma once

#include <stdio.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "GLObject.hpp"

GLObject::GLObject(int width, int height, glm::vec2 initPosition): shader("src/vertexShader.glsl", "src/fragmentShader.glsl") {
    this->vertices = new GLfloat [12] {
        initPosition.x, initPosition.y, 0.f,
        initPosition.x + width, initPosition.y, 0.f,
        initPosition.x + width, initPosition.y + height, 0.f,
        initPosition.x, initPosition.y + height, 0.f
    };

    this->vertexDistribution = new GLuint [6] {
        0, 1, 2,
        2, 3, 0
    };

    this->texturePosition = new GLfloat [8] {
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f
	};
}

GLObject::~GLObject() {
    delete[] this->vertices;
    delete[] this->texturePosition;
    delete[] this->vertexDistribution;
}

void GLObject::initObject(glm::mat4 projection, std::string textureSource) {
    this->shader.setUniform("projection", projection);
    this->shader.initBuffers(this->vertices, this->texturePosition, textureSource, this->vertexDistribution);
}

void GLObject::draw() {
    this->shader.runShader();
}