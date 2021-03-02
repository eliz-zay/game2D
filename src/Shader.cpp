#pragma once

#define STB_IMAGE_IMPLEMENTATION

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
    glDeleteBuffers(1, &this->ebo);
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

void Shader::initBuffers(GLfloat* vertices, GLfloat* texturePosition, Helper::TextureData textureData) {
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vboPosition);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glGenBuffers(1, &this->vboTexture);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, texturePosition, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

	GLenum format = textureData.channels == 3 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, textureData.width, textureData.height, 0, format, GL_UNSIGNED_BYTE, textureData.data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Shader::initBuffers2(GLfloat* vertices, GLfloat* texturePosition, int size) {
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vboPosition);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboPosition);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18 * size, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glGenBuffers(1, &this->vboTexture);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboTexture);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12 * size, NULL, GL_STATIC_DRAW);
    for (int i = 0; i < size; i++) {
        glBufferSubData(GL_ARRAY_BUFFER, i * 12 * sizeof(GLfloat), sizeof(GLfloat) * 12, texturePosition);
    }

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
}

void Shader::runShader() {
	glUseProgram(this->programID);

	for (const auto& kv: this->uniform) {
		std::tuple<GLuint, EnumUniformType, std::any> value = kv.second;
		EnumUniformType type = std::get<1>(value);

		if (type == EnumUniformType::GLM_MAT4) {
			glm::mat4* uniform = std::any_cast<glm::mat4*>(std::get<2>(value));
			glUniformMatrix4fv(std::get<0>(value), 1, GL_FALSE, &((*uniform)[0][0]));
		} else if (type == EnumUniformType::GLM_VEC4) {
			glm::vec4* uniform = std::any_cast<glm::vec4*>(std::get<2>(value));
			glUniform4fv(std::get<0>(value), 1, &((*uniform)[0]));
		}
	}

	glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Shader::runShader2(std::string text) {
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

    for (int i = 0; i < text.size(); i++) {
        Character* ch = TextLib::getChar(text[i]);
        glBindTexture(GL_TEXTURE_2D, ch->textureId);
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }
}