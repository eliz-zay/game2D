#ifndef HELPER
#define HELPER

namespace Helper {
    struct RectCoordinates {
        GLfloat x0, y0, x1, y1;
    };

    struct TextureData {
        int width, height, channels;
        unsigned char* data;
    };
    
    TextureData parseTexture(std::string source);
}

#endif