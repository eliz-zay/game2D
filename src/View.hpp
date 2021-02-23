#ifndef VIEW
#define VIEW

#include <glm/glm.hpp>

class View {
    glm::mat4 projection;
public:
    View(int width, int heigth);

    glm::mat4 getProjection();
};

#endif