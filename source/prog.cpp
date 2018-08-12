#include "Scene.hpp"
#include "Shape.hpp"
#include "Box.hpp"
#include "material.hpp"

#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char *argv[])
{

    Scene scene2;
    load_sdf("scene2.sdf", scene2);

    unsigned const image_width = 800;
    unsigned const image_height = 600;
    std::string const filename = "./scene2.ppm";

    Renderer renderer{image_width, image_height, filename};

    Window window{{image_width, image_height}};

    while (!window.should_close())
    {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            window.close();
        }
        window.show(renderer.color_buffer());
    }

    return 0;
}
