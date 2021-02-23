#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "Window.hpp"

Window::~Window() {
	glfwTerminate();
}

void Window::initWindow(int width, int height) {
    if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(0); //TODO: throw exception
	}

    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "My window", NULL, NULL);
	if (window == NULL ){
		fprintf(stderr, "Failed to open GLFW window\n" );
		glfwTerminate();
		exit(0);  //TODO: throw exception
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		exit(0); //TODO: throw exception
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

void Window::clearWindow() {
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::refreshWindow() {
    glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::shouldBeOpened() {
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
}