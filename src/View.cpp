#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "View.hpp"

glm::mat4 View::projection = glm::mat4(1.f);

void View::setResolution(int width, int heigth) {
    View::projection = 
        glm::rotate(glm::mat4(1.f), glm::radians(180.f), glm::vec3(1.f, 0.f, 0.f)) * 
        glm::translate(glm::mat4(), glm::vec3(-1.f, -1.f, 0.f)) *
        glm::scale(glm::vec3(2./(1.5 * width), 2./(heigth), 1.f));
}

glm::mat4* View::getProjection() {
    return &(View::projection);
}