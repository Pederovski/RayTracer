#include <iostream>
#include <glm/glm.hpp>
#include "header/Vertex.h"
#include "header/Camera.h"
#include <chrono>

int main()
{

    auto start = std::chrono::steady_clock::now();

    Vertex eye1 = Vertex{ -2, 0, 0 };
    Vertex eye2 = Vertex{ -1, 0,0 };
    Camera cam = Camera(eye1, eye2, false);

    Scene s;

    cam.render(s);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    //glm::mat4 proj;
    //std::cout << "Yes" << "\n" << "Japp";
}
