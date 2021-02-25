#pragma once

#include <stb_image.h>

#include "Helper.hpp"

Helper::TextureData Helper::parseTexture(std::string source) {
    Helper::TextureData textureData;
    textureData.data = stbi_load(source.c_str(), &textureData.width, &textureData.height, &textureData.channels, 0);
	if (!textureData.data) {
		std::cout << "Failed to load texture" << std::endl;
		// TODO: throw exception
	}

    return textureData;
}