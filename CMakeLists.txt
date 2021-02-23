cmake_minimum_required (VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)

project (game)

find_package(OpenGL REQUIRED)

add_subdirectory (external)

include_directories(
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/glm-0.9.7.1/
	external/stb_image/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
)

file(GLOB src
	"src/main.cpp"
    "src/shader/*.hpp"
    "src/shader/*.cpp"
    "src/*.glsl"
)

add_executable(game
	${src}
)
target_link_libraries(game
	${ALL_LIBS}
)


