#pragma once

#include <stdio.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "GLObject.hpp"

#include "Helper.cpp"

GLObject::GLObject(glm::vec2 initPosition, std::string textureSource): shader("src/vertexShader.glsl", "src/fragmentShader.glsl") {
    Helper::TextureData textureData = Helper::parseTexture(textureSource);

    GLfloat* vertices = new GLfloat [12] {
        initPosition.x, initPosition.y, 0.f,
        initPosition.x + textureData.width, initPosition.y, 0.f,
        initPosition.x + textureData.width, initPosition.y + textureData.height, 0.f,
        initPosition.x, initPosition.y + textureData.height, 0.f
    };

    this->vertexDistribution = new GLuint [6] {
        0, 1, 2,
        2, 3, 0
    };

    this->texturePosition = new GLfloat [8] {
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f
	};

    this->transformMatrix = glm::mat4(1.f);

    this->currentCoord = Helper::RectCoordinates({
        initPosition.x, initPosition.y, 
        initPosition.x + textureData.width, initPosition.y + textureData.height
    });

    this->shader.initBuffers(vertices, this->texturePosition, textureData, this->vertexDistribution);

    stbi_image_free(textureData.data);
    delete[] vertices;
}

GLObject::~GLObject() {
    delete[] this->texturePosition;
    delete[] this->vertexDistribution;
}

void GLObject::initObject(glm::mat4* projection) {
    this->shader.setUniform("projection", projection);
    this->shader.setUniform("transform", &(this->transformMatrix));
}

void GLObject::move(GLFWwindow* window) {
    const GLfloat EPS = 0.0001;
    float speed = 3.0f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && (this->currentCoord.y0 > 0)) {
        this->transformMatrix = glm::translate(this->transformMatrix, glm::vec3(0.f, -speed * 1.f, 0.f));
        this->currentCoord.y0 -= speed * 1.f;
        this->currentCoord.y1 -= speed * 1.f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && (this->currentCoord.y1 < WINDOW_HEIGHT)) {
        this->transformMatrix = glm::translate(this->transformMatrix, glm::vec3(0.f, speed * 1.f, 0.f));
        this->currentCoord.y0 += speed * 1.f;
        this->currentCoord.y1 += speed * 1.f;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && (this->currentCoord.x1 < WINDOW_WIDTH)) {
        this->transformMatrix = glm::translate(this->transformMatrix, glm::vec3(speed * 1.f, 0.f, 0.f));
        this->currentCoord.x0 += speed * 1.f;
        this->currentCoord.x1 += speed * 1.f;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && (this->currentCoord.x0 > 0)) {
        this->transformMatrix = glm::translate(this->transformMatrix, glm::vec3(-speed * 1.f, 0.f, 0.f));
        this->currentCoord.x0 -= speed * 1.f;
        this->currentCoord.x1 -= speed * 1.f;
    }
}

void GLObject::draw() {
    this->shader.runShader();
}