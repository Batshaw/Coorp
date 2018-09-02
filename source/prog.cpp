#include "Scene.hpp"
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

    /* Scene scene1{};
    load_sdf("scene1.sdf", scene1);
 */
    Scene scene2{};
    load_sdf("scene2.sdf", scene2);

    Renderer renderer{scene2._width, scene2._height, scene2._name};
    /* std::thread render_thread([&renderer]() {
        renderer.render();
    }); */

    for (std::shared_ptr<Shape> shape : scene2.shape_vector)
    {
        cout << *shape << std::endl;
    }

    renderer.render(scene2);
    Window window{{scene2._width, scene2._height}};

    while (!window.should_close())
    {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            window.close();
        }
        window.show(renderer.color_buffer());
    }
    /*     render_thread.join();
 */
    return 0;
}
