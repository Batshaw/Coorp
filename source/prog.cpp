#include "Scene.hpp"
#include "Shape.hpp"
#include "Box.hpp"
#include "material.hpp"

#include <renderer.hpp>
#include <window.hpp>
#include "sdfloader.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

int main(int argc, char *argv[])
{

    Scene scene2;
    load_sdf("scene2.sdf", scene2);

    Renderer renderer(scene2);
    std::thread render_thread([&renderer]() {
        renderer.render();
    });

    Window window{{scene2._width, scene2._height}};

    while (!window.should_close())
    {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            window.close();
        }
        window.show(renderer.color_buffer());
    }
    render_thread.join();
    return 0;
}
