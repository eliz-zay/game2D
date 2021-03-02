#ifndef VIEW
#define VIEW

#include <glm/glm.hpp>

class View {
    private:
        static int width, height;
        static glm::mat4 projection;
        
        View();

    public:
        static void setResolution(int width, int height);
        static glm::mat4* getProjection();
};

#endif