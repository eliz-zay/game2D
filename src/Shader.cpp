#pragma once

#include <iostream>

#include "glm/ext.hpp"
#include <glm/gtx/string_cast.hpp>

#include <src/shader/shader.hpp>

#include <src/Shader.hpp>

#include <src/TextLib.cpp>

Shader::Shader(std::string vertexShader, std::string fragmentShader) {
    this->programID = LoadShaders(vertexShader.c_str(), fragmentShader.c_str());
}

Shader::~Shader() {
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &this->vboPosition);
	glDeleteBuffers(1, &this->vboTexture);
    glDeleteVertexArrays(1, &this->vao);
	glDeleteProgram(this->programID);
}

template <typename T>
void Shader::setUniform(const char* name, T value, EnumUniformType valueType) {
	this->uniform.emplace(
		name,
		std::make_tuple(glGetUniformLocation(this->programID, name), valueType, value)
	);
}

void Shader::initBuffers(GLfloat* vertices, GLfloat* texturePosition, int length) {
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vboPosition);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboPosition);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18 * length, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glGenBuffers(1, &this->vboTexture);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboTexture);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12 * length, NULL, GL_STATIC_DRAW);
    for (int i = 0; i < length; i++) {
        glBufferSubData(GL_ARRAY_BUFFER, i * 12 * sizeof(GLfloat), sizeof(GLfloat) * 12, texturePosition);
    }

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void Shader::setContext() {
	glUseProgram(this->programID);
	glBindVertexArray(this->vao);

	for (const auto& kv: this->uniform) {
		std::tuple<GLuint, EnumUniformType, std::any> value = kv.second;
		EnumUniformType type = std::get<1>(value);

		if (type == EnumUniformType::GLM_MAT4) {
			glm::mat4* uniformValue = std::any_cast<glm::mat4*>(std::get<2>(value));
			glUniformMatrix4fv(std::get<0>(value), 1, GL_FALSE, &((*uniformValue)[0][0]));
		} else if (type == EnumUniformType::GLM_VEC4) {
			glm::vec4* uniformValue = std::any_cast<glm::vec4*>(std::get<2>(value));
			glUniform4fv(std::get<0>(value), 1, &((*uniformValue)[0]));
		}
	}
}

void Shader::runShader(GLuint texture, int offset) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, offset, 6);
}