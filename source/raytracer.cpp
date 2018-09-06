#include <renderer.hpp>
#include <window.hpp>
#include "scene.hpp"
//#include "mingw-std-threads/mingw.thread.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <string>

int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";

  Renderer renderer{image_width, image_height, filename};

  //create separate thread to see updates of pixels while rendering
  // renderer.render();

  // New Scene:
  Scene newScene;
  load_sdf("scene1.sdf", newScene);
  renderer.render(newScene);


  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
