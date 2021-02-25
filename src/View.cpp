#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "View.hpp"

View::View(int width, int heigth) {
    this->projection = 
        glm::rotate(glm::mat4(1.f), glm::radians(180.f), glm::vec3(1.f, 0.f, 0.f)) * 
        glm::translate(glm::mat4(), glm::vec3(-1.f, -1.f, 0.f)) *
        glm::scale(glm::vec3(2./width, 2./heigth, 1.f));
}

glm::mat4* View::getProjection() {
    return &(this->projection);
}