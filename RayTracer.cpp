#include <iostream>
#include <glm/glm.hpp>
#include "header/Vertex.h"
#include "header/Camera.h"

int main()
{
    Vertex eye1 = Vertex{ -2, 0, 0 };
    Vertex eye2 = Vertex{ -1, 0,0 };
    Camera cam = Camera(eye1, eye2);

    Scene s;

    cam.render(s);

    glm::mat4 proj;

    std::cout << "Yes" << "\n" << "Japp";
}
