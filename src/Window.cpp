#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <exception>

#include "Window.hpp"

Window::~Window() {
	glfwTerminate();
}

GLFWwindow* Window::getWindow() {
	return this->window;
}

void Window::initWindow(int width, int height) {
    if (!glfwInit()) {
		throw std::runtime_error("Window: Failed to initialize GLFW");
	}

    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "My window", NULL, NULL);
	if (window == NULL ) {
		throw std::runtime_error("Window: Failed to open GLFW window");
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Window: Failed to initialize GLEW");
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void Window::clearWindow() {
	glClearColor(0.5f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::refreshWindow() {
    glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::shouldBeOpened() {
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
}