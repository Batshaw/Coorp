
#include <renderer.hpp>
#include <window.hpp>
//#include "mingw-std-threads/mingw.thread.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <string>
#include "scene.hpp"

int main(int argc, char *argv[])
{

  // New Scene:
  Scene newScene{};
  load_sdf("scene1.sdf", newScene);

  unsigned const image_width{newScene.width_};
  unsigned const image_height{newScene.height_};

  Renderer renderer{image_width, image_height, newScene.name_};

  renderer.render(newScene);

  for (std::shared_ptr<Shape> shape : newScene.shape_vector_)
  {
    cout << *shape;
  }

  //create separate thread to see updates of pixels while rendering

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
