#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "glm/ext.hpp"
#include <glm/gtx/string_cast.hpp>

#include <src/shader/shader.hpp>
#include "Shader.hpp"

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

void Shader::setUniform(const char* name, glm::mat4* value) {
	this->uniform.emplace(
		name,
		std::make_tuple(glGetUniformLocation(this->programID, name), value)
	);
}

void Shader::initBuffers(GLfloat* vertices, GLfloat* texturePosition, Helper::TextureData textureData, GLuint* vertexDistribution) {
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vboPosition);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glGenBuffers(1, &this->vboTexture);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, texturePosition, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, vertexDistribution, GL_STATIC_DRAW); 

	glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

	GLenum format = textureData.channels == 3 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, textureData.width, textureData.height, 0, format, GL_UNSIGNED_BYTE, textureData.data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Shader::runShader() {
	glUseProgram(this->programID);

	for (const auto& kv: this->uniform) {
		std::tuple<GLuint, glm::mat4*> value = kv.second;
		glUniformMatrix4fv(std::get<0>(value), 1, GL_FALSE, &((*(std::get<1>(value)))[0][0]));
	}

	glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}