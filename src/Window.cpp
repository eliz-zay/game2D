#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <exception>

#include "Window.hpp"

GLFWwindow* Window::window = nullptr;

GLFWwindow* Window::getWindow() {
	return Window::window;
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

	Window::window = glfwCreateWindow(width, height, "My window", NULL, NULL);
	if (Window::window == NULL ) {
		throw std::runtime_error("Window: Failed to open GLFW window");
	}

	glfwMakeContextCurrent(Window::window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Window: Failed to initialize GLEW");
	}

	glfwSetInputMode(Window::window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.5f, 0.2f, 0.2f, 0.0f);
}

void Window::clearWindow() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::refreshWindow() {
    glfwSwapBuffers(Window::window);
	glfwPollEvents();
}

bool Window::shouldBeOpened() {
    return glfwGetKey(Window::window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
}

void Window::closeWindow() {
	glfwTerminate();
}