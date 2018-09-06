#include <renderer.hpp>
#include <window.hpp>

#include "util.hpp"
//#include "mingw-std-threads/mingw.thread.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <string>


int main(int argc, char *argv[])
{

  // New Scene:
  Scene newScene{};
  load_sdf("scene1.sdf",newScene);

  unsigned const image_width = newScene.width_;
  unsigned const image_height = newScene.height_;

  Renderer renderer{image_width, image_height, newScene.name_};

  renderer.render(newScene);

  //create separate thread to see updates of pixels while rendering
  // renderer.render();

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
